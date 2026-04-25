#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Function to delete tree and prevent memory leak
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

TreeNode* buildBSTFromLevelOrder(const vector<int>& levelOrder) {
    if (levelOrder.empty()) return nullptr;
    
    vector<TreeNode*> nodes;
    for (int val : levelOrder) {
        nodes.push_back(new TreeNode(val));
    }
    
    for (int i = 0; i < nodes.size(); i++) {
        int leftIdx = 2 * i + 1;
        int rightIdx = 2 * i + 2;
        if (leftIdx < nodes.size()) nodes[i]->left = nodes[leftIdx];
        if (rightIdx < nodes.size()) nodes[i]->right = nodes[rightIdx];
    }
    
    return nodes[0];
}

void reverseInorder(TreeNode* root, int& cnt, int& result) {
    if (!root || cnt <= 0) return;
    
    reverseInorder(root->right, cnt, result);
    cnt--;
    if (cnt == 0) {
        result = root->val;
        return;
    }
    reverseInorder(root->left, cnt, result);
}

int findKthLargest(TreeNode* root, int cnt) {
    int result = -1;
    reverseInorder(root, cnt, result);
    return result;
}

int main() {
    vector<int> levelOrder;
    int value;
    
    // Read 7 integers for the tree nodes
    for (int i = 0; i < 7; i++) {
        cin >> value;
        levelOrder.push_back(value);
    }
    
    // Read cnt
    int cnt;
    cin >> cnt;
    
    // Build BST
    TreeNode* root = buildBSTFromLevelOrder(levelOrder);
    
    // Find kth largest
    int result = findKthLargest(root, cnt);
    
    cout << result << endl;
    
    // Clean up memory
    deleteTree(root);
    
    return 0;
}
