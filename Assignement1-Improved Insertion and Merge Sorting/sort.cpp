#include <cstdio>
#include <cstdlib>
#include <limits>
#include "sort.h"
#include "math.h"

int ivector_length(int* v, int n)
{
  int sum;

  sum = 0;
  for (int i = 0; i < n; i++)
  {
    sum += (v[i] < 0) ? -v[i] : v[i];
  }

  return sum;
}

int * arrayOfvectorLengths(int** A, int r,int n)
{
    int* temp = new int[r+1];
    for( int j=0;j<=r;j++) {
        temp[j]= ivector_length(A[j],n);
    }
    return temp;
}


/*
 * insertion sort
 */
 
 void insertion_sort(int** A, int n, int l, int r)
{ 
  int i;
  int* key;

  for (int j = l+1; j <= r; j++)
    {
      key = A[j];
      i = j - 1;

      while ((i >= l) && (ivector_length(A[i], n) > ivector_length(key, n)))
        {
	  A[i+1] = A[i];
	  i = i - 1;
	}

      A[i+1] = key;
    }
}


/*
*   TO IMPLEMENT: Improved Insertion Sort
*/

void insertion_sort_im(int** A, int n ,int l, int r)
{
    int i, j, check; 
    int* key;
    int* temp = arrayOfvectorLengths(A,r,n);
 
    for (i = l+1; i <= r; i++) {
    
    	key = A[i];
    	check = temp[i];
        j = i - 1;
        
        while (j >= 0 && (temp[j] > check)) {
            temp[j+1] = temp[j];
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
        temp[j+1] = check;
    }
    delete[] temp;
}

/*
*   TO IMPLEMENT: Improved Merge Sort 
*/

void merge_s2(int** A, int* len, int s, int m, int r, int n)
{
    int x = m - s +1;
    int y = r - m;

    
    int* L = new int[x+1];
    int* R = new int[y+1];
    int** LA= new int*[x];
    for(int i=0; i < x; ++i ){
        LA[i] = new int[n];
        L[i] = len[s+i];
        LA[i] = A[s+ i];
    }
    int** RA = new int* [y];
    for(int j=0; j<y; ++j) {
        RA[j]= new int[n];
        R[j]= len[m + j +1 ];

        
        RA[j] = A[m+j+1];
    }
    L[x] = std::numeric_limits<int>::max();
    R[y] = std::numeric_limits<int>::max();
    
    int i=0;
    int j=0;
    
    for(int k=s; k<= r; k++){
        if(L[i] <= R[j]) {
            len[k] = L[i];
            A[k] = LA[i];
            i = i+1;
        }
        else {
            len[k] = R[j];
            A[k] = RA[j];
            j=j+1;
        }
    }
    delete[] L;
    delete[] R;
}
void merge_s1(int** A, int *len, int s,int r,int n)
{
    int m;
    if(s<r)
    {
        m = floor((s + r)/2);

        
        merge_s1(A, len, s, m, n);
        merge_s1(A, len, m+1, r, n);

        merge_s2(A, len, s, m, r, n);
    }
}
void merge_sort(int** A, int n, int s, int r)
{
    int* len = arrayOfvectorLengths(A,r,n);
    merge_s1(A,len,s,r,n);
    delete [] len;

}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(int** A, int n, int l, int r)
{
  for (int i = l+1; i <= r; i++)
    if (ivector_length(A[i-1], n) > ivector_length(A[i], n))
      return false;
  return true;
}


/*
 * generate sorted/reverse/random arrays of type hw1type
 */
int** create_ivector(int n, int m)
{
  int** iv_array;

  iv_array = new int*[m];
  for (int i = 0; i < m; i++)
    iv_array[i] = new int[n];

  return iv_array;
}

void remove_ivector(int** iv_array, int m)
{
  for (int i = 0; i < m; i++)
    delete[] iv_array[i];
  delete[] iv_array;
}

int** create_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = (i+j)/n;

  return iv_array;
}

int** create_reverse_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = ((m-i)+j)/n;

  return iv_array;
}

int** create_random_ivector(int n, int m, bool small)
{
  random_generator rg;
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      {
	rg >> iv_array[i][j];
	if (small)
	  iv_array[i][j] %= 100;
	else
	  iv_array[i][j] %= 65536;
      }

  return iv_array;
}