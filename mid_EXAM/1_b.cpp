#include <iostream>
#include <queue>
#include <fstream>
#include <string>

using namespace std;
typedef struct node {
    int freq;        
    string symbol;  
    struct node* left; 
    struct node* right; 
} Node;

string decodeContent(string encode, Node* root) {

    string encodedContent = encode;

    string decodedStr = "";
    Node* current = root;
    for (char bit : encodedContent) {
        if (bit == '0')
            current = current->left;
        else
            current = current->right;

        if (!current->left && !current->right) {  
            decodedStr += current->symbol;
            current = root;
        }
    }

    return decodedStr;
}struct Compare {
    bool operator()(Node* x, Node* y) {
        return x->freq > y->freq; 
    }
};

Node* createNode(int freq, string symbol) {
    Node* newNode = new Node();
    newNode->freq = freq;
    newNode->symbol = symbol;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

void generateCodes(Node* root, const string& str, string symbols[], string codes[], int& index) {
    if (!root) return;

    if (!root->left && !root->right) {
        symbols[index] = root->symbol;
        codes[index] = str;
        index++;
    }

    generateCodes(root->left, str + "0", symbols, codes, index);
    generateCodes(root->right, str + "1", symbols, codes, index);
}


Node* buildHuffmanTree(string symbols[], int frequencies[], int size) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (int i = 0; i < size; i++) {
        pq.push(createNode(frequencies[i], symbols[i]));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();


        Node* newNode = createNode(left->freq + right->freq, "");
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    return pq.top();
}


void printHuffmanTree(Node* root, string indent = "", bool isLeft = false) {
    if (!root) return;

    if (!root->symbol.empty()) {
        cout << indent << (isLeft ? "/-- " : "\\-- ") << root->symbol << ": " << root->freq << endl;
    } else {
        cout << indent << (isLeft ? "/-- " : "\\-- ") << root->freq << endl;
    }

    printHuffmanTree(root->left, indent + (isLeft ? "|   " : "    "), true);
    printHuffmanTree(root->right, indent + (isLeft ? "|   " : "    "), false);
}

void saveCodesToFile(string symbols[], string codes[], int size, const string& filename) {
    ofstream file(filename);
    for (int i = 0; i < size; i++) {
        file << symbols[i] << " " << codes[i] << "\n";
    }
    file.close();
}


int main() {
    string symbols[] = {"A", "B", "C", "D", "E", "F"};
    int frequencies[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(frequencies) / sizeof(frequencies[0]);

    Node* root = buildHuffmanTree(symbols, frequencies, size);

    string resultSymbols[size];
    string resultCodes[size];
    int index = 0;

    generateCodes(root, "", resultSymbols, resultCodes, index);

    //cout << "\nHuffman Tree:" << endl;
    //printHuffmanTree(root);

    cout << "\nHuffman Codes for each symbol:" << endl;
    for (int i = 0; i < index; i++) {
        cout << resultSymbols[i] << ": " << resultCodes[i] << endl;
    }

    saveCodesToFile(resultSymbols, resultCodes, index, "huffman_codes.txt");

    string decode = decodeContent("111101101110101000111100",root );
    cout << decode << endl;
    return 0;
}
