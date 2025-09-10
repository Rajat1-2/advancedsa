#include<bits/stdc++.h>
using namespace std;

class node {
public:
    int data;
    node *left;
    node *right;
    int height;

    node(int val) {
        data = val;
        left = right = nullptr;
        height = 1;
    }
};

int getheight(node* root) {
    if (root == nullptr) {
        return 0;
    } else {
        return root->height;
    }
}

int getbalance(node* nd) {
    if (nd == nullptr) {
        return 0;
    } else {
        return getheight(nd->left) - getheight(nd->right);
    }
}

node* rightrotate(node* y) {
    node* x = y->left;
    node* t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = max(getheight(y->left), getheight(y->right)) + 1;
    x->height = max(getheight(x->left), getheight(x->right)) + 1;

    return x;
}

node* leftrotate(node* x) {
    node* y = x->right;
    node* t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = max(getheight(x->left), getheight(x->right)) + 1;
    y->height = max(getheight(y->left), getheight(y->right)) + 1;

    return y;
}

node* inserttotree(node* nd, int key) {
    if (nd == nullptr) {
        return new node(key);
    }

    if (key < nd->data) {
        nd->left = inserttotree(nd->left, key);
    } else if (key > nd->data) {
        nd->right = inserttotree(nd->right, key);
    } else {
        return nd;
    }

    nd->height = 1 + max(getheight(nd->left), getheight(nd->right));
    int balance = getbalance(nd);

    if (balance > 1 && key < nd->left->data) {
        return rightrotate(nd);
    }
    if (balance < -1 && key > nd->right->data) {
        return leftrotate(nd);
    }
    if (balance > 1 && key > nd->left->data) {
        nd->left = leftrotate(nd->left);
        return rightrotate(nd);
    }
    if (balance < -1 && key < nd->right->data) {
        nd->right = rightrotate(nd->right);
        return leftrotate(nd);
    }

    return nd;
}

node* minvaluenode(node* nd) {
    node* current = nd;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

node* deletenode(node* root, int key) {
    if (root == nullptr) {
        return root;
    }

    if (key < root->data) {
        root->left = deletenode(root->left, key);
    } else if (key > root->data) {
        root->right = deletenode(root->right, key);
    } else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        } else if (root->left == nullptr) {
            node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            node* temp = root->left;
            delete root;
            return temp;
        } else {
            node* temp = minvaluenode(root->right);
            root->data = temp->data;
            root->right = deletenode(root->right, temp->data);
        }
    }

    if (root == nullptr) {
        return root;
    }

    root->height = 1 + max(getheight(root->left), getheight(root->right));
    int balance = getbalance(root);
       
    //  LL
    if (balance > 1 && getbalance(root->left) >= 0) {
        return rightrotate(root);
    }
    // LR
    if (balance > 1 && getbalance(root->left) < 0) {
        root->left = leftrotate(root->left);
        return rightrotate(root);
    }
    // RR
    if (balance < -1 && getbalance(root->right) <= 0) {
        return leftrotate(root);
    }
    // RL
    if (balance < -1 && getbalance(root->right) > 0) {
        root->right = rightrotate(root->right);
        return leftrotate(root);
    }

    return root;
}

void inorder(node* root) {
    if (root == nullptr) {
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main() {
    int x;
    cout << "enter root value: ";
    cin >> x;
    node* root = new node(x);

    int val;
    cout << "enter values to insert (0 to stop): ";
    while (cin >> val && val != 0) {
        root = inserttotree(root, val);
    }

    cout << "inorder traversal after insertion: ";
    inorder(root);
    cout << endl;

    cout << "enter values to delete (0 to stop): ";
    while (cin >> val && val != 0) {
        root = deletenode(root, val);
        cout << "inorder traversal: ";
        inorder(root);
        cout << endl;
    }

    return 0;
}


// test  cases for all deletion and insertions ->
//         30
//        /  \
//      20    50
//     /     /
//   10    40    70
//                   \
//                    80

// Inorder traversal: 10 20 30 40 50 70 80

// enter root value: 50
// enter values to insert (0 to stop): 30
// 70
// 20
// 10
// 40
// 50
// 80
// 0
// inorder traversal after insertion: 10 20 30 40 50 70 80 
// enter values to delete (0 to stop): 80
// inorder traversal: 10 20 30 40 50 70 
// 10
// inorder traversal: 20 30 40 50 70 
// 30
// inorder traversal: 20 40 50 70 
// 70
// inorder traversal: 20 40 50 
// 40
// inorder traversal: 20 50 
// 0