// C++(STL) program for Huffman Coding with STL 
#include <iostream> 
#include <string> 
#include <vector>
#include<queue> 
#include<map>
#include<fstream>
using namespace std; 

unordered_map<char,string> codes;

// A Huffman tree node 
struct MinHeapNode { 

	
	char data; // One of the input characters 
	unsigned freq; // frequency of the character

	MinHeapNode *left, *right; // Left and right child 

	MinHeapNode(char data, unsigned freq) 
	{ 

		left = right = NULL; 
		this->data = data; 
		this->freq = freq; 
	} 
}; 

// For comparison of 
// two heap nodes (needed in min heap) 
struct compare { 

	bool operator()(MinHeapNode* l, MinHeapNode* r) 
	{ 
		return (l->freq > r->freq); 
	} 
}; 

// Prints huffman codes from 
// the root of Huffman Tree. 
void printCodes(struct MinHeapNode* root, string str) 
{ 

	if (!root) 
		return; 

	if (root->data != '$') {
		codes[root->data] = str;
		cout << root->data << ": " << str << "\n"; 
	}

	printCodes(root->left, str + "0"); 
	printCodes(root->right, str + "1"); 
} 

// The main function that builds a Huffman Tree and 
// print codes by traversing the built Huffman Tree 
void HuffmanCodes(vector<char> &data, vector<int> &freq, int size) 
{ 
	struct MinHeapNode *left, *right, *top; 
	

	// Create a min heap & inserts all characters of data[] 
	priority_queue<MinHeapNode*, vector<MinHeapNode*>, 
				compare> 
		minHeap; 

	for (int i = 0; i < size; ++i) 
		minHeap.push(new MinHeapNode(data[i], freq[i])); 

	// Iterate while size of heap doesn't become 1 
	while (minHeap.size() != 1) { 

		// Extract the two minimum 
		// freq items from min heap 
		left = minHeap.top(); 
		minHeap.pop(); 

		right = minHeap.top(); 
		minHeap.pop(); 

		top = new MinHeapNode('$',left->freq + right->freq); 

		top->left = left; 
		top->right = right; 

		minHeap.push(top); 
	} 

	// Print Huffman codes using 
	// the Huffman tree built above 

	printCodes(minHeap.top(), ""); 
} 

// Driver Code 
int main() 
{ 
    int c = 0;
    map<char,int> mpp;
    ifstream fin("iiests.txt");
    char ch;

    while (fin >> noskipws >> ch) {
		mpp[ch]++;	
	}	
    vector<char> arr;
    vector<int> freq;
    for(auto it : mpp){
        arr.push_back(it.first);
        freq.push_back(it.second);
    }
	fin.close();
	int size = arr.size();

	HuffmanCodes(arr, freq, size); 

	ifstream finput("iiests.txt");
	ofstream foutput("encoded-iiests.txt");

	
	while (finput >> noskipws >> ch) {
		foutput<<codes[ch];
	}
	
	finput.close();
	foutput.close();

	return 0; 
} 

