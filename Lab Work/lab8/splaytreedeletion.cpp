#include <bits/stdc++.h>
using namespace std;

struct node {
    int data;
    node* left;
    node* right;
    node(int val) {
        data = val;
        left = right = nullptr;
    }
};

node* rightrotate(node* x) {
    node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

node* leftrotate(node* x) {
    node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}



node* splay(node* root, int key) {
    if (!root || root->data == key) return root;
    if (key < root->data) {
        if (!root->left) return root;
        if (key < root->left->data) {
            root->left->left = splay(root->left->left, key);
            root = rightrotate(root);
        } else if (key > root->left->data) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right) root->left = leftrotate(root->left);
        }
        return root->left ? rightrotate(root) : root;
    } else {
        if (!root->right) return root;
        if (key > root->right->data) {
            root->right->right = splay(root->right->right, key);
            root = leftrotate(root);
        } else if (key < root->right->data) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left) root->right = rightrotate(root->right);
        }
        return root->right ? leftrotate(root) : root;
    }
}
node* deleteNode(node* root, int key) {
    if (!root) return nullptr;
    root = splay(root, key);
    if (root->data != key) return root; // Key not found

    node* temp;
    if (!root->left) {
        temp = root->right;
    } else {
        temp = splay(root->left, key); // splay the largest node in left subtree
        temp->right = root->right;
    }
    delete root;
    return temp;
}

node* insert(node* root, int key) {
    if (!root) return new node(key);
    root = splay(root, key);
    if (root->data == key) return root;
    node* newnode = new node(key);
    if (key < root->data) {
        newnode->right = root;
        newnode->left = root->left;
        root->left = nullptr;
    } else {
        newnode->left = root;
        newnode->right = root->right;
        root->right = nullptr;
    }
    return newnode;
}

node* search(node* root, int key) {
    return splay(root, key);
}

void inorder(node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
// void inorder(node* root) {
//     if (!root) return;
//     inorder(root->left);
//     cout << root->data << " ";
//     inorder(root->right);
// }

int main() {
    node* root = nullptr;
    int x;
    cout << "enter values to insert (0 to stop): ";
    while (cin >> x && x != 0) {
         root = insert(root, x);
    }
   
    cout << "inorder traversal: ";
    inorder(root);
    cout << endl;
    

    cout << "enter key to delete: ";
    int k;
     while (cin >> k && k != 0) {
         root = deleteNode(root, k);
    }
    
    cout << "inorder traversal after deletion: ";
    inorder(root);
    cout << endl;
}

/*

enter values to insert (0 to stop): 2 4 3 786 54 34 900 1289 45 32 2 1
0
inorder traversal: 1 2 3 4 32 34 45 54 786 900 1289 
enter key to delete: 786
45 54 0
inorder traversal after deletion: 1 2 3 4 32 34 900 1289 


*/
