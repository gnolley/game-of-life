#version 430 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D tex;
uniform float t;

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{             
    float cellAlive = texture(tex, TexCoords).r;    
    
    vec3 foregroundColor = hsv2rgb(vec3(t / 10, 1.0, 1.0));
    vec3 backgroundColor = hsv2rgb(vec3(t / 10, 0.75, 0.2));
   
    vec3 col = mix(backgroundColor, foregroundColor, cellAlive);

    FragColor = vec4(col, 1.0);
}