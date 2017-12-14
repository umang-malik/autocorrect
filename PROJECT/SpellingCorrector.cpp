#include<iostream>
#include<algorithm>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<utility>

#include "SpellingCorrector.h"

using namespace std;
/*MEMBER FUNCTIONS OF CLASS KEYBOARD*/
int Abs(int a)
{
	return (a>0) ? a : -a;
}

/*Function to find the distance between two keys*/
int keyboard::distance(char a, char b)
{
	return Abs(key[a - 'a'].first - key[b - 'a'].first) + Abs(key[a - 'a'].second - key[b - 'a'].second);
}

/*Function to initialize the keyboard*/
void keyboard::make_keyboard()
{
	char K[3][10] = { { 'q','w','e','r','t','y','u','i','o','p' },{ 'a','s','d','f','g','h','j','k','l' },{ 'z','x','c','v','b','n','m' } };
	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<10; j++)
		{
			key[K[i][j] - 'a'].first = i;
			key[K[i][j] - 'a'].second = j;
		}
	}
}

/*MEMBER FUNCTIONS OF THE CLASS SpellingCorrector*/

/*Function to compare two elements on the basis of the frequency*/
bool Compare(const pair<string, int> &lhs, const pair<string, int> &rhs)
{
	return lhs.second<rhs.second;
}

/*Function to filter the non alphabetic elements of a text file*/
void Filter(char str[], size_t length)
{
	for (unsigned int i = 0; i<length; i++)
	{
		if (isalpha(str[i]))
			str[i] = tolower(str[i]);
		else
			str[i] = '-';
	}
}

/*Function to load the dictionary*/
void SpellingCorrector::load(const string& filename,int weight)
{
	/*copying the file to an array*/
	ifstream file(filename.c_str(), ios_base::in);
	file.seekg(0, ios_base::end);
	size_t length = file.tellg();
	file.seekg(0, ios_base::beg);
	string data(length, '0');
	file.read(&data[0], length);
	file.close();

	/*Filtering the elements of the array*/
	Filter(&data[0], length);

	/*Adding the words to the Dictionary*/

	string temp;
	for (unsigned int i = 0; i<length; i++)
	{
		if (data[i] == '-')
		{
			if (temp != "")
				dictionary[temp]+=weight;
			temp = "";
			continue;
		}
		else
			temp = temp + data[i];
	}
}

/*Function to check if a word is in the dictionary.*/
int SpellingCorrector::is_known(string& word)
{
	const map<string, int>::iterator it = dictionary.find(word);
	if (it != dictionary.end())
		return 1;
	else
		return 0;
}

/*Function to find the correction*/
//Returns the top 3 words concatenated by '+' sign.
string SpellingCorrector::correct(string &original_word)    //Original_word can be in any case.
{
	vector<string> result;
	map<string, int> candidates;
	string word = original_word, words_returned = "" ;
	
	for (unsigned int i = 0; i<word.length(); i++)
	{
		word[i] = tolower(word[i]);
	}

	if (dictionary.find(word) != dictionary.end())
		words_returned =words_returned + original_word + "+";    //If word is found in dictionary																	/*Finding the elements which are 1 edit away.*/
	
	map<string, string>::iterator it1 = cache.find(word);	//If word is found in the cache.
	if (it1 != cache.end())
		return it1->second + "+ + ";

	/*First Edit Words*/
	edits(word, result);
	known(result, candidates);

	/* 1 Edit:2 Edit = 50:1 */

	for (map<string, int>::iterator it = candidates.begin(); it != candidates.end(); it++)
		it->second *= 50;

	/*Finding the elements which are 2 edits away.*/
	for (unsigned int i = 0; i<result.size(); i++)
	{
		vector<string> subresult;
		edits(result[i], subresult);
		known(subresult, candidates);
	}


	if (candidates.size() > 0)
	{	
		string temp_str;
		temp_str = max_element(candidates.begin(), candidates.end(), Compare)->first;
		words_returned += temp_str + '+';
		candidates[temp_str] = 0;
		temp_str = max_element(candidates.begin(), candidates.end(), Compare)->first;
		words_returned = words_returned + temp_str + '+';
		candidates[temp_str] = 0;
		temp_str = max_element(candidates.begin(), candidates.end(), Compare)->first;
		words_returned += temp_str;
		return words_returned;
	}
	return (""); //No correction found for the word.
}

/*Function to check words from the dictionary*/
void SpellingCorrector::known(vector<string> &results, map<string, int> &candidates)
{
	const map<string, int>::iterator END = dictionary.end();
	for (unsigned int i = 0; i<results.size(); i++)
	{
		map<string, int>::iterator it = dictionary.find(results[i]);
		if (it != END)
			candidates[results[i]] += it->second;
	}
}

/*Function to find all possible edits to the word.*/
/*The current ratio being used is 3:2:1:5 in the order below*/
void SpellingCorrector::edits(string word, vector<string>&results)
{
	/*DELETION*/
	if(word.length()>4)
		for (unsigned int i = 0; i<word.length(); i++)
		{
			for (int j=0;j<3;j++)
				results.push_back(word.substr(0, i) + word.substr(i + 1));
		}

	/*TRANSPOSITION*/
	for (unsigned int i = 0; i<word.length() - 1; i++)
	{
		for(int j=0;j<2;j++)
			results.push_back(word.substr(0, i) + word[i + 1] + word[i] + word.substr(i + 2));
	}

	/*INSERTION*/
	if(word.length()>=4)
		for (unsigned int i = 0; i<word.length() + 1; i++)
		{
			for (char j = 'a'; j <= 'z'; j++)
			{
				results.push_back(word.substr(0, i) + j + word.substr(i));
			}
		}

	/*ALTERATION*/
	for (unsigned int i = 0; i<word.length(); i++)
	{
		for (char j = 'a'; j <= 'z'; j++)
		{
			if(qwerty.distance(word[i],j)==1)
				for(int k=0;k<5;k++)
					results.push_back(word.substr(0, i) + j + word.substr(i + 1));
		}
	}
}

/*Function to add words to the dictionary during runtime.*/
void SpellingCorrector::AddToKnown(string& word, const string& filename)
{
	ofstream file(filename.c_str(), ios_base::app);
	file.seekp(0, ios_base::end);

	string temp = word + '\n';
	file << temp;
	file.close();
	dictionary[word]++;
}

/*Function to save the current output to and delete the output.txt file*/
void SpellingCorrector::saveData(const string& filename)
{
	ifstream filein("output.txt");
	ofstream fileout(filename.c_str(), ios_base::app);
	
	filein.seekg(0, ios_base::end);
	unsigned int size = filein.tellg();
	filein.seekg(0, ios_base::beg);
	string output(size, '-');
	filein.read(&output[0], size);
	filein.close();

	remove("output.txt");

	fileout << output;
	fileout << '\n';
	fileout.close();
}

/*Function to load the replacements into the cache.*/
void SpellingCorrector::load_replacement(const string &filename)
{
	replacement temp_replacement;
	string temp_initial, temp_modified;
	ifstream fin(filename.c_str(), ios_base::in);
	while (!fin.eof())
	{
		fin.read((char*)&temp_replacement, sizeof(temp_replacement));
		temp_initial = temp_replacement.initial;
		temp_modified = temp_replacement.modified;
		cache[temp_initial] = temp_modified;
	}
	fin.close();
}

/*Function to add a replacement*/
void SpellingCorrector::add_replacement(const string &filename, string input, string output)
{
	replacement temp_replacement;
	strcpy(temp_replacement.initial,input.c_str());
	strcpy(temp_replacement.modified, output.c_str());
	
	ofstream fout(filename.c_str(), ios::app);
	fout.write((char*)&temp_replacement, sizeof(temp_replacement));
	cache[input] = output;
}
/*MEMBER FUNCTIONS OF THE CLASS AUTOCORRECT*/

/*Function for simple sentences and paragraphs*/
void AutoCorrect::long_correct(string& sentence)
{
	string word;
	ofstream fout("output.txt", ios_base::out); 
	for (unsigned int i = 0; i<sentence.length(); i++)
	{
		if (isalpha(sentence[i]))
		{
			word = word + sentence[i];
		}
		else
		{
			if (word != "")
			{
				string words_returned = corrector.correct(word),list_word[3];
				int j = 0, k = 0;
				while (j < words_returned.length() && k < 3)
				{
					if (words_returned[j] == '+')
					{
						k++;
						j++;
						continue;
					}
					list_word[k] += words_returned[j];
					j++;
				}
				fout << list_word[0];
				if(i!=sentence.length()-1)
					fout << sentence[i];
			}
			else
				fout << sentence[i];
			word = "";
		}
	}
	fout << '\n';
}

