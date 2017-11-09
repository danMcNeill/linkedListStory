#include <stdio.h>
#include <iostream>
#include "Story.h"
#include <fstream>

using namespace std;

Story::Story() {
	//cout << "Entering Story normal constructor\n";
	head = NULL;
	next = NULL;
	isPigLatin = false;
}

Story::Story(const Story& copy) {
	//cout << "Entering Story copy constructor\n";

	Paragraph* temp = copy.getHead();
	if(temp == NULL) {
		head = NULL;
		next = NULL;
		return;
	}
	head = new Paragraph(*temp);
	//head->setHead(temp->getHead());
	Paragraph* temp2 = head;
	temp = temp->getNextParagraph();
	while(temp != NULL) {
		temp2->setNextParagraph(new Paragraph(*temp));
		//temp2->next->setWord(temp->getWord());
		temp = temp->getNextParagraph();
		temp2 = temp2->getNextParagraph();
	}


	next = NULL;





	/*Paragraph* temp = copy.getHead();
	if(temp == NULL) {
		head = NULL;
		next = NULL;
		isPigLatin = false;
		return;
	}
	else {
		head = new Paragraph(*temp);
		//head->setHead(temp->getHead());
		Paragraph* temp2 = head;
		//temp = temp->getNextParagraph();
	

	if(temp->getNextParagraph() == NULL) {
		head->setNextParagraph(NULL);
	}
	temp = temp->getNextParagraph();
	while(temp != NULL) {
		temp2->setNextParagraph(new Paragraph(*temp));
		//temp2->next->setWord(temp->getWord());
		temp = temp->getNextParagraph();
		temp2 = temp2->getNextParagraph();
	}

	next = NULL;
	isPigLatin = copy.isPigLatin;
	}*/
	/*Paragraph* old = copy.head;
	head = new Paragraph(*old); // do i need getHead or just .head??
	Paragraph* temp = head;
	old = old->getNextParagraph();
	//temp = temp->next;
	while(temp && old) {
		temp->setNextParagraph(new Paragraph(*old));
		temp = temp->getNextParagraph();
		if(old != NULL)
			old = old->getNextParagraph();
	}
	next = NULL;*/
}

Story::Story(std::string s) {
	//cout << "Entering Story constructor with file name\n";

	const char* newString = s.c_str();
	string line;
	ifstream file(newString);
	Paragraph* temp;

	if(file.is_open()) {
		getline(file, line);
		head = new Paragraph(line);
		temp = head;
		while(getline(file, line)) {
			//cout << "line lnth: " << line.length() << "\n";
			if(line.length() == 0)
				continue;
			temp->setNextParagraph(new Paragraph(line));
			temp = temp->getNextParagraph();
		}
		next = NULL;
		file.close();
	}
	else {
		cout << "Cannot open this file.\n";
	}

	isPigLatin = false;

}

Story::~Story() {
	//cout << "Entering Story deconstructor\n";

	Paragraph* temp = head;
	Paragraph* temp2 = head;
	while(temp) {
		temp2 = temp2->getNextParagraph();
		//cout << *temp << "\n";
		delete temp;
		temp = temp2;
	}
}

void Story::show() {
	cout << "Entering Story show function\n";
}

Story& Story::operator=(const Story& oldStory) {

	Story* newStory = new Story();
	if(oldStory.getHead() != NULL) {
		Paragraph* old = oldStory.head;
		newStory->setHead(new Paragraph(*old));
		Paragraph* temp = newStory->getHead();
		old = old->getNextParagraph();
		//temp = temp->next;
		while(temp && old) {
			temp->setNextParagraph(new Paragraph(*old));
			temp = temp->getNextParagraph();
			if(old != NULL)
				old = old->getNextParagraph();
		}
		next = NULL;
	}

	return *newStory;


}

Story Story::operator+(const Story& oldStory) {
	//cout << "Entering Story + Story function\n";

	Story s1(*this);
	Story* s2 = new Story(oldStory);
	Paragraph* temp = s1.getHead();
	while(temp->getNextParagraph()) {
		temp = temp->getNextParagraph();
	}
	temp->setNextParagraph(s2->getHead());
	return s1;



	/*Story* newStory = new Story();
	if(oldStory.getHead() != NULL) {
		Paragraph* old = oldStory.head;
		newStory->setHead(new Paragraph(*old)); // do i need getHead or just .head??
		Paragraph* temp = newStory->getHead();
		old = old->getNextParagraph();
		//temp = temp->next;
		while(temp && old) {
			temp->setNextParagraph(new Paragraph(*old));
			temp = temp->getNextParagraph();
			if(old != NULL)
				old = old->getNextParagraph();
		}
		next = NULL;
	}

	return *newStory;*/
}

Story Story::operator+(const Paragraph& p) {
	//cout << "Entering Story + Paragraph function\n";

	Story s = *this; //deep copies in assignment operator
	Paragraph* temp = s.getHead();
	if(temp == NULL) {
		s.setHead(new Paragraph(p));
		return s;
	}

	while(temp->getNextParagraph() != NULL) {
		temp = temp->getNextParagraph();
	}

	temp->setNextParagraph(new Paragraph(p));

	return s;
}

Story& Story::operator++() {
	//cout << "Entering prefix increment Story function.\n";
	Paragraph* temp;
	for(temp=head; temp!=NULL; temp=temp->getNextParagraph()) {
		*temp = ++(*temp);
	}
	return *this;
}

Story Story::operator++(int i) {
	//cout << "Entering postix increment Story function\n";
	Story s(*this);
	Paragraph* temp = head;
	while(temp) {
		(*temp)++;
		temp = temp->getNextParagraph();
	}
	return s;
}

Story& Story::operator--() {
	//cout << "Entering prefix decrement Story function\n";
	Paragraph* temp;
	for(temp=head; temp!=NULL; temp=temp->getNextParagraph()) {
		--(*temp);
	}
	return *this;
}

Story Story::operator--(int i) {
	//cout << "Entering postfix decrement Story function\n";
	Story s(*this);
	Paragraph* temp;
	for(temp=head; temp!=NULL; temp=temp->getNextParagraph()) {
		(*temp)--;
	}
	return s;
}

Story& Story::operator+(int i) {
	//cout << "Entering Story + 1 function\n";
	Paragraph* temp = head;
	if(i == 1) {
		while(temp != NULL) {
			*temp+1;
			temp = temp->getNextParagraph();
		}
	}
	return *this;
}

ostream& operator<<(ostream& o, const Story& s) {
	//cout << "Entering Story output function\n";
	Paragraph* temp;
	temp = s.getHead();
	while(temp != NULL) {
		o << *temp << "\n";
		temp = temp->getNextParagraph();
	}
	o << "\n";
	return o;
}

Paragraph Story::first() {
	//cout << "Entering Story first function\n";
	Paragraph *p;
	if(head != NULL) {
		p = new Paragraph(*head);
		p->setNextParagraph(NULL);
	}
	
	return *p;
}

Story Story::rest() { //doesn't work
	//cout << "Entering Story rest function\n";

	Story s;
	Paragraph* temp, *temp2;
	if(head->getNextParagraph()) {
		Paragraph* p = new Paragraph(*(head->getNextParagraph()));
		s.setHead(p);
		temp = p;
		temp2 = head->getNextParagraph();
		temp2 = temp2->getNextParagraph();
		while(temp2) {
			temp->setNextParagraph(new Paragraph(*temp2));
			temp = temp->getNextParagraph();
			temp2 = temp2->getNextParagraph();
		}
	}
	else
		s.setHead(NULL);

	s.setNextStory(NULL);
	
	return s;


/*	Story s;
	Paragraph* temp, *temp2;
	if(head->getNextParagraph()) {
		Paragraph* p = new Paragraph(*(head->getNextParagraph()));
		s.setHead(p);
		temp = p;
		temp2 = head->getNextParagraph();
		if(temp2->getNextParagraph() == NULL) {
			s.setNextStory(NULL);
			temp->setNextParagraph(NULL);
			return s;
		}

		temp2 = temp2->getNextParagraph();
		while(temp2->getNextParagraph()) {
			temp->setNextParagraph(new Paragraph(*temp2));
			temp = temp->getNextParagraph();
			temp2 = temp2->getNextParagraph();
		}
		
	}
	else
		s.setHead(NULL);

	s.setNextStory(NULL);
	
	return s;*/






	/*Story s;
	Paragraph* temp;
	if(head != NULL) { // must make copies
		Paragraph* p = new Paragraph(*(head->getNextParagraph()));
		s.setHead(p);
		temp = head->getNextParagraph();
		temp = temp->getNextParagraph();
		while(temp!=NULL) {
			temp->setNextParagraph(new Paragraph(*temp));
			temp = temp->getNextParagraph();
		}

	}
	else 
		s.setHead(NULL);
	
	s.setNextStory(NULL);

	return s;*/
}

void Story::save(std::string s) {
	//cout << "Entering Story save function\n";


	ofstream storyFile;
	storyFile.open(s.c_str());
	Paragraph* temp = head;
	while(temp) {
		storyFile << *temp;
		temp = temp->getNextParagraph();
	}



	//storyFile.open(s.c_str());
	//storyFile << *this;

	storyFile.close();
}

Paragraph* Story::getHead() const{
	return head;
}

void Story::setHead(Paragraph* p) {
	head = p;
}

Story* Story::getNextStory() const {
	return next;
}

void Story::setNextStory(Story* s) {
	next = s;
}
