#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
//layout (location = 3) in mat4 aModel;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPosition;

uniform mat4 model;
uniform mat4 VP;

void main()
{ 
	gl_Position = VP * model * vec4(aPos, 1.0); 
	//gl_Position = VP * aModel * vec4(aPos, 1.0);
	fragPosition = vec3(model * vec4(aPos, 1.0));
	//fragPosition = vec3(aModel * vec4(aPos, 1.0));
	texCoord = aTexCoord;
	normal = mat3(transpose(inverse(model))) * aNormal;
	//normal = mat3(transpose(inverse(aModel))) * aNormal;
}
