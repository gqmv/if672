#include <iostream>
#include <string>

using namespace std;

template <typename T, typename Q>
struct Pair{
    T first;
    Q second;

    Pair(T first, Q second){
        this->first = first;
        this->second = second;
    }
};

template <typename T, typename Q, typename F>
struct Triplet{
    T first;
    Q second;
    F third;
    Triplet(T first, Q second, F third){
        this->first = first;
        this->second = second;
        this->third = third;
    }
};

struct Node{
    int value;
    Node *right;
    Node *left;
    
    Node(int value){
        this->value = value;
        this->right = nullptr;
        this->left = nullptr;
    }
};

Node* bst_rotate_left(Node * root){
    Node* r = root->right;
    Node* rl = r->left;
    root->right = rl;
    r->left = root;
    return r;
}

Node* bst_rotate_right(Node * root){
    Node* l = root->left;
    Node* lr = l->right;
    root->left = lr;
    l->right = root;
    return l;
}


Pair<Node*, int>* bst_insert(Node *root, int value, unsigned int recursion_count = 0){
    if(root == nullptr){
        return new Pair<Node*, int>(new Node(value), recursion_count);
    }
    else if(value == root->value){
        return new Pair<Node*, int>(root, recursion_count);
    }
    else if(value < root->value){
        if (root->left != nullptr && root->left->value == value){
            root = bst_rotate_right(root);
            return new Pair<Node*, int>(root, recursion_count);
        }
        Pair<Node*, int>* p = bst_insert(root->left, value, recursion_count + 1);
        root->left = p->first;
        return new Pair<Node*, int>(root, p->second);
    }
    else if(value > root->value){
        if (root->right != nullptr && root->right->value == value){
            root = bst_rotate_left(root);
            return new Pair<Node*, int>(root, recursion_count);
        }
        Pair<Node*, int>* p = bst_insert(root->right, value, recursion_count + 1);
        root->right = p->first;
        return new Pair<Node*, int>(root, p->second);
    }
}


Pair<Node*, int>* bst_delete_min(Node *root){
    if (root->left == nullptr){
        Node* r = root->right;
        int v = root->value;
        delete root;
        return new Pair<Node*, int>(r, v);
    }
    else{
        Pair<Node*, int> *p = bst_delete_min(root->left);
        root->left = p->first;
        return new Pair<Node*, int> (root, p->second);
    }
}


Triplet<Node*, int, int>* bst_delete(Node *root, int value, unsigned int recursion_count = 0){
    if(root == nullptr){
        return new Triplet<Node*, int, int> (nullptr, NULL, recursion_count);
    }
    else if(value < root->value){
        Triplet<Node*, int, int> *p = bst_delete(root->left, value, recursion_count + 1);
        root->left = p->first;
        return new Triplet<Node*, int, int>(root,p->second, p->third);
    }else if(value > root->value){
        Triplet<Node*, int, int> *p = bst_delete(root->right, value, recursion_count + 1);
        root->right = p->first;
        return new Triplet<Node*, int, int>(root, p->second, p->third);
    }else{
        if(root->left == nullptr){
            Node* r = root->right;
            delete(root);
            return new Triplet<Node*, int, int>(r,value , recursion_count);
        }
        else if(root->right == nullptr){
            Node* l = root->left;
            delete(root);
            return new Triplet<Node*, int, int>(l, value,recursion_count);
        }
        else{
            Pair<Node*, int> *p = bst_delete_min(root->right);
            root->right = p->first;
            root->value = p->second;
            return new Triplet<Node*, int, int>(root, value ,recursion_count);
        }
    }
}


Pair<Node*, int>* bst_delete_root(Node *root){
    if (root == nullptr){
        return new Pair<Node*, int>(nullptr, NULL);
    }
    else if(root->left == nullptr){
        Node* r = root->right;
        int v = root->value;
        delete(root);
        return new Pair<Node*, int>(r, v);
    }
    else if(root->right == nullptr){
        Node* l = root->left;
        int v = root->value;
        delete(root);
        return new Pair<Node*, int>(l, v);
    }
    else{
        Pair<Node*, int> *p = bst_delete_min(root->right);
        root->right = p->first;
        int v = root->value;
        root->value = p->second;
        return new Pair<Node*, int>(root, v);
    }
}


void bst_preorder(Node *root){
    if(root != nullptr){
        cout << root->value << endl;
        bst_preorder(root->left);
        bst_preorder(root->right);
    }
}


int main () {
    Node* root = nullptr;
    
    while (true){
        string operation;
        int value;

        cin >> operation;
        if (operation == "END"){
            break;
        }

        if (operation == "EMG"){
            Pair<Node*, int>* p = bst_delete_root(root);
            root = p->first;
            int new_root_value;
            int deleted_value;
            if (p->first == nullptr){
                new_root_value = -1;
            }
            else{
                new_root_value = p->first->value;
            }
            if (p->second == NULL){
                deleted_value = -1;
            }
            else{
                deleted_value = p->second;
            }
            cout << deleted_value << " " << new_root_value << endl;

            continue;
        }

        cin >> value;

        if (operation == "SLD"){
            Pair<Node*, int> *p = bst_insert(root, value);
            root = p->first;
            cout << p->second << endl;
        }
        else if (operation == "STK")
        {
            Triplet<Node*, int, int> *p = bst_delete(root, value);
            root = p->first;
            if (p->second == NULL){
                cout << "NULL" << endl;
            }
            else{
                cout << p->third << endl;
            }            
        }
    }
    if (root != nullptr){
        bst_preorder(root);
    }
    else{
        cout << -1 << endl;
    }
}
