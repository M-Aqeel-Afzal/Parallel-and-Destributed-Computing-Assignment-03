#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
#include<iostream>
using namespace std;
// Roll number :i190650
// last digit = 0
void PRIMES(long long num)
{
	bool A[num+1];
	memset(A,true,sizeof(A));
	int sr=sqrt(num);
	#pragma omp parallel for   schedule(dynamic,0) num_threads(9)
	for(int i=2;i<=sr;i++)
	{
			if(A[i] == true)
			{
				for(int j = i*i; j<=num; j+=i)
					A[j]=false;

			}
	}

	for(int i=num;i>=2;i--)
	{
		if(A[i])
		{
			printf("largest possible prime number: %d\n ", i);
			break;
		}
	}

}

int main()
{
long long num =1999999;

double total_time = 0.0;
clock_t start=clock();
PRIMES(num);
clock_t end=clock();
total_time +=(double)(end-start)/CLOCKS_PER_SEC;
cout<<"Total time of execution: "<<total_time<<endl;
return 0;
}
