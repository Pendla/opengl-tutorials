#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;
in vec2 TexCoords;

uniform vec3 eyePos;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
uniform Material material;

void main()
{
    // Ambient component
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // Diffuse component
    vec3 normal = normalize(normal);
    vec3 lightDirection = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // Specular component
    vec3 viewDirection = normalize(eyePos - fragPos);
    vec3 reflectDir = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
