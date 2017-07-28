#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 eyePos;

void main()
{
    float ambientFactor = 0.1;
    vec3 ambient = lightColor * ambientFactor;

    vec3 lightDirection = normalize(lightPosition - fragPos);
    float diff = max(dot(normalize(normal), lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularFactor = 0.5;
    vec3 viewDirection = normalize(eyePos - fragPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);

    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
    vec3 specular = specularFactor * spec * lightColor;

    FragColor = vec4(objectColor * (diffuse + ambient + specular), 1.0);
}