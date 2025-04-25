#Nama  : Muhammad syukri#
#NPM   : 2308107010060#

Program Sorting
Program ini melakukan pengujian performa berbagai algoritma sorting (pengurutan) pada data angka dan kata.
Cara Menjalankan Program
Persiapan Awal

Pastikan Anda memiliki compiler C (GCC) yang sudah terinstal di sistem Anda
Clone atau download repository ini ke komputer Anda

Langkah 1: Generate Data Uji
Pertama, generate data angka dan kata yang akan digunakan untuk pengujian:

# Compile generator angka
gcc generator_angka.c -o generator_angka

# Compile generator kata
gcc generator_kata.c -o generator_kata

# Jalankan generator untuk membuat data uji
./generator_angka
./generator_kata

Proses ini akan menghasilkan file file_angka.txt dan file_kata.txt di folder data/ yang berisi 20 juta data acak.

Langkah 2: Kompilasi Program Utama
gcc main.c sort.h -o sorting

Langkah 3: Jalankan Program
./sorting

Program akan melakukan pengujian algoritma sorting (Bubble Sort, Selection Sort, Insertion Sort, Merge Sort, Quick Sort, dan Shell Sort) dengan berbagai ukuran data (10.000 hingga 2.000.000) dan menampilkan waktu eksekusi serta penggunaan memori untuk setiap algoritma.
Struktur Program

generator_angka.c - Program untuk generate data angka acak
generator_kata.c - Program untuk generate data kata acak
sort.h - Header file berisi implementasi algoritma sorting
main.c - Program utama yang menjalankan pengujian

