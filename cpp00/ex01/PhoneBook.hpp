#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

#define MAX_CONTACTS 8

class PhoneBook
{
	private:
		Contact _contacts[MAX_CONTACTS];
		int     _count;
		int     _nextIndex;

	public:
		PhoneBook();

		void addContact(const Contact &contact);
		void searchContact() const;
};

#endif
