## Nama  : Muhammad syukri NPM   : 2308107010060

# Program Sorting
### Program ini melakukan pengujian performa berbagai algoritma sorting (pengurutan) pada data angka dan kata.

# Cara Menjalankan Program
Persiapan Awal

## Langkah 1: Generate Data Uji
Pertama, generate data angka dan kata yang akan digunakan untuk pengujian:

### Compile generator angka
<pre><code>gcc generator_angka.c -o generator_angka</code></pre>

### Compile generator kata
<pre><code>gcc generator_kata.c -o generator_kata</code></pre>

### Jalankan generator untuk membuat data uji
<pre><code>./generator_angka
./generator_kata</code></pre>


Proses ini akan menghasilkan file file_angka.txt dan file_kata.txt di folder data/ yang berisi 20 juta data acak.

## Langkah 2: Kompilasi Program Utama
<pre><code>gcc main.c sort.h -o sorting</code></pre>

## Langkah 3: Jalankan Program
<pre><code>./sorting</code></pre>

Program akan melakukan pengujian algoritma sorting (Bubble Sort, Selection Sort, Insertion Sort, Merge Sort, Quick Sort, dan Shell Sort) dengan berbagai ukuran data (10.000 hingga 2.000.000) dan menampilkan waktu eksekusi serta penggunaan memori untuk setiap algoritma.

## Struktur Program

- generator_angka.c - Program untuk generate data angka acak
- generator_kata.c - Program untuk generate data kata acak
- sort.h - Header file berisi implementasi algoritma sorting
- main.c - Program utama yang menjalankan pengujian

