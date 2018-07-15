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

struct DirLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 direction;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

#define NBR_OF_POINT_LIGHTS 4
uniform PointLight pointLights[NBR_OF_POINT_LIGHTS];
uniform DirLight dirLight;

uniform Material material;

vec3 calculateDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(eyePos - fragPos);

    vec3 result = calculateDirLight(dirLight, norm, viewDir);

    for(int i = 0; i < NBR_OF_POINT_LIGHTS; i++)
    {
        result += calculatePointLight(pointLights[i], norm, fragPos, viewDir);
    }

    FragColor = vec4(result, 1.0);
}

vec3 calculateDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    float diffuseFactor = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float specularFactor = pow(
        max(dot(viewDir, reflectDir), 0.0),
        material.shininess
    );

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diffuseFactor * vec3(
        texture(material.diffuse, TexCoords)
    );
    vec3 specular = light.specular * specularFactor * vec3(
        texture(material.specular, TexCoords)
    );

    return ambient + diffuse + specular;
}

vec3 calculatePointLight(
    PointLight light,
    vec3 normal,
    vec3 fragPos,
    vec3 viewDir
)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diffuseFactor = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float specularFactor = pow(
        max(dot(viewDir, reflectDir), 0.0),
        material.shininess
    );

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (
        light.constant +
        light.linear * distance +
        light.quadratic * distance * distance
    );

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diffuseFactor * vec3(
        texture(material.diffuse, TexCoords)
    );
    vec3 specular = light.specular * specularFactor * vec3(
        texture(material.specular, TexCoords)
    );

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}
