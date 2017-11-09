#include <stdio.h>
#include <iostream>
#include "Word.h"

using namespace std;

Word::Word() {
	//cout << "Entering Word normal constructor\n";
	word = "";
	next = NULL;
}

Word::Word(const Word& copy) {
	//cout << "Entering Word copy constructor\n";
	word = copy.word;
	next = NULL;
}

Word::Word(std::string w) {
	//cout << "Entering Word with value constructor\n";
	word = w;
	next = NULL;
}

Word::~Word() {
	//cout << "Entering Word deconstructor\n";

}

void Word::show() {
	//cout << "Entering Word show function\n";
	cout << word << "\n";
}

Word& Word::operator=(const Word& oldWord) {
	//cout << "Entering Word assignment operator\n";
	Word* w = new Word();

	w->word = oldWord.word;
	
	return *w;
}

Sentence Word::operator+(const Sentence& oldSentence) {
	/*cout << "Entering Word + Sentence\n";
	//word[0] = toupper(word[0]);
	Sentence s;
	WordNode* temp, *temp2;
	WordNode* wn1 = new WordNode();
	wn1->w = new Word(*this); // sets first node's Word to new first word
	wn1->wp = oldSentence.getHead(); // sets first node's WordNode pointer to old sentence head........... does not work
	s.head = wn1; // sets new sentences head to pointer to new node
	temp = oldSentence.getHead(); // stores pointer to old first node in temp
	temp2 = temp->wp; // store pointer to old second node in temp2	

	for(; temp2!=NULL ;) {
		WordNode* node = new WordNode(); // creates new word node
		node->w = new Word(temp->w); // sets new word node's word to temp's word
		node->wp = temp2;
		temp = temp2;
		temp2 = temp2->wp;
	}

	return s;*/

	Sentence s = oldSentence;
	Word* w = new Word(*this);
	w->next = s.getHead();
	s.setHead(w);
	s.setNextSentence(NULL);

	return s;
	
	
}

Sentence Word::operator+(const Word& secondWord) {
	//cout << "Entering Word + Word\n";
	Sentence s;
	Word* w1 = new Word(*this);
	Word* w2 = new Word(secondWord);
	w1->next = w2;
	w2->next = NULL;
	s.setHead(w1);
	s.setNextSentence(NULL);
	return s;



	/*WordNode* wn1 = new WordNode();
	wn1->w = new Word(*this);
	WordNode* wn2 = new WordNode();
	wn2->w = new Word(secondWord);
	wn1->wp = wn2;
	wn2->wp = NULL;
	s.head = wn1;
	return s;*/
}

Word& Word::operator++() {
	//cout << "Entering Word prefix increment function\n";
	originalWord = word;
	string wordCopy = word;
	if(wordCopy[0]=='A' || wordCopy[0]=='a' || wordCopy[0]=='E' || wordCopy[0]=='e' || wordCopy[0]=='I' || wordCopy[0]=='i' || wordCopy[0]=='O' || wordCopy[0]=='o' || wordCopy[0]=='U' || wordCopy[0]=='u') {
		wordCopy.append("way");
		//wordCopy = wordCopy.substr(1, word.length()-1);
	}
	else {
		int firstVowel = 0;
		int x = 0;
		string tempString;

		for(x=1; x<wordCopy.length(); x++) {
			if(wordCopy[x]=='A' || wordCopy[x]=='a' || wordCopy[x]=='E' || wordCopy[x]=='e' || wordCopy[x]=='I' || wordCopy[x]=='i' || wordCopy[x]=='O' || wordCopy[x]=='o' || wordCopy[x]=='U' || wordCopy[x]=='u') {
				firstVowel = x;
				break;
			}
		}
		tempString = wordCopy.substr(0, firstVowel);
		wordCopy.erase(0, firstVowel);
		wordCopy.append(tempString);
		wordCopy.append("ay");
				


		/*if(wordCopy[0].isupper()) {
			string upperFirst = " ";
			upperFirst = wordCopy.at(x).toupper();
			word = upperFirst;
			word.append(wordCopy, x+1);
			word.append(wordCopy[0].tolower());
			word.append(wordCopy, 1, x-1);
			word.append("ay");
		}
		else {
			word = word.at(x);
			word.append(wordCopy, x+1);
			word.append(wordCopy[0]);
			word.append(wordCopy, 1, x-1);
			word.append("ay");
		}*/
	}

	isPigLatin = true;

	word = wordCopy;
	
	return *this;
}

Word Word::operator++(int i) {
	//cout << "Entering Word postfix increment function\n";
	Word w(*this);
	for(int i=0; i<word.length(); i++) {
		word[i] = ::toupper(word[i]);
	}
	return w;
}

Word& Word::operator--() {
	//cout << "Entering Word prefix decrement\n";

	if(isPigLatin) {
		word = originalWord;
	}



	return *this;
}

Word Word::operator--(int i) {
	//cout << "Entering Word postfix decrement\n";
	Word w(*this);
	for(int i=0; i<word.length(); i++) {
		word[i] = ::tolower(word[i]);
	}
	return w;
}

Word& Word::operator+(int i) {
	//cout << "Entering Word + 1 function\n";
	if(i == 1) {
		word[0] = ::toupper(word[0]);
	}
	return *this;
}

ostream& operator<<(ostream& o, const Word& w) {
	//cout << "Entering Word output to file function\n";

	o << w.word;


	return o;
}

void Word::setWord(std::string s) {
	word = s;
}

std::string Word::getWord() {
	return word;
}

Word* Word::getNext() {
	return next;
}

void Word::setNext(Word* w) {
	next = w;
}

void Word::setOriginal(string s) {
	originalWord = s;
}

string Word::getOriginal() {
	return originalWord;
}
