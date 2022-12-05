#include <iostream>
#include <set>
using namespace std;
const int ALPHABET_SIZE = 26;
struct TrieTree {
	TrieTree* alphabet[ALPHABET_SIZE];
	bool isEndOfWord;
};
struct TrieTree* getNode()
{
    struct TrieTree* pNode = new TrieTree;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->alphabet[i] = NULL;

    return pNode;
}

void insert(struct TrieTree* root, string key)
{
    struct TrieTree* pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->alphabet[index])
            pCrawl->alphabet[index] = getNode();

        pCrawl = pCrawl->alphabet[index];
    }


    pCrawl->isEndOfWord = true;
}

void inside(TrieTree* tmp,set<char>&sad2) {
    bool f2 = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (tmp->alphabet[i]) f2 = 1;
    }
    if (!f2) return;
    if (sad2.empty()) return;
    set<char>::iterator it, it2;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (tmp->alphabet[i]) {
            it = sad2.begin();
            char c = *it - 'a';
            bool f = 0;
            for (int j = 0; j < sad2.size(); j++) {
                if (i == c) {
                    it = sad2.erase(it);
                    f = 1;
                }
                else {
                    it2 = it;
                    it2++;
                    if (it2 != sad2.end()) {
                        it++;
                        c = *it - 'a';
                    }
                }
            }
            inside(tmp->alphabet[i],sad2);
            if (sad2.empty()) return;
        }
    }
}
bool searchLetters(TrieTree* root,string s) {
    set<char> sad;
    for (int i = 0; i < s.length(); i++) {
        sad.insert(s[i]);
    }
    set<char> sad2;
    set<char>::iterator it,it2;
    TrieTree* tmp = root;   
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sad2 = sad;
        if (tmp->alphabet[i]) {
            it = sad2.begin();
            char c = *it - 'a';
            bool f = 0;
            for (int j = 0; j < sad2.size(); j++) {
                if (i == c) {
                    it = sad2.erase(it);
                    f = 1;
                }
                else {
                    it2 = it;
                    it2++;
                    if (it2 != sad2.end()) {
                        it++;
                        c = *it - 'a';
                    }
                }
            }
            if (sad2.empty()) return true;
            inside(tmp->alphabet[i], sad2);
        }
        if (sad2.empty()) return true;
    }
    return false;
}

int main() {
    string keys[] = { "the", "a", "there",
                   "answer", "any", "by",
                    "bye", "their","hrdstz"};
    int n = sizeof(keys) / sizeof(keys[0]);

    struct TrieTree* root = getNode();

    for (int i = 0; i < n; i++)
        insert(root, keys[i]);

    string s;
    cin >> s;
    cout << searchLetters(root,s);

}