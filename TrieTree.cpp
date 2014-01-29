#include<iostream>
#include<string>
#include<map>
#include <vector>

using namespace std;

#warning update it for supporing unicode character
const int branchNum = 26;

struct TrieNode
{
	bool isStrEnd;
	TrieNode *next[branchNum];
	TrieNode()
	{
		isStrEnd = false;
		memset(next, NULL, sizeof(next));
	}
};

class TrieTree
{
public:
	TrieTree();
	~TrieTree();
    
	void createNewShuashua(string keyword);
    vector<string> findAllShuashua(string keyword);
    
// TODO: Search Shuashua By tag and keyword
    void createNewShuashua(string tag, string keyword);
    vector<string> findAllShuashua(string tag, string keyword);
    
private:
	void findShuashuaByKeyword(TrieNode *node, string keyword, vector<string>& word);
	void deleteShuashua(TrieNode *node);
    
	TrieNode *root;
};

TrieTree::TrieTree()
{
	root = new TrieNode();
}

TrieTree::~TrieTree()
{
	deleteShuashua(root);
}

void TrieTree::createNewShuashua(string keyword)
{
	TrieNode *node = root;
	for (int i = 0; i < keyword.length(); i++)
	{
		if (node->next[keyword[i] - 'a'] == NULL)
		{
			node->next[keyword[i] - 'a'] = new TrieNode();
		}
		node = node->next[keyword[i] - 'a'];
	}
	node->isStrEnd = true;
}

void TrieTree::deleteShuashua(TrieNode *node)
{
	if (node == NULL) return;
    
	for (int i = 0; i < branchNum; i++)
	{
		deleteShuashua(node->next[i]);
	}
	delete node;
}

vector<string> TrieTree::findAllShuashua(string keyword)
{
	vector<string> result;
    
	int i;
	TrieNode *node = NULL;
    
	for (i = 0, node = root; i < keyword.length() && node != NULL; i++)
	{
		node = node->next[keyword[i] - 'a'];
	}
    
	if (node == NULL) return result;
    
	findShuashuaByKeyword(node, keyword, result);
    
	return result;
}

void TrieTree::findShuashuaByKeyword(TrieNode *node, string keyword, vector<string>& word)
{
	if (node == NULL) return;
	if (node->isStrEnd) word.push_back(keyword);
    
	for (int i = 0; i < branchNum; i++)
	{
        string newKeyword = keyword + (char)('a' + i);
		findShuashuaByKeyword(node->next[i], newKeyword, word);
	}
}
                                     
int main()
{
    TrieTree t;
    t.createNewShuashua("a");
    t.createNewShuashua("abandon");
    t.createNewShuashua("abandoned");
    t.createNewShuashua("abashed");
    
    vector<string> tips = t.findAllShuashua("ab");
    for(int i = 0 ; i < tips.size() ; i ++)  
        cout << tips[i] << endl;
    
    return 0;
}
