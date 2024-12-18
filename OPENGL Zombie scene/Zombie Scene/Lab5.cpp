#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

int main()
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Lab5", NULL, NULL);

	if (window == NULL)
	{
		cout << "GLFW Window did not instantiate\n";
		glfwTerminate();
		return -1;
	}

	//Binds
	glfwMakeContextCurrent(window);

	return 0;

}