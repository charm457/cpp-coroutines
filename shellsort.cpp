
#include <iostream>
#include <vector>

using namespace std;

void sortshell(vector<int>& arr, int size, int shag){
    for(;shag > 0; shag--){
        for(int i = 0; i < size; i++){
            int j = i;
            
            while(j + shag < size && arr[j] > arr[j + shag]){
                swap(arr[j], arr[j + shag]);
                j += shag;  
            }
        }
    }
}

int main(){
    vector<int> array = {5,3,2,4,9};
    sortshell(array,5,2);
    for(auto a:array){
        cout << a << ' ';
    }
    cout << endl;
    return 0;
}