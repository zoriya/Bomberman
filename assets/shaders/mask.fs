#version 100

precision mediump float;

// Input vertex attributes (from vertex shader)
varying vec3 fragPosition;

void main() {
    // Texel color fetching from texture sampler

    // NOTE: Implement here your fragment shader code

    gl_FragColor = vec4(fragPosition, 1.0);

}