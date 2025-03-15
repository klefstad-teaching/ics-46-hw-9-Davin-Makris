#include "ladder.h"

void error(string word1, string word2, string msg){
	std::cerr << "HEY YOU! werds" << word1 << word2 << "msg: " << msg << std::endl; 
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
	if (-1 * d <= int(str1.length() - str2.length()) && (int(str1.length() - str2.length()) <= d)){
		if (str1.length() == str2.length()){
				return is_adjacent_same_len(str1, str2, d);
		}
		return is_adjacent_diff_len(str1, str2, d);
	}
	return false;
}
/*
vector<string> all_word_variations(const string& str){
	vector<string> variations;
	size_t stringlen = str.length();
	for (size_t i = 0; i <= stringlen; ++i){
		string word = str.substr(0, i) + "*" + str.substr(i, stringlen-i);
		variations.push_back(word);	
	}
	for (size_t i = 0; i < stringlen; ++i){
		string word = str;
		word.replace(i, 1, "*");
		variations.push_back(word);
	}
	return variations;
}
*/
bool is_adjacent_same_len(const string& word1, const string& word2, int d){
	int differing_chars = 0;
	for (size_t i = 0; i < word1.length() && differing_chars <= d; ++i){
		if (word1[i] != word2[i])
			++differing_chars;
	}
	return differing_chars <= d;
}
bool is_adjacent_diff_len(const string& word1, const string& word2, int d){
	string shorter, longer;
	(word1.length() > word2.length()) ? (longer = word1, shorter = word2) : (longer = word2, shorter = word1);
	int differing_chars = 0;
	for (size_t i = 0, j = 0; i < longer.length() && j < shorter.length() && differing_chars <=d;){
		if (shorter[j] != longer[i]){
			
			++differing_chars;
			++i;
		}
		else {
			++i;
			++j;
		}
	}
	return differing_chars <= d;
}

bool is_adjacent(const string& word1, const string& word2){
	return (edit_distance_within(word1, word2, 1));
}
string to_lowercase(const string& word){
	string lc_word = word;
	for (size_t i=0; i < word.length(); ++i)
		lc_word[i] = tolower(lc_word[i]);
	return lc_word;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
	queue<vector<string>> ladder_queue;
	ladder_queue.push({to_lowercase(begin_word)});
	set<string> visited;
	visited.insert(to_lowercase(begin_word));
	string lc_end_word = to_lowercase(end_word);

	while (!ladder_queue.empty()){
		vector<string> ladder = ladder_queue.front();
		ladder_queue.pop();
		const string last_word = ladder.back();
		for (const auto& word: word_list){
			if (is_adjacent(last_word, word)){
				if (visited.find(word) == visited.end()){
					visited.insert(word);
					vector<string> new_ladder = ladder;
					new_ladder.push_back(word);
					if (word == lc_end_word){
						if (new_ladder.size() == 1)
							return {};
						return new_ladder;
					}
					ladder_queue.push(new_ladder);
					cout << "created ladder ";
					for (const auto& wordString: new_ladder)
						cout << wordString << " ";
					cout << endl;
				}
				
			}
		}
	} 
	error(begin_word, end_word, "no ladder found");
	return {"No word ladder found.\n"};
}

void load_words(set<string> & word_list, const string& file_name){
	ifstream file; 
    file.open(file_name);
	string word;
	while (file >> word){
	    word_list.insert(to_lowercase(word));
	}
    file.close();		
}

void print_word_ladder(const vector<string>& ladder){
	cout << "Word ladder found: ";
	for (string word: ladder)
		cout << word << " ";
	cout << endl;
}
void verify_word_ladder(){
	
}