#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Main.h"
#include "LoadShaders.h"


using namespace std;

//VAO vertex attribute positions in correspondence to vertex attribute type
enum VAO_IDs { Triangles, Indices, Colours, Textures, NumVAOs = 2 };

//VAOs
GLuint VAOs[NumVAOs];

//Buffer types
enum Buffer_IDs { ArrayBuffer, NumBuffers = 4 };

//Buffer objects
GLuint Buffers[NumBuffers];
GLuint program;

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

	//Load shaders
	ShaderInfo shaders[] =
	{
		{ GL_VERTEX_SHADER, "shaders/vertexShader.vert" },
		{ GL_FRAGMENT_SHADER, "shaders/fragmentShader.frag" },
		{ GL_NONE, NULL }
	};

	program = LoadShaders(shaders);
	glUseProgram(program);

	glViewport(0, 0, 1280, 720);

	//Sets the framebuffer_size_callback() function as the callback for the window resizing event
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	float vertices[] = 
	{
	-0.5f, -0.5f, 0.0f, //pos 0 | x, y, z
	0.5f, -0.5f, 0.0f, //pos 1
	0.0f, 0.5f, 0.0f //pos 2
	};


	//Sets index of VAO
	glGenVertexArrays(NumVAOs, VAOs);
	//Binds VAO to a buffer
	glBindVertexArray(VAOs[0]);
	//Sets indexes of all required buffer objects
	glGenBuffers(NumBuffers, Buffers);

	//Binds VAO to array buffer
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[Triangles]);
	//Allocates buffer memory for the vertices
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Allocates vertex attribute memory for vertex shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//Index of vertex attribute for vertex shader
	glEnableVertexAttribArray(0);

	//Unbinding
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//Render loop
	while (glfwWindowShouldClose(window) == false)
	{
		//Input
		ProcessUserInput(window); //Takes user input

		//Rendering
		glClearColor(0.25f, 0.0f, 1.0f, 1.0f); //Colour to display on cleared window
		glClear(GL_COLOR_BUFFER_BIT); //Clears the colour buffer

		glBindVertexArray(VAOs[0]); //Bind buffer object to render
		glDrawArrays(GL_TRIANGLES, 0, 3); //Render buffer object

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