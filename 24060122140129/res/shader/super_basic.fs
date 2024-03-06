#version 330 core

// Output data
layout(location = 0) out vec4 color;

void main(){
	FragColor = vec4(color, 1.0);
}