#include <iostream>
using namespace std;

int main(int arr, char* arr[])
{
    for(int i=arr-1; i>0; i--)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    return 0;
}
