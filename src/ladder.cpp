#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << endl;
    exit(EXIT_FAILURE);
}

bool is_adjacent(const string& word1, const string& word2) {
    int len1 = word1.length(), len2 = word2.length();
    if (abs(len1 - len2) > 1) return false;

    int diff = 0, i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (word1[i] != word2[j]) {
            if (++diff > 1) return false;
            if (len1 > len2) i++;  
            else if (len2 > len1) j++;  
            else { i++; j++; }  
        } else { i++; j++; }
    }
    return true;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        return {};
    }

    queue<vector<string>> ladder_queue;
    set<string> visited;
    
    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        
        string last_word = ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                
                if (word == end_word) {
                    return new_ladder;
                }

                ladder_queue.push(new_ladder);
                visited.insert(word);
            }
        }
    }
    return {};
}


void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Unable to open file " << file_name << endl;
        exit(EXIT_FAILURE);
    }

    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }

    cout << "Word ladder found: ";

    cout << ladder[0];
    for (size_t i = 1; i < ladder.size(); ++i) {
        cout << " " << ladder[i];
    }
    cout << " \n";
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.length(), len2 = str2.length();
    if (abs(len1 - len2) > d) return false;

    int diff = 0, i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            if (++diff > d) return false;  
            if (len1 > len2) i++;  
            else if (len2 > len1) j++;  
            else { i++; j++; }  
        } else { i++; j++; }
    }
    return true;
}