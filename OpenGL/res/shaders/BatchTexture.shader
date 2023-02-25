#shader vertex
#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texIndex;

out vec2 v_TexCoord;
out float v_TexIndex;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0);
	v_TexCoord = texCoord;
	v_TexIndex = texIndex;
};

#shader fragment
#version 450 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_TexIndex;
uniform sampler2D u_Textures[2];

void main()
{
	int index = int(v_TexIndex);
	color = texture(u_Textures[index], v_TexCoord);
}