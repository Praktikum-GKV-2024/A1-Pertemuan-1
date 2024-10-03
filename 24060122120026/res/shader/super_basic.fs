# version 330 core

// in vec4 position;
in vec3 color;

// Output data
//layout(location = 0)
out vec4 Fragcolor;

void main(){

	// Output color = color of the texture at the specified UV
	// color = vec4(gl_FragCoord., 0, 1); //vec4(1., 0., 0., 1.);
	Fragcolor = vec4(color, 1.0); //set fragment color from the input
}