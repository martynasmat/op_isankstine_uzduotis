#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <set>
#include <regex>

using namespace std;

int main() {
    map<string, int> word_map;
    multimap<string, int> line_map;
    set<string> word_set;
    set<string> url_set;

    ifstream file("../text.txt");
    if(!file) {
        cout << "Nepavyko atidaryti failo." << endl;
        return -1;
    }

    ofstream output_count("../word_count.txt");

    string line;
    int line_number = 0;
    while(getline(file, line)) {
        line_number++;
        stringstream ss(line);
        string word;

        while(ss >> word) {
            while (!word.empty() && ::ispunct(word.front())) {
                word.erase(word.begin());
            }
            while (!word.empty() && ::ispunct(word.back())) {
                word.pop_back();
            }

            regex url_regex(R"(https?:\/\/[a-zA-Z0-9\.\/\-\?\=]+|www\.[a-zA-Z0-9\.\/\-\?\=]+|[a-z.]+\.[a-zA-Z0-9\.\/\-\?\=]{2,})");
            smatch url_match;
            if (regex_match(word, url_match, url_regex)) {
                url_set.insert(word);
            }

            word_map[word]++;
            output_count << word << " " << word_map[word] << endl;

            word_set.insert(word);
            line_map.insert(pair<string, int> (word, line_number));
        }
    }
    file.close();
    output_count.close();

    ofstream output_table("../cross-reference.txt");
    output_table << setw(25) << ' ';
    for(int i = 1; i <= line_number; i++) {
        output_table << left << setw(to_string(line_number).length() + 2) << i;
    }
    output_table << endl;
    for (const auto& word : word_set) {
        if (word_map[word] > 1) {
            output_table << setw(25) << left << word;
            for (int i = 1; i <= line_number; i++) {
                auto range = line_map.equal_range(word);
                bool found = false;
                for (auto it = range.first; it != range.second; ++it) {
                    if (it->second == i) {
                        output_table << setw(4) << "X";
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    output_table << setw(4) << " ";
                }
            }
            output_table << endl;
        }
    }

    ofstream output_urls("../urls.txt");
    for (const auto& url : url_set) {
        output_urls << url << endl;
    }
    return 0;
}
