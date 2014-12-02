#version 130

in vec3 Position;
uniform float gScale;

void main()
{
    gl_Position = vec4(gScale * Position.x, gScale * Position.y, Position.z, 1.0);
}
