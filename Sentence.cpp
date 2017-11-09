#include <stdio.h>
#include <iostream>
#include "Sentence.h"
#include <sstream>

using namespace std;

Sentence::Sentence() {
	//cout << "Entering Sentence normal constructor\n";
	head = NULL;
	next = NULL;
	punc = '.';
}

Sentence::Sentence(const Sentence& copy) {
	//cout << "Entering Sentence copy constructor\n";
	Word* temp = copy.getHead();
	punc = copy.punc;
	if(temp == NULL) {
		head = NULL;
		return;
	}
	head = new Word();
	head->setWord(temp->getWord());
	Word* temp2 = head;
	temp = temp->getNext();
	while(temp != NULL) {
		temp2->setNext(new Word(temp->getWord()));
		//temp2->next->setWord(temp->getWord());
		temp = temp->getNext();
		temp2 = temp2->getNext();
	}
	next = NULL;

	/*head = new Word(*old);
	Word* temp = head;
	old = old->getNext();
	//temp = temp->next;
	while(temp && old) {
		temp->setNext(new Word(*old));
		temp = temp->getNext();
		if(old != NULL)
			old = old->getNext();
	}
	next = NULL;*/
}

Sentence::Sentence(std::string s) {
	//cout << "Entering Sentence value constructor\n";

	punc = '\0';
	stringstream sentence(s);
	string tempString;
	Word* tempWord;
	char p;

	sentence >> tempString;
	head = new Word(tempString);
	tempWord = head;

	while(sentence >> tempString) {
		if((tempString[tempString.length()-1] == '.') || (tempString[tempString.length()-1] == '?') || (tempString[tempString.length()-1] == '!')) {
			p = tempString[tempString.length()-1];
			punc = p;
			tempString = tempString.substr(0, tempString.length()-1);
			tempWord->setNext(new Word(tempString));
			tempWord = tempWord->getNext();
			tempWord->setNext(NULL);
			break;

		}
		else {
			tempWord->setNext(new Word(tempString));
			tempWord = tempWord->getNext();
		}
	}

	next = NULL;

	
}

Sentence::~Sentence() {
	//cout << "Entering Sentence destructor\n";
	Word* temp = head;
	Word* temp2 = head;
	while(temp) {
		temp2 = temp2->getNext();
		delete temp;
		temp = temp2;
	}
}

void Sentence::show() {
	//cout << "Entering Sentence show function\n";
}

Sentence& Sentence::operator=(const Sentence& oldSentence) {
	//cout << "Entering Sentence assignment operator\n";

	// deleting old stuff
	Word* temp = head;
	Word* temp2 = head;
	while(temp) {
		temp2 = temp2->getNext();
		delete temp;
		temp = temp2;
	}


	Sentence* newSentence = new Sentence();
	if(oldSentence.getHead() != NULL) {
		Word* old = oldSentence.head;
		newSentence->setHead(new Word(*old)); // do i need getHead or just .head??
		Word* temp = newSentence->getHead();
		old = old->getNext();
		//temp = temp->next;
		while(temp && old) {
			temp->setNext(new Word(*old));
			temp = temp->getNext();
			if(old != NULL)
				old = old->getNext();
		}
		next = NULL;
	}

	return *newSentence;
}

Paragraph Sentence::operator+(const Paragraph& p) {
	//cout << "Entering Sentence + Paragraph function\n";
	Paragraph newP = p;
	Sentence* newS = new Sentence(*this);
	newS->next = newP.getHead();
	newP.setHead(newS);
	newP.setNextParagraph(NULL);
	return newP;
}

Paragraph Sentence::operator+(const Sentence& s) {
	//cout << "Entering Sentence + Sentence function\n";
	Paragraph pa;
	Sentence* s1 = new Sentence(*this);
	Sentence* s2 = new Sentence(s);
	s1->setNextSentence(s2);
	s2->setNextSentence(NULL);
	pa.setHead(s1);
	return pa;
}

Sentence Sentence::operator+(const Word& w) {
	//cout << "Entering Sentence + Word function\n";


	Sentence s = *this; //deep copies in assignment operator
	Word* temp = s.getHead();
	if(temp == NULL) {
		s.setHead(new Word(w));
		return s;
	}

	while(temp->getNext() != NULL) {
		temp = temp->getNext();
	}

	temp->setNext(new Word(w));

	return s;
}


	


	/*temp1 = oldSentence.getHead();
	temp2 = s.getHead();
	while(temp1!=NULL) {
		temp2->next = new Word(*temp1);
		temp1 = temp1->next;
		temp2 = temp2->next;
	}
	s.setNextSentence = NULL;
*/


Sentence& Sentence::operator++() {
	//cout << "Entering Sentence prefix increment\n";

	Word* tempWord;
	for(tempWord=head; tempWord!=NULL; tempWord=tempWord->getNext()) {
		++(*tempWord); 
	}
	return *this;
}

Sentence Sentence::operator++(int i) {
	//cout << "Entering Sentence postfix increment\n";
	
	Sentence s(*this);

	Word* tempWord;
	for(tempWord=getHead(); tempWord!=NULL; tempWord=tempWord->getNext()) {
		(*tempWord)++;
	}
	return s;
}

Sentence& Sentence::operator--() {
	//cout << "Entering Sentence prefix decrement\n";
	
	Word* tempWord;
	for(tempWord=head; tempWord!=NULL; tempWord=tempWord->getNext()) {
		--(*tempWord);
	}
	return *this;
}

Sentence Sentence::operator--(int i) {
	//cout << "Entering Sentence postfix decrement\n";

	Sentence s(*this);

	Word* tempWord;
	for(tempWord=getHead(); tempWord!=NULL; tempWord=tempWord->getNext()) {
		(*tempWord)--;
	}
	return s;
}

Sentence& Sentence::operator+(int i) {
	//cout << "Entering Sentence + 1 function\n";

	std::string temp;
	if(i == 1) {
		if(head != NULL) {
			temp = head->getWord();
			temp[0] = toupper(temp[0]); // return new sentence or edited sentence????
			head->setWord(temp);
		}
	}
	return *this;
}

ostream& operator<<(ostream& o, const Sentence& s) {
	//cout << "Entering Sentence output to file function\n";

	Word* tempWord;
	tempWord = s.getHead();
	while(tempWord != NULL) {
		if(tempWord->getNext()) {
			o << tempWord->getWord() << " ";
		}
		else {
			o << tempWord->getWord() << s.punc;
		}
		tempWord = tempWord->getNext();
	}


	return o;
}

Word Sentence::first() {
	//cout << "Entering Sentence first function\n";
	Word *w;
	if(head != NULL) {
		w = new Word(*head);
		w->setNext(NULL);
	}
	return *w;
}

Sentence Sentence::rest() {
	//cout << "Entering Sentence rest function\n";

	Sentence s;
	Word* temp, *temp2;
	if(head->getNext()) {
		Word* w = new Word(*(head->getNext()));
		s.setHead(w);
		temp = w;
		temp2 = head->getNext();
		temp2 = temp2->getNext();
		while(temp2) {
			temp->setNext(new Word(*temp2));
			temp = temp->getNext();
			temp2 = temp2->getNext();
		}
	}
	else
		s.setHead(NULL);

	s.setNextSentence(NULL);
	
	return s;

	/*head = new Word();
	head->setWord(temp->getWord());
	Word* temp2 = head;
	temp = temp->getNext();
	while(temp != NULL) {
		temp2->setNext(new Word(temp->getWord()));
		//temp2->next->setWord(temp->getWord());
		temp = temp->getNext();
		temp2 = temp2->getNext();
	}*/



	/*Sentence s;
	Word* temp;
	if(head != NULL) { // must make copies
		Word* w = new Word(*(head->getNext()));
		s.setHead(w);
		temp = head->getNext();
		temp = temp->getNext();
		while(temp!=NULL) {
			w = new Word(*temp);
			temp = temp->getNext();
		}

	}
	else 
		s.setHead(NULL);
	
	s.setNextSentence(NULL);

	return s;*/
}

Word* Sentence::getHead() const{
	return head;
}

void Sentence::setHead(Word* w) {
	head = w;
}

void Sentence::setNextSentence(Sentence* s) {
	next = s;
}

Sentence* Sentence::getNextSentence() const{
	return next;
}

void Sentence::setPunc(char c) {
	punc = c;
}

char Sentence::getPunc() {
	return punc;
}
