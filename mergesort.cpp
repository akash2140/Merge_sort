//This is merge sort program using a defined number of threads.
#include<iostream>
#include<pthread.h>
#define MAX 20 
#define THREAD_MAX 4 
using namespace std; 
  
 
int a[MAX]; 
int part = 0;
int n; 
void merge(int low, int mid, int high) 
{ 
    int left[mid - low + 1];  
    int right[high - mid]; 
  
   
    int n1=mid-low+1,n2=high-mid,i=0,j=0; 
  
    
    for (i = 0; i < n1; i++) 
        left[i]=a[i+low]; 
  
    
    for (i = 0; i < n2; i++) 
        right[i]=a[i+mid+1]; 
  
    int k = low;
    i=0,j=0; 
    
  
    
    while (i < n1 && j < n2) 
    { 
        if (left[i] <= right[j]) 
            a[k++] = left[i++]; 
        else
            a[k++] = right[j++]; 
    } 
    while (i < n1) { 
        a[k++] = left[i++]; 
    } 
  while (j < n2) { 
        a[k++] = right[j++]; 
    }
}

// merge sort function 
void merge_sort(int low, int high) 
{ 
    
    int mid = low + (high - low) / 2; 
    if (low < high) { 
  
         
        merge_sort(low, mid); 
  
        
        merge_sort(mid + 1, high); 
  
       
        merge(low, mid, high); 
    } 
} 


void* merge_sort1(void* arg) 
{ 
    
    int thread_part = part++; 
  
    
    int low = thread_part * (n / 4); 
    int high = (thread_part + 1) * (n / 4) - 1; 
  
    int mid = low + (high - low) / 2; 
    if (low < high) { 
        merge_sort(low, mid); 
        merge_sort(mid + 1, high); 
        merge(low, mid, high); 
    } 
} 


int main() 
{ 
   
    cout<<"\nENTER SIZE OF ARRAY";
    cin>>n;
    cout<<"\nENTER ELEMENTS OF ARRAY";
    for (int i = 0; i < n; i++) 
    {
    	cin>>a[i];
    }
    pthread_t threads[THREAD_MAX];
    for (int i = 0; i < THREAD_MAX; i++)
    { 
        pthread_create(&threads[i], NULL, merge_sort1, 
                                        (void*)NULL); 
                    
    }
    for (int i = 0; i < 4; i++) 
    {
        pthread_join(threads[i], NULL); 
    }
    merge(0, (n / 2 - 1) / 2, n / 2 - 1); 
    merge(n / 2, n/2 + (n-1-n/2)/2, n - 1); 
    merge(0, (n - 1)/2, n - 1); 
    cout<<"Sorted array: "; 
    for (int i = 0; i < n; i++)
    { 
        cout<<a[i]<< " "; 
        
    }

    
    
 }    
        
        
    
