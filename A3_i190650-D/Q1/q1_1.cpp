#include<stdio.h>
#include<iostream>
#include<omp.h>
#include<stdbool.h>
using namespace std;
// Roll number :i190650
// last digit = 0
bool prime(long long  num)
{
bool is_prime = true;
#pragma omp parallel for schedule(dynamic, 0) num_threads(9)
	for(long long i = 2; i <=num/2; i++)
	{

		
		if(num%i==0)
		{

		is_prime=false;
		
		}
	
	}
return is_prime;
}
int main( int argc, char* argv[])
{

long long  num = 7999993;

double total_time = 0.0;
clock_t start=clock();
bool flag=prime(num);
clock_t end=clock();
total_time +=(double)(end-start)/CLOCKS_PER_SEC;
cout<<"Total time of execution: "<<total_time<<endl;

if(flag)
cout<<"prime\n";
else
cout<<"not prime\n";


}


