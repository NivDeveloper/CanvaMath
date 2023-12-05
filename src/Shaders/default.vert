#version 430 core
// default vert

precision lowp float;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

layout (std140, binding = 0) uniform Transforms {
    mat4 view;
    mat4 proj;
    vec3 viewPos;
};

uniform mat4 model;
out vec4 uv;

void main()
{
    uv = vec4(aTexCoord.x, aTexCoord.y, 0.0f, 1.0f);
    // gl_Position = proj * view * model * vec4(aPos, 1.0f);
    gl_Position = proj * view * model * vec4(aPos, 1.0f);
}