//VERTEX_SHADER
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_texCoord;

void main()
{
    gl_Position = position;
    v_texCoord = texCoord;
}

//FRAGMENT_SHADER
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;

uniform sampler2D u_textureSlot;
uniform float u_alpha;

void main()
{
    color = vec4(1.0f, 1.0f, 1.0f, u_alpha) * texture(u_textureSlot, v_texCoord);
}