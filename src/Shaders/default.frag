#version 430 core

out vec4 FragColor;
  
uniform sampler2D Tex;
in vec4 uv;

void main()
{
    FragColor = texture(Tex, vec2(uv.x, uv.y));

}