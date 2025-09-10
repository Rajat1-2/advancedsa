#include<bits/stdc++.h>
using namespace std;


int randomIdx(int s, int e)
//returns random element not index
{
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distrib(s, e);

    int random_number = distrib(gen);
    return random_number;
}

int inpartition(vector<int>&vec,int low,int high){
    int random= randomIdx(low,high);
    swap(vec[random],vec[high]);
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




// median of three as pivot 
int inthreepartition(vector<int> &vec, int low, int high) {
    vector<int> rndIdx(3);
    for (int i = 0; i < 3; i++) {
        // randomidx return  random element 
        rndIdx[i] = randomIdx(low, high);
    }

    sort(rndIdx.begin(), rndIdx.end());
    int median = rndIdx[1]; 

    swap(vec[median], vec[high]);

    int pivot = vec[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[i + 1], vec[high]);
    return i + 1;
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