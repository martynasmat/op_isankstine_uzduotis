#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;

int main() {
    map<string, int> word_map;

    ifstream file("C:\\Users\\marty\\Documents\\objektinis_isankstine\\text.txt");
    if(!file) {
        cout << "Nepavyko atidaryti failo." << endl;
        return -1;
    }

    string word;
    while(file >> word) {
        word[0] = toupper(word[0]);
        if(::ispunct(word[0])) {
            word.erase(0);
        }else if(::ispunct(word[word.length() - 1])) {
            word.erase(word.length() - 1);
        }
        word_map[word]++;
        cout << word << " " << word_map[word] << endl;
    }
    return 0;
}
