#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <math.h>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <unordered_set>


using namespace std;

string sentinal(string prePrompt, string repeatPrompt, string accept, string accept2 = "notvalidinput", string accept3 = "notvalidinput", string accept4 = "notvalidinput", string accept5 = "notvalidinput", string accept6 = "notvalidinput") {
    string userInput;
    cout << prePrompt;
    cout << repeatPrompt;
    for (getline(cin, userInput); userInput != accept && userInput != accept2 && userInput != accept3 && userInput != accept4 && userInput != accept5 && userInput != accept6; getline(cin, userInput)) {
        cout << repeatPrompt;
    }
    return userInput;
}

void require(bool conditonal, string msg = "") {
    if (!conditonal) {
        cout << endl << "Requirement not met \"" << msg << "\" Terminating Program..." << endl;
        exit(0);
    }
}

int valuate(string wrd) {
    static unordered_map<string, int> wrdValue;
    if (wrdValue[wrd] != 0) return wrdValue[wrd];

    const int charVal[26] = {
        /* a */  1, /* b */  4, /* c */  5, /* d */  3, /* e */  1,
        /* f */  5, /* g */  3, /* h */  4, /* i */  1, /* j */  7,
        /* k */  6, /* l */  3, /* m */  4, /* n */  2, /* o */  1,
        /* p */  4, /* q */  8, /* r */  2, /* s */  2, /* t */  2,
        /* u */  4, /* v */  5, /* w */  5, /* x */  7, /* y */  4,
        /* z */  8
    };

    int val = 0;

    for (char c : wrd) {
        val += charVal[c - 'a'];
    }

    if (wrd.size() > 5) val += 10;

    wrdValue[wrd] = val;

    return val;
}

struct Node {
    char c;
    bool isPrefix;
    bool isWord;
    Node* child[26]; //child[char - 'a'] i.e. ['a' - 'a'] == [0] // ['z' - 'a'] == [25]

    Node(char _c, bool _isPrefix = false, bool _isWord = false) {
        c = _c;
        isPrefix = _isPrefix;
        isWord = _isWord;
        for (int i = 0; i < 26; i++)
            child[i] = nullptr;

    }

    Node(int _ci, bool _isPrefix = false, bool _isWord = false) {
        require(_ci >= 0 && _ci < 26, "_ci in Node must be between 0, and 25");
        c = char(_ci + 'a');
        isPrefix = _isPrefix;
        isWord = _isWord;
        for (int i = 0; i < 26; i++)
            child[i] = nullptr;
    }
};

class TrieTree {
private:
    Node* root[26];
public:
    TrieTree() {
        for (char c = 'a'; c <= 'z'; c++) {
            root[c - 'a'] = new Node(c);
        }
    }

    bool isWord(string sub) {
        Node* n = access(sub);
        if (n == nullptr) return false;
        return n->isWord;
    }
    bool isPrefix(string sub) {
        Node* crnt = root[sub[0] - 'a'];

        for (int i = 1; i < sub.size(); i++) {
            if (crnt->child[sub[i] - 'a'] == nullptr) return false;
            if (!crnt->child[sub[i] - 'a']->isPrefix) return false;
            crnt = crnt->child[sub[i] - 'a'];
        }
        return crnt->isPrefix;
    }

    Node* access(string sub) {
        if (sub.size() == 0) return nullptr;

        Node* crnt = root[sub[0] - 'a'];

        for (int i = 1; i < sub.size() && crnt != nullptr; i++) {
            crnt = crnt->child[sub[i] - 'a'];
        }
        return crnt;
    }

    void withPrefix(string prefix, vector<string>& returnWords) {
        Node* start = access(prefix);
        if (start == nullptr) return;
        if (start->isWord) returnWords.push_back(prefix);
        if (!start->isPrefix) return;

        for (int i = 0; i < 26; i++) {
            withPrefix(prefix + char('a' + i), returnWords, start->child[i]);
        }
    }
    void withPrefix(string prefix, vector<string>& returnWords, Node* start) {
        if (start == nullptr) return;
        if (start->isWord) returnWords.push_back(prefix);
        if (!start->isPrefix) return;

        for (int i = 0; i < 26; i++) {
            withPrefix(prefix + char('a' + i), returnWords, start->child[i]);
        }
    }

    void addWord(string wrd) { //this function ends by setting the last letter's node->isWord = true
        //ci holds the char's index
        unsigned short int ci = wrd[0] - 'a';

        Node* crnt = root[ci]; //crnt = starting letter node
        crnt->isPrefix = true; //this is a valid path to a word

        for (int i = 1; i < wrd.size() - 1; i++) { //start at the second letter, end at the second to last letter
            ci = wrd[i] - 'a'; //convert char to a 0-25 int

            //if the child letter has not yet been made, is must be created, else, just change it's values
            if (crnt->child[ci] == nullptr) {
                crnt->child[ci] = new Node(wrd[i], true); //define new Node with the letter in question and that it is a Prefix to a word
            }
            else {
                crnt->child[ci]->isPrefix = true; //set Prefix to true incase it was not already true
            }

            crnt = crnt->child[ci]; //go to the node we just made/changed
        }

        ci = wrd[wrd.size() - 1] - 'a';

        if (crnt->child[ci] == nullptr) {
            crnt->child[ci] = new Node(char(ci + 'a'), false, true); //this node should have prefix = false because it is not a prefix to another word yet, it is a word 
        }
        else {
            //no change to prefix incase the node rests on the path of a larger word
            crnt->child[ci]->isWord = true;
        }


    }

};

bool validWord(string wrd) {
    for (char c : wrd) {
        if (!((c >= 'A' && c <= 'z') || (c >= 'a' && c <= 'z'))) {
            return false;
        }
    }
    return true;
}

bool isPrefix(string wrd, vector<string> wrdlist) {
    static unordered_map<string, char> validPrefixes;
    if (validPrefixes[wrd] == 'T') {
        cout << "map used\n";
        return true;
    }
    if (validPrefixes[wrd] == 'F') {
        cout << "map used\n";
        return false;
    }

    for (string l : wrdlist) {
        bool flag = true;

        for (int i = 0; i < wrd.size() && flag; i++) {
            flag = (l[i] == wrd[i]);
        }

        if (flag == true) {
            validPrefixes[wrd] = 'T';
            return true;
        }
    }
    validPrefixes[wrd] = 'F';
    return false;
}

void lowerCase(string& wrd) {
    for (char& c : wrd) {
        c = tolower(c);
    }
}

struct cord {
    int x, y;
};

void /*helper*/findWords(Node* n, vector<vector<char>>& matrix, unordered_set<string>& returnWords, TrieTree trie, string sub, int x, int y) {
    //up, down, right, left, upright, upleft, downright, downleft
    const int dx[] = { 0, 0, 1,-1, 1,-1, 1,-1 };
    const int dy[] = { 1,-1, 0, 0, 1, 1,-1,-1 };
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < matrix.size() && ny >= 0 && ny < matrix[x].size() && matrix[nx][ny] != '#') {
            char hold = matrix[nx][ny];
            matrix[nx][ny] = '#';
            if (n->child[hold - 'a'] != nullptr) {
                if (n->child[hold - 'a']->isWord) {
                    returnWords.insert(sub + hold);
                }
                if (n->child[hold - 'a']->isPrefix) {
                    findWords(n->child[hold - 'a'], matrix, returnWords, trie, (sub + hold), nx, ny);
                }
            }

            matrix[nx][ny] = hold;
        }
    }
}
void findWords(vector<vector<char>>& matrix, vector<string>& returnWords, TrieTree trie) {
    unordered_set<string> wordset;
    for (int x = 0; x < matrix.size(); x++) {
        string hold = " ";
        for (int y = 0; y < matrix[x].size(); y++) {
            hold[0] = matrix[x][y];
            matrix[x][y] = '#';
            findWords(trie.access(hold), matrix, wordset, trie, hold, x, y);

            matrix[x][y] = hold[0];
        }
    }
    for (string x : wordset) {
        returnWords.push_back(x);
    }

    std::sort(returnWords.begin(), returnWords.end(), [](const std::string& a, const std::string& b) {
        return valuate(a) < valuate(b);
        });
}

struct aforb {
    char bf[2], af[2];
};
void /*helper*//*helper*/SfindWords(Node* n, vector<vector<char>>& matrix, unordered_set<string>& returnWords, TrieTree trie, string sub, unordered_map<string, aforb>& swapChar, aforb& changes, int x, int y) {

    //up, down, right, left, upright, upleft, downright, downleft
    const int dx[] = { 0, 0, 1,-1, 1,-1, 1,-1 };
    const int dy[] = { 1,-1, 0, 0, 1, 1,-1,-1 };
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < matrix.size() && ny >= 0 && ny < matrix[x].size() && matrix[nx][ny] != '#') {
            char hold = matrix[nx][ny];
            matrix[nx][ny] = '#';
            if (n->child[hold - 'a'] != nullptr) {
                if (n->child[hold - 'a']->isWord) {
                    swapChar[(sub + hold)] = changes;
                    returnWords.insert(sub + hold);
                }
                if (n->child[hold - 'a']->isPrefix) {
                    SfindWords(n->child[hold - 'a'], matrix, returnWords, trie, (sub + hold), swapChar, changes, nx, ny);
                }
            }

            matrix[nx][ny] = hold;
        }
    }
}
void /*helper*/SfindWords(vector<vector<char>>& matrix, unordered_set<string>& returnWords, TrieTree trie, unordered_map<string, aforb>& swapChar, aforb changes) {

    for (int x = 0; x < matrix.size(); x++) {
        for (int y = 0; y < matrix[x].size(); y++) {
            char hold = matrix[x][y];
            matrix[x][y] = '#';
            string s = " ";
            s[0] = hold;
            SfindWords(trie.access(s), matrix, returnWords, trie, s, swapChar, changes, x, y);

            matrix[x][y] = hold;
        }
    }
}
void /*external*/findSwaps(vector<vector<char>>& matrix, vector<string>& returnWords, TrieTree trie, unordered_map<string, aforb>& swapChar) {
    unordered_set<string> wordset;
    for (int x = 0; x < matrix.size(); x++) {
        if (matrix.size() >= 25) cout << "swaps are " << fixed << setprecision(2) << 100.00 * (double(x) / matrix.size()) << "% solved" << endl;
        for (int y = 0; y < matrix[x].size(); y++) {
            for (char af = 'a'; af <= 'z'; af++) {
                aforb changes;
                char bf = matrix[x][y];
                matrix[x][y] = af;
                changes.bf[0] = bf;
                changes.af[0] = af;
                SfindWords(matrix, wordset, trie, swapChar, changes);
                matrix[x][y] = bf;
            }
        }
    }
    for (string x : wordset) {
        returnWords.push_back(x);
    }

    std::sort(returnWords.begin(), returnWords.end(), [](const std::string& a, const std::string& b) {
        return valuate(a) < valuate(b);
        });
}

void /*two swap helper*/findSwaps(vector<vector<char>>& matrix, unordered_set<string>& wordset, TrieTree trie, unordered_map<string, aforb>& swapChar, aforb& changes) {
    for (int x = 0; x < matrix.size(); x++) {
        if (matrix.size() >= 25) cout << "swaps are " << fixed << setprecision(2) << 100.00 * (double(x) / matrix.size()) << "% solved" << endl;
        for (int y = 0; y < matrix[x].size(); y++) {
            for (char af = 'a'; af <= 'z'; af++) {
                char bf = matrix[x][y];
                matrix[x][y] = af;
                changes.bf[0] = bf;
                changes.af[0] = af;
                SfindWords(matrix, wordset, trie, swapChar, changes);
                matrix[x][y] = bf;
            }
        }
    }
}

void /*external*/findTwoSwaps(vector<vector<char>>& matrix, vector<string>& returnWords, TrieTree trie, unordered_map<string, aforb>& swapChar) {
    unordered_set<string> wordset;
    for (int x = 0; x < matrix.size(); x++) {
        if (matrix.size() >= 25) cout << "swaps are " << fixed << setprecision(2) << 100.00 * (double(x) / matrix.size()) << "% solved" << endl;
        for (int y = 0; y < matrix[x].size(); y++) {
            for (char af = 'a'; af <= 'z'; af++) {
                aforb changes;
                char bf = matrix[x][y];
                matrix[x][y] = af;
                changes.bf[1] = bf;
                changes.af[1] = af;
                findSwaps(matrix, wordset, trie, swapChar, changes);
                matrix[x][y] = bf;
            }
        }
    }
    for (string x : wordset) {
        returnWords.push_back(x);
    }

    std::sort(returnWords.begin(), returnWords.end(), [](const std::string& a, const std::string& b) {
        return valuate(a) < valuate(b);
        });
}


