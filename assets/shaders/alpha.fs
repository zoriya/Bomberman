#version 330

precision mediump float;

// Input vertex attributes (from vertex shader)
varying vec2 fragTexCoord;
varying vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform float alpha;

// NOTE: Add here your custom variables

void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = texture2D(texture0, fragTexCoord);

    // Convert texel color to grayscale using NTSC conversion weights

    texelColor.a = alpha;

    gl_FragColor = texelColor;
    // Calculate final fragment color
    //gl_FragColor = vec4(gray, gray, gray, texelColor.a);
}