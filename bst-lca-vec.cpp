#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <iterator>
// This snippet is the solution to a LCA problem
// construct a binary search tree and calculate the distance between any two nodes
// The distance is defined as the simple path between the two nodes going throught the LCA. 
// If any of the node is not in the tree, return -1;
// Each node is unique (not two nodes have the same value, node values are all non-negative).
//
// g++ bst-lca-vec.cpp -std=c++11
//
using namespace std;

void printVec(const vector<int>& bst){
    copy(bst.begin(), bst.end(), ostream_iterator<int>(cout, ","));
    cout << "\n";
}

int parent(int i){
    return i-1/2;
}

int leftChild(int i){
    return 2*i + 1;
}

int rightChild(int i){
    return 2*(i+1);
}

void bstInsert(vector<int>& bst, int current_pos, int i){
    cout << "trying to insert " << i << " at pos " << current_pos << " while vec size is " << bst.size() << "\n";
    if(current_pos >= bst.size()){
        int more = current_pos - bst.size() + 1;
        // TODO: use range insert here
        while(more--){
            bst.push_back(-1);
        }
        bst[current_pos] = i;
        return;
    }
 
    if(bst[current_pos] == -1){
        bst[current_pos] = i;
        return;
    }
    if(i < bst[current_pos]){
        bstInsert(bst, leftChild(current_pos), i);
        return;
    }
    if(i > bst[current_pos]){
        bstInsert(bst, rightChild(current_pos), i);
        return;
    }
    throw "duplicate insertion";
}

void inOrder(const vector<int>& bst, int i){
    //cout << "in order, pos: " << i << "\n";
    if(i < 0 || i >= bst.size())
        return;
    inOrder(bst, leftChild(i));
    if(bst[i] != -1)
        cout << bst[i] << ",";
    inOrder(bst, rightChild(i));
}

int LCA(const vector<int>& bst, int pos, int n1, int n2){
    if(pos<0 || pos>=bst.size())
        return -1;
    if(bst[pos] == -1)
        return -1;
    if(n1 < bst[pos] && n2 < bst[pos]){
        return LCA(bst, leftChild(pos), n1, n2); 
    }
    if(n1 > bst[pos] && n2 > bst[pos]){
        return LCA(bst, rightChild(pos), n1, n2);
    }
    return pos; 
}

// distance between an ancestor lca and a node n
int dist(const vector<int>& bst, int lca, int n){
    if(lca < 0 || lca >= bst.size() || bst[lca] == -1)
        throw "invalid ancestor";
    if(n < bst[lca]){
        int left = leftChild(lca);
        if(left >= bst.size() || bst[left] == -1)
            throw "not in tree";
        return 1+dist(bst, left, n);
    }
    if(n > bst[lca]){
        int right = rightChild(lca);
        if(right >= bst.size() || bst[right] == -1)
            throw "not in tree";
        return 1+dist(bst, right, n);
    }
    return 0;
}

int main(){

    vector<int> nodes{2,3,7,4,6,9,1,5,8};
    vector<int> bst(nodes.size(), -1);
    for(auto i : nodes){
        printVec(bst);
        if(bst[0] == -1){
            bst[0] = i;
        }
        else{
            bstInsert(bst, 0, i);
        }
    }
    inOrder(bst, 0);
    cout << "\n";
    while(true){
        int n1, n2;
        cin >> n1 >> n2;
        int lca = LCA(bst, 0, n1, n2);
        try{
            if(lca!=-1){
                int d = dist(bst, lca, n1) + dist(bst, lca, n2);
                cout << "lca of " << n1 << " and " << n2 << " is " << bst[lca] << "\n";
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
