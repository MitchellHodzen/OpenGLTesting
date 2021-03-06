#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 VP;

void main()
{
	gl_Position = VP * model * vec4(aPos, 1.0);
	//gl_Position = vec4(aPos, 1.0);
	texCoord = aTexCoord;
}
