# Morgan Hodge - Zombie Scene -  Project Documentation

 TODO : Detail how to run the executable and required libraries to run it

 # Youtube Walkthrough - 

# Tools Used

### Libraries Used
- [OpenGL](https://www.opengl.org/)
- [irrKlang](https://www.ambiera.com/irrklang/)
- 
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

### Animation

# Research-related implementation
fill this out 
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


