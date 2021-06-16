#version 100

precision mediump float;

// Input vertex attributes (from vertex shader)
varying vec3 fragPosition;

uniform float alpha;

void main() {
    // Texel color fetching from texture sampler

    // NOTE: Implement here your fragment shader code

    gl_FragColor = vec4(fragPosition, alpha);

}