#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Main.h"
using namespace std;

int main()
{
	//Initilisation of GLFW
	glfwInit();

	//Initilisation of GLFWwindow object
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Lab5", NULL, NULL);

	//Checks if window has been successfully instantiated
	if (window == NULL)
	{
		cout << "GLFW Window did not instantiate\n";
		glfwTerminate();
		return -1;
	}

	//Binds OpenGL to window
	glfwMakeContextCurrent(window);
	glewInit();
	glViewport(0, 0, 1280, 720);

	//Sets the framebuffer_size_callback() function as the callback for the window resizing event
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Render loop
	while (glfwWindowShouldClose(window) == false)
	{
		//Input
		ProcessUserInput(window); //Takes user input

		//Rendering
		glClearColor(0.25f, 0.0f, 1.0f, 1.0f); //Colour to display on cleared window
		glClear(GL_COLOR_BUFFER_BIT); //Clears the colour buffer

		//Refreshing
		glfwSwapBuffers(window); //Swaps the colour buffer
		glfwPollEvents(); //Queries all GLFW events
	}

	//Safely terminates GLFW
	glfwTerminate();

	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//Resizes window based on contemporary width & height values
	glViewport(0, 0, width, height);
}

void ProcessUserInput(GLFWwindow* WindowIn)
{
	//Closes window on 'exit' key press
	if (glfwGetKey(WindowIn, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(WindowIn, true);
	}
	if (glfwGetKey(WindowIn, GLFW_KEY_W) == GLFW_PRESS)
	{
		cout << "W was pressed" << endl;
	}
	if (glfwGetKey(WindowIn, GLFW_KEY_S) == GLFW_PRESS)
	{
		cout << "S was pressed" << endl;
	}
	if (glfwGetKey(WindowIn, GLFW_KEY_A) == GLFW_PRESS)
	{
		cout << "A was pressed" << endl;
	}
	if (glfwGetKey(WindowIn, GLFW_KEY_D) == GLFW_PRESS)
	{
		cout << "D was pressed" << endl;
	}
}