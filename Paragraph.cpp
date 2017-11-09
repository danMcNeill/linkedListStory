#include <stdio.h>
#include <iostream>
#include "Paragraph.h"
#include <sstream>

using namespace std;

Paragraph::Paragraph() {
	//cout << "Entering Paragraph normal constructor\n";
	head = NULL;
	next = NULL;
}

Paragraph::Paragraph(const Paragraph& copy) {
	//cout << "Entering Paragraph copy constructor\n";

	Sentence* temp = copy.getHead();
	if(temp == NULL) {
		head = NULL;
		next = NULL;
		return;
	}
	head = new Sentence(*temp);
	//head->setHead(temp->getHead());
	Sentence* temp2 = head;
	temp = temp->getNextSentence();
	while(temp != NULL) {
		temp2->setNextSentence(new Sentence(*temp));
		//temp2->next->setWord(temp->getWord());
		temp = temp->getNextSentence();
		temp2 = temp2->getNextSentence();
	}

	next = NULL;



	/*Sentence* old = copy.head;
	head = new Sentence(*old); 
	Sentence* temp = head;
	old = old->getNextSentence();
	//temp = temp->next;
	while(temp && old) {
		temp->setNextSentence(new Sentence(*old));
		temp = temp->getNextSentence();
		if(old != NULL)
			old = old->getNextSentence();
	}
	next = NULL;*/
}

Paragraph::Paragraph(std::string s) {
	//cout << "Entering Paragraph value constructor\n";

	stringstream sentence(s);
	string word;
	string concatSen = "";
	Sentence* temp;
	char p;


// looking for first sentence
	while(sentence >> word) {
		//concatSen = concatSen + word;
		if((word[word.length()-1] == '.') || (word[word.length()-1] == '?') || (word[word.length()-1] == '!')) {
			//char p = word[word.length()-1];
			//word = word.substr(0, word.length()-1);
			concatSen = concatSen + " " + word;
			break;
		}
		else {
			concatSen = concatSen + " " + word;
		}
	}
	head = new Sentence(concatSen);
	//head->setPunc(p);
	temp = head;
	concatSen = "";

// looking for rest of sentences
	while(sentence >> word) {
		//concatSen = concatSen + word;
		if((word[word.length()-1] == '.') || (word[word.length()-1] == '?') || (word[word.length()-1] == '!')) {
			//char p = word[word.length()-1];
			//word = word.substr(0, word.length()-1);
			concatSen = concatSen + " " + word;
			temp->setNextSentence(new Sentence(concatSen));
			temp = temp->getNextSentence();
			//temp->setPunc(p);
			concatSen = "";
			continue;
		}
		else {
			concatSen = concatSen + " " + word;
		}
	}
	next = NULL;
	temp->setNextSentence(NULL);



}

Paragraph::~Paragraph() {
	//cout << "Entering Paragraph destructor\n";

	Sentence* temp = head;
	Sentence* temp2 = head;
	while(temp) {
		temp2 = temp2->getNextSentence();
		//cout << temp->getHead()->getWord();
		delete temp;
		temp = temp2;
	}
}

void Paragraph::show() {
	//cout << "Entering Paragraph show function\n";
}

Paragraph& Paragraph::operator=(const Paragraph& oldParagraph) {
	//cout << "Entering Paragraph assignment operator\n";

	Paragraph* newParagraph = new Paragraph();
	if(oldParagraph.getHead() != NULL) {
		Sentence* old = oldParagraph.head;
		newParagraph->setHead(new Sentence(*old));
		Sentence* temp = newParagraph->getHead();
		old = old->getNextSentence();
		//temp = temp->next;
		while(temp && old) {
			temp->setNextSentence(new Sentence(*old));
			temp = temp->getNextSentence();
			if(old != NULL)
				old = old->getNextSentence();
		}
		next = NULL;
	}

	return *newParagraph;
}

Story Paragraph::operator+(const Story& s) {
	//cout << "Entering Paragraph + Story function\n";
	Story newS = s;
	Paragraph* newP = new Paragraph(*this);
	newP->next = newS.getHead();
	newS.setHead(newP);
	newS.setNextStory(NULL);
	return newS;
}

Paragraph Paragraph::operator+(const Paragraph& p) {
	//cout << "Entering Paragraph + Paragraph function\n";
	Paragraph pa(*this);
	Paragraph* pa2 = new Paragraph(p);
	Sentence* temp = pa.getHead();
	while(temp->getNextSentence()) {
		temp = temp->getNextSentence();
	}
	temp->setNextSentence(pa2->getHead());
	return pa;
}

Paragraph Paragraph::operator+(const Sentence& s) {
	//cout << "Entering Paragraph + Sentence function\n";
	
	Paragraph p = *this; //deep copies in assignment operator
	Sentence* temp = p.getHead();
	if(temp == NULL) {
		p.setHead(new Sentence(s));
		return p;
	}

	while(temp->getNextSentence() != NULL) {
		temp = temp->getNextSentence();
	}

	temp->setNextSentence(new Sentence(s));

	return p;
}

Paragraph& Paragraph::operator++() {
//	cout << "Entering Paragraph prefix increment\n";
	Sentence* temp;
	for(temp=head; temp!=NULL; temp=temp->getNextSentence()) {
		++(*temp);
	}
	return *this;
}

Paragraph Paragraph::operator++(int i) {
	//cout << "Entering Paragraph postfix increment\n";
	Paragraph p(*this);
	Sentence* temp;
	for(temp=getHead(); temp!=NULL; temp=temp->getNextSentence()) {
		(*temp)++;
	}
	return p;
}

Paragraph& Paragraph::operator--() {
	//cout << "Entering Paragraph prefix decrement\n";
	Sentence* temp;
	for(temp=head; temp!=NULL; temp=temp->getNextSentence()) {
		--(*temp);
	}
	return *this;
}

Paragraph Paragraph::operator--(int i) {
	//cout << "Entering Paragraph postfix decrement\n";
	Paragraph p(*this);
	Sentence* temp;
	for(temp=getHead(); temp!=NULL; temp=temp->getNextSentence()) {
		(*temp)--;
	}
	return p;
}

Paragraph& Paragraph::operator+(int i) {
	//cout << "Entering Paragraph + 1 function\n";
	/*Sentence* temp = head;
	Word* w = head->head;
	std::string tempString;
	while(head != NULL) {
		if(w->word != NULL) {
			tempString = w->word;
			tempString[0] = ::toupper(tempString[0]);
			*w.setWord(tempString);
		}
		temp = temp->next;
	}
	return *this;*/

	Sentence* temp = head;
	if(i == 1) {
		while(temp != NULL) {
			(*temp)+1;
			temp = temp->getNextSentence();
		}
	}
	return *this;
}

ostream& operator<<(ostream& o, const Paragraph& p) {
	//cout << "Entering Paragraph output to file function\n";
	o << "\t";
	Sentence* temp;
	temp = p.getHead();
	while(temp != NULL) {
		o << *temp << " ";
		temp = temp->getNextSentence();
	}
	o << "\n";
	return o;
}

Sentence Paragraph::first() {
	//cout << "Entering Paragraph first function\n";
	Sentence* s;
	if(head != NULL) {
		s = new Sentence(*head);
		s->setNextSentence(NULL);
	}
	
	return *s;
}

Paragraph Paragraph::rest() {
	//cout << "Entering Paragraph rest function\n";


	Paragraph p;
	Sentence* temp, *temp2;
	if(head->getNextSentence()) {
		Sentence* s = new Sentence(*(head->getNextSentence()));
		p.setHead(s);
		temp = s;
		temp2 = head->getNextSentence();
		temp2 = temp2->getNextSentence();
		while(temp2) {
			temp->setNextSentence(new Sentence(*temp2));
			temp = temp->getNextSentence();
			temp2 = temp2->getNextSentence();
		}
	}
	else
		p.setHead(NULL);

	p.setNextParagraph(NULL);
	
	return p;


	
	/*Paragraph p;
	Sentence* temp, *temp2;
	if(head->getNextSentence()) {
		Sentence* s = new Sentence(*(head->getNextSentence()));
		p.setHead(s);
		temp = s;
		temp2 = head->getNextSentence();
		if(temp2->getNextSentence() == NULL) {
			p.setNextParagraph(NULL);
			return p;
		}

		temp2 = temp2->getNextSentence();
		while(temp2->getNextSentence()) {
			temp->setNextSentence(new Sentence(*temp2));
			temp = temp->getNextSentence();
			temp2 = temp2->getNextSentence();
		}
	}
	else
		p.setHead(NULL);

	p.setNextParagraph(NULL);
	
	return p;*/

/*
	Paragraph p;
	Sentence* temp;
	if(head != NULL) { // must make copies
		Sentence* s = new Sentence(*(head->getNextSentence()));
		p.setHead(s);
		temp = head->getNextSentence();
		temp = temp->getNextSentence();
		while(temp!=NULL) {
			s = new Sentence(*temp);
			temp = temp->getNextSentence();
		}

	}
	else 
		p.setHead(NULL);
	
	p.setNextParagraph(NULL);

	return p;*/
}

Sentence* Paragraph::getHead() const {
	return head;
}

void Paragraph::setHead(Sentence* s) {
	head = s;
}

Paragraph* Paragraph::getNextParagraph() const {
	return next;
}

void Paragraph::setNextParagraph(Paragraph* p) {
	next = p;
}
