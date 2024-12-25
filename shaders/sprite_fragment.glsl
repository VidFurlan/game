#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D sprite;
uniform vec3 spriteColor;

void main() {
    vec4 sampled = texture(sprite, TexCoords);
    FragColor = vec4(spriteColor, 1.0) * sampled;
}
