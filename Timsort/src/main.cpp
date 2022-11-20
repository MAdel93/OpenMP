/*
*				In His Exalted Name
*	Title:	Pseudo-Timsort Sequential Code
*	Author: Ahmad Siavashi, Email: siavashi@aut.ac.ir
*	Date:	24/11/2015
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define MAX(A, B) ((A)>(B))?(A):(B)
#define MIN(A, B) ((A)<(B))?(A):(B)
#define NUM_THREADS 1



void printArray(int *array, long long size);
void fillArray(int *array, long long size);
void merge(int *a, long long n, long long m);
void mergeSort (int *a, long long n);
void insertionSort(int *a, long long n);


int main(int argc, char *argv[]){
	//-----------------------------------------------initialization----------------------------------------
	int *array = NULL;
	long long int size = 0;
	if(argc < 2){
		printf("[-] Invalid No. of arguments.\n");
		printf("[-] Try -> <size_of_array>\n");
		printf(">>> ");
		scanf("%lld", &size);
	}else{
		size = atoi(argv[1]);
	}
	array = (int *) malloc(sizeof(int) * size);
	//-------------------------------------------------start record runtime and fill array--------------------------
	auto s_time = omp_get_wtime();
	fillArray(array, size);(array, size);
	fillArray(array, size);
	//--------------------------------------------------call function and creat parallel region--------------------
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel
	{
		#pragma omp single nowait
			mergeSort (array, size);
	}	
	auto e_time = omp_get_wtime();
	//------------------------------------------------------print runtime----------------------------------
	printf("execution time is:%f\n",e_time-s_time);
	// TODO: Implement Pseudo-Timsort Algorithm
	
	free(array);
	system("PAUSE");
	return EXIT_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------subfunctions----------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fillArray(int *array, long long size){
	srand(time(NULL));
	while(size-->0){
		*array++ = rand() % 100;
	}
}

void printArray(int *array, long long size){
	while(size-->0){
		printf("%d, ", *array++);
	}
	printf("\n");
}

void insertionSort(int *a, long long n){
    int i, j, temp;
    for (i = 1; i < n; i++) {
        temp = a[i];
        for (j = i; j > 0 && temp < a[j - 1]; j--) {
            a[j] = a[j - 1];
        }
        a[j] = temp;
    }
}

void merge(int *a, long long n, long long m){
	int i, j, k;
    int *temp = (int *) malloc(n * sizeof (int));
    for (i = 0, j = m, k = 0; k < n; k++) {
        temp[k] = j == n   ? a[i++]
             : i == m      ? a[j++]
             : a[j] < a[i] ? a[j++]
             :               a[i++];
    }
    for (i = 0; i < n; i++) {
        a[i] = temp[i];
    }
    free(temp);
}

void mergeSort (int *a, long long n){
    int m;
	if (n < 64){
		insertionSort(a, n);
		return;
	}
    m = n / 2;
	#pragma omp task 
	mergeSort(a, m);
	#pragma omp task 
    mergeSort(a + m, n - m);
	#pragma omp taskwait
    merge(a, n, m);    
}