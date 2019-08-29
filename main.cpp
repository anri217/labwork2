#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

char* readFile(const char filename[]) 
{
	ifstream in(filename, ios::binary); // Open input stream from file
	in.seekg(0, ios::end);
	int length = in.tellg();
	char* str = new char[length + 1];
	in.seekg(0, ios::beg);
	in.read(str, length);
	str[length] = '\0';

	in.close();

	return str;
}

const char vowels[20] = { 'а', 'е', 'ё', 'и', 'о', 'у', 'ы', 'э', 'ю', 'я', 'А', 'Е', 'Ё', 'И', 'О', 'У', 'Ы', 'Э', 'Ю', 'Я' };
bool isVowel(char a)
{
	for (size_t i = 0; i < 20; ++i) {
		if (a == vowels[i]) return true;
	}
	return false;
}

vector <char*> textHandler(char* str)
{
	int i = 0, startIndex = -1;

	vector <char*> words;

	while (str[i] != '\0') {
		if (((str[i + 1] == ' ') || (str[i + 1] == '\0')) && startIndex != -1) { //i указывает на последнюю букву в слове
			bool isValid = true;
			for (size_t j = startIndex; j <= i; ++j) {
				if (!((str[j] >= 'а' && str[j] <= 'я') || (str[j] >= 'А' && str[j] <= 'Я'))) {
					isValid = false;
				}
			}
			if (isValid) {
				isValid = false;
				for (size_t j = startIndex; j < i && !isValid; ++j) {
					isValid = isVowel(str[j]) && isVowel(str[j + 1]);
				}
				if (isValid) {
					char* word = new char[i - startIndex + 2];
					strncpy_s(word, i - startIndex + 2, str + startIndex, i - startIndex + 1);//куда копируем, сколько нужно выделить, с какого места начинаем копировать, сколько копируем
					words.push_back(word);
				}
			}
			startIndex = -1;
		}
		else if (str[i] != ' ' && startIndex == -1) startIndex = i;
		++i;
	}

	return words;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	ifstream ifs("input.txt");
	char* str = readFile("input.txt");
	ifs.close();

	vector <char*> gWords = textHandler(str);

	cout << "All text: " << str << endl;

	cout << "Valid words: ";
	for (size_t i = 0; i < gWords.size(); ++i) {
		cout << gWords[i] << " ";
	}

	delete[] str;
	for (size_t i = 0; i < gWords.size(); ++i) {
		delete[] gWords[i];
	}

	system("pause");
	return 0;
}