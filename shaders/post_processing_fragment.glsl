#version 330 core

// CRT shader: https://www.shadertoy.com/view/sljXDz

float PI = 3.14159265359;

in vec2 TexCoords;
out vec4 color;

uniform sampler2D scene;

uniform vec2 offsets[9];
uniform int edge_kernel[9];
uniform float blur_kernel[9];

uniform vec2 screenResolution;
uniform vec2 scanLineOpacity;
uniform float vignetteOpacity;

uniform float distortion_amount;
uniform float bloom_amount;
uniform float mask_amount;

vec2 curveRemapCoord(vec2 coords) {
    coords = coords * 2.0 - 1.0;
    vec2 offset = abs(coords.yx) / vec2(6.0, 4.0);
    coords += coords * offset * offset;
    coords = coords * 0.5 + 0.5;
    return coords;
}

vec4 scanLine(float coord, float resolution, float opacity) {
    float intensity = sin(coord * resolution * PI * 2.0);
    intensity = ((0.5 * intensity) + 0.5) * 0.9 + 0.1;
    return vec4(vec3(pow(intensity, opacity)), 1.0);
}

vec4 vignette(vec2 coords, vec2 resolution, float opacity) {
    float intensity = coords.x * coords.y * (1.0 - coords.x) * (1.0 - coords.y);
    return vec4(vec3(clamp(pow((resolution.x / 4.0) * intensity, opacity), 0.0, 1.0)), 1.0);
}

void main() {
    vec2 remappedCoords = curveRemapCoord(TexCoords);
    vec4 baseColor = texture(scene, remappedCoords);

    baseColor *= vignette(remappedCoords, screenResolution, vignetteOpacity);

    baseColor *= scanLine(remappedCoords.x, screenResolution.y * 0.3, scanLineOpacity.x);
    baseColor *= scanLine(remappedCoords.y, screenResolution.x * 0.3, scanLineOpacity.y);

    if (remappedCoords.x < 0.0 || remappedCoords.x > 1.0 || remappedCoords.y < 0.0 || remappedCoords.y > 1.0) {
        baseColor = vec4(0.0, 0.0, 0.0, 1.0);
    }

    color = baseColor;
}
