#include <bits/stdc++.h>
using namespace std;

int partition(vector<int>& vec, int low, int high) {
    int pivot = vec[low];  
    int i = low + 1;
    int j = high;

    while (i <= j) {
        while (i <= high && vec[i] <= pivot) i++;
        while (j >= low + 1 && vec[j] > pivot) j--;

        if (i < j) {
            swap(vec[i], vec[j]);
        }
    }

    swap(vec[low], vec[j]);
    return j; 
}

void quicksort(vector<int>& vec, int low, int high) {
    if (low < high) {
        int part = partition(vec, low, high);
        quicksort(vec, low, part - 1);   
        quicksort(vec, part + 1, high);  
    }
}

int main() {
    int n;
    cout << "No of elements in array: ";
    cin >> n;

    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }

    quicksort(vec, 0, n - 1);

    cout << "Sorted array will be : ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
