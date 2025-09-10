#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int data;
    Node *left;
    Node *right;
    int height;

    public:
    Node(int val){
        data=val;
        left=right=nullptr;
        height=1;

    }
};


int getHeight(Node* node) {
    if(node==nullptr) return 0;
    else{
        return node->height;
    }
}

int getBalance(Node* node) {
    if(node==nullptr) return 0;
    else{
        return getHeight(node->left)-getHeight(node->right);
    }
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

// Node* inserttotree(Node *root,int key){
//     // int val;
//     // cout << "Enter the value : ";
//     // cin >> val;

//     if(root->data==nullptr){
//         return;
//     }

//     else if(val > root->data){
//         inserttotree(root->right,val);
//     }
//     else{
//         inserttotree(root->left, val);
//     }

    

// }
Node* inserttotree(Node* node, int key) {
    if (!node)
        return new Node(key);

    if (key < node->data)
        node->left = inserttotree(node->left, key);
    else if (key > node->data)
        node->right = inserttotree(node->right, key);
    else
        return node; 

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    // LL
    if (balance > 1 && key < node->left->data)
        return rightRotate(node);

    // RR
    if (balance < -1 && key > node->right->data)
        return leftRotate(node);
      // LR
    if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL
    if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}




int main() {
    int x;
    cout << "Enter root value: ";
    cin >> x;
    Node* root = new Node(x);

    int val;
    cout << "Enter values to insert (0 to stop): ";
    while (cin >> val && val != 0) {
        root = inserttotree(root, val);
    }

    cout << "Inorder traversal: ";
    inorder(root);
    cout << endl;
}

// PS C:\Users\rajat\Desktop\sem5\Advance DS\Lab Work\lab5> cd "c:\Users\rajat\Desktop\sem5\Advance DS\Lab Work\lab5\" ; if ($?) { g++ avl.cpp -o avl } ; if ($?) { .\avl }   
// Enter root value: 50
// Enter values to insert (0 to stop): 30
/* 
70
20
10
40
50
80
0
// Inorder traversal: 10 20 30 40 50 70 80