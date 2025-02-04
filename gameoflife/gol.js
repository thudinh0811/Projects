"use strict"

/** @class */
var Module = {

	WIDTH: 10,
	HEIGHT: 10,
	
	time: {
		/** @type number */
		start: 0,
		/** @type number */
		current: 0,
		/** @type number */
		delta: 0,
	},

	/** @type Int32Array[] */
	data: [ ],
	data_index: 0,

	/** @type string[] */
	sha: [ ],
	sha_index: 0,
	sha_set: new Set(),
	reset_cmd: false,

	/** @type HTMLCanvasElement */
	canvas: undefined,

	/** @type WebGL2RenderingContext */
	gl: undefined,

	gl_objects: {
		/** @type WebGLBuffer */
		data_buffer: undefined,
		/** @type WebGLVertexArrayObject */
		data_vao: undefined,

		/** @type WebGLProgram */
		program_cells: undefined,
		/** @type WebGLProgram */
		program_background: undefined,

		uniform_locations: {
			iAlive: -1,
			iDimension: -1,
			iSize: -1,
			iTime: -1,
			iIndex: -1,
		},
	},
};

function main() {
	Module['canvas'] = document.getElementById('canvas');
	Module['gl'] = Module.canvas.getContext('webgl2');

	if (!Module.gl)
		alert('Unable to run webgl in the browser');
	else
		requestAnimationFrame(game_init);
}

function game_init(timestamp) {
	var ctx = Module.gl;

	Module.time.start = timestamp;
	Module.time.current = timestamp;
	Module.time.delta = 0.1;

	Module.canvas.width = window.innerWidth;
	Module.canvas.height = window.innerHeight;

	Module.WIDTH = Math.floor(Module.canvas.width / 10);
	Module.HEIGHT = Math.floor(Module.canvas.height / 10);

	//Module.WIDTH = Math.min(Module.WIDTH, 128);
	//Module.HEIGHT = Math.min(Module.HEIGHT, 128);

	Module.data.push(new Int32Array(Module.WIDTH * Module.HEIGHT));
	Module.data.push(new Int32Array(Module.WIDTH * Module.HEIGHT));

	window.addEventListener("keydown", (event) => { if (event.code == "KeyR") {Module.reset_cmd = true}});

	ctx.viewport(
		0,
		0,
		Module.canvas.width,
		Module.canvas.height);

	ctx.clearColor(0.1, 0.1, 0.1, 1.0);
	ctx.clear(ctx.COLOR_BUFFER_BIT);

	create_shaders();

	create_buffers();

	game_reset();

	requestAnimationFrame(game_loop);
}

function game_reset() {
	var currentBuffer = Module.data[0];
	for (var i = 0; i < currentBuffer.length; i++) {
		currentBuffer[i] = Math.round(Math.random());
	}
	Module.data_index = 0;

	Module.sha = [];
	Module.sha_index = 0;
	for (var i = 0; i < 30; i++) {
		Module.sha.push(i.toString(16));
	}

	Module.reset_cmd = false;
}

function game_loop(timestamp) {
	// Update time records.
	var time = Module.time;
	time.delta = timestamp - time.current;
	time.current = timestamp;

	var ctx = Module.gl;
	ctx.useProgram(Module.gl_objects.program_cells);
	ctx.clear(ctx.COLOR_BUFFER_BIT);

	var locs = Module.gl_objects.uniform_locations;
	ctx.uniform1f(locs.iTime, time.current);
	ctx.uniform2f(locs.iDimension, Module.WIDTH, Module.HEIGHT);
	ctx.uniform2f(locs.iSize, Module.canvas.width, Module.canvas.height);

	ctx.bindBuffer(ctx.ARRAY_BUFFER, Module.gl_objects.data_buffer);
	ctx.bufferSubData(ctx.ARRAY_BUFFER, 0, Module.data[Module.data_index]);

	ctx.enableVertexAttribArray(0);
	ctx.vertexAttribIPointer(0, 1, ctx.INT, Module.data[0].BYTES_PER_ELEMENT, 0);
	ctx.vertexAttribDivisor(0, 1);

	ctx.drawArraysInstanced(ctx.TRIANGLES, 0, 6, Module.data[0].length);

	ctx.disableVertexAttribArray(0)

	update_data_buffers();

	Module.sha_set.clear();
	Module.sha.forEach(s => Module.sha_set.add(s));
	if (Module.reset_cmd) {
		game_reset();
	}

	setTimeout(() => requestAnimationFrame(game_loop), 100);
}

function create_shaders() {
	var ctx = Module.gl;
	var targets = Module.gl_objects;

	targets.program_cells = compile_shader_program(
		ctx,
		//--Vertex Shader------------------------------------------------
`#version 300 es

vec2 positions[6] = vec2[](
     vec2(-1.0, -1.0),
     vec2(1.0, -1.0),
     vec2(1.0, 1.0),
     vec2(-1.0, -1.0),
     vec2(1.0, 1.0),
     vec2(-1.0, 1.0)
);

mat4 idn = mat4(1.0, 0.0, 0.0, 0.0,
     	      	0.0, 1.0, 0.0, 0.0,
     	      	0.0, 0.0, 1.0, 0.0,
     	      	0.0, 0.0, 0.0, 1.0);


uniform vec2 iDimension;

layout (location = 0) in int vAlive;

out float alive;

mat4 grid_and_place(vec2 dim, int index) {
		 // scale the boxes to all fit.
     mat4 m = idn;
     m[0][0] = 1.0 / dim.x;
     m[1][1] = 1.0 / dim.y;
     m[2][2] = 1.0;
     m[3][3] = 1.0;

		 // Move the box to bottom left.
     vec2 move = vec2(m[0][0], m[1][1]) * 2.0;
     mat4 m2  = idn;
     m2[3][0] = (int(dim.x) % 2 == 0) ? (move.x * 0.5) : 0.0;
     m2[3][0] -= move.x * float(int(dim.x) / 2);
     m2[3][1] = (int(dim.y) % 2 == 0) ? (move.y * 0.5) : 0.0;
     m2[3][1] -= move.y * float(int(dim.y) / 2);
     m2[3][2] = 0.0;
     m2[3][3] = 1.0;

		 // Move to proper location.
     mat4 m3 = idn;
     m3[3][0] = move.x * float(index % int(dim.x));
     m3[3][1] = move.y * float(index / int(dim.x));

		 // Scale to 95% to expose grid lines.
     float adj = 0.95;
     mat4 m4 = idn;
     m4[0][0] = adj;
     m4[1][1] = adj;
     m4[2][2] = 1.0;
     m4[3][3] = 1.0;
     return m3 * m2 * m * m4;
}

void main() {
     mat4 m = grid_and_place(iDimension, gl_InstanceID);
		 alive = float(vAlive);
     gl_Position = m * vec4(positions[gl_VertexID], 0.0, 1.0);
}
`,
		//--------------------------------------------------------------
		//----Fragment Shader-------------------------------------------
`#version 300 es
precision highp float;

in float alive;
out vec4 color;

uniform vec2 iSize;
uniform float iTime;

vec4 vertical[2] = vec4[](vec4(0.2, 0.0, 0.2, 1.0), vec4(0.3, 0.5, 0.2, 1.0));
vec4 horizontal[2] = vec4[](vec4(01, 0.4, 0.1, 1.0), vec4(0.5, 0.1, 0.4, 1.0));

void main() {
     vec2 c = gl_FragCoord.xy / iSize;
     vec4 h = mix(horizontal[0], horizontal[1], c.x);
     vec4 v = mix(vertical[0], vertical[1], c.y);
     color = h * v;

     if (alive > 0.5) {
     	color.x = 1.0;
     }
}
`);
		//--------------------------------------------------------------

	if (targets.program_cells == null) {
		alert("error on starting");
	}

	var locs = Module.gl_objects.uniform_locations;
	locs.iSize = ctx.getUniformLocation(targets.program_cells, 'iSize');
	locs.iTime = ctx.getUniformLocation(targets.program_cells, 'iTime');
	locs.iAlive = ctx.getUniformLocation(targets.program_cells, 'iAlive');
	locs.iDimension = ctx.getUniformLocation(targets.program_cells, 'iDimension');
	locs.iIndex = ctx.getUniformLocation(targets.program_cells, 'iIndex');
}

/** @param {WebGL2RenderingContext} ctx
 * @param {string} vsource
 * @param {string} fsource
 * @returns {WebGLProgram}
 */
function compile_shader_program(ctx, vsource, fsource) {
	var program = ctx.createProgram();
	var vshader = ctx.createShader(ctx.VERTEX_SHADER);
	var fshader = ctx.createShader(ctx.FRAGMENT_SHADER);

	ctx.shaderSource(vshader, vsource);
	ctx.shaderSource(fshader, fsource);

	ctx.compileShader(vshader);
	ctx.compileShader(fshader);

	if (!ctx.getShaderParameter(vshader, ctx.COMPILE_STATUS)) {
		console.log("vshader cannot compile");
		console.log(ctx.getShaderInfoLog(vshader));
		return null;
	}
	if (!ctx.getShaderParameter(fshader, ctx.COMPILE_STATUS)) {
		console.log("fshader cannot compile");
		console.log(ctx.getShaderInfoLog(fshader));
		return null;
	}

	ctx.attachShader(program, vshader);
	ctx.attachShader(program, fshader);

	ctx.linkProgram(program);
	if (!ctx.getProgramParameter(program, ctx.LINK_STATUS)) {
		console.log("error linking program");
		return null;
	}

	ctx.deleteShader(vshader);
	ctx.deleteShader(fshader);
	return program;
}

function create_buffers() {
	var ctx = Module.gl;
	var targets = Module.gl_objects;

	targets.data_buffer = ctx.createBuffer();
	targets.data_vao = ctx.createVertexArray();

	ctx.bindBuffer(ctx.ARRAY_BUFFER, targets.data_buffer);
	ctx.bufferData(ctx.ARRAY_BUFFER, Module.data[0].byteLength, ctx.DYNAMIC_DRAW);
}

async function update_data_buffers() {
	var inData = Module.data[Module.data_index];
	Module.data_index = (Module.data_index + 1) % 2;
	var outData = Module.data[Module.data_index];

	for (var i = 0; i < inData.length; i++) {
		var alive = count_neighbours_alive(i, inData);
		if (inData[i] > 0) {
			if (alive >= 2 && alive <= 3)
				outData[i] = 1;
			else
				outData[i] = 0
		} else if (alive == 3){
			outData[i] = 1;
		} else {
			outData[i] = 0;
		}
	}

	var index = Module.sha_index++;
	Module.sha_index = Module.sha_index % Module.sha.length;
	Module.sha[index] = cyrb64Hash(outData);
}

/**
 * @param {number} index
 * @param {Uint32Array} data
 * @returns number
**/
function count_neighbours_alive(index, data) {
	var addr = to_address(index);
	var alive = 0;
	var neigh = [
		// above and below
		[addr[0], addr[1] + 1],
		[addr[0], addr[1] - 1],

		// right
		[addr[0] + 1, addr[1] + 1],
		[addr[0] + 1, addr[1]],
		[addr[0] + 1, addr[1] - 1],
		
		// left
		[addr[0] - 1, addr[1] - 1],
		[addr[0] - 1, addr[1]],
		[addr[0] - 1, addr[1] + 1],
	];

	for (var n in neigh) {
		if (address_inbounds(neigh[n][0], neigh[n][1])) {
			var a = data[to_index(neigh[n][0], neigh[n][1])] 
			if (a > 0) {
				alive++;
			}
		}
	}

	return alive;
}

/** @param {number} num
 * @returns {number[2]}
 */
function to_address(num) {
	return [
		num % Module.WIDTH,
		Math.floor(num / Module.WIDTH),
	];
}

/**
 * @param {number} x
 * @param {number} y 
 * @returns {number}
 */
function to_index(x, y) {
	return (y * Module.WIDTH) + x;
}

/** @param {number} x
 * @param {number} y
 * @returns {boolean}
 */
function address_inbounds(x, y) {
	return x >= 0 && x < Module.WIDTH && y >= 0 && y < Module.HEIGHT;
}

main();
