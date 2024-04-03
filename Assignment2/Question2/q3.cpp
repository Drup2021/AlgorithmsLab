// C++ program to encode and decode a string using
// Huffman Coding.
#include <iostream>
#include <fstream>
#include <vector>
#include<queue>
#include<map>
#define MAX_TREE_HT 256
using namespace std;

// to map each character its huffman value
map<char, string> codes;
map<string,char> invertCodes;
// To store the frequency of character of the input data
map<char, int> freq;

// A Huffman tree node
struct MinHeapNode {
	char data; // One of the input characters
	int freq; // Frequency of the character
	MinHeapNode *left, *right; // Left and right child

	MinHeapNode(char data, int freq)
	{
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

// utility function for the priority queue
struct compare {
	bool operator()(MinHeapNode* l, MinHeapNode* r)
	{
		return (l->freq > r->freq);
	}
};

// utility function to print characters along with
// there huffman value
void printCodes(struct MinHeapNode* root, string str)
{
	if (!root)
		return;
	if (root->data != '$')
		cout << root->data << ": " << str << "\n";
	printCodes(root->left, str + "0");
	printCodes(root->right, str + "1");
}

// utility function to store characters along with
// there huffman value in a hash table, here we
// have C++ STL map
void storeCodes(struct MinHeapNode* root, string str)
{
	if (root == NULL)
		return;
	if (root->data != '$')
		codes[root->data] = str;
	storeCodes(root->left, str + "0");
	storeCodes(root->right, str + "1");
}

// STL priority queue to store heap tree, with respect
// to their heap root node value
priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare>
	minHeap;

// function to build the Huffman tree and store it
// in minHeap
void HuffmanCodes(int size)
{
	struct MinHeapNode *left, *right, *top;
	for (map<char, int>::iterator v = freq.begin();
		v != freq.end(); v++)
		minHeap.push(new MinHeapNode(v->first, v->second));
	while (minHeap.size() != 1) {
		left = minHeap.top();
		minHeap.pop();
		right = minHeap.top();
		minHeap.pop();
		top = new MinHeapNode('$',
							left->freq + right->freq);
		top->left = left;
		top->right = right;
		minHeap.push(top);
	}
	storeCodes(minHeap.top(), "");
}

// utility function to store map each character with its
// frequency in input string
void calcFreq(string str, int n)
{
	for (int i = 0; i < str.size(); i++)
		freq[str[i]]++;
}

// function iterates through the encoded string s
// if s[i]=='1' then move to node->right
// if s[i]=='0' then move to node->left
// if leaf node append the node->data to our output string
string decode_file(struct MinHeapNode* root, string s)
{
	string ans = "";
	struct MinHeapNode* curr = root;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '0')
			curr = curr->left;
		else
			curr = curr->right;

		// reached leaf node
		if (curr->left == NULL and curr->right == NULL) {
			ans += curr->data;
			curr = root;
		}
	}
	// cout<<ans<<endl;
	return ans + '\0';
}
string decode_instantaneous(string text){
	string temp_string = "";
	string ans = "";
	for(char it : text){
		temp_string += it;
		if(invertCodes.find(temp_string) != invertCodes.end()){
			ans += invertCodes[temp_string];
			temp_string = "";
		}
	}
	return ans;
}
// Driver code
int main()
{
	string str;
	ifstream fin("iiests2.txt");
	char ch;
	while (fin >> noskipws >> ch) {
		str += ch;
	}	
	string encodedString, decodedString;
	calcFreq(str, str.length());
	HuffmanCodes(str.length());
	cout << "Character With their Frequencies:\n";
	for (auto v = codes.begin(); v != codes.end(); v++)
		cout << v->first << ' ' << v->second << endl;

	for (auto i : str)
		encodedString += codes[i];

	cout << "\nEncoded Huffman data:\n"
		<< encodedString << endl;

	// Function call

	for(auto it : codes){
		invertCodes[it.second] = it.first;
	}
	int totalFreq;
	for(auto it : freq){
		totalFreq += it.second;
	}

	map<char,float>prob;
	for(auto it : freq){
		prob[it.first] = (float)(it.second) / totalFreq;
	}
	float entropy=0;
	for(auto it : prob){
		entropy += it.second * log(it.second);
	}
	entropy *= -1;
	entropy /= log(2);

	cout<<"Entropy is : "<<entropy<<endl;
	int numerator = 0;
	int denominator = 0;
	string newstr = "the sun dipped below the horizon, casting a golden glow over the tranquil meadow. a gentle breeze rustled through the tall grass, carrying with it the sweet scent of wildflowers. nestled among the swaying blades, a small rabbit named oliver watched as the world around him began to slumber. oliver had always been a dreamer, his mind filled with visions of faraway lands and grand adventures. while other rabbits spent their days foraging for food and tending to their burrows, oliver would often wander to the edge of the meadow, gazing longingly at the distant mountains that beckoned to him like silent sentinels.tonight, as the stars began to twinkle overhead, oliver felt an irresistible urge to explore. with a determined hop, he set off into the unknown, his heart brimming with excitement and anticipation.the night was alive with the sounds of nocturnal creatures, their calls echoing through the darkness. oliver paid them no mind, his eyes fixed on the towering peaks that loomed ever closer with each step. he had heard tales of a hidden valley beyond the mountains, a place where magic danced on the wind and dreams took flight.as dawn broke on the horizon, oliver crested the final ridge and beheld the valley spread out before him in all its splendor. it was a place of breathtaking beauty, where crystal-clear streams meandered through lush meadows and ancient forests whispered secrets to the wind.overwhelmed by the sheer magnificence of it all, oliver felt tears prickling at the corners of his eyes. this was the adventure he had always dreamed of, a journey into the heart of the unknown where anything was possible.for days, oliver wandered the valley, drinking in its wonders and forging friendships with its inhabitants. he danced with fireflies beneath the moonlit sky, sang songs with the birds in the treetops, and raced with the deer through fields of wildflowers.but as the days turned into weeks, oliver began to feel a tug at his heartstrings, a longing for the familiar comforts of home. despite the beauty that surrounded him, he missed his family and the simple joys of life in the meadow.with a heavy heart, oliver bid farewell to his newfound friends and set off on the long journey back to the meadow. as he retraced his steps through the mountains, he carried with him memories that would last a lifetime and a renewed appreciation for the beauty of the world around him.when at last he reached the edge of the meadow, oliver was greeted with open arms by his family and friends. though he had returned home, he knew that a part of him would forever remain in the enchanted valley, a testament to the power of dreams and the magic that lies within us all.";
	
	// map<char,int> freq_new;
	// for(auto it : newstr){
	// 	freq_new[it]++;
	// }
	// for(auto it : codes){
	// 	numerator += it.second.length() * freq_new[it.first];
	// 	denominator += freq_new[it.first];
	// }

	for(auto it : codes){
		numerator += it.second.length() * freq[it.first];
		denominator += freq[it.first];
	}

	
	// decodedString = decode_file(minHeap.top(), encodedString);
	string decodedStr = decode_instantaneous(encodedString);
	cout << "\nDecoded Huffman Data:\n"<< decodedStr << endl;

	float avg_code_len = (float)numerator / denominator;
	cout<<" The average code length  : "<<avg_code_len; 
	fin.close();
	return 0;
}
