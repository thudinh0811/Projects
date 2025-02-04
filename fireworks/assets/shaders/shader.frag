#version 300 es
precision highp float;

out vec4 color;

uniform vec2 iSize;
uniform float iTime;

vec4 vertical[2] = vec4[](
     vec4(0.15, 0.07, 0.05, 1.0),
     vec4(0.03, 0.03, 0.11, 1.0));
vec4 horizontal[2] = vec4[](
     vec4(0.23, 0.22, 0.13, 1.0),
     vec4(0.06, 0.12, 0.14, 1.0));

void main() {
     vec2 c = gl_FragCoord.xy / iSize;
     vec4 h = mix(horizontal[0], horizontal[1], c.x);
     vec4 v = mix(vertical[0], vertical[1], c.y);

     color = v;
 }