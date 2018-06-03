#version 330 core

struct Materials 
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float shine;
};

struct Light
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 position;
};

in vec4 Color;
in vec2 texCoord;
in vec3 Position;
in vec3 Normal;

out vec4 color;

uniform sampler2D texture;

uniform	vec4 lightColor;
uniform vec3 viewPos;
uniform vec4 objectColor;

uniform Light light;
uniform Materials material;

void main()
{
	//color = texture(texture,texCoord);

	float intensity = 1.5f / length(light.position - Position);

	//ambient
	vec3 ambient = light.ambient * material.ambient;

	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - Position);
	float diff = max(dot(lightDir,norm),0.0f);
	vec3 diffuse = intensity * diff * light.diffuse * material.diffuse;

	//specular
	float specularPower = 0.5f;
	vec3 viewDir = normalize(viewPos - Position);
	vec3 reflectLightDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir,reflectLightDir),0.0f),material.shine);
	vec3 specular = intensity * spec * light.specular * material.specular;
	
	color = vec4(ambient + diffuse + specular,1.0f);
}