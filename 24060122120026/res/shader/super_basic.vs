# version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;

out vec3 color;

void main(){
	// Output position of the vertex, in clip space : MVP * position
	gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
	color = aColor;
}