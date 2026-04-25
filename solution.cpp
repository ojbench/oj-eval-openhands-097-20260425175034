#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* buildBSTFromLevelOrder(const vector<int>& levelOrder) {
    if (levelOrder.empty()) return nullptr;
    
    vector<TreeNode*> nodes;
    for (int val : levelOrder) {
        if (val != -1) {  // Assuming -1 represents null nodes
            nodes.push_back(new TreeNode(val));
        } else {
            nodes.push_back(nullptr);
        }
    }
    
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i] != nullptr) {
            int leftIdx = 2 * i + 1;
            int rightIdx = 2 * i + 2;
            if (leftIdx < nodes.size()) nodes[i]->left = nodes[leftIdx];
            if (rightIdx < nodes.size()) nodes[i]->right = nodes[rightIdx];
        }
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

vector<int> parseArray(const string& input) {
    vector<int> result;
    string cleaned = input;
    
    // Remove brackets and spaces
    cleaned.erase(remove(cleaned.begin(), cleaned.end(), '['), cleaned.end());
    cleaned.erase(remove(cleaned.begin(), cleaned.end(), ']'), cleaned.end());
    cleaned.erase(remove(cleaned.begin(), cleaned.end(), ' '), cleaned.end());
    
    stringstream ss(cleaned);
    string token;
    while (getline(ss, token, ',')) {
        if (!token.empty()) {
            result.push_back(stoi(token));
        }
    }
    return result;
}

int main() {
    string input;
    int cnt;
    
    // Read input
    getline(cin, input);
    cin >> cnt;
    
    // Parse the array input
    vector<int> levelOrder = parseArray(input);
    
    // Build BST
    TreeNode* root = buildBSTFromLevelOrder(levelOrder);
    
    // Find kth largest
    int result = findKthLargest(root, cnt);
    
    cout << result << endl;
    
    return 0;
}
