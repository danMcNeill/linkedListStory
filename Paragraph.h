#ifndef PARAGRAPH_H
#define PARAGRAPH_H

class Sentence;
class Story;
class Paragraph;

#include <stdio.h>
#include <string>
#include "Sentence.h"
#include "Story.h"

class Paragraph {

	private:
		//Sentence s;
		Sentence* head;

		Paragraph* next;


	public:
		
		Paragraph();

		Paragraph(const Paragraph&);

		Paragraph(std::string s);

		~Paragraph();

		void show();

		Paragraph& operator=(const Paragraph&);

		Story operator+(const Story&);

		Paragraph operator+(const Paragraph&);

		Paragraph operator+(const Sentence&);

		Paragraph& operator++();

		Paragraph operator++(int);

		Paragraph& operator--();

		Paragraph operator--(int);

		Paragraph& operator+(int);

		friend std::ostream& operator<<(std::ostream& o, const Paragraph& p);

		Sentence first();

		Paragraph rest();

		Sentence* getHead() const;

		void setHead(Sentence*);

		Paragraph* getNextParagraph() const;

		void setNextParagraph(Paragraph*);
};

#endif /* PARAGRAPH_H */
