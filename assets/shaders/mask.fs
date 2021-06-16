#version 100

precision mediump float;

// Input vertex attributes (from vertex shader)
varying vec3 fragPosition;
varying vec2 fragTexCoord;

uniform sampler2D texture0;
uniform float alpha;

void main() {
    // Texel color fetching from texture sampler

    // NOTE: Implement here your fragment shader code
    vec4 tmp = texture2D(texture0, fragTexCoord);

    tmp.a = alpha;

    gl_FragColor = tmp;
    //gl_FragColor = vec4(fragColor.r, fragColor.g, fragColor.b, alpha);

}