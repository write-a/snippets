#include <iostream>
#include <vector>

// This snippet is the solution to a LCA problem
// construct a binary search tree and calculate the distance between any two nodes
// The distance is defined as the simple path between the two nodes going throught the LCA. 
// If any of the node is not in the tree, return -1;
// Each node is unique (not two nodes have the same value, node values are all non-negative).
//
// g++ bst-lca.cpp -std=c++11
//

using namespace std;

typedef struct MyNode {
    int data;
    struct MyNode* left;
    struct MyNode* right;
    MyNode(int data):data(data),left(nullptr),right(nullptr){}
} MyNode;

MyNode* bstInsert(MyNode* root, int val){
    if(!root){
        return new MyNode(val);
    }
    if(val < root->data){
        root->left = bstInsert(root->left, val);
        return root;
    }
    if(val > root->data){
        root->right = bstInsert(root->right, val);
        return root;
    }
    // inserting duplicate node
    throw "duplicate insertion";
}

MyNode* LCA(MyNode* root, int val1, int val2){
    if(!root)
        return nullptr;
    cout << root->data << " " << val1 << " " << val2 << "\n";
    if(val1 < root->data && val2 < root->data){
        return LCA(root->left, val1, val2);
    }
    if(val1 > root->data && val2 > root->data){
        return LCA(root->right, val1, val2);
    }
    // both the subtrees must exist and neither of the values 
    // is the current node's value, then one of the value 
    // is not in the tree
    return root;
}

void inOrder(MyNode* root){

    if(!root)
        return;
    inOrder(root->left);
    cout << root->data << ",";
    inOrder(root->right);
}

int dist(MyNode* lca, int val){
    if(!lca)
        return 0;
    if(val < lca->data){
        if(!lca->left)
            throw "not in tree";
        return 1+dist(lca->left, val);
    
    }
    if(val > lca->data){
        if(!lca->right)
            throw "not in tree";
        return 1+dist(lca->right, val);
    }
    return 0;

}

int main(){

    vector<int> nodes{2,3,7,4,6,9,1,5,8};
    MyNode* root=nullptr;
    for(auto i : nodes){
        if(!root){
            root = bstInsert(root, i);
        }
        else{
            bstInsert(root, i);
        }
    }
    inOrder(root);
    cout << "\n";
    while(true){
        int n1, n2;
        cin >> n1 >> n2;
        MyNode* lca = LCA(root, n1, n2);
        try{
            if(lca){
                int d = dist(lca, n1) + dist(lca, n2);
                cout << "lca of " << n1 << " and " << n2 << " is " << lca->data << "\n";
                cout << "distance between " << n1 << " and " << n2 << " is " << d << "\n";
            }else{
                cout << "No LCA, at least one of " << n1 << " and " << n2 << " is not in the tree\n";                
            }
        }catch(...){
            cout << "Can't calculate distance, at least one of " << n1 << " and " << n2 << " is not in the tree\n";
            return -1;
        }
    }

}
