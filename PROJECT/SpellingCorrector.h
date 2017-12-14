#ifndef _SPELLINGCORRECTOR_H_
#define _SPELLINGCORRECTOR_H_
#include<map>
#include<vector>
#include<utility>

class keyboard {
private:
	std::pair<int, int > key[26];
public:
	int distance(char a, char b);
	void make_keyboard();
};

class SpellingCorrector
{
private:
	std::map<std::string, int> dictionary;
	void edits(std::string, std::vector<std::string>&result);
	void known(std::vector<std::string>&results, std::map<std::string, int>&candidates);
public:
	std::map<std::string, std::string> cache;	//Stores the corrections of words for future reference.
	void load(const std::string& filename,int weight=1);
	void load_replacement(const std::string& filename);
	keyboard qwerty;
	std::string correct(std::string &word);
	void AddToKnown(std::string& word, const std::string& filename);
	void saveData(const std::string& filename);
	void add_replacement(const std::string &filename, std::string input, std::string output);
	int is_known(std::string& word);
};

class AutoCorrect
{
public:
	SpellingCorrector corrector;
	void long_correct(std::string& sentence);
};

struct replacement
{
	char initial[25];
	char modified[25];
};

#endif // SPELLINGCORRECTOR_H_INCLUDED
