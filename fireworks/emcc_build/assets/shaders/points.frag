#version 300 es
precision highp float;

in vec4 PassColor;

out vec4 color;

void main() {
     vec2 coord = gl_PointCoord - vec2(0.5);
     float len = length(coord);
     //float a = len < 0.5 ? 1.0 : 0.0; 
     float a = len < 0.5 ? (len < 0.2 ? 1.0 : mix(1.0, 0.0, len * 2.0)) : 0.0;
     color = vec4(PassColor.xyz, PassColor.w * a);
}
