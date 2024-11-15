#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <math.h>
#include <iomanip>
#include <algorithm>
#include <unordered_set>

#include "Header1.h"

using namespace std;
 
int main()
{
    if ("n" == sentinal("Start", "(y/n)?", "y", "n")) 
        return 0;

    ifstream infile;

    TrieTree trie;


    string filename = "wordlist.txt";

    infile.open(filename); //spellcast words
    if (!infile.is_open()) {
        cout << "\nTerminating program...\n"
            << "file could not be opened\n";
        system("pause");
        return 0;
    }

    cout << "filling Trietree from " << filename << "..." << endl;
    for (string word = ""; infile >> word;) {
        if (validWord(word)) {
            lowerCase(word);
            trie.addWord(word);
        }
    }
    infile.close();


    cout << "Search ended, entering matrix solver" << endl;
    cout << "Enter a list of lowercase letters all on one line from left to right" << endl;
    cout << "type '<' to exit" << endl;
    cout << "matrix>";

    string input = "";
    for (getline(cin, input); input != "<"; getline(cin, input)) {
        if (validWord(input)) {
            lowerCase(input);
            int dems = sqrt(input.size());

            if (dems != sqrt(input.size())) {
                cout << "\n-WARNING- input length of " << input.size() << " is not a square -WARNING-\n";
                cout << "using first " << dems * dems << " letters for matrix" << endl;

            }

            vector<vector<char>> matrix;
            int i = 0;
            for (int x = 0; x < dems; x++) {
                cout << "\n";
                vector<char> row;
                matrix.push_back(row);
                for (int y = 0; y < dems; y++) {
                    cout << "[" << input[i] << "]";
                    matrix[x].push_back(input[i++]);
                }
            }


            cout << "\n\n";
            vector<string> wrds;
            cout << "solving " << dems << "x" << dems << " matrix...\n";
            findWords(matrix, wrds, trie);

            cout << wrds.size() << " words found\n";
            int repeat = 14;
            repeat++;
            if (repeat > wrds.size()) repeat = wrds.size();
            for (int i = wrds.size() - repeat; i < wrds.size(); i++) {
                cout << wrds[i] << " -> " << valuate(wrds[i]) << endl;
            }

            if (dems <= 1)
                cout << "matrix to small to run swaps";
            else if ("y" == sentinal("\ncalculate 1 letter swaps", "(y/n)?", "y", "n")) {
                cout << "-1 letter swaps- ";

                unordered_map<string, aforb> swap;
                wrds.resize(0);
                findSwaps(matrix, wrds, trie, swap);
                cout << wrds.size() << " words found\n";
                repeat = 5;
                repeat++;
                for (int i = wrds.size() - 1; i > wrds.size() - repeat; i--) {
                    string wrd = wrds[i];
                    cout << "[" << swap[wrd].bf[0] << "][" << swap[wrd].af[0] << "]" << wrd << " -> " << valuate(wrd) << endl;
                }

                if ("y" == sentinal("\ncalculating 2 letter swaps will take many seconds especially on larger matrixes\ncalculate 2 letter swaps", "(y/n)?", "y", "n")) {
                    cout << "-swaps2- ";
                    wrds.resize(0);
                    findTwoSwaps(matrix, wrds, trie, swap);
                    cout << wrds.size() << " words found\n";
                    repeat = 5;
                    repeat++;
                    for (int i = wrds.size() - 1; i > wrds.size() - repeat; i--) {
                        string wrd = wrds[i];
                        cout << "[" << swap[wrd].bf[0] << "][" << swap[wrd].af[0] << "] [" << swap[wrd].bf[1] << "][" << swap[wrd].af[1] << "]" << wrd << " -> " << valuate(wrd) << endl;
                    }
                }
            }
        }
        else {
            cout << "invalid input" << endl;
        }
        
        
        cout << "\nmatrix>";
    }
}


