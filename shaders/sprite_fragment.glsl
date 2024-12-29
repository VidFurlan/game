#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D spriteTexture;
uniform sampler2D maskTexture;
uniform vec3 spriteColor;
uniform bool useMask;

void main() {
    vec4 sprite = texture(spriteTexture, TexCoords);
    if (useMask) {
        vec4 mask = texture(maskTexture, TexCoords);
        FragColor = vec4(spriteColor, mask.r) * sprite;
    }
    else {
        FragColor = vec4(spriteColor, 1.0) * sprite;
    }
}
