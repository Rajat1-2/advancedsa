#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    char data;
    Node* left;
    Node* right;

    Node(char val) {
        data = val;
        left = right = nullptr;
    }
};

Node* insertinbtree(Node* root, char val) {
    if (root == nullptr) return new Node(val);
    if (val < root->data)
        root->left = insertinbtree(root->left, val);
    else
        root->right = insertinbtree(root->right, val);
    return root;
}

Node* findMin(Node* root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

Node* deletioninbtree(Node* root, char key) {
    if (root == nullptr) return nullptr;

    if (key < root->data)
        root->left = deletioninbtree(root->left, key);
    else if (key > root->data)
        root->right = deletioninbtree(root->right, key);
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
        Node* temp = findMin(root->right);
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
void preorder(Node* root) {
    if (root == nullptr) return;
    cout << root->data << " ";
    inorder(root->left);
    
    inorder(root->right);
}
void postorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
   
    inorder(root->right);
     cout << root->data << " ";
}

bool searchinbtree(Node* root, char value) {
    if (root == nullptr) return false;
    if (root->data == value) return true;
    if (value < root->data) return searchinbtree(root->left, value);
    return searchinbtree(root->right, value);
}

int heightoftree(Node* root) {
    if (root == nullptr) return 0;
    return 1 + max(heightoftree(root->left), heightoftree(root->right));
}

int longestpathtill(Node* root, char val) {
    if (root == nullptr) return -1;
    if (root->data == val) return heightoftree(root);
    if (val < root->data)
        return longestpathtill(root->left, val);
    else{
        return longestpathtill(root->right, val);
    }
}
// int height(Node* root) {
//     if (!root) return -1;
//     return 1 + max(height(root->left), height(root->right));
// }

int heightOfNode(Node* root, char key) {
    if (!root) return -1;
    if (key == root->data) return heightoftree(root);
    if (key < root->data) return heightOfNode(root->left, key);
    return heightOfNode(root->right, key);
}

char minoftree(Node* root) {
    while (root->left != nullptr)
        root = root->left;
    return root->data;
}

char maxoftree(Node* root) {
    while (root->right != nullptr)
        root = root->right;
    return root->data;
}

Node* mirroroftree(Node* root) {
    if (root == nullptr) return nullptr;

    Node* newnode = new Node(root->data);
    newnode->left = mirroroftree(root->right);
    newnode->right = mirroroftree(root->left);

    return newnode;
}

int depth(Node* root, char val, int level = 0) {
    if (root == nullptr) return -1;
    if (root->data == val) return level;
    if (val < root->data)
        return depth(root->left, val, level + 1);
    else{
        return depth(root->right, val, level + 1);
    }
}

void printParent(Node* root, char val, Node* parent = nullptr) {
    if (root == nullptr) {
        cout << "Node not found.\n";
        return;
    }

    if (root->data == val) {
        if (parent)
            cout << "Parent of " << val << " is " << parent->data << endl;
        else{
            cout << val << " is the root node and has no parent.\n";
        }
        return;
    }

    if (val < root->data)
        printParent(root->left, val, root);
    else{
        printParent(root->right, val, root);
    }
}


int main() {
    Node* root = nullptr;
    int choice;
    char val;

    do {
        
        cout << "1. Insert\n2. Delete\n3. Inorder Traversal\n4. Search\n";
        cout << "5. Height of Tree\n6. Min Element\n7. Max Element\n";
        cout << "8. Longest Path from Node\n9. Depth of Node\n10. Print Parent\n";
        cout << "11. Mirror Tree\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                root = insertinbtree(root, val);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> val;
                root = deletioninbtree(root, val);
                break;
            case 3:
                cout << "Inorder Traversal: ";
                inorder(root);
                cout << endl;
                break;
            case 4:
                cout << "Enter value to search: ";
                cin >> val;
                if (searchinbtree(root, val))
                    cout << val << " found in BST\n";
                else
                    cout << val << " not found\n";
                break;
            case 5:
                cout << "Height of tree: " << heightoftree(root) << endl;
                break;
            case 6:
                cout << "Minimum element: " << minoftree(root) << endl;
                break;
            case 7:
                cout << "Maximum element: " << maxoftree(root) << endl;
                break;
            case 8:
                cout << "Enter node to find longest path from: ";
                cin >> val;
                cout << "Longest path from " << val << ": " << longestpathtill(root, val) << endl;
                break;
            case 9:
                cout << "Enter node to find depth: ";
                cin >> val;
                cout << "Depth of " << val << ": " << depth(root, val) << endl;
                break;
            case 10:
                cout << "Enter node to find parent: ";
                cin >> val;
                printParent(root, val);
                break;
            case 11: {
                cout << "Inorder of Mirror Tree: ";
                Node* mirror = mirroroftree(root);
                inorder(mirror);
                cout << endl;
                break;
            }
            case:12{
                cout << "Preorder of tree : ";
                preorder(root);
                cout << endl;
                break;
            }
            case:13{
                cout << "Postorder of tree : ";
                preorder(root);
                cout << endl;
                break;
            }
            case:14{
                 cout << "Enter node to find height: ";
                cin >> val;
                cout << "Depth of " << val << ": " << heightOfNode(root, val) << endl;
                break;
            }
            case 0:
                break;
            default:
                cout << "Invalid option!" << endl;
        }
    } while (choice != 0);

    return 0;
}
