#include<iostream>
#include<vector>
#include<queue>
#include<fstream>
using namespace std;

typedef struct Node{
    int freq;
    string symbol;
    struct Node *left;
    struct Node *right;
}Node;

void countFreq(string file, string symbol[256], int frequency[256], int *size){
    ifstream in(file);
    int freq[256];
    while(!in.eof()){
        char ch;
        in >> ch;
        freq[ch]++;
    }
    in.close();

    for(int i = 0; i<=256; i++){
        if(freq[i] != 0){
            symbol[*size] = (char) i;
            frequency[*size] = freq[i];
            (*size)++;
        }
    }
}
Node* createNode(string symbol, int frequency, Node *left, Node* right){
    Node *newNode = (Node *) malloc(sizeof(Node));

    newNode-> freq = frequency;
    newNode-> symbol = symbol;
    newNode->left = left;
    newNode->right = right;

    return newNode;
}
bool operator<(const Node &x,const Node &y){
    return x.freq > y.freq;
}
Node* generateHuffmanTree(priority_queue<Node> pq){
    while(pq.size() > 1){
        Node temp1 = pq.top();
        pq.pop();

        Node temp2 = pq.top();
        pq.pop();

        pq.push(*createNode(temp1.symbol + temp2.symbol, temp1.freq+temp2.freq, &temp1, &temp2));

    }

    return new Node(pq.top());
}
void generateHuffmanCodes(Node* root, string code, string sym[], string codes[],int *codeIndex){
    if(root == NULL){
        return;
    }
    else if(root->left == NULL && root->right == NULL){
        sym[*codeIndex] = root->symbol;
        codes[*codeIndex] = code;
        cout << sym[*codeIndex] << " : " << code[*codeIndex] << endl;
        codeIndex++;
    }

    generateHuffmanCodes(root->left, code + "0", sym, codes, codeIndex);
    generateHuffmanCodes(root->right, code + "1", sym, codes, codeIndex);

}
int main(){
    string symbol[256];
    int frequency[256];
    int size = 0;
    countFreq("input.txt", symbol, frequency, &size);
    
    priority_queue<Node> pq;
    for(int i = 0; i<size; i++){
        pq.push(*createNode(symbol[i] , frequency[i], NULL, NULL));
    }

    Node* root = generateHuffmanTree(pq);

    string sym[size];   //to store symbols of leafe nodes
    string code[size];   // to store codes for each symbol
    int codeIndex = 0;
    generateHuffmanCodes(root, "", sym, code, &codeIndex);

    ofstream out("huffman_codes.txt");
    for(int i = 0; i<codeIndex; i++){
        cout << sym[i] << " : " << code[i] << endl;
    }
    out.close();
}
