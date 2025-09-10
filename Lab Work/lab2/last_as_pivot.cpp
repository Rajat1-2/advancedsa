#include<bits/stdc++.h>
using namespace std;

int inpartition(vector<int>&vec,int low,int high){
    int pivot=vec[high];
    

    int i=low-1;
    for(int j=low;j<high;j++){
        if(vec[j]<=pivot)
        {
           i++;
           swap(vec[i],vec[j]);
        }
    }
    swap(vec[i+1],vec[high]);
    return i+1;


}
int desendingpartition(vector<int>&vec,int low,int high){
    int pivot=vec[high];
    

    int i=low-1;
    for(int j=low;j<high;j++){
        if(vec[j]>=pivot)
        {
           i++;
           swap(vec[i],vec[j]);
        }
    }
    swap(vec[i+1],vec[high]);
    return i+1;


}



void quicksort(vector<int>&vec,int low,int high){

  if(low<high){
      int partion=inpartition(vec,low,high);
    //   desending sort
    //   int partion=desendingpartition(vec,low,high);

      quicksort(vec,low,partion-1);
      quicksort(vec,partion+1,high);
  }
}


int main(){

    int n;
    cout << "no of elements in arr : ";
    cin >> n;

    vector<int>vec(n,0);
    int ele;
    for(int i=0;i<n;i++){
        cin >> vec[i];
        
    }

    quicksort(vec,0,n-1);

    for(int i=0;i<n;i++){
        cout << vec[i] << "  ";
    }
    
    return 0;
}