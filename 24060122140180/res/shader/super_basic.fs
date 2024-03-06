#version 330 core

// Output data
layout(location = 0) out vec4 color;

void main(){
    // Menggunakan sin dan cos dari waktu untuk menghasilkan warna yang berubah-ubah
    float r = 0.5 + 0.5 * sin(gl_FragCoord.x / 50.0 + gl_FragCoord.y / 100.0);
    float g = 0.0; // Untuk warna merah, gunakan nilai hijau nol
    float b = 0.5 + 0.5 * cos(gl_FragCoord.z / 150.0 + gl_FragCoord.x / 50.0); // Biru + Ungu

    // Output color
    color = vec4(r, g, b, 1.0);
}
