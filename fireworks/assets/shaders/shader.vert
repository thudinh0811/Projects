#version 300 es

vec2 positions[6] = vec2[](
     vec2(1.0, -1.0),
     vec2(-1.0, -1.0),
     vec2(1.0, 1.0),
     vec2(1.0, 1.0),
     vec2(-1.0, -1.0),
     vec2(-1.0, 1.0)
);

mat4 idn = mat4(1.0, 0.0, 0.0, 0.0,
     	      	0.0, 1.0, 0.0, 0.0,
     	      	0.0, 0.0, 1.0, 0.0,
     	      	0.0, 0.0, 0.0, 1.0);

uniform vec2 iDimension;
uniform vec2 iCursor;
uniform mat4 iProjection;

void main() {
     gl_Position = idn * vec4(positions[gl_VertexID], -1.0, 1.0);
}
