
#include <iostream>
#include <cmath>
#include <omp.h>
using namespace std;

void gen_numbers(long int[], long int);
int count_prime(long int[], long int, int, double*);
bool is_prime(long int);

int main(int argc, char* argv[])
{
	long int n = 1000000; // size of array
	long int* numbers = new long int[n]; // allocating heap memory for array
	int threads = atoi(argv[1]);
	int count; // declaring variables
	double t = 0;
	double* time = &t;
	
	gen_numbers(numbers, n); // generating elements of array
	count = count_prime(numbers, n, threads, time); // counting prime numbers within elements of array
	
	cout << "Total number of primes: " << count << endl; // printing number of prime elements in array;
	cout << "That took " << *time << " seconds!" << endl; // printing time process took.
	cout << "Each thread took " << *time/threads << " seconds!" << endl; // printing time each thread took to perform task.
	
	delete numbers, time; // deallocating heap memory to prevent leaks
	
	return 0;
	
}

void gen_numbers(long int numbers[], long int size)
{
	for (int i = 0; i < size; i++)
		numbers[i] = i;
}

int count_prime(long int numbers[], long int size, int t, double* time)
{
	int count = 0;
	double start = omp_get_wtime();
	# pragma omp parallel for reduction(+: count) num_threads(t) // setting reduction operator to + and variable to count
	for (int i = 0; i < size; i++) // iterating through the array
		if (is_prime(numbers[i])) // checking if element is prime
			count++; // incrementing variable
	double end = omp_get_wtime();
	*time = end - start;
	return count;
}

bool is_prime(long int n)
{
	if (n < 2) // base case
		return false;
	for (int i = 2; i < sqrt(n); i++) // iterating through factors of n
	{
		if (n % i == 0) // checking if i is a factor of n
			return false;
	}
	return true;
}