#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

vector<string> split_string(string);

struct TrieNode {
  char ch;
  bool end;
  unordered_map<char, TrieNode*> map_;
  TrieNode(char ch_) : ch(ch_), end(false) {}
  TrieNode(){}
};

void add_to_trie(const string contact, TrieNode* root_ptr) {
  TrieNode* cur_ptr = root_ptr;
  for (int i=0; i<contact.size(); i++) {
    if (cur_ptr->map_.find(contact[i]) != cur_ptr->map_.end()) {
        // Found the character so go to the that trie node.
        cur_ptr = cur_ptr->map_.find(contact[i])->second;
    } else {
        // We did not find it, so add new node.
        TrieNode* temp_ptr = new TrieNode(contact[i]);
        cur_ptr->map_[contact[i]] = temp_ptr;
        cur_ptr = temp_ptr;
    }
  }
  // We reached end , ie last character, we we should denote end of 
  // character.
  cur_ptr->end = true;
}

int find_words(TrieNode* ptr) {
    int count = 0;
    if(ptr->end) {
        count++;
    }
    for (auto iter = ptr->map_.begin(); iter != ptr->map_.end(); iter++) {
      count += find_words(iter->second);
    }
    return count;
}
int find_from_trie(const string contact, TrieNode* root_ptr) {
    int nums = 0;
    bool incomplete_word = false;
    TrieNode* temp_ptr = root_ptr;
    for (int i=0; i<contact.size();i++) {
      if (temp_ptr->map_.find(contact[i]) == temp_ptr->map_.end()) {
        // We dont have one of the chars, so exiting here itself.
        incomplete_word = true;
        break;
      } else {
        temp_ptr = temp_ptr->map_.find(contact[i])->second;
      }
    }
    // Now we found the contact prefix, we need to go through remaining
    // possible words and count the words.
    if (!incomplete_word)
       nums = find_words(temp_ptr);
    return nums;
}
int main()
{
    const string add = "add";
    const string find = "find";
    TrieNode* trie_pointer = new TrieNode('*');
    
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int n_itr = 0; n_itr < n; n_itr++) {
        string opContact_temp;
        getline(cin, opContact_temp);

        vector<string> opContact = split_string(opContact_temp);

        string op = opContact[0];
        string contact = opContact[1];
        if (op == add) {
            add_to_trie(contact, trie_pointer);
        } else if (op == find) {
            cout << find_from_trie(contact, trie_pointer) << endl;
        }
    }

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
