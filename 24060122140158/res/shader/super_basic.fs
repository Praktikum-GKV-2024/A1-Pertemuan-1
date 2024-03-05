#version 330 core
<<<<<<< HEAD

in vec3 color; // Receive color from vertex shader
=======
>>>>>>> 1732cef9a7f0157ef28370fc4b8b8abfe2c26619

out vec4 FragColor;

<<<<<<< HEAD
void main() {
    FragColor = vec4(color, 1.0); // Set fragment color from the input
=======
void main(){

	// Output color, warna yang akan digambar ke layar
	color = vec4(1., 0., 0., 1.);
>>>>>>> 1732cef9a7f0157ef28370fc4b8b8abfe2c26619
}