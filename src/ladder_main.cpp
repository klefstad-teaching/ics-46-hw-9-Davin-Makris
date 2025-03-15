#include "ladder.h"

using namespace std;
int main() {
	set<string> word_list;
	load_words(word_list, "src/words.txt");
	vector<string> ladder = generate_word_ladder("awake", "sleep", word_list);
	print_word_ladder(ladder);
}