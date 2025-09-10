

#include<bits/stdc++.h>
using namespace std;


int inthreepartition(int low, int high, vector<int>& arr) {
    int rand1 = low + rand() % (high - low + 1);
    int rand2 = low + rand() % (high - low + 1);
    int rand3 = low + rand() % (high - low + 1);

    vector<pair<int,int>> picks = {
        {arr[rand1], rand1},
        {arr[rand2], rand2},
        {arr[rand3], rand3}
    };
    sort(picks.begin(), picks.end());
    int medianIndex = picks[1].second;

    swap(arr[medianIndex], arr[high]);
    return partitionAscHighAsPivot(low, high, arr);
}


void quicksort(vector<int>&vec,int low,int high){

  if(low<high){
    //   int partion=inpartition(vec,low,high);
      int partion=inthreepartition(vec,low,high);

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