#version 330
precision highp float;
precision highp int;

varying float noise;

//uniform float brightness;

float random( vec3 scale, float seed ) {
  return fract( sin( dot( gl_FragCoord.xyz + seed, scale ) ) * 43758.5453 + seed ) ;
}

vec3 mult(vec3 a, vec3 b){
    return vec3(a.r *b.r, a.g * b.g, a.b * b.b);
}

void main() {

       brightness = 0.86080327;
    // get a random offset
    float offset = .01 * random( vec3( 12.9898, 78.233, 0151.7182 ), 0.0 );

    // not quite depth, but how bright the sphere is (higher is dimmer)
    float depth = 0.25;

    // lookup vertically in the texture, using noise and offset
    // to get the right RGB colour
    vec2 tPos = vec2( 0, ( brightness + depth ) * noise + offset );
    // vec4 color = texture2D( tExplosion, ( brightness - depth ) - tPos );
    vec3 color = mult(vec3(0, 1, 0), vec3( ( brightness - depth ) - tPos.y ));
    gl_FragColor = vec4( color, 1.0 );

}
