#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

// 実行すると対象が Zaphod Beeblebrox に恩赦されたことを告げる。
// 署名 25 / 実行 5。
class PresidentialPardonForm : public AForm
{
	private:
		std::string const	_target;

	protected:
		virtual void	_executeAction(void) const;

	public:
		// 直交正準形 (Orthodox Canonical Form)
		PresidentialPardonForm(void);
		PresidentialPardonForm(PresidentialPardonForm const &src);
		PresidentialPardonForm &operator=(PresidentialPardonForm const &rhs);
		virtual ~PresidentialPardonForm(void);

		PresidentialPardonForm(std::string const &target);

		std::string const	&getTarget(void) const;
};

#endif
