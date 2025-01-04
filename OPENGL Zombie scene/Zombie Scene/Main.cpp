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
//Terrain
#include "FastNoiseLite.h" 

using namespace glm;
using namespace std;
using namespace irrklang;


//MVP Dec
mat4 model;
mat4 view;
mat4 projection;

//camera variables
vec3 cameraPosition = vec3(0.0f, 2.0f, 8.0f); //posoiton of starting camera
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

//Cloud movement variables
float moveSpeed = 0.5f;      
float maxRange = 3.0f;       // Range of movement (left to right)
float animationTime = 0.0f;  

// Global variables 1st terrain
GLuint terrainVAO, terrainVBO, terrainEBO;
std::vector<float> terrainVertices;
std::vector<unsigned int> terrainIndices;

//Second terrain
GLuint terrainVAO2, terrainVBO2, terrainEBO2;
std::vector<float> terrainVertices2;
std::vector<unsigned int> terrainIndices2;

//Third terrain
GLuint terrainVAO3, terrainVBO3, terrainEBO3;
std::vector<float> terrainVertices3;
std::vector<unsigned int> terrainIndices3;

//VAO vertex attribute positions in correspondence to vertex attribute type
enum VAO_IDs { Triangles, Indices, Colours, Textures, NumVAOs = 2 };
//VAOs
GLuint VAOs[NumVAOs];

//Buffer types
enum Buffer_IDs { ArrayBuffer, NumBuffers = 4 };
//Buffer objects
GLuint Buffers[NumBuffers];
// Define terrain type flags
const int TERRAIN_1 = 1;
const int TERRAIN_2 = 2;
const int TERRAIN_3 = 3;

void GenerateTerrain(std::vector<float>& vertices, std::vector<unsigned int>& indices, int width, int height, float scale,int terrainType) {
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin); // Set Perlin noise
    noise.SetFrequency(0.3f);                            // Increase frequency for more lumps
    float amplitude = 0.4f;                              // Increase amplitude for higher hills


    if (terrainType == TERRAIN_2)
    {
        noise.SetFrequency(0.3f);        // Increase frequency for more frequent bumps
        amplitude = 15.0f;              // Increase amplitude for taller bumps
    }

    if (terrainType == TERRAIN_3)
    {
        noise.SetFrequency(0.1f);        // Increase frequency for more frequent bumps
        amplitude = 125.0f;              // Increase amplitude for taller bumps
    }

        // Generate vertices with height variation
        for (int z = 0; z < height; ++z) {
            for (int x = 0; x < width; ++x) {
                float heightValue = noise.GetNoise((float)x * scale, (float)z * scale);
                vertices.push_back(x * scale);                // X position
                vertices.push_back(heightValue * amplitude);  // Y position (height)
                vertices.push_back(z * scale);                // Z position

                // color attributes 
                // vertices.push_back(0.1f); // R
                // vertices.push_back(0.8f); // G
                 // vertices.push_back(0.1f); // B

            }
        }

        // Generate indices for triangle strips
        for (int z = 0; z < height - 1; ++z) {
            for (int x = 0; x < width - 1; ++x) {
                int topLeft = z * width + x;
                int topRight = topLeft + 1;
                int bottomLeft = topLeft + width;
                int bottomRight = bottomLeft + 1;

                // First triangle
                indices.push_back(topLeft);
                indices.push_back(bottomLeft);
                indices.push_back(topRight);

                // Second triangle
                indices.push_back(topRight);
                indices.push_back(bottomLeft);
                indices.push_back(bottomRight);
            }
        }
    }


int main()
{
    int windowWidth = 1280;
    int windowHeight = 720;


    //Audio
    ISoundEngine* engine = createIrrKlangDevice();
    if (!engine)
        return 0;
    engine->play2D("audio/mixkit-light-rain-loop-2393.wav", true);


    //Initialisation of GLFW
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Zombie Scene", NULL, NULL);


    //Checks if window has been successfully instantiated
    if (window == NULL)
    {
        cout << "GLFW Window did not instantiate\n";
        glfwTerminate();
        return -1;
    }
    //Bind Cursor to window
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
    Model Cloud("media/Cloud/Cloud_Polygon_Blender_1.fbx");
    Model House("media/House/objHouse.obj");
    Model Signature("media/Signature/signature.obj");
    Model Rock("media/rock/Rock07-Base.obj");
    Model Ghoul("media/Ghoul/swampGhoul.obj");

    glViewport(0, 0, windowWidth, windowHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    // Generate terrain
    // Generate terrain 1 
    GenerateTerrain(terrainVertices, terrainIndices, 100, 100, 0.4f, TERRAIN_1);



    // Setup VAO and VBO
    glGenVertexArrays(1, &terrainVAO);
    glGenBuffers(1, &terrainVBO);
    glGenBuffers(1, &terrainEBO);

    glBindVertexArray(terrainVAO);
    glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
    glBufferData(GL_ARRAY_BUFFER, terrainVertices.size() * sizeof(float), terrainVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, terrainIndices.size() * sizeof(unsigned int), terrainIndices.data(), GL_STATIC_DRAW);

    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    //Generate terrain 2
    GenerateTerrain(terrainVertices2, terrainIndices2, 500, 500, 0.1f, TERRAIN_2);

    // Setup VAO and VBO for the second terrain
    glGenVertexArrays(1, &terrainVAO2);
    glGenBuffers(1, &terrainVBO2);
    glGenBuffers(1, &terrainEBO2);

    glBindVertexArray(terrainVAO2);
    glBindBuffer(GL_ARRAY_BUFFER, terrainVBO2);
    glBufferData(GL_ARRAY_BUFFER, terrainVertices2.size() * sizeof(float), terrainVertices2.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, terrainIndices2.size() * sizeof(unsigned int), terrainIndices2.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Generate terrain 3
    GenerateTerrain(terrainVertices3, terrainIndices3, 500, 500, 0.1f, TERRAIN_3);

    // Setup VAO and VBO for the second terrain
    glGenVertexArrays(1, &terrainVAO3);
    glGenBuffers(1, &terrainVBO3);
    glGenBuffers(1, &terrainEBO3);

    glBindVertexArray(terrainVAO3);
    glBindBuffer(GL_ARRAY_BUFFER, terrainVBO3);
    glBufferData(GL_ARRAY_BUFFER, terrainVertices3.size() * sizeof(float), terrainVertices3.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO3);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, terrainIndices3.size() * sizeof(unsigned int), terrainIndices3.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //Terrain End


    //Render loop
    while (glfwWindowShouldClose(window) == false)
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        animationTime += deltaTime;  // Increment animation time
        ProcessUserInput(window); //Takes user input

        //Rendering
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f); //Set Background colour
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST); //Renders the closest object first (fixes the overlapping issue)


        //transform (perspective)
        model = mat4(1.0f);
        model = scale(model, vec3(0.025f, 0.025f, 0.025f));
        model = rotate(model, (float)radians(0.0f), vec3(1.0, 0.0, 0.0));
        model = translate(model, vec3(0.0f, -2.0f, -1.5f));
        view = lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        projection = perspective(radians(45.0f), (float)windowWidth / (float)(windowHeight), 0.1f, 100.0f);

        // Render terrain
        glBindVertexArray(terrainVAO);
        model = mat4(1.0f);
        model = scale(model, vec3(0.7f, 0.7f, 0.7f));
        model = translate(model, vec3(-17.0f, 0.0f, -5.0f));
        SetMatrices(program);
        glDrawElements(GL_TRIANGLES, terrainIndices.size(), GL_UNSIGNED_INT, 0);

        // Render the second terrain
        glBindVertexArray(terrainVAO2);
        model = mat4(1.0f);
        model = scale(model, vec3(0.3f, 0.1f, 0.5f)); // Smaller scale for the second terrain
        model = translate(model, vec3(-120.0f, -3.0f, -5.0f)); // New position to the left of the first terrain
        SetMatrices(program);
        glDrawElements(GL_TRIANGLES, terrainIndices2.size(), GL_UNSIGNED_INT, 0);

        //Render the third terrain
        glBindVertexArray(terrainVAO3);
        model = mat4(1.0f);
        model = scale(model, vec3(0.3f, 0.1f, 0.5f)); // Smaller scale for the second terrain
        model = translate(model, vec3(-120.0f, -5.0f, 60.0f)); // New position to the left of the first terrain
        SetMatrices(program);
        glDrawElements(GL_TRIANGLES, terrainIndices3.size(), GL_UNSIGNED_INT, 0);
        
        //Render the Ghoul
        model = mat4(1.0f); 
        model = scale(model, vec3(1.5f, 1.5f, 1.5f));; 
        model = translate(model, vec3(0.0f, 1.6f, 0.3f));; 
        SetMatrices(program);
        Ghoul.Draw(program);

        //Render my signature
        model = mat4(1.0f); 
        model = scale(model, vec3(0.002f, 0.002f, 0.002f));
        model = translate(model, vec3(-2.0f, 9.0f, 5.0f)); 
        model = rotate(model, radians(90.0f), vec3(1.0f, 0.0f, 0.0f)); 
        SetMatrices(program);
        Signature.Draw(program);

        //Render Cloud (Ainmiated) 
        float xOffset = sin(animationTime) * 0.2f; 
        model = mat4(1.0f); 
        model = scale(model, vec3(10.0f, 4.0f, 10.0f)); 
        model = translate(model, vec3(xOffset, 3.0f, -1.5f)); 
        SetMatrices(program);
        Cloud.Draw(program);

        //More clouds to fill out the scene
        model = mat4(1.0f); 
        model = scale(model, vec3(6.0f, 1.0f, 6.0f)); 
        model = translate(model, vec3(xOffset, 8.0f, 0)); 
        SetMatrices(program);
        Cloud.Draw(program);
        //Maybe another cloud

        //Render Building
        model = mat4(1.0f); 
        model = scale(model, vec3(25.0f, 25.0f, 25.0f));
        model = translate(model, vec3(0.0f, 0.01f, -0.1f));; 
        SetMatrices(program);
        House.Draw(program);

        // Render rock 
        model = mat4(1.0f); 
        model = scale(model, vec3(0.05f, 0.05f, 0.05f));
        model = translate(model, vec3(-5.0f, 8.0f, -1.5f));; 
        SetMatrices(program);
        Rock.Draw(program);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    //Safely terminates GLFW
    glfwTerminate();
    engine->drop(); // delete engine
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    //Resises window based on contemporary width & height values
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

//mouse movement
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