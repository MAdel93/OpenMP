#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void SieveOfEratosthenes(int lenght, int numthread)
{
	vector<bool> prime(lenght + 1, true);
	//-----------------------------------------------create parallel region
    #pragma omp parallel num_threads(numthread)
	{
		vector<bool> Pprime(lenght + 1, true);
        int id = omp_get_thread_num();
		for (int p = id + 2; p*p <= lenght; p=p+numthread)
        {
            if (Pprime[p] == true)
		    for (int i = p * 2; i <= lenght; i += p)
			    Pprime[i] = false;
        }
        #pragma omp critical
		{

			for (int p = 2; p <= lenght; p++)
				prime[p] = prime[p] && Pprime[p];
		}
	}          
	//------------------------------------------------------print number of prime                                                                                                                                                                                                                                                                                                                                                                                                                            
	for (int p = 2; p <= lenght; p++)
        {
            if (prime[p])
			cout << p << " ";
        }
}

int main()
{
	//------------------------------------------------initialization
	int lenght, numthread;
	cout << "Enter lenght";
	cin >> lenght;
	cout << "Enter number of threads";
	cin >> numthread;
	cout << "Following are the prime numbers smaller "
		<< " than or equal to " << lenght << endl;
	//---------------------------------------------------Call prime producer function
	auto s_time = omp_get_wtime();
	SieveOfEratosthenes(lenght,numthread);
	auto e_time = omp_get_wtime();
	//-------------------------------------------------------print Run-Time
	cout << "the execution time " << e_time - s_time << "\n";
	cout << "\n";
	return 0;
}
