#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <codecvt>
#include <fstream>
#include <string>


int main(){
	std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
	
	std::ifstream in("text.txt");
	if (!in.is_open()){
		std::cout << "In Error" << std::endl;
		return 1;
	}

	std::wofstream out("ex1.txt");
	if (!out.is_open()){
		std::cout << "out Error" << std::endl;
		return 1;
	}

	std::string tmp;
	while (std::getline(in, tmp)) {
		size_t len = mbstowcs(NULL, tmp.c_str(), 0) + 1;
		wchar_t* tmp2 = new wchar_t[len];
		int count = mbstowcs(tmp2, tmp.c_str(), len);
		out << tmp2 << std::endl;
		delete[]tmp2;
	}
	
	in.close();
	out.close();
	return 0; 
}
