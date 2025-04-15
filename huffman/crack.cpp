#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef struct node {
    int freq;
    string symbol;
    struct node *left, *right;
} Node;

// Overloading the < operator for the priority queue (max-heap)
bool operator<(const Node* x, const Node* y) {
    return x->freq < y->freq;  // Max-heap: compare to merge the highest frequencies first
}

// Function to create a new node
Node* createNode(int frequency, string sym, Node* left, Node* right) {
    Node* newNode = new Node();  // Use new instead of malloc
    newNode->freq = frequency;
    newNode->symbol = sym;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

// Function to generate Huffman codes by traversing the tree
void generateHuffmanCodes(Node* root, string code, vector<string>& codes, vector<char>& symbols) {
    if (!root) return;

    // Leaf node: Store the symbol and its code
    if (!root->left && !root->right) {
        symbols.push_back(root->symbol[0]); // Store the symbol
        codes.push_back(code);               // Store the corresponding Huffman code
    }

    // Recur for left and right subtrees
    generateHuffmanCodes(root->left, code + "0", codes, symbols);
    generateHuffmanCodes(root->right, code + "1", codes, symbols);
}

// Function to build the Huffman tree
Node* buildHuffmanTree(priority_queue<Node*>& pq) {
    while (pq.size() > 1) {
        Node* temp1 = pq.top();
        pq.pop();

        Node* temp2 = pq.top();
        pq.pop();

        Node* node = createNode(temp1->freq + temp2->freq, temp1->symbol + temp2->symbol, temp1, temp2);
        pq.push(node);
    }

    // The final node in the queue is the root of the Huffman tree
    return pq.top();
}

int main() {
    char chars[] = {'a', 'b', 'c', 'd', 'e'};
    int freq[] = {45, 8, 12, 10, 4};

    // Create a priority queue (max-heap) of Node pointers
    priority_queue<Node*> pq;

    for (int i = 0; i < 5; i++) {
        Node* newNode = createNode(freq[i], string(1, chars[i]), nullptr, nullptr);
        pq.push(newNode);
    }

    // Build the Huffman tree
    Node* root = buildHuffmanTree(pq);

    // Generate Huffman codes
    vector<string> codes;
    vector<char> symbols;
    generateHuffmanCodes(root, "", codes, symbols);

    // Print the Huffman codes
    cout << "Huffman Codes:\n";
    for (size_t i = 0; i < codes.size(); i++) {
        cout << symbols[i] << ": " << codes[i] << endl;
    }

    return 0;
}
