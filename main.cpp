//
//  main.cpp
//  Recitation2
//
//  Created by Augustus Crosby on 6/2/19.
//  Copyright © 2019 Augustus Crosby. All rights reserved.
//

#include <iostream>
#include <random>

using namespace std;

void swap(double *a, double *b);
void insertionSort(double A[]);
void merge(double A[], int l, int m, int r);
void mergeSort(double A[], int l, int r);
int partition(double A[], int l, int r);
void quickSort(double A[], int l, int r);
void selectionSort(double A[]);
int n; // length of A[]


int main(int argc, const char * argv[]) {
    n = 150000; // input different values
    double A[150000]; // input here too
    
    
    // put random numbers inside
    for (int i = 0; i < n; i++){
        
        // help from https://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c
        double lowBound = 100.00;
        double uppBound = 1000.00;
        uniform_real_distribution<double> unif(lowBound,uppBound);
        default_random_engine re;
        A[i] = unif(re);
    }
    // timer help from https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
    auto start = chrono::high_resolution_clock::now();
    
    //insertionSort(A); // change this when needed
    //mergeSort(A, 0, n - 1);
    //quickSort(A, 0, n - 1);
    selectionSort(A);
    
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    
    cout << "Time taken to sort: " << duration.count() << " microseconds\n" << endl;
    
    /*for (int i = 0; i < n; i++){
        cout << A[i] << " ";
    }*/
    
    return 0;
}
void swap(double *a, double *b){
    double temp = *a;
    *a = *b;
    *b = temp;
}

void insertionSort(double A[]){
    for (int j = 1; j < n; j++){
        double key = A[j];
        int i = j - 1;
        while (i >= 0 && A[i] > key){ // have to change some of the code bc the book starts at 1
            A[i+1] = A[i];              //instead of starting at 0.
            i = i - 1;
        }
        A[i+1] = key;
    }
}

void merge(double A[], int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    
    double L[n1];
    double R[n2];
    
    for (i = 0; i < n1; i++){
        L[i] = A[l+i];
    }
    for (j = 0; j < n2; j++){
        R[j] = A[m+1+j];
    }
    
    i = 0;
    j = 0;
    k = 0;
    
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[i];
            j++;
        }
        k++;
    }
    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(double A[], int l, int r){
    int m;
    
    if (l < r){
        m = (l + r)/2;
        
        mergeSort(A, l, m);
        mergeSort(A, m + 1, r);
        merge(A, l, m, r);
    }
}

int partition(double A[], int l, int r){
    int x = r; // pivot
    
    int i = l - 1;
    
    for (int j = l; j < r - 1; j++){
        if (A[j] <= x){
            i++;
            swap(&A[i], &A[j]);
        }
    }
    swap(A[i+1], A[r]);
    return i + 1;
}

void quickSort(double A[], int l, int r){
    if (l < r) {
        int m = partition(A, l, r);
        
        quickSort(A, l, m - 1);
        quickSort(A, m + 1, r);
    }
}

void selectionSort(double A[]){
    int min;
    
    for (int i = 1; i < n - 1; i++){
        min = i;
        for (int j = i + 1; j < n; j++){
            if (A[i] < A[min]){
                min = j;
            }
        }
        swap(&A[min], &A[i]);
    }
}
