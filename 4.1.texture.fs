#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

//
uniform float mixValue;

// texture sampler
uniform sampler2D texturel;
uniform sampler2D texture2;

void main()
{
	vec2 reverseTexCoord = vec2(TexCoord.x, 1.0f - TexCoord.y);
	FragColor = mix(texture(texturel, reverseTexCoord), texture(texture2, 2 * TexCoord), mixValue) * vec4(ourColor, 1.0f);

}