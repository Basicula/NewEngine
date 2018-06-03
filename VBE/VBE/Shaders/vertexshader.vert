#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 normal;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec4 Color;
out vec2 texCoord;
out vec3 Position;
out vec3 Normal;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	
	texCoord = vec2(texCoords.x,1.0f-texCoords.y);
	Position = vec3(model * vec4(position,1.0f));
	Color = color;
	Normal = mat3(transpose(inverse(model))) * normal;
}