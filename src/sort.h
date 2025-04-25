#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================
// Prototype Fungsi Sorting
// ============================

// Bubble Sort
void bubbleSortAngka(int arr[], int n);
void bubbleSortKata(char* arr[], int n);

// Selection Sort
void selectionSortAngka(int arr[], int n);
void selectionSortKata(char* arr[], int n);

// Insertion Sort
void insertionSortAngka(int arr[], int n);
void insertionSortKata(char* arr[], int n);

// Quick Sort
int partitionAngka(int arr[], int low, int high);
void quickSortAngka(int arr[], int low, int high);
int partitionKata(char* arr[], int low, int high);
void quickSortKata(char* arr[], int low, int high);

// Merge Sort
void mergeAngka(int arr[], int l, int m, int r);
void mergeSortAngka(int arr[], int l, int r);
void mergeKata(char* arr[], int l, int m, int r);
void mergeSortKata(char* arr[], int l, int r);

// Shell Sort
void shellSortAngka(int arr[], int n);
void shellSortKata(char* arr[], int n);

// ============================
// Implementasi Bubble Sort
// ============================

// Angka
void bubbleSortAngka(int arr[], int n) {
    int temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Kata
void bubbleSortKata(char* arr[], int n) {
    char* temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (strcmp(arr[j], arr[j+1]) > 0) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// ============================
// Selection Sort
// ============================

// Angka
void selectionSortAngka(int arr[], int n) {
    int minIdx, temp;
    for (int i = 0; i < n-1; i++) {
        minIdx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

// Kata
void selectionSortKata(char* arr[], int n) {
    int minIdx;
    char* temp;
    for (int i = 0; i < n-1; i++) {
        minIdx = i;
        for (int j = i+1; j < n; j++) {
            if (strcmp(arr[j], arr[minIdx]) < 0) {
                minIdx = j;
            }
        }
        temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

// ============================
// Insertion Sort
// ============================

// Angka
void insertionSortAngka(int arr[], int n) {
    int key, j;
    for (int i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Kata
void insertionSortKata(char* arr[], int n) {
    char* key;
    int j;
    for (int i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && strcmp(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// ============================
// Quick Sort
// ============================

// Angka
int partitionAngka(int arr[], int low, int high) {
    int pivot = arr[high], temp;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }
    temp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = temp;
    return (i + 1);
}

void quickSortAngka(int arr[], int low, int high) {
    // Menggunakan iterasi untuk menghindari stack overflow pada ukuran besar
    if (low < high) {
        // Untuk dataset besar, batasi kedalaman rekursi
        if (high - low < 1000) {
            int pi = partitionAngka(arr, low, high);
            quickSortAngka(arr, low, pi - 1);
            quickSortAngka(arr, pi + 1, high);
        } else {
            // Gunakan iterative approach untuk dataset besar
            int *stack = malloc((high - low + 1) * sizeof(int));
            if (!stack) {
                perror("Gagal mengalokasikan memori untuk stack quick sort");
                exit(EXIT_FAILURE);
            }
            
            int top = -1;
            
            stack[++top] = low;
            stack[++top] = high;
            
            while (top >= 0) {
                high = stack[top--];
                low = stack[top--];
                
                int pi = partitionAngka(arr, low, high);
                
                if (pi - 1 > low) {
                    stack[++top] = low;
                    stack[++top] = pi - 1;
                }
                
                if (pi + 1 < high) {
                    stack[++top] = pi + 1;
                    stack[++top] = high;
                }
            }
            
            free(stack);
        }
    }
}

// Kata
int partitionKata(char* arr[], int low, int high) {
    char* pivot = arr[high];
    int i = (low - 1);
    char* temp;
    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSortKata(char* arr[], int low, int high) {
    // Menggunakan iterasi untuk menghindari stack overflow pada ukuran besar
    if (low < high) {
        // Untuk dataset besar, batasi kedalaman rekursi
        if (high - low < 1000) {
            int pi = partitionKata(arr, low, high);
            quickSortKata(arr, low, pi - 1);
            quickSortKata(arr, pi + 1, high);
        } else {
            // Gunakan iterative approach untuk dataset besar
            int *stack = malloc((high - low + 1) * sizeof(int));
            if (!stack) {
                perror("Gagal mengalokasikan memori untuk stack quick sort kata");
                exit(EXIT_FAILURE);
            }
            
            int top = -1;
            
            stack[++top] = low;
            stack[++top] = high;
            
            while (top >= 0) {
                high = stack[top--];
                low = stack[top--];
                
                int pi = partitionKata(arr, low, high);
                
                if (pi - 1 > low) {
                    stack[++top] = low;
                    stack[++top] = pi - 1;
                }
                
                if (pi + 1 < high) {
                    stack[++top] = pi + 1;
                    stack[++top] = high;
                }
            }
            
            free(stack);
        }
    }
}

// ============================
// Merge Sort
// ============================

// Angka
void mergeAngka(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1, n2 = r - m;
    
    // Alokasi memori dinamis untuk menghindari stack overflow
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    
    if (!L || !R) {
        if (L) free(L);
        if (R) free(R);
        perror("Gagal mengalokasikan memori untuk merge sort");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    i = j = 0; k = l;
    while (i < n1 && j < n2) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    
    free(L);
    free(R);
}

void mergeSortAngka(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortAngka(arr, l, m);
        mergeSortAngka(arr, m + 1, r);
        mergeAngka(arr, l, m, r);
    }
}

// Kata
void mergeKata(char* arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1, n2 = r - m;
    
    // Alokasi memori dinamis untuk menghindari stack overflow
    char **L = malloc(n1 * sizeof(char*));
    char **R = malloc(n2 * sizeof(char*));
    
    if (!L || !R) {
        if (L) free(L);
        if (R) free(R);
        perror("Gagal mengalokasikan memori untuk merge sort kata");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    i = j = 0; k = l;
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    
    free(L);
    free(R);
}

void mergeSortKata(char* arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortKata(arr, l, m);
        mergeSortKata(arr, m + 1, r);
        mergeKata(arr, l, m, r);
    }
}

// ============================
// Shell Sort
// ============================

// Angka
void shellSortAngka(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i], j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Kata
void shellSortKata(char* arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            char* temp = arr[i];
            int j;
            for (j = i; j >= gap && strcmp(arr[j - gap], temp) > 0; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

#endif // SORT_H