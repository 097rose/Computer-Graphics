#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 deformation;

out vec2 texCoord;
out vec4 worldPos;
out vec3 normal;

void main()
{
    mat4 m = M;
    m = deformation * m;
	gl_Position = P * V * m * vec4(aPos, 1.0);
	texCoord = aTexCoord;
	worldPos = m * vec4(aPos, 1.0);
	mat4 normal_transform = transpose(inverse(m));
	normal = normalize((normal_transform * vec4(aNormal, 0.0)).xyz);;
}