

int main(){
    int choice;
    cin >> choice;
    // 0 for min and 1 for max
    bool max;
    if(choice==0){
        max=false;
    }
    else if (choice ==1){
        max=true;
    }
    int x;
    while(true){
        cout << "1 for insertin heap\n"
        cout << "2 for build heap\n"
        cout << "3 for insert\n";
        cout << "4 search ele";
        cout << "5 dispaly"
        cout << "6 haep sort"
        cout << "7  pq operations"

        switch(x){
            case 1:
            {
                int n;
                cin >>n;
                heap.resize(n);
                for(int i=0;i<n;i++){
                    cin >> heap[i];
                }
                buildHeap(heap,max);
                break;
            }
            case 2:
            {
                int val;
                cin>>val;
                insertHeap(heap,val,max);
                break;

            }
            case 3:
            {
                cin >> k;
                deleteKth(heap,k);
                break;
            }
            case 4:{
                cin >> k;
                searchKth(heap,k);
                break;
            }
            case  5:{
                displayHeap(heap);
                break;
            }
            case 6:
            {
                heapSort(heap);
                break;
            }
            case 7:
            {
                priorityQueueDemo();
                break;
            }
            case 8:{
                exit(0);
            }
            default:
            {
                cout << "invalid choice"
            }

        }


    }

}