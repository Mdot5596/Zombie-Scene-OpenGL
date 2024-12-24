//STD
#include <iostream>
#include "GLAD/glad.h"
//GLEW
//#include <GL/glew.h>
//#include "LoadShaders.h"
//GLM
#include "glm/glm/ext/vector_float3.hpp"
#include "glm/glm/ext/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

//Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//LEARNOPENGL
#include <learnopengl/shader_m.h>
#include <learnopengl/model.h>
#include "main.h"

//Audio
#include <irrKlang.h>

using namespace glm;
using namespace std;
using namespace irrklang;

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

    //audio
    ISoundEngine* engine = createIrrKlangDevice();
    if (!engine)
        return 0;
    engine->play2D("audio/mixkit-light-rain-loop-2393.wav", true);

    //aduio end

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
    // glewInit();


    //Initialisation of GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "GLAD failed to initialise\n";
        return -1;
    }

    //Loading of shaders
    Shader program("shaders/vertexShader.vert", "shaders/fragmentShader.frag");
    program.use();
    Model Signature("media/Signature/signature.obj");
    Model Rock("media/rock/Rock07-Base.obj");
  //Model zombie("media/zombie/zombi.obj");
    Model Ghoul("media/Ghoul/swampGhoul.obj");

      //Sets the viewport size within the window to match the window size of 1280x720
    glViewport(0, 0, windowWidth, windowHeight);

    //Sets the framebuffer_size_callback() function as the callback for the window resizing event
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //mousecallback
    glfwSetCursorPosCallback(window, mouse_callback);


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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clears the colour and depth buffer
        glEnable(GL_CULL_FACE);

        //transform (perspective)
        model = mat4(1.0f);
        model = scale(model, vec3(0.025f, 0.025f, 0.025f));
        model = rotate(model, (float)radians(0.0f), vec3(1.0, 0.0, 0.0));
        model = translate(model, vec3(0.0f, -2.0f, -1.5f));
        view = lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        projection = perspective(radians(45.0f), (float)windowWidth / (float)(windowHeight), 0.1f, 100.0f);

        //Render my signature
        model = mat4(1.0f); // Reset to identity matrix
        model = scale(model, vec3(0.002f, 0.002f, 0.002f));
        model = translate(model, vec3(-3500.0f, 5.0f, 5.0f));
        model = rotate(model, radians(90.0f), vec3(1.0f, 0.0f, 0.0f)); // Rotate 90 degrees around the X-axis so the sigatures stood up
        SetMatrices(program);
        Signature.Draw(program);

        //Render the rock
        model = mat4(1.0f); // Reset to identity matrix
        model = scale(model, vec3(0.025f, 0.025f, 0.025f));
        model = translate(model, vec3(0.0f, -2.0f, -1.5f)); // Position as needed
        SetMatrices(program);
        Rock.Draw(program);

        //Render the Ghoul
        model = mat4(1.0f); // Reset to identity matrix
        model = scale(model, vec3(1.0f, 1.0f, 1.0f)); // Scale the zombie model up significantly
        model = translate(model, vec3(0.0f, -2.0f, -1.5f)); // Position as needed
        SetMatrices(program);
        Ghoul.Draw(program);

        //Render the zombie
        //model = mat4(1.0f); // Reset to identity matrix
        // model = scale(model, vec3(0.002f, 0.002f, 0.002f)); // Scale the zombie model
        //model = translate(model, vec3(-1000.0f, 0.0f, 0.0f)); // Move left by 200 units
        //SetMatrices(program);
        //zombie.Draw(program);


        //Refreshing
        glfwSwapBuffers(window); //Swaps the colour buffer
        glfwPollEvents(); //Queries all GLFW events
    }

    //Safely terminates GLFW
    glfwTerminate();
    engine->drop(); // delete engine
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

    //Plays scream each time space is pressed
    static bool spacePressed = false; // Track if space is currently pressed

    if (glfwGetKey(WindowIn, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        if (!spacePressed) // Trigger only when key is first pressed
        {
            ISoundEngine* engine = createIrrKlangDevice();
            cout << "Spacebar pressed: Playing audio!" << endl;
            engine->play2D("audio/mixkit-falling-male-scream-391.wav");
            spacePressed = true;
        }
    }

    else
    {
        spacePressed = false; // Reset when spacebar is released
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

void SetMatrices(Shader& ShaderProgramIn)
{
    mat4 mvp = projection * view * model;
    ShaderProgramIn.setMat4("mvpIn", mvp);
}