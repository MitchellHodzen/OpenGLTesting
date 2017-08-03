#version 450 core
out vec4 FragColor;

in vec2 texCoord;
uniform sampler2D currentTexture;
void main()
{
	FragColor = texture(currentTexture, texCoord);
}
