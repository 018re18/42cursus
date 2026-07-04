#include "PhoneBook.hpp"
#include <iostream>
#include <string>

static bool promptField(const std::string &label, std::string &value)
{
	while (true)
	{
		std::cout << label << ": ";
		if (!std::getline(std::cin, value))
			return false;
		if (!value.empty())
			return true;
		std::cout << "This field cannot be empty." << std::endl;
	}
}

static bool addContact(PhoneBook &phoneBook)
{
	std::string firstName;
	std::string lastName;
	std::string nickname;
	std::string phoneNumber;
	std::string darkestSecret;

	if (!promptField("First name", firstName)
		|| !promptField("Last name", lastName)
		|| !promptField("Nickname", nickname)
		|| !promptField("Phone number", phoneNumber)
		|| !promptField("Darkest secret", darkestSecret))
		return false;

	Contact contact;
	contact.setInfo(firstName, lastName, nickname, phoneNumber, darkestSecret);
	phoneBook.addContact(contact);
	return true;
}

int main()
{
	PhoneBook phoneBook;
	std::string command;

	while (true)
	{
		std::cout << "Enter a command (ADD, SEARCH, EXIT): ";
		if (!std::getline(std::cin, command))
			break;

		if (command == "ADD")
		{
			if (!addContact(phoneBook))
				break;
		}
		else if (command == "SEARCH")
			phoneBook.searchContact();
		else if (command == "EXIT")
			break;
		else
			std::cout << "Unknown command." << std::endl;
	}

	return 0;
}
