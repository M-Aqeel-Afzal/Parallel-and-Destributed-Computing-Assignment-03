#include <iostream>
#include<string.h>
#include<omp.h>
#include<stdio.h>
using namespace std;
// Roll number :i190650
// last digit = 0
int count_occurrence(string &whole, string &part)
{
	int str1=whole.length();
	int str2=part.length();
	int result = 0;
int j;
	
		#pragma omp parallel for   schedule(static,0) num_threads(9)
		for(int i=0;i<=str1-str2;i++)
		{
			cout<<"thread: "<<omp_get_thread_num()<<endl;
				for(j=0; j<str2;j++)
				{
					if(whole[i+j] != part[j])
					break;
				}
				
				if(j==str2)
					result++;

		}
return result;

}
int main()
{
string str1="ATTTGCGCAGACCTAAGCA";
string str2="GCA";
int tc= count_occurrence(str1,str2);
cout<<"Whole: "<<str1<<"     part: "<<str2<<"    Total occurences: "<<tc<<endl;

str1="AAABCDEFGAAGEREAANMT";
str2="AA";
tc= count_occurrence(str1,str2);
cout<<"Whole: "<<str1<<"     part: "<<str2<<"    Total occurences: "<<tc<<endl;
str1="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
str2="BTTT";
tc= count_occurrence(str1,str2);
cout<<"Whole: "<<str1<<"     part: "<<str2<<"    Total occurences: "<<tc<<endl;
return 0;
}
