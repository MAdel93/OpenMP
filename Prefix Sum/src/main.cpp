#include <iostream>
#include <omp.h>
#include <stdio.h>

using namespace std;

int main () 
{ 
    long long sum = 0 ;
    long long n = 0;
    int i = 0;
    int id = 0;
    long long partial_sum=0;
    int nthreads=0;
    float time_var=0;
    cout << " [ -] please enter N : " ;
    cin >> n ;
    cout << " [ -] please enter Number of threads : " ;
    cin >> nthreads ;
    omp_set_num_threads(nthreads);
    #pragma omp parallel private (i, id, partial_sum)
    {
        
        //int nthreads=omp_get_num_threads();
        //printf("Total num of thread: %d", nthreads);
        //omp_set_num_threads(4);
        partial_sum = 0;
        id=omp_get_thread_num();
        auto s_time = omp_get_wtime();

        #pragma omp parallel for 
            for ( i =id; i <= n ; i = i+nthreads){
                partial_sum += i; 
                //printf("\n partial_sum %d = %d \n", id , partial_sum);
            }
                
        #pragma omp critical
            sum += partial_sum;
        
        
        auto e_time = omp_get_wtime();
        time_var = e_time - s_time;
        
    }
    printf("sum amount = %lld", sum);
    printf("\n time exe = %f",time_var );
    
    
    return (0);
} 