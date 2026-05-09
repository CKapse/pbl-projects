#include <iostream>
using namespace std;

class avl_node {
    int value;
    avl_node *left, *right;
public:
    friend class avlTree;
};

class avlTree {
    avl_node *root;
public:
    int height(avl_node *);
    int diff(avl_node *);
    avl_node *rr_rotation(avl_node *);
    avl_node *ll_rotation(avl_node *);
    avl_node *lr_rotation(avl_node *);
    avl_node *rl_rotation(avl_node *);
    avl_node *balance(avl_node *);
    void insert();
    avl_node *insert(avl_node *, avl_node *);
    void display(avl_node *, int);
    void inorder(avl_node *);
    void preorder(avl_node *);
    void postorder(avl_node *);

    avlTree() { root = NULL; }

    void display()   { display(root, 1); }
    void inorder()   { inorder(root); }
    void preorder()  { preorder(root); }
    void postorder() { postorder(root); }
};

avl_node* avlTree::ll_rotation(avl_node *parent) {
    avl_node *temp = parent->left;
    parent->left   = temp->right;
    temp->right    = parent;
    return temp;
}

avl_node* avlTree::rr_rotation(avl_node *parent) {
    avl_node *temp = parent->right;
    parent->right  = temp->left;
    temp->left     = parent;
    return temp;
}

avl_node* avlTree::lr_rotation(avl_node *parent) {
    avl_node *temp = parent->left;
    parent->left   = rr_rotation(temp);
    return ll_rotation(parent);
}

avl_node* avlTree::rl_rotation(avl_node *parent) {
    avl_node *temp = parent->right;
    parent->right  = ll_rotation(temp);
    return rr_rotation(parent);
}

int avlTree::height(avl_node *temp) {
    if (temp == NULL) return 0;
    int l = height(temp->left);
    int r = height(temp->right);
    return max(l, r) + 1;
}

int avlTree::diff(avl_node *temp) {
    return height(temp->left) - height(temp->right);
}

avl_node* avlTree::balance(avl_node *temp) {
    int bal = diff(temp);
    if (bal > 1) {
        if (diff(temp->left) >= 0)
            temp = ll_rotation(temp);
        else
            temp = lr_rotation(temp);
    } else if (bal < -1) {
        if (diff(temp->right) <= 0)
            temp = rr_rotation(temp);
        else
            temp = rl_rotation(temp);
    }
    return temp;
}

void avlTree::insert() {
    char ch;
    do {
        avl_node *temp = new avl_node;
        cout << "Enter value: ";
        cin  >> temp->value;
        temp->left = temp->right = NULL;
        root = insert(root, temp);
        cout << "Insert another? (Y/N): ";
        cin  >> ch;
    } while (ch == 'Y' || ch == 'y');
}

avl_node* avlTree::insert(avl_node *root, avl_node *temp) {
    if (root == NULL) {
        root        = new avl_node;
        root->value = temp->value;
        root->left  = root->right = NULL;
        return root;
    }
    if (temp->value < root->value) {
        root->left  = insert(root->left, temp);
        root = balance(root);
    } else if (temp->value > root->value) {
        root->right = insert(root->right, temp);
        root = balance(root);
    }
    return root;
}

void avlTree::display(avl_node *ptr, int level) {
    if (ptr != NULL) {
        display(ptr->right, level + 1);
        cout << "\n";
        if (ptr == root)
            cout << "Root -> ";
        else
            for (int i = 0; i < level; i++)
                cout << "        ";
        cout << ptr->value;
        display(ptr->left, level + 1);
    }
}

void avlTree::inorder(avl_node *ptr) {
    if (ptr != NULL) {
        inorder(ptr->left);
        cout << ptr->value << "  ";
        inorder(ptr->right);
    }
}

void avlTree::preorder(avl_node *ptr) {
    if (ptr != NULL) {
        cout << ptr->value << "  ";
        preorder(ptr->left);
        preorder(ptr->right);
    }
}

void avlTree::postorder(avl_node *ptr) {
    if (ptr != NULL) {
        postorder(ptr->left);
        postorder(ptr->right);
        cout << ptr->value << "  ";
    }
}

int main() {
    avlTree tree;
    int choice;

    do {
        cout << "\n===== AVL Tree Menu =====\n";
        cout << "1. Insert\n";
        cout << "2. Display Tree\n";
        cout << "3. Inorder\n";
        cout << "4. Preorder\n";
        cout << "5. Postorder\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin  >> choice;

        switch (choice) {
            case 1: tree.insert();    break;
            case 2: tree.display();   cout << "\n"; break;
            case 3: tree.inorder();   cout << "\n"; break;
            case 4: tree.preorder();  cout << "\n"; break;
            case 5: tree.postorder(); cout << "\n"; break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}