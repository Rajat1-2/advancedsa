#include <bits/stdc++.h>
using namespace std;

struct btreenode {
    int t;
    vector<int> keys;
    vector<btreenode*> children;
    bool leaf;
    btreenode(int _t, bool _leaf) : t(_t), leaf(_leaf) {
        keys.reserve(2*t-1);
        children.reserve(2*t);
    }
};

btreenode* btree_create_node(int t, bool leaf) {
    return new btreenode(t, leaf);
}

btreenode* btree_search(btreenode* node, int k) {
    if (!node) return nullptr;
    int i = 0;
    while (i < (int)node->keys.size() && k > node->keys[i]) i++;
    if (i < (int)node->keys.size() && node->keys[i] == k) return node;
    if (node->leaf) return nullptr;
    return btree_search(node->children[i], k);
}

void btree_split_child(btreenode* parent, int idx) {
    btreenode* y = parent->children[idx];
    int t = y->t;
    btreenode* z = btree_create_node(t, y->leaf);
    for (int j = 0; j < t-1; j++) {
        z->keys.push_back(y->keys[j + t]);
    }
    if (!y->leaf) {
        for (int j = 0; j < t; j++) {
            z->children.push_back(y->children[j + t]);
        }
    }
    y->keys.resize(t-1);
    if (!y->leaf) y->children.resize(t);
    parent->children.insert(parent->children.begin() + idx + 1, z);
    parent->keys.insert(parent->keys.begin() + idx, y->keys[t-1]);
}

void btree_insert_non_full(btreenode* node, int k) {
    int i = (int)node->keys.size() - 1;
    if (node->leaf) {
        node->keys.push_back(0);
        while (i >= 0 && node->keys[i] > k) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = k;
    } else {
        while (i >= 0 && node->keys[i] > k) i--;
        i++;
        if ((int)node->children[i]->keys.size() == 2*node->t - 1) {
            btree_split_child(node, i);
            if (node->keys[i] < k) i++;
        }
        btree_insert_non_full(node->children[i], k);
    }
}

void btree_insert(btreenode*& root, int k) {
    if (!root) {
        root = btree_create_node(2, true);
        root->keys.push_back(k);
        return;
    }
    if ((int)root->keys.size() == 2*root->t - 1) {
        btreenode* s = btree_create_node(root->t, false);
        s->children.push_back(root);
        btree_split_child(s, 0);
        int i = 0;
        if (s->keys[0] < k) i++;
        btree_insert_non_full(s->children[i], k);
        root = s;
    } else btree_insert_non_full(root, k);
}

int btree_get_pred(btreenode* node, int idx) {
    btreenode* cur = node->children[idx];
    while (!cur->leaf) cur = cur->children.back();
    return cur->keys.back();
}

int btree_get_succ(btreenode* node, int idx) {
    btreenode* cur = node->children[idx+1];
    while (!cur->leaf) cur = cur->children.front();
    return cur->keys.front();
}

void btree_merge(btreenode* node, int idx) {
    btreenode* c1 = node->children[idx];
    btreenode* c2 = node->children[idx+1];
    int t = node->t;
    c1->keys.push_back(node->keys[idx]);
    for (int i = 0; i < (int)c2->keys.size(); i++) {
        c1->keys.push_back(c2->keys[i]);
    }
    if (!c1->leaf) {
        for (int i = 0; i < (int)c2->children.size(); i++) {
            c1->children.push_back(c2->children[i]);
        }
    }
    node->keys.erase(node->keys.begin() + idx);
    node->children.erase(node->children.begin() + idx + 1);
    delete c2;
}

void btree_fill(btreenode* node, int idx) {
    if (idx != 0 && (int)node->children[idx-1]->keys.size() >= node->t) {
        btreenode* child = node->children[idx];
        btreenode* left = node->children[idx-1];
        child->keys.insert(child->keys.begin(), node->keys[idx-1]);
        if (!left->leaf) child->children.insert(child->children.begin(), left->children.back());
        node->keys[idx-1] = left->keys.back();
        left->keys.pop_back();
        if (!left->leaf) left->children.pop_back();
    } else if (idx != (int)node->keys.size() && (int)node->children[idx+1]->keys.size() >= node->t) {
        btreenode* child = node->children[idx];
        btreenode* right = node->children[idx+1];
        child->keys.push_back(node->keys[idx]);
        if (!right->leaf) child->children.push_back(right->children.front());
        node->keys[idx] = right->keys.front();
        right->keys.erase(right->keys.begin());
        if (!right->leaf) right->children.erase(right->children.begin());
    } else {
        if (idx != (int)node->keys.size()) btree_merge(node, idx);
        else btree_merge(node, idx-1);
    }
}

void btree_remove_from_leaf(btreenode* node, int idx) {
    node->keys.erase(node->keys.begin() + idx);
}

void btree_remove_from_nonleaf(btreenode* node, int idx) {
    int k = node->keys[idx];
    if ((int)node->children[idx]->keys.size() >= node->t) {
        int pred = btree_get_pred(node, idx);
        node->keys[idx] = pred;
        // remove pred recursively
        // find pred index in child
        btreenode* cur = node->children[idx];
        btree_remove_from_nonleaf(cur, (int)cur->keys.size()-1);
    } else if ((int)node->children[idx+1]->keys.size() >= node->t) {
        int succ = btree_get_succ(node, idx);
        node->keys[idx] = succ;
        btreenode* cur = node->children[idx+1];
        btree_remove_from_nonleaf(cur, 0);
    } else {
        btree_merge(node, idx);
        btreenode* cur = node->children[idx];
        // find k in merged child
        int i = 0;
        while (i < (int)cur->keys.size() && cur->keys[i] != k) i++;
        if (i < (int)cur->keys.size()) {
            if (cur->leaf) btree_remove_from_leaf(cur, i);
            else btree_remove_from_nonleaf(cur, i);
        }
    }
}

void btree_remove(btreenode*& node, int k) {
    if (!node) return;
    int idx = 0;
    while (idx < (int)node->keys.size() && node->keys[idx] < k) idx++;
    if (idx < (int)node->keys.size() && node->keys[idx] == k) {
        if (node->leaf) btree_remove_from_leaf(node, idx);
        else btree_remove_from_nonleaf(node, idx);
    } else {
        if (node->leaf) return;
        bool flag = (idx == (int)node->keys.size());
        if ((int)node->children[idx]->keys.size() < node->t) btree_fill(node, idx);
        if (flag && idx > (int)node->keys.size()) btree_remove(node->children[idx-1], k);
        else btree_remove(node->children[idx], k);
    }
    if (node->keys.empty()) {
        btreenode* tmp = node;
        if (node->leaf) node = nullptr;
        else node = node->children[0];
        if (tmp != node) delete tmp;
    }
}

void btree_traverse(btreenode* node) {
    if (!node) return;
    int i;
    for (i = 0; i < (int)node->keys.size(); i++) {
        if (!node->leaf) btree_traverse(node->children[i]);
        cout << node->keys[i] << " ";
    }
    if (!node->leaf) btree_traverse(node->children[i]);
}

int main() {
    int t;
    cin >> t;
    btreenode* root = nullptr;
    string cmd;
    while (cin >> cmd) {
        if (cmd == "insert") {
            int x; cin >> x;
            btree_insert(root, x);
        } else if (cmd == "search") {
            int x; cin >> x;
            btreenode* res = btree_search(root, x);
            cout << (res ? "true" : "false") << "\n";
        } else if (cmd == "delete") {
            int x; cin >> x;
            btree_remove(root, x);
        } else if (cmd == "display") {
            btree_traverse(root);
            cout << "\n";
        } else if (cmd == "exit") break;
    }
    return 0;
}


// 3
// insert 5
// insert 15
// insert 10
// display
// 5 10 15 
// delete 15
// display
// 5 10 
// exit