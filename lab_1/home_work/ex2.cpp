#include <iostream>
#include <codecvt>
#include <fstream>
#include <string>
#include <vector>

int main(){
	std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>); // спросить зачем эта строчка
	setlocale(0, "");

	std::wifstream in("karatkevich.txt");
	if (!in.is_open()){
		std::cout << "In Error" << std::endl;
		return 1;
	}

	std::vector<std::wstring> vec;
	std::wstring tmp;
	while (in >> tmp) {
		vec.push_back(tmp);
	}
	//std::sort(vec.begin(), vec.end(), [](const std::wstring word, const std::wstring word2){ return word < word2; });

	std::wofstream out("Result_karatkevich.txt");
	if (!out.is_open()){
		std::cout << "Out Error" << std::endl;
		return 1;
	}

	size_t min_word = vec.front().size();
	size_t max_word = vec.front().size();
	for (auto word : vec){
		if (word.length() < min_word ){
			min_word = word.length();
		}
		if (word.length() > max_word){
			max_word = word.length();
		}
	}
	
	out << "Min words:\n";
	size_t min_counter = 0;
	for (auto word : vec){
		if (word.length() == min_word){
			out << word << " ";
			++min_counter;
		}
	}
	out << "\n\nMax words:\n";
	size_t max_counter = 0;
	for (auto word : vec){
		if (word.length() == min_word){
			out << word << " ";
			++max_counter;
		}
	}

	out << "\n\nMin words: " << min_counter << "\n";
	out << "Max words: " << max_counter << "\n";

	in.close();
	out.close();
	return 0; 
}
