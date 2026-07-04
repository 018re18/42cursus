#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

PhoneBook::PhoneBook() : _count(0), _nextIndex(0)
{
}

void PhoneBook::addContact(const Contact &contact)
{
	_contacts[_nextIndex] = contact;
	_nextIndex = (_nextIndex + 1) % MAX_CONTACTS;
	if (_count < MAX_CONTACTS)
		_count++;
}

static std::string formatColumn(const std::string &str)
{
	if (str.length() > 10)
		return str.substr(0, 9) + ".";
	return str;
}

void PhoneBook::searchContact() const
{
	if (_count == 0)
	{
		std::cout << "The phonebook is empty." << std::endl;
		return;
	}

	std::cout << std::right << std::setw(10) << "Index" << "|"
			<< std::setw(10) << "First Name" << "|"
			<< std::setw(10) << "Last Name" << "|"
			<< std::setw(10) << "Nickname" << std::endl;

	for (int i = 0; i < _count; i++)
	{
		std::ostringstream indexStr;
		indexStr << i;
		std::cout << std::right << std::setw(10) << formatColumn(indexStr.str()) << "|"
				<< std::setw(10) << formatColumn(_contacts[i].getFirstName()) << "|"
				<< std::setw(10) << formatColumn(_contacts[i].getLastName()) << "|"
				<< std::setw(10) << formatColumn(_contacts[i].getNickname()) << std::endl;
	}

	std::cout << "Enter the index of the contact to display: ";
	std::string input;
	std::getline(std::cin, input);

	std::istringstream iss(input);
	int index;
	if (!(iss >> index) || !(iss.eof()) || index < 0 || index >= _count)
	{
		std::cout << "Invalid index." << std::endl;
		return;
	}

	const Contact &contact = _contacts[index];
	std::cout << "First Name:    " << contact.getFirstName() << std::endl;
	std::cout << "Last Name:     " << contact.getLastName() << std::endl;
	std::cout << "Nickname:      " << contact.getNickname() << std::endl;
	std::cout << "Phone Number:  " << contact.getPhoneNumber() << std::endl;
	std::cout << "Darkest Secret: " << contact.getDarkestSecret() << std::endl;
}
