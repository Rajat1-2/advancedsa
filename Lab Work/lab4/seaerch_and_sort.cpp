#include<bits/stdc++.h>
using namespace std;



void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;  
    int n2 = r - m;       

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}



void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}


void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        swap(arr[i], arr[minIndex]);
    }
}



bool linearSearch(vector<int>&arr,int target){
    for(int i=0;i<arr.size();i++){
        if(target==arr[i]){
            // cout << "Target found at index : " << i;
            // break;
            return true;
        }
    }
    return false;

}

bool binarySearch(vector<int>&arr,int target){
    int choice;
    cout << "\nSort Operations:\n";
    cout << "1. Insertion Sort\n";
    cout << "2. Selection Sort\n";
    cout << "3. Merge Sort\n";
    
    cin >> choice;
    if(choice==1){
        insertionSort(arr);
    }
    else if(choice==2){
        selectionSort(arr);
    }
    else if(choice==3){
        mergeSort(arr,0,arr.size()-1);
    }

    int low=0;
    int high=arr.size()-1;
    while(low<=high){
        int mid=low+(mid-low)/2;
        if(arr[mid]==target){
            // cout << "Target found at index : " << mid;
            return true;
            // break;
        }
        else if(arr[mid]> target){
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    }
    return false;
    

 
}

int main(){
    int n;
    cout << "Enter no of ele: ";
    cin >> n;
    
    // cout << endl;
    vector<int>arr(n);
    for(int i=0;i<n;i++){
        cin >> arr[i];
        // cout << "hii";
    }
    int target;
    cout << "Enter target : " ;
    cin >> target;

    int choice;
    
    cout << "\nSearch Operations:\n";
    cout << "1. Linear Search\n";
    cout << "2. Binary Search\n";
    cin >> choice;
    cout << endl;
    bool ans=false;

    if(choice==1){
        ans= linearSearch(arr,target);
    }
    else if (choice==2){
        ans= binarySearch(arr,target);
    }

    // cout << ans;
    if(ans==true){
        cout << "Element found !!!";
    }
    else{
        cout << " oops!! not found";
    }
    return 0;


    
    
    
}