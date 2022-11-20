#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int inner_product ( vector < int >& A , vector < int >& B , size_t & inner_product ) {
    // guard
    if ( A . size () != B . size () ) {
        return EXIT_FAILURE ;
    }
    auto N = A . size () ;
    inner_product = 0;
    int sum;
    int nthreads=8;
    omp_set_num_threads(nthreads);
    #pragma omp parllel private (i, id, sum) 
    {
        
        sum=0;
        //int nthreads=omp_get_num_threads();
        printf("num of threads= %d", nthreads);
        int id = omp_get_thread_num();
        
        // inner product computation
        #pragma omp parallel for
        for ( auto i = id; i < N ;  i = i+nthreads) {
            sum += A [ i ] * B [ i ];
            
            // printf("\n amount of sum thread %d for %d = %d", id, i ,sum);
        }
        printf("num of thread=%d",nthreads);
        #pragma omp critical
            inner_product += sum;
    }
    
    return EXIT_SUCCESS ;
}

int main () {
    size_t N ;
    cout << " [ -] please enter N : " ;
    // get N
    cin >> N ;
    vector < int > A ( N ) , B ( N ) ;
    // initialization ( could be anything )
    for ( auto i = 0; i < N ; ++ i ) {
        A [ i ] = i + 1;
        B [ i ] = N - ( i + 1) + 1;
    }
    auto s_time = omp_get_wtime();
    size_t product = 0;
    if ( inner_product ( A , B , product ) == EXIT_SUCCESS ) {
        auto e_time = omp_get_wtime();
        cout << " [ -] inner product computed successfully . " << endl ;
        cout << " [ -] inner product is " << product << endl ;
        cout << " [ -] measured execution time is " << e_time - s_time << " seconds . " <<
        endl ;
    }
    else {
        cout << " [ -] inner product computation failed . " << endl ;
    }
    return EXIT_SUCCESS ;
}

