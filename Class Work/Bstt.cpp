#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node *left, *right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

Node* insertinbtree(Node* root, int val) {
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

Node* deletioninbtree(Node* root, int key) {
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

int main() {
    int n;
    cout << "Enter root node  ";
    cin >> n;

    Node* root = new Node(n);

    int count;
    cin >> count;

    cout << "Enter elements to insert";
    while (count--) {
        int ele;
        cin >> ele;
        root = insertinbtree(root, ele);
    }

    cout << "Inorder traversal before deletion:" << endl;
    inorder(root);
    cout << endl;

    int del;
    cout << "Enter element to delete: ";
    cin >> del;

    root = deletioninbtree(root, del);

    cout << "Inorder traversal after deletion" << endl;
    inorder(root);
    cout << "\n";

    return 0;
}
