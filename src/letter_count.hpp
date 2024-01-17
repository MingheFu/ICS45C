int char_to_index(char ch){

	if (ch >= 'A' && ch <= 'Z'){
		return ch - 'A';
	} else {
		return -1;
	}
}
char index_to_char(int i){
	return static_cast<char>('A'+ i);
}
void count(string s, int counts[]){
	for (char c : s){
		if (isalpha(c)){
			c = toupper(c);
			int index = char_to_index(c);
			if (index != -1) {
				counts[index]++;
			}
		}
	}
}

void print_counts(int counts[], int len){
	for (int i = 0; i < len; ++i) {
		std::cout << index_to_char(i) << ' ' << counts[i] << '\n';
	}
}

