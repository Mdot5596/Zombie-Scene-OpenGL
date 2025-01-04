#version 460

// Colour output
out vec4 FragColor;

// Texture coordinates from the vertex shader
in vec2 textureCoordinatesFrag;

// Samplers for two textures
uniform sampler2D textureIn1;  // First texture
uniform sampler2D textureIn2;  // Second texture

// Blend factor to mix the two textures
uniform float blendFactor;     // Range: 0.0 (100% textureIn1) to 1.0 (100% textureIn2)

void main()
{
    // Sample both textures
    vec4 texture1 = texture(textureIn1, textureCoordinatesFrag);
    vec4 texture2 = texture(textureIn2, textureCoordinatesFrag);

    // Blend the two textures
    FragColor = mix(texture1, texture2, blendFactor);
}