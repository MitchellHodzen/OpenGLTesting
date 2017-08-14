#version 450 core
out vec4 FragColor;
uniform sampler2D tex;
in  vec2 texCoord;


void main()
{
	FragColor = texture(tex, texCoord);
	//FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	//FragColor = textureSample;
}
