#ifndef WORD_H
#define WORD_H

class Sentence;
class Word;

#include <stdio.h>
#include <string>
#include "Sentence.h"

class Word {

	private:
		std::string word;
		Word* next;
		std::string originalWord;
		bool isPigLatin;

	public:
		Word();

		Word(const Word&);

		Word(std::string);
		
		~Word();

		void show();

		Word& operator=(const Word&);

		Sentence operator+(const Sentence&);

		Sentence operator+(const Word&);

		Word& operator++();

		Word operator++(int);

		Word& operator--();

		Word operator--(int);

		Word& operator+(int);

		friend std::ostream& operator<<(std::ostream& o, const Word& w);

		void setWord(std::string s);

		std::string getWord();

		Word* getNext();

		void setNext(Word*);

		std::string getOriginal();

		void setOriginal(std::string);
};

#endif /* WORD_H */
