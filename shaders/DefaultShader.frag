#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;
uniform vec3 color;

uniform vec3 lightPos;
uniform vec3 lightColor;

void main()
{   
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0.0f);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 lightOrigin = vec3(0, 0, 0);
    
    vec3 lightDir = normalize(lightPos - lightOrigin);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    result += (ambient + diffuse) * color;

    FragColor = vec4(result, 1.0f);    
}
