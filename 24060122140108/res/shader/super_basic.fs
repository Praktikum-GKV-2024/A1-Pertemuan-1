#version 330 core

// Output data
layout(location = 0) out vec4 color;

void main(){
    // Menggunakan koordinat titik sebagai dasar untuk mengubah warna
    float x = gl_FragCoord.x / 800.0; // 800 adalah lebar layar
    float y = gl_FragCoord.y / 600.0; // 600 adalah tinggi layar
    
    // Menggunakan koordinat titik untuk menghasilkan warna yang berubah-ubah
    float r = x; // Komponen merah bergantung pada posisi x
    float g = y; // Komponen hijau bergantung pada posisi y
    float b = 0.5; // Komponen biru tetap konstan
    
    // Output color
    color = vec4(r, g, b, 1.0);
}
