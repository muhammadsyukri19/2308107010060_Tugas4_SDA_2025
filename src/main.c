#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sort.h"

#define MAX_DATA 2500000  // Menambah ukuran maksimum untuk aman
#define MAX_WORD_LEN 50

// === Fungsi Load Data ===
void load_numbers(const char *path, int array[], int amount) {
    FILE *file = fopen(path, "r");
    if (!file) {
        perror("Gagal membuka file angka");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < amount; i++) {
        if (fscanf(file, "%d", &array[i]) != 1) break;
    }
    fclose(file);
}

void load_words(const char *path, char* array[], int amount) {
    FILE *file = fopen(path, "r");
    if (!file) {
        perror("Gagal membuka file kata");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < amount; i++) {
        array[i] = malloc(MAX_WORD_LEN * sizeof(char));
        if (!array[i]) {
            perror("Gagal mengalokasikan memori untuk kata");
            exit(EXIT_FAILURE);
        }
        if (fscanf(file, "%s", array[i]) != 1) {
            free(array[i]); // Bebaskan memori jika gagal membaca
            array[i] = NULL;
            break;
        }
    }
    fclose(file);
}

// === Fungsi Copy Array ===
void copy_array(int destination[], int source[], int n) {
    memcpy(destination, source, n * sizeof(int)); // Lebih efisien menggunakan memcpy
}

void copy_word_array(char* destination[], char* source[], int n) {
    for (int i = 0; i < n; i++) {
        // Salin string, bukan pointer
        strcpy(destination[i], source[i]);
    }
}

// === Pilihan Tipe Data ===
int choose_data_type() {
    int choice;
    printf("=== Pilih Tipe Data ===\n");
    printf("1. Angka\n2. Kata\nPilihan Anda [1-2]: ");
    scanf("%d", &choice);
    if (choice != 1 && choice != 2) {
        printf("Pilihan tidak valid.\n");
        exit(EXIT_FAILURE);
    }
    return choice;
}

// === Header & Footer ===
void print_header() {
    printf("\nHasil Pengurutan:\n\n");
    printf("| Algoritma yang Digunakan            | Waktu yang Dibutuhkan (Detik)  | Memori yang Digunakan (MB)    |\n");
    printf("|-------------------------------------|--------------------------------|-------------------------------|\n");
}

void print_footer() {
    printf("\n");
}

// === Wrapper Fungsi untuk Menyamakan Tipe ===
// Angka
void wrapperMergeSortAngka(int arr[], int n) {
    // Alokasi array tambahan untuk merge sort untuk mencegah rekursi yang terlalu dalam
    int *temp = malloc(n * sizeof(int));
    if (!temp) {
        perror("Gagal mengalokasikan memori untuk merge sort angka");
        exit(EXIT_FAILURE);
    }
    mergeSortAngka(arr, 0, n - 1);
    free(temp);
}

void wrapperQuickSortAngka(int arr[], int n) {
    quickSortAngka(arr, 0, n - 1);
}

// Kata
void wrapperMergeSortKata(char* arr[], int n) {
    mergeSortKata(arr, 0, n - 1);
}

void wrapperQuickSortKata(char* arr[], int n) {
    quickSortKata(arr, 0, n - 1);
}

// === Fungsi Utama ===
int main() {
    int data_type = choose_data_type();
    int data_size;
    
    printf("Masukkan jumlah data yang ingin diurutkan: ");
    scanf("%d", &data_size);
    
    if (data_size <= 0 || data_size > MAX_DATA) {
        printf("Jumlah data tidak valid. Masukkan nilai antara 1 dan %d.\n", MAX_DATA);
        return 1;
    }

    printf("\nMenjalankan pengurutan untuk %d data...\n", data_size);
    print_header();

    clock_t start_time, end_time;
    double duration;

    if (data_type == 1) {
        // Alokasi memori untuk data awal
        int *initial_data = malloc(sizeof(int) * data_size);
        if (!initial_data) {
            printf("Gagal dalam alokasi memori untuk data awal.\n");
            return 1;
        }

        // Alokasi memori untuk data yang akan disorting
        int *data = malloc(sizeof(int) * data_size);
        if (!data) {
            printf("Gagal dalam alokasi memori untuk data sorting.\n");
            free(initial_data);
            return 1;
        }

        load_numbers("../data/data_angka.txt", initial_data, data_size);

        const char *sort_names[] = {
            "Bubble Sort (angka)", "Selection Sort (angka)", "Insertion Sort (angka)",
            "Merge Sort (angka)", "Quick Sort (angka)", "Shell Sort (angka)"
        };
        void (*sort_functions[])(int[], int) = {
            bubbleSortAngka, selectionSortAngka, insertionSortAngka,
            wrapperMergeSortAngka, wrapperQuickSortAngka, shellSortAngka
        };

        for (int i = 0; i < 6; i++) {
            copy_array(data, initial_data, data_size);
            start_time = clock();
            sort_functions[i](data, data_size);
            end_time = clock();
            duration = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
            printf(" %-37s  %-30.3f  %-30.2f \n", sort_names[i], duration, sizeof(int) * data_size / (1024.0 * 1024.0));
        }

        free(initial_data);
        free(data);
    } else {
        // Alokasi array untuk pointer kata
        char **words = malloc(sizeof(char*) * data_size);
        if (!words) {
            printf("Gagal dalam alokasi memori untuk array kata.\n");
            return 1;
        }

        // Alokasi array kedua untuk copy saat sorting
        char **words_copy = malloc(sizeof(char*) * data_size);
        if (!words_copy) {
            printf("Gagal dalam alokasi memori untuk copy array kata.\n");
            free(words);
            return 1;
        }

        // Alokasi memori untuk setiap kata di array copy
        for (int i = 0; i < data_size; i++) {
            words_copy[i] = malloc(MAX_WORD_LEN * sizeof(char));
            if (!words_copy[i]) {
                // Bebaskan semua memori yang sudah dialokasikan jika gagal
                for (int j = 0; j < i; j++) {
                    free(words_copy[j]);
                }
                free(words_copy);
                free(words);
                printf("Gagal dalam alokasi memori untuk kata copy.\n");
                return 1;
            }
        }

        load_words("../data/data_kata.txt", words, data_size);

        const char *sort_names[] = {
            "Bubble Sort (kata)", "Selection Sort (kata)", "Insertion Sort (kata)",
            "Merge Sort (kata)", "Quick Sort (kata)", "Shell Sort (kata)"
        };
        void (*sort_functions[])(char*[], int) = {
            bubbleSortKata, selectionSortKata, insertionSortKata,
            wrapperMergeSortKata, wrapperQuickSortKata, shellSortKata
        };

        for (int i = 0; i < 6; i++) {
            // Copy data kata
            copy_word_array(words_copy, words, data_size);
            
            start_time = clock();
            sort_functions[i](words_copy, data_size);
            end_time = clock();
            
            duration = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
            printf(" %-37s  %-30.3f  %-31.2f \n", sort_names[i], duration, sizeof(char) * data_size * MAX_WORD_LEN / (1024.0 * 1024.0));
        }

        // Pembebasan memori
        for (int i = 0; i < data_size; i++) {
            free(words[i]);
            free(words_copy[i]);
        }
        free(words);
        free(words_copy);
    }

    print_footer();
    return 0;
}