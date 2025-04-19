#version 330 core

in vec2 v_texindex;
in vec4 v_color;

out vec4 f_color;

uniform sampler2D u_texture;

void main() {
    f_color = vec4(texture(u_texture, v_texindex).r);
    f_color *= v_color;
}
