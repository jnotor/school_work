// ToString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include <iostream>
#include <string>


class Person
{
public:
	Person(std::string name) :m_name(name)
	{

	}

	std::string GetName() const
	{
		return m_name;
	}

	virtual ~Person()
	{
		std::cout << "Deleting " << m_name << std::endl;
	}

private:
	std::string m_name;

};


int main()
{
	std::list<const Person *> stackOfPeople;
	Person * p1 = new Person("Huey 1");
	Person * p2 = new Person("Louie 2");
	Person * p3 = new Person("Dewey 3");

	stackOfPeople.push_front(p1);
	stackOfPeople.push_front(p2);
	stackOfPeople.push_front(p3);

	for (const Person* p : stackOfPeople)
	{
		std::string name = p->GetName();
		std::cout << name << " " << std::endl;
	}
	std::cout <<  std::endl;


	std::list<const Person *> queueOfPeople;

	queueOfPeople.push_back(p1);
	queueOfPeople.push_back(p2);
	queueOfPeople.push_back(p3);

	for (const Person* p : queueOfPeople)
	{
		std::string name = p->GetName();
		std::cout << name << " " << std::endl;
	}

	std::cout << "calling pop methods" << std::endl;
	stackOfPeople.pop_front();
	queueOfPeople.pop_front();

	for (const Person* p : stackOfPeople)
	{
		std::string name = p->GetName();
		std::cout << name << " " << std::endl;
	}
	std::cout << std::endl;

	for (const Person* p : queueOfPeople)
	{
		std::string name = p->GetName();
		std::cout << name << " " << std::endl;
	}

	std::cout << "calling clear methods" << std::endl;
	stackOfPeople.clear();
	queueOfPeople.clear();
	std::cout << "calling delete" << std::endl;
	delete p1;
	delete p2;
	delete p3;

    return 0;
}
//make a game class to hold everything, responsible for all the news and deletes. 
//only place deletion is going to occur is in game class, at the end
//everything else, use const pointers
