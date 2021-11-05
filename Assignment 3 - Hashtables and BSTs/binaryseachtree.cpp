/**
 * Except where otherwise noted, the following code is licensed under the Creative Commons Attribution 4.0 International license (CC BY 4.0):
 * http://creativecommons.org/licenses/by/4.0/
 * Copyright 2021 Gabriel Vieira
 * https://github.com/gqmv
 *
 * Whenever using, citing, or modifying this work, be sure to include a copy of the license and this notice.
 */

#include <bits/stdc++.h>

using namespace std;

/**
 * A generalistic Binary Search Tree implementation that supports only insertion and getting the post order string representation of the tree.
 */
template <typename T>
class BinarySearchTree
{
private:
    T data;
    BinarySearchTree *left, *right;

public:
    BinarySearchTree(T data)
    {
        this->data = data;
        left = right = nullptr;
    }

    /**
     * Inserts a new node in the tree.
     *
     * @param data The data to be inserted.
     * @return A pointer to the root of the tree.
     */
    BinarySearchTree *insert(T data)
    {
        if (data < this->data)
        {
            if (left == nullptr)
                left = new BinarySearchTree(data);
            else
                left->insert(data);
        }
        else
        {
            if (right == nullptr)
                right = new BinarySearchTree(data);
            else
                right->insert(data);
        }

        return this;
    }

    /**
     * Gets the post order string representation of the tree.
     *
     * @return The post order string representation of the tree.
     */
    string getPostOrder()
    {
        stringstream ss;

        if (left != nullptr)
            ss << left->getPostOrder();

        if (right != nullptr)
            ss << right->getPostOrder();

        ss << data << "\n";

        return ss.str();
    }
};

int main()
{
    int value;
    cin >> value;

    BinarySearchTree<int> *root = new BinarySearchTree<int>(value);

    while (cin >> value)
    {
        root->insert(value);
    }

    cout << root->getPostOrder();
}