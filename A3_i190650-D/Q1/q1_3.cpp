#include<iostream>
#include<omp.h>
#include<math.h>
using namespace std;
int prime(long long num)
{
bool A[num+1];
int sr=sqrt(num);

for(int p = 2; p<=num;p++)
{
	A[p]=p;
}
#pragma omp parallel for   schedule(guided,4) num_threads(9)
for(int p = 2; p<=sr;p++)
{
	if(A[p] != 0 )
	{
		int j = p*p;
		while(j<=num)
		{
			A[j]=0;
			j=j+p;
		}

	}
}
int i =0,l=0;
for(int p=num;p>=2;p--)
{
	if(A[p]!=0)
	{
		l=p;
		break;
	}
}
return l;
}
int main()
{
double total_time = 0.0;
clock_t start=clock();
cout<<"Largest possible prime number: "<<prime(7999999)<<endl;
clock_t end=clock();
total_time +=(double)(end-start)/CLOCKS_PER_SEC;
cout<<"Total time of execution: "<<total_time<<endl;
return 0;
}
