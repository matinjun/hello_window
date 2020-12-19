#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texturel;

void main()
{
	FragColor = texture(texturel, TexCoord) * vec4(ourColor, 1.0f);

}