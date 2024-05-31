#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    map<string, int> word_map;
    multimap<string, int> line_map;
    vector <string> urls;

    ifstream file("C:\\Users\\marty\\Documents\\objektinis_isankstine\\text.txt");
    if(!file) {
        cout << "Nepavyko atidaryti failo." << endl;
        return -1;
    }

    string line;
    int line_number = 0;
    while(getline(file, line)) {
        line_number++;
        stringstream ss(line);
        string word;

        while(ss >> word) {
            word[0] = toupper(word[0]);
            if (::ispunct(word[0])) {
                word.erase(0);
            } else if (::ispunct(word[word.length() - 1])) {
                word.erase(word.length() - 1);
            }
            word_map[word]++;
            cout << word << " " << word_map[word] << endl;

            line_map.insert(pair<string, int> (word, line_number));
            cout << word << " " << line_number << endl;
        }
    }
    return 0;
}
