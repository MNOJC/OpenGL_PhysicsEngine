
#version 410 core

in vec3 ourColor;
out vec4 FragColor;

uniform vec4 u_Color;

void main() 
{
    FragColor = u_Color;
}