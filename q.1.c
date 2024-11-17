#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 24
#define ROW_COUNT 8
#define COL_COUNT 3

// Function prototypes
void setArray(int arr[], int size);
int deleteElement(int arr[], int size, int index);
int addElement(int arr[], int size, int index, int value);
void reshapeArray(int arr[], int size, int matrix[ROW_COUNT][COL_COUNT]);
void printTranspose(int matrix[ROW_COUNT][COL_COUNT]);
bool containsDuplicate(int arr[], int size);
void printArray(const int arr[], int size);
void printMatrix(const int matrix[][COL_COUNT], int rows);

int main() {
    int array[MAX_SIZE];
    int matrix[ROW_COUNT][COL_COUNT];
    int currentSize = MAX_SIZE;

    // Set array values
    setArray(array, MAX_SIZE);
    printf("Initial array:\n");
    printArray(array, currentSize);

    // Deletes an element at a specific index
    int deleteIndex = 4; // Change the index
    currentSize = deleteElement(array, currentSize, deleteIndex);
    printf("\nArray after removing element at index %d:\n", deleteIndex);
    printArray(array, currentSize);

    // Adds an element at a specific index
    int insertIndex = 3; // Change the index
    int insertValue = 88; // Change the value
    currentSize = addElement(array, currentSize, insertIndex, insertValue);
    printf("\nArray after inserting %d at index %d:\n", insertValue, insertIndex);
    printArray(array, currentSize);

    // Reshapes an array into 2D matrix
    reshapeArray(array, MAX_SIZE, matrix);
    printf("\n2D matrix after reshaping:\n");
    printMatrix(matrix, ROW_COUNT);

    // Print matrix transpose
    printf("\nTranspose of the matrix:\n");
    printTranspose(matrix);

    // Check for duplicates
    if (containsDuplicate(array, currentSize)) {
        printf("\nThe array contains duplicates.\n");
    } else {
        printf("\nThe array does not contain duplicates.\n");
    }

    return 0;
}

// Function definitions
void setArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1; // Start from 1 instead of 0
    }
}

int deleteElement(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        printf("Invalid index: %d\n", index);
        return size; // No changes to size
    }

    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }

    return size - 1; // Decrease size after removal
}

int addElement(int arr[], int size, int index, int value) {
    if (index < 0 || index > size || size >= MAX_SIZE) {
        printf("Invalid index: %d or array is full.\n", index);
        return size; // No changes to size
    }

    for (int i = size; i > index; i--) {
        arr[i] = arr[i - 1];
    }

    arr[index] = value;
    return size + 1; // Increase size after insertion
}

void reshapeArray(int arr[], int size, int matrix[ROW_COUNT][COL_COUNT]) {
    if (size != ROW_COUNT * COL_COUNT) {
        printf("Error: Array size does not match matrix dimensions.\n");
        return;
    }

    for (int i = 0; i < ROW_COUNT; i++) {
        for (int j = 0; j < COL_COUNT; j++) {
            matrix[i][j] = arr[i * COL_COUNT + j];
        }
    }
}

void printTranspose(int matrix[ROW_COUNT][COL_COUNT]) {
    for (int j = 0; j < COL_COUNT; j++) {
        for (int i = 0; i < ROW_COUNT; i++) {
            printf("matrix[%d][%d] = %d\n", i, j, matrix[i][j]);
        }
        puts("");
    }
}

bool containsDuplicate(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                return true;
            }
        }
    }
    return false;
}

void printArray(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("array[%d] = %d\n", i, arr[i]);
    }
}

void printMatrix(const int matrix[][COL_COUNT], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < COL_COUNT; j++) {
            printf("matrix[%d][%d] = %d\n", i, j, matrix[i][j]);
        }
        puts("");
    }
}