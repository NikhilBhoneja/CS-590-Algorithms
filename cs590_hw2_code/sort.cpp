#include <cstdio>
#include <cstdlib>
#include "sort.h"

int string_compare(char* s1, char *s2)
{ 
/*
 * We assume that s1 and s2 are non-null pointers
 */
  int i;

  i = 0;
  while ((s1[i] != 0) && (s2[i] != 0) && (s1[i] == s2[i]))
    i++;

  if (s1[i] == s2[i])
    return 0;
  else
    {
      if (s1[i] < s2[i])
	return -1;
      else
	return 1;
    }
} /*>>>*/

/* This is the simple insertion sort */

void insertion_sort(char** A, int l, int r)
{ 
	int i;
  	char* key;
  	for (int j = l+1; j <= r; j++)
    	{
      	key = A[j];
      	i = j - 1;
      	while ((i >= l) && (string_compare(A[i], key) > 0))
        {
		A[i+1] = A[i];
 		i = i - 1;
	}
     	A[i+1] = key;
    	}
}

/* This is insertion sort for digits */

void insertion_sort_digit(char** A, int* A_len, int l, int r, int d)
{
	int i;
  	char* key;
  	for(int j=l+1; j<=r; j++)
  	{
   		key = A[j];   
    		i = j-1;
    	while(( i>=l ) && (string_compare( A[i],key)>0 ) )
    	{
      		A[i+1]= A[i];
      		A_len[i+1]=A_len[i];
      		i= i-1;
    	}
   	A[i+1]=key;
   	A_len[i+1]=d;
  	}
}

/* This is counting sort for digits */

void counting_sort_digit(char** A, int* A_len, char** B, int* B_len, int n, int d)
{
	int max = 256;
        int *arrc  = new int[max];
        for(int i = 0; i<=max; i++)
        {
        	arrc [i] = 0;
        }
        for(int i = 0; i < n; i++)
        {
        	if(d>A_len[i]){
          	arrc [0]++;
        }
        else
        {
          	arrc[A[i][d-1]]++;
        }
        }
        for(int i = 1; i<=max; i++)
        { 
        	arrc[i] += arrc[i-1];
        }
        for(int i = n-1; i>=0; i--)
        {
        	if(d<=A_len[i]){
          	B[arrc [A[i][d-1]]-1] = A[i];
          	B_len[arrc[A[i][d-1]]-1] = A_len[i];
          	arrc[A[i][d-1]] -= 1;
        }
        else
        {
          	B[arrc [0]-1] = A[i];
          	B_len[arrc [0]-1] = A_len[i];
          	arrc [0] -= 1;
        }
        }
        for(int i = 0; i<n; i++)
        {
        	A[i] = B[i];
        	A_len[i] = B_len[i];
        }
        delete[] arrc ;
}

/* This method perform radix sort using insertion sort for digits*/

void radix_sort_is(char** A, int* A_len, int n, int m)
{ 
	for (int i=m; i>0; i--)
	{
    		insertion_sort_digit(A,A_len, 0, n-1, i);
  	}
}

/* This method performs radix sort using counting sort for digits */

void radix_sort_cs(char** A, int* A_len, int n, int m)
{ 
	char** arr = new char*[n];
	int* len = new int[n];
	for(int i=m;i>0;i--)
	{
		counting_sort_digit(A,A_len,arr,len,n,i);		
	}
	delete[] arr;
	delete[] len;
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */

bool check_sorted(char** A, int l, int r)
{
	for (int i = l+1; i < r; i++)
    	if (string_compare(A[i-1],A[i]) > 0)
     		return false;
  	return true;
}