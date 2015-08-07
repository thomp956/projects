
#include <iostream>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>

using namespace std;

/** \brief Heapifies an array
*	\param int* array
*	\param int i
*	\param int size
*/
void heapify(int* array, int i, int size)
{
	// Setup left, right, and smallest
	int l = i*2; int r = (i*2)+1; int smallest;
	
	// See if left is smallest
	if(l <= size && array[l]<array[i])
	{
		smallest = l;	
	} else 
	{
		smallest = i;
	}
	
	// See if right is smallest
	if(r <= size && array[r]<array[smallest])
	{
		smallest = r;
	}
	
	// Check smallest
	if(smallest != i)
	{
		int temp = array[i];
		array[i] = array[smallest];
		array[smallest] = temp;
		heapify(array, smallest, size);
	}
	
}

/** \brief Builds a heap out of a given array
*	\param int* array
*	\param int size
*/
void buildHeap(int* array, int size)
{
	for(int i=(size/2); i > 0; i--)
	{
		heapify(array, i, size);
	}	
}


// short integer random number generator from stdlib
int rand(void); 

int main()
{ 
  int size;
  cout << endl << "How many elements in the input array ";  cin >> size;
  int* dataArray = new int [size + 1];   // get array of right size (with invisible 0th element)
 
  // fill array -- fill 0th element but don't show it.
  for (int k=0; k< size+1 ; k++)  dataArray[k] = rand();
  //for (int k=0; k< size+1 ; k++)  dataArray[k] = size -k;
  cout<<"Input array:\n";
  for (int k=1; k<size+1; k++)
    cout<<dataArray[k]<<" ";
  cout<<endl;
 
  buildHeap(dataArray, size);     
          
  //show heap (but not ignored 0th element)
  cout<<"Heap built from the input array:\n";
  for (int k=1; k<size+1; k++)
    cout<<dataArray[k]<<" ";
  cout<<endl;

}