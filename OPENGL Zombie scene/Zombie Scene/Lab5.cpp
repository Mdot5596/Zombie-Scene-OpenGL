//STD
#include <iostream>

//GLEW
#include <GL/glew.h>

//GENERAL
#include "main.h"
#include "LoadShaders.h"

//TEXTURING
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//GLM
#include "glm/glm/ext/vector_float3.hpp"
#include "glm/glm/ext/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

using namespace glm;
using namespace std;

//MVP Dec
mat4 model;
mat4 view;
mat4 projection;

//camera variables
vec3 cameraPosition = vec3(0.0f, 0.0f, 3.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

//for camera movement(mouse)
float cameraYaw = -90.0f;
float cameraPitch = 0.0f;
bool mouseFirstEntry = true;
float cameraLastXPos = 800.0f / 2.0f;
float cameraLastYPos = 600.0f / 2.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

//VAO vertex attribute positions in correspondence to vertex attribute type
enum VAO_IDs { Triangles, Indices, Colours, Textures, NumVAOs = 2 };
//VAOs
GLuint VAOs[NumVAOs];

//Buffer types
enum Buffer_IDs { ArrayBuffer, NumBuffers = 4 };
//Buffer objects
GLuint Buffers[NumBuffers];


int main()
{
    int windowWidth = 1280;
    int windowHeight = 720;

    //Initialisation of GLFW
    glfwInit();
    //Initialisation of 'GLFWwindow' object
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Lab5", NULL, NULL);

    //Checks if window has been successfully instantiated
    if (window == NULL)
    {
        cout << "GLFW Window did not instantiate\n";
        glfwTerminate();
        return -1;
    }

    //cursor auutomaticly binds to window and hides curoso
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    //Binds OpenGL to window
    glfwMakeContextCurrent(window);

    //Initialisation of GLEW
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

    //Sets the viewport size within the window to match the window size of 1280x720
    glViewport(0, 0, windowWidth, windowHeight);

    //Sets the framebuffer_size_callback() function as the callback for the window resizing event
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //mousecallback
    glfwSetCursorPosCallback(window, mouse_callback);

    float vertices[] = {
        //Positions             //Textures
        0.5f, 0.5f, 0.0f,       1.0f, 1.0f, //top right
        0.5f, -0.5f, 0.0f,      1.0f, 0.0f, //bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, //bottom left
        -0.5f, 0.5f, 0.0f,      0.0f, 1.0f  //top left
    };

    unsigned int indices[] = {
        0, 1, 3, //first triangle
        1, 2, 3 //second triangle
    };

    //Sets index of VAO
    glGenVertexArrays(NumVAOs, VAOs); //NumVAOs, VAOs
    //Binds VAO to a buffer
    glBindVertexArray(VAOs[0]); //VAOs[0]
    //Sets indexes of all required buffer objects
    glGenBuffers(NumBuffers, Buffers); //NumBuffers, Buffers
    //glGenBuffers(1, &EBO);

    //Binds vertex object to array buffer
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[Triangles]); //Buffers[Triangles]
    //Allocates buffer memory for the vertices of the 'Triangles' buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Binding & allocation for indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[Indices]); //Buffers[Indices]
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Allocation & indexing of vertex attribute memory for vertex shader
    //Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Textures
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Unbinding
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Texture index
    unsigned int texture;
    //Textures to generate
    glGenTextures(1, &texture);

    //Binding texture to type 2D texture
    glBindTexture(GL_TEXTURE_2D, texture);

    //Selects x axis (S) of texture bound to GL_TEXTURE_2D & sets to repeat beyond normalised coordinates
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //Selects y axis (T) equivalently
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Parameters that will be sent & set based on retrieved texture
    int width, height, colourChannels;
    //Retrieves texture data
    unsigned char* data = stbi_load("media/woodPlanks.jpg", &width, &height, &colourChannels, 0);

    if (data) //If retrieval successful
    {
        //Generation of texture from retrieved texture data
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        //Automatically generates all required mipmaps on bound texture
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else //If retrieval unsuccessful
    {
        cout << "Failed to load texture.\n";
        return -1;
    }

   

    //Render loop
    while (glfwWindowShouldClose(window) == false)
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //Input
        ProcessUserInput(window); //Takes user input

        //Rendering
        glClearColor(0.25f, 0.0f, 1.0f, 1.0f); //Colour to display on cleared window
        glClear(GL_COLOR_BUFFER_BIT); //Clears the colour buffer

        //transform (perspective)
        model = mat4(1.0f);
        model = scale(model, vec3(2.0f, 2.0f, 2.0f));
        model = rotate(model, (float)radians(-45.0f), vec3(1.0, 0.0, 0.0));
        model = translate(model, vec3(0.0f, 1.0f, -1.5f));
        view = lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        projection = perspective(radians(45.0f), (float)windowWidth / (float)(windowHeight), 0.1f, 100.0f);
        
        //transofrm(rotation)
        mat4 transform = mat4(1.0f);
       // transform = rotate(transform, (float)glfwGetTime(), vec3(0.0f, 0.0f, 1.0f));
        transform = scale(transform, vec3(0.5f, 0.5f, 0.5f));
        GLint transformIndex = glGetUniformLocation(program, "transformIn");
        glUniformMatrix4fv(transformIndex, 1, GL_FALSE, value_ptr(transform));
        //mvp tpye shit
        mat4 mvp = projection * view * model;
        int mvpLoc = glGetUniformLocation(program, "mvpIn");
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, value_ptr(mvp));


        //Drawing
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAOs[0]); //Bind buffer object to render; VAOs[0]
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
    const float movementSpeed = 1.0f * deltaTime;
    //Closes window on 'exit' key press
    if (glfwGetKey(WindowIn, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(WindowIn, true);
    }

    if (glfwGetKey(WindowIn, GLFW_KEY_W) == GLFW_PRESS)
    {
        cout << "W was pressed" << endl;
        cameraPosition += movementSpeed * cameraFront;
    }
    if (glfwGetKey(WindowIn, GLFW_KEY_S) == GLFW_PRESS)
    {
        cout << "S was pressed" << endl;
        cameraPosition -= movementSpeed * cameraFront;
    }
    if (glfwGetKey(WindowIn, GLFW_KEY_A) == GLFW_PRESS)
    {
        cout << "A was pressed" << endl;
        cameraPosition -= normalize(cross(cameraFront, cameraUp)) * movementSpeed;
    }
    if (glfwGetKey(WindowIn, GLFW_KEY_D) == GLFW_PRESS)
    {
        cout << "D was pressed" << endl;
        cameraPosition += normalize(cross(cameraFront, cameraUp)) * movementSpeed;
    }
}

//mousemovement
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (mouseFirstEntry) {
        cameraLastXPos = (float)xpos;
        cameraLastYPos = (float)ypos;
        mouseFirstEntry = false;
    }

    float xOffset = (float)xpos - cameraLastXPos;
    float yOffset = cameraLastYPos - (float)ypos;
    cameraLastXPos = (float)xpos;
    cameraLastYPos = (float)ypos;
    const float sensitivity = 0.025f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;
    cameraYaw += xOffset;
    cameraPitch += yOffset;
    if (cameraPitch > 89.0f)
    {
        cameraPitch = 89.0f;
    }
    else if (cameraPitch < -89.0f)
    {
        cameraPitch = -89.0f;
    }
    vec3 direction;
    direction.x = cos(radians(cameraYaw)) * cos(radians(cameraPitch));
    direction.y = sin(radians(cameraPitch));
    direction.z = sin(radians(cameraYaw)) * cos(radians(cameraPitch));
    cameraFront = normalize(direction);
}