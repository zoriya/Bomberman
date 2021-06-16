#version 330

precision mediump float;

// Input vertex attributes (from vertex shader)
varying vec2 fragTexCoord;
varying vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform float white;

// NOTE: Add here your custom variables

void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = texture2D(texture0, fragTexCoord);

    if (white > texelColor.r)
        texelColor.r = white;
    if (white > texelColor.g)
        texelColor.g = white;
    if (white > texelColor.b)
        texelColor.b = white;

    // Convert texel color to grayscale using NTSC conversion weights
    //float gray = dot(texelColor.rgb, vec3(0.299, 0.587, 0.114));

    gl_FragColor = texelColor;
    // Calculate final fragment color
    //gl_FragColor = vec4(gray, gray, gray, texelColor.a);
}