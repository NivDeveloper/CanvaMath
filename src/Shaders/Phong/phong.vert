#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

layout (std140, binding = 0) uniform Transforms {
    mat4 view;
    mat4 proj;
    vec3 viewPos;
};

uniform mat4 model;


out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;
out vec3 vPos;

void main() {
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    // Normal = aNormal;
    Normal = mat3(transpose(inverse(model))) * aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
    TexCoord = aTexCoord;
    vPos = viewPos;
} 