#ifndef SENTENCE_H
#define SENTENCE_H

class Word;
class Paragraph;
class Sentence;


#include <stdio.h>
#include <string>
#include "Word.h"
#include "Paragraph.h"



/*class WordNode {
			public:
				Word* w;
				WordNode* wp;
		};
*/
class Sentence {

	private:
		//Word w;
		//WordNode* head;

		Word* head;
		Sentence* next;
		char punc;

	public:

		Sentence();

		Sentence(const Sentence&);

		Sentence(std::string s);

		~Sentence();

		void show();

		Sentence& operator=(const Sentence&);

		Paragraph operator+(const Paragraph&);

		Paragraph operator+(const Sentence&);

		Sentence operator+(const Word&);

		Sentence& operator++();

		Sentence operator++(int);

		Sentence& operator--();

		Sentence operator--(int);

		Sentence& operator+(int);

		friend std::ostream& operator<<(std::ostream& o, const Sentence& s);

		Word first();

		Sentence rest();

		Word* getHead() const;

		void setHead(Word*);

		void setNextSentence(Sentence*);

		Sentence* getNextSentence() const;

		char getPunc();

		void setPunc(char);
};

#endif /* SENTENCE_H */
