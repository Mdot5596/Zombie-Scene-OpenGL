#pragma once

//framebuffer_size_callback() needs GlFW, so include moved here
#include <GLFW/glfw3.h>


//Called on window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//Processes user input 
void ProcessUserInput(GLFWwindow* WindowIn);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void SetMatrices(Shader& ShaderProgramIn);