# Morgan Hodge - Zombie Scene -  Project Documentation

## How to run the scene
### In order to run the exe:
- Unzip the "Zombie Scene exe" file
- Create a folder at the location C:\Users\Public\OpenGL
- Inside this folder create 4 subfolders: include and lib (this is where you will place the OpenGL includes and libs)
- assimp (this is where you will put the contents from the Assimp download)
-  audio (this is where you will download IrrKlang and store the audio files for the scene)
- You can find links to all the downloads bellow
- Once that is set up, you can double-click the exe, and it should run without errors

# Youtube Walkthrough - https://youtu.be/z9JmAVT52C4

# Tools Used

### Libraries/Dependencies Used
- [OpenGL](https://www.opengl.org/)
- [GLFW](https://www.glfw.org/download.html)
- [GLEW](https://glew.sourceforge.net/)
- [irrKlang](https://www.ambiera.com/irrklang/)
- [cmake](https://cmake.org/download/)
- [assimp](https://github.com/assimp/assimp/blob/master/Build.md)
- [FastNoiseLite](https://github.com/Auburn/FastNoiseLite/tree/master)
- [Glad](https://glad.dav1d.de/)
- [stb image](https://github.com/nothings/stb/blob/master/stb_image.h)
  
### Models
- **Website:** [TurboSquid](https://www.turbosquid.com/)
  - [Abandoned House Model and Texture](https://www.turbosquid.com/3d-models/abandoned-old-house-3d-2287730)
  - [Cloud Model](https://www.turbosquid.com/3d-models/3d-cloud-polygon-blender-1-model-1895708)
  - [Zombie Model and Texture](https://www.turbosquid.com/3d-models/nextgen-ghoul-x/527095)
  - [Rock Model and Texture](https://www.turbosquid.com/3d-models/rock07base3ds-3d-1899446)

### Audio
- **Library:** [irrKlang](https://www.ambiera.com/irrklang/)
  - Tutorial: [How to Implement irrKlang](https://www.youtube.com/watch?v=PLh79OjVFws)
  - [Rain Sound Effect](https://mixkit.co/free-sound-effects/rain/)
  - [Scream Sound Effect](https://mixkit.co/free-sound-effects/scream/)

### PCG (Procedural Content Generation)
To generate terrain, I researched and utilised the following resources:
- [OpenGL Normal Mapping Tutorial](https://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/)
- [Perlin Noise and FastNoiseLite](https://glusoft.com/godot-tutorials/make-terrain-perlin-noise-FastNoiseLite/)
- Lab Session 8 (on GitHub)


# Research-related implementation

### Audio Research
For implementing interactive audio playback in my project, I utilised the IrrKlang audio library. To understand how to integrate it effectively, I referred to a tutorial video that demonstrated setting up and controlling audio events within a 3D scene. This helped me implement features like the rain sound effects and a triggered scream when the spacebar is pressed.

**Source:** [“irrKlang Tutorial - How to Add Sound to Your C++ Project” (2021)](https://www.youtube.com/watch?v=PLh79OjVFws)

This tutorial, published within the last five years, provided up-to-date and practical guidance on integrating sound effects in a modern game development context. The video even demonstrates how to add the include and libs into the VS directory.


### Animation Research

To implement the cloud animation in my project, I applied transformation techniques to move the cloud model smoothly across the scene. By utilising translation transformations, I was able to control the cloud's position over time, creating a natural left-to-right movement. The following variables were used to manage the animation:
```cpp
// Cloud movement variables
float moveSpeed = 0.5f;      // Speed of movement
float maxRange = 3.0f;       // Range of movement (left to right)
float animationTime = 0.0f;  // Tracks elapsed time for animation
```
This approach was informed by research into basic transformation techniques in OpenGL, specifically the use of translation matrices to alter an object's position within the scene. Resources such as the tutorial on Basic Transformations in OpenGL provided insights into implementing these transformations effectively.

**Source:** (https://www.geeksforgeeks.org/basic-transformations-opengl/)

This resource, published within the past five years, offered clear guidance on applying translation, rotation, and scaling transformations in OpenGL. 

# Evaluation
This scene follows my approved pitch: *"A scene with a zombie in the center. The camera/player can move around the scene. The zombie will create noise such as growling, etc. The scene will have dark lighting (moonlight) and SFX such as rain and lightning. The zombie will be in a setting like being trapped in debris or something similar."*

I achieved this vision by creating a scene that features:
- A zombie trapped in rocky debris at the center of the screen, surrounded by an abandoned building.
- Camera movement controlled by keyboard and mouse functionality.
- Rain sound effects and interactive audio playback: pressing the spacebar causes the player to scream out of shock.

### Reflection
I am very happy with what I have achieved, as I feel I have gained substantial experience in several areas:
- **Coding in OpenGL 4.X**: Strengthened my understanding of graphics programming.
- **Procedural Content Generation (PCG)**: Learned terrain generation using FastNoiseLite and Perlin Noise.
- **Model Loading**: Successfully implemented model loading using ASSIMP.
- **Software Integration**: Enhanced my skills in linking libraries and resources with `<includes>` and `<libs>`.

In this assignment, I aimed to achieve the maximum possible marks by covering all required elements:
- To Pass (0-40 marks)
- 40-70  (40-70 marks)
- Two advanced features (70+ marks)

I enjoyed working on this project, and it took considerable time and effort to complete, but the process was incredibly rewarding.

### Future Improvements
- **Gameplay Elements:** In the future, I would like to add gameplay mechanics to the scene. Although I am unsure how to implement this at the current stage, I am confident I could research and figure it out.
- **Lightning Effects:** Unfortunately, I was unable to implement lightning effects as described in my pitch. This was more complex than anticipated, as simply downloading a lightning asset from TurboSquid was not sufficient. In the future, I aim to revisit this and find a way to bring this feature to life.


