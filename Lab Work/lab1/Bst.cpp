#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int char;
    Node *left, *right;

    Node(char val) {
        data = val;
        left = right = nullptr;
    }
};

Node* insertinbtree(Node* root, char val) {
    if (root == nullptr) return new Node(val);

    if (val < root->data)
        root->left = insertinbtree(root->left, val);
    else{
        root->right = insertinbtree(root->right, val);
       }

    return root;
}

Node* findMin(Node* root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

Node* deletioninbtree(Node* root, char key) {
    if (root == nullptr) return nullptr;

    if (key < root->data) {
        root->left = deletioninbtree(root->left, key);
    }
    else if (key > root->data) {
        root->right = deletioninbtree(root->right, key);
    }
    else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        else if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findMin(root->right); // inorder successor
        root->data = temp->data;
        root->right = deletioninbtree(root->right, temp->data);
    }

    return root;
}

void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

 void searchinbtree(Node *root , char value){
    if(root->data==value){
        cout << "ele found"  << endl ;
    }
    else if (root->data > value){
        searchinbtree(root->left);
    }
    else if (root->data < value){
        searchinbtree(root->right);
    }
    else{
        cout << "ele not in this BST " << endl;
    }

    
 }

 int heightoftree(Node* root){
    if(root == nullptr) return 0;
    else{
        return 1+max(heightoftree(root->left),heightoftree(root->right));
    }
 }

 int longestpathtill(Node* root,char val){
    if(root==nullptr) return -1;
    if(root->data== val) return heightoftree(root);
    else if(root->data > val) return longestpathtill(root->left,val);
    else{
        return longestpathtill(root->right,val);
    }
    // int left=longestpathtill(root->left,val);
    // int right=longestpathtill(root->right,val);
    // return 1+max(left,right);
 }

 int minoftree(Node *root){
    if(root->left!=nullptr){
        minoftree(root->left);

    }
    else{
        return root->data;
    }
 }

 int maxoftree(Node *root){
    if(root->right!=nullptr){
        minoftree(root->right);

    }
    else{
        return root->data;
    }
 }

 Node mirroroftree(Node *root){
    
    if(root==nullptr){
        return nullptr
    }
    Node * newnode=new Node(root);
    newnode->left=new Node(root->right);
    newnode->right=new Node(root->left);

    return newnode;

 }



int main() {
    char n;
    cout << "Enter root node  ";
    cin >> n;

    Node* root = new Node(n);

    int count;
    cin >> count;

    cout << "Enter elements to insert";
    while (count--) {
        char ele;
        cin >> ele;
        root = insertinbtree(root, ele);
    }

    cout << "Inorder traversal before deletion:" << endl;
    inorder(root);
    cout << endl;

    char del;
    cout << "Enter element to delete: ";
    cin >> del;

    root = deletioninbtree(root, del);

    cout << "Inorder traversal after deletion" << endl;
    inorder(root);
    cout << "\n";

    searchinbtree(root, del);
    cout << "height of this tree is : " << heightoftree(root) << endl;
    cout << "min ele in this tree is : " << minoftree(root) << endl;
    cout << "max ele in this tree is : " << maxoftree(root) << endl;
    cout << longestpathtill(root,del);

    Node* isoroot=mirroroftree(root);
    inorder(isoroot) << endl ;



    return 0;
}
  int pivot=vec[high-1];
    int partion=partition(vec,high,pivot);

    quicksort(vec,low,partion-1);
    quicksort(vec,partion+1,high);