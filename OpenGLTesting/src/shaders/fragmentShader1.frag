#version 450 core
out vec4 FragColor;

in vec2 texCoord;
uniform sampler2D currentTexture;
uniform vec3 ambientLight;
uniform vec3 objectColor;
void main()
{
	float ambientIntensity = 0.5;
	FragColor = texture(currentTexture, texCoord) * vec4((ambientLight*ambientIntensity) * objectColor, 1);
}
