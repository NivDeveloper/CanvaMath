#version 430 core
// mandel frag

precision lowp float;

in vec4 uv;
out vec4 frag_color;
 
#define MAX_ITERATIONS 500

float scale = 1.0;
int get_iterations()
{
    float real = (((uv.x - 0.5)/scale) * 4.0);
    float imag = (uv.y - 0.5)/scale * 4.0;
    int iterations = 0;
    float const_real = real;
    float const_imag = imag;
 
    while (iterations < MAX_ITERATIONS)
    {
        float tmp_real = real;
        real = (real * real - imag * imag) + const_real;
        imag = (2.0 * tmp_real * imag) + const_imag;
         
        float dist = real * real + imag * imag;
         
        if (dist > 4.0)
        break;
 
        ++iterations;
    }
    return iterations;
}

vec4 return_color()
{
    int iter = get_iterations();
    if (iter == MAX_ITERATIONS)
    {
        gl_FragDepth = 0.0f;
        return vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
 
    float iterations = 100 * float(iter) / MAX_ITERATIONS;
    float b = sin(iterations);
    float r = sin(iterations*1.3f)*0.8;
    float g = sin(iterations*1.3f)*0.8;
    return vec4(r, g, b, 1.0f);
}
 
void main()
{
    frag_color = return_color();
    // frag_color = vec4(0.5, 0.82, 0.09, 0.5);
}