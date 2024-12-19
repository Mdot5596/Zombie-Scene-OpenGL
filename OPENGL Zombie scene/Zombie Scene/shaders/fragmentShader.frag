#version 460
//Colour value to send to next stage
out vec4 FragColor;
in vec3 ourColor;

void main()
{
    //RGBA values
    FragColor = vec4(ourColor, 0.0f);
}