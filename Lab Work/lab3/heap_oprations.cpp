#include <bits/stdc++.h>
using namespace std;

// pointer swap 
void swapVal(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Heapify for Max 
void heapify_Max(vector<int> &heap, int n, int i) {
    int largest = i; 
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left] > heap[largest]) largest = left;
    if (right < n && heap[right] > heap[largest]) largest = right;

    if (largest != i) {
        swapVal(heap[i], heap[largest]);
        heapify_Max(heap, n, largest);
    }
}

// Heapify for Min 
void heapify_Min(vector<int> &heap, int n, int i) {
    int smallest = i; 
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left] < heap[smallest]) smallest = left;
    if (right < n && heap[right] < heap[smallest]) smallest = right;

    if (smallest != i) {
        swapVal(heap[i], heap[smallest]);
        heapify_Min(heap, n, smallest);
    }
}

// build heap based on preferencxe
void buildHeap(vector<int> &heap, bool isMax) {
    int n = heap.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        if (isMax) heapify_Max(heap, n, i);
        else heapify_Min(heap, n, i);
    }
}

void insertHeap(vector<int> &heap, int val, bool isMax) {
    heap.push_back(val);
    int i = heap.size() - 1;
    if (isMax) {
        while (i > 0 && heap[(i - 1) / 2] < heap[i]) {
            swapVal(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    } else {
        while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
            swapVal(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
}

void deleteKth(vector<int> &heap, int k, bool isMax) {
    int n = heap.size();
    if (k < 0 || k >= n) {
        
        return;
    }
    heap[k] = heap.back();
    heap.pop_back();
    if (isMax) {
        heapify_Max(heap, heap.size(), k);
    } else {
        heapify_Min(heap, heap.size(), k);
    }
}

void searchKth(vector<int> &heap, int k) {
    if (k < 0 || k >= heap.size()) {
        return;
    }
   
    cout << "Element at  that index  is: " << heap[k] << "\n";
}
// based on max heap 
void heapSort(vector<int> heap) {
    int n = heap.size();
    buildHeap(heap, true); 
    for (int i = n - 1; i > 0; i--) {
        swapVal(heap[0], heap[i]);
        heapify_Max(heap, i, 0);
    }
    cout << "heapified array is : ";
    for (int x : heap) cout << x << " ";
    cout << "\n";
}


// pq using max heap
void priorityQueueDemo() {
    vector<int> pq;
    int choice, val;
    while (true) {
        cout << "\n Pq Menu:\n";
        cout << "1. Insert\n2. Get Max\n3. Remove Max\n4. Exit\n";
        cin >> choice;
        if (choice == 1) {
            cout << "Enter value: ";
            cin >> val;
            insertHeap(pq, val, true);
        } else if (choice == 2) {
            if (!pq.empty()) cout << "Max: " << pq[0] << endl;
            else cout << "Empty Queue" << endl;
        } else if (choice == 3) {
            if (!pq.empty()) {
                cout << "Removed: " << pq[0] << endl;
                deleteKth(pq, 0, true);
            } else cout << "Empty Queue" << endl;
        } else break;
    }
}

void displayHeap(vector<int> &heap) {
    for (int x : heap) cout << x << " ";
    cout << endl;
}

int main() {
    vector<int> heap;
    bool isMax;
    int type;
    cout << "Choose Heap Type: 1 for Max Heap, 0 for Min Heap: ";
    cin >> type;
    isMax = (type == 1);

    int choice, val, k;
    while (true) {
        cout << "\nHeap Operations:\n";
        cout << "1. Build Heap\n";
        cout << "2. Insert\n";
        cout << "3. Delete kth element\n";
        cout << "4. Search kth element\n";
        cout << "5. Display Heap\n";
        cout << "6. Heap Sort\n";
        cout << "7. Priority queue operations \n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                {
                    int n;
                    cout << "Enter number of elements: ";
                    cin >> n;
                    heap.resize(n);
                    cout << "Enter elements: ";
                    for (int i = 0; i < n; i++) cin >> heap[i];
                    buildHeap(heap, isMax);
                }
                break;
            case 2:
                cout << "Enter value to insert: ";
                cin >> val;
                insertHeap(heap, val, isMax);
                break;
            case 3:
                cout << "Enter index to delete: ";
                cin >> k;
                deleteKth(heap, k, isMax);
                break;
            case 4:
                cout << "Enter index to search: ";
                cin >> k;
                searchKth(heap, k);
                break;
            case 5:
                displayHeap(heap);
                break;
            case 6:
                heapSort(heap);
                break;
            case 7:
                priorityQueueDemo();
                break;
            case 8:
                exit(0);
            default:
                cout << "Invalid choice\n";
        }
    }
}
