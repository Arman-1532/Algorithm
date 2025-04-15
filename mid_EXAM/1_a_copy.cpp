#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

typedef struct node
{
    int freq;
    string symbol;
    struct node *left;
    struct node *right;
} Node;

bool operator<(const Node &x, const Node &y)
{
    return x.freq > y.freq;
}

Node createNode(string sym, int frequency, Node *left, Node *right)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->freq = frequency;
    newNode->symbol = sym;
    newNode->left = left;
    newNode->right = right;

    return *newNode;
}

void print_queue(priority_queue<Node> pq)
{
    while (pq.size() > 0)
    {
        Node tmp1 = pq.top();
        pq.pop();
        cout << tmp1.symbol << ": " << tmp1.freq << endl;
    }
}

void generateCodes(Node *root, string code, vector<pair<string, string>> &huffmanCodes)
{
    if (!root)
        return;

    if (!root->left && !root->right)
    {
        huffmanCodes.push_back(make_pair(root->symbol, code));
    }

    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

vector<pair<string, string>> generateHuffmanCodes(const string &freqFileName)
{
    ifstream freqFile(freqFileName);
    if (!freqFile)
    {
        cerr << "Error: Unable to open " << freqFileName << endl;
        exit(1);
    }

    priority_queue<Node> pq;
    string line;

    while (getline(freqFile, line))
    {
        if (line.empty())
            continue;

        string symbol;
        int frequency;

        if (line[0] == ' ')
        {
            symbol = " ";
            frequency = stoi(line.substr(1));
        }
        else
        {
            size_t spacePos = line.find(' ');
            symbol = line.substr(0, spacePos);
            frequency = stoi(line.substr(spacePos + 1));
        }

        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->freq = frequency;
        newNode->symbol = symbol;
        newNode->left = nullptr;
        newNode->right = nullptr;
        pq.push(*newNode);
    }

    freqFile.close();

    while (pq.size() > 1)
    {
        Node tmp1 = pq.top();
        pq.pop();
        Node tmp2 = pq.top();
        pq.pop();

        pq.push(createNode(tmp1.symbol + tmp2.symbol, tmp1.freq + tmp2.freq, new Node(tmp1), new Node(tmp2)));
    }

    Node *root = new Node(pq.top());

    vector<pair<string, string>> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    return huffmanCodes;
}
int main()
{
    // Reading symbols and frequencies from a file
    ifstream freqFile("frequencies.txt");
    if (!freqFile)
    {
        cerr << "Error: Unable to open frequencies.txt" << endl;
        return 1;
    }

    priority_queue<Node> pq;
    string line;

    while (getline(freqFile, line))
    { // Read each line, including whitespace
        if (line.empty())
            continue; // Skip empty lines

        string symbol;
        int frequency;

        // Handle whitespace explicitly
        if (line[0] == ' ')
        {
            symbol = " ";                     // Assign the space symbol
            frequency = stoi(line.substr(1)); // Extract frequency from the rest of the line
        }
        else
        {
            size_t spacePos = line.find(' ');            // Find the space separator
            symbol = line.substr(0, spacePos);           // Extract symbol
            frequency = stoi(line.substr(spacePos + 1)); // Extract frequency
        }

        // Create a new node and push it into the priority queue
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->freq = frequency;
        newNode->symbol = symbol;
        newNode->left = nullptr;
        newNode->right = nullptr;
        pq.push(*newNode);
    }

    freqFile.close();

    cout << "Initial Priority Queue:" << endl;
    print_queue(pq);

    while (pq.size() > 1)
    {
        Node tmp1 = pq.top();
        pq.pop();
        Node tmp2 = pq.top();
        pq.pop();

        pq.push(createNode(tmp1.symbol + tmp2.symbol, tmp1.freq + tmp2.freq, new Node(tmp1), new Node(tmp2)));
    }

    Node *root = new Node(pq.top());

    // Generate Huffman codes
    vector<pair<string, string>> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    cout << "Huffman Codes:" << endl;
    for (const auto &code : huffmanCodes)
    {
        cout << code.first << ": " << code.second << endl;
    }
    return 0;
}