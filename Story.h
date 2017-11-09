#ifndef STORY_H
#define STORY_H

class Paragraph;
class Story;

#include <stdio.h>
#include <string>
#include "Paragraph.h"

class Story {

	private:
		//Paragraph p;
		Paragraph* head;

		Story* next;

		bool isPigLatin;

	public:
		
		Story();

		Story(const Story&);

		Story(std::string);

		~Story();

		void show();

		Story& operator=(const Story&);

		Story operator+(const Story&);

		Story operator+(const Paragraph&);

		Story& operator++();

		Story operator++(int);

		Story& operator--();

		Story operator--(int);

		Story& operator+(int);

		friend std::ostream& operator<<(std::ostream& o, const Story& s);

		Paragraph first();

		Story rest();

		void save(std::string);

		Paragraph* getHead() const;

		void setHead(Paragraph*);

		Story* getNextStory() const;

		void setNextStory(Story*);

};

#endif /* STORY_H */
