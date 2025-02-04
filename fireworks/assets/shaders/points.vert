#version 300 es

uniform mat4 iAspect;
uniform float iScale;

layout (location = 0) in vec3 Position;
layout (location = 1) in vec4 Color;

out vec4 PassColor;

void main() {
     PassColor = Color;
     gl_PointSize = 20.0 * iScale;
     gl_Position = iAspect * vec4(Position, 1.0);
}