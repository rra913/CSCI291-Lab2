#include<stdio.h>
#include <stdbool.h>

#define SIZE 24
#define nRows 8
#define nCols 3

// PROTOTYPES
void print_array(int array[], int length);
void print_matrix(int mat[][nCols], int rows);

void set_array(int arr[], int length);
void rem_align(int arr[], int length, int pos);
void insert_align(int arr[], int length, int pos, int value);
void reshape(int arr[], int length, int arr2d[nRows][nCols]);
void print_trans_matrix(int arr2d[nRows][nCols]);
bool found_duplicate(int arr[], int length);
void flip (int arr[], int length);

int main(void) {
    int arr[SIZE];
    int arr2d[nRows][nCols];

    printf("1. set_array\n");
    set_array(arr, SIZE);
    print_array(arr, SIZE);

    printf("\n2. rem_align\n");
    rem_align(arr, SIZE, 7);
    print_array(arr, SIZE);

    printf("\n3. insert_align\n");
    insert_align(arr, SIZE, 7, 1);
    print_array(arr, SIZE);

    printf("\n4. reshape\n");
    reshape(arr, SIZE, arr2d);
    print_matrix(arr2d, nRows);

    printf("\n5. print_trans_matrix\n");
    print_trans_matrix(arr2d);

    printf("\n6. found_duplicate\n");
    bool val = found_duplicate(arr, SIZE);
    (val == true) ? printf("Duplicate Found\n") : printf("Duplicate Not Found\n");

    printf("\n7. flip\n");
    flip (arr, SIZE);
    print_array(arr, SIZE);
}

void print_array(int array[], int length){
    for(int i=0;i<length; i++)
        printf("array[%d]= %d\n", i, array[i]);
}

void print_matrix(int mat[][nCols], int rows){
   for(int i=0;i<rows; i++){
    for(int j=0;j<nCols; j++)
         printf("mat[%d][%d]= %d\n", i,j, mat[i][j]);
    puts("");
   }
}

//FUNCTION DEFINITIONS
void set_array(int arr[], int length) {
    //Sets an element of an array to its index position
    for (int i = 0; i < length; i++) {
        arr[i] = i;
    }
    return;
}

void rem_align(int arr[], int length, int pos) {
    // Checks if the input is valid
    if (pos > length-1) {
        printf("Invalid Position.\n");
        return;
    }

    // Declaring a variable to store the last element of array
    int last_element = arr[length-1];

    // Setting all elements after index pos to the element next to it
    for (int i = pos; i < length-1; i++) {
        arr[i] = arr[i+1];
    }

    // Sets the last element of the array to variable last_element
    arr[length-1] = last_element;

    return;
}

void insert_align(int arr[], int length, int pos, int value) {
    // Checks if the input is valid
    if (pos > length-1) {
        printf("Invalid Length.\n");
        return;
    }

    // Setting all elements after index pos to the element before i
    for (int i = length; i > pos; i--) {
        arr[i] = arr[i-1];
    }

    // Sets the element at index pos to value
    arr[pos] = value;

    return;
}

void reshape(int arr[], int length, int arr2d[nRows][nCols]) {
    // Checks if the input is valid
    if (length != nRows*nCols) {
        printf("Invalid Input!\n");
        return;
    }

    // Declaring a variable to store the index position of arr in the loop
    int arr_index = 0;

    // Sets the element in arr to arr2d row by row
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            arr2d[i][j] = arr[arr_index];
            arr_index++;
        }
    }
    return;
}

void print_trans_matrix(int arr2d[nRows][nCols]) {
    // Prints the matrix with the columns printed as rows and the rows printed as columns
    for(int i = 0; i < nCols; i++) {
        for(int j = 0; j < nRows; j++) {
            printf("%d ", arr2d[j][i]);
        }
        printf("\n");
    }
}

bool found_duplicate(int arr[], int length) {
    // Loop runs till all elements are checked
    for (int i = 0; i < length; i++) {
        // Loop runs to to check elements after index i
        for (int j = 0; j < i; j++) {
            // Returns true if a duplicate element is found
            if (arr[j] == arr[i]) {
                return true;
            }
        }
    }
    return false;
}

void flip(int arr[], int length) {
    // Declares an array to copy elements of arr
    int dupArr[length];

    // Copies elements of arr to dupArray
    for (int i = 0; i < length; i++) {
        dupArr[i] = arr[i];
    }

    // Sets element of arr at index i to the element of dupArray at length-i
    for (int i = 0; i < length; i++) {
        arr[i] = dupArr[(length-1)-i];
    }
}