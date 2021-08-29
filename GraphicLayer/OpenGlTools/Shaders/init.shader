#VertexShader
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 col;
layout (location = 2) in vec2 aTexCoord;

out vec3 vertexColor;
out vec2 TexCoord;

uniform mat4 transform;

void main(){
	gl_Position = transform * vec4(position, 1.0);
	vertexColor = col;
	TexCoord = aTexCoord;
}

#FragmentShader

#version 330 core

out vec4 color;

//uniform vec4 u_color;
in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main(){
	color = texture(ourTexture, TexCoord);

}
