#include <iostream>
using namespace std;

void mySort(int arr[], int n)
{
 //Implement this
    int temp;
    for(int i=0;i<n-1;i++) {
        for(int j=0;j<n-1;j++){
            if(arr[j]>arr[j+1]) {
                temp = arr[j+1];
                arr[j+1]=arr[j];
                arr[j]=temp;
            }
        }
    }
}

void printArray(int arr[], int size)
{
 //Implement this
    for(int i=0;i<size;i++){
        if(i==size-1) cout<<arr[i];
        else cout << arr[i] << " ";
    }
    
    
}

int main() {

    int arr[] = { 3, 1, 2, 5, 6, 7,10 };
    int n = sizeof(arr) / sizeof(arr[0]);
    mySort(arr, n);
    cout << "Sorted array: \n";
    printArray(arr, n);
    return 0;
}
