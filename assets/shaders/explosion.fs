#version 100

precision mediump float;

// Input vertex attributes (from vertex shader)
varying vec3 fragPosition;
varying vec3 fragNormal;
varying vec2 fragTexCoord;

uniform sampler2D texture0;
uniform float alpha;

void main() {
    // Texel color fetching from texture sampler

    // NOTE: Implement here your fragment shader code
    vec4 tmp;
    tmp.rgb = texture2D(texture0, fragTexCoord).rgb;


    tmp.a = alpha;

    gl_FragColor = tmp;
    //gl_FragColor = vec4(fragColor.r, fragColor.g, fragColor.b, alpha);

}