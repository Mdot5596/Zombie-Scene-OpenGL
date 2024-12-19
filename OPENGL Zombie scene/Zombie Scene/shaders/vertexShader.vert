#version 460
//Triangle position with values retrieved from main.cpp
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aColor;
out vec3 ourColor;

//Triangle vertices sent through gl_Position to next stage
void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
    ourColor=aColor;
}