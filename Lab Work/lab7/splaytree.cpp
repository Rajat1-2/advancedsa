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
    int k;
    cout << "enter key to search: ";
    cin >> k;
    root = search(root, k);
    cout << "root after splay: " << root->data << endl;
    cout << "inorder traversal: ";
    inorder(root);
}

/*

enter values to insert (0 to stop): 3 12 4 45 78 2 33 21 10 5 7
0
inorder traversal: 2 3 4 5 7 10 12 21 33 45 78 
enter key to search: 21
root after splay: 21
inorder traversal: 2 3 4 5 7 10 12 21 33 45 78


*/
