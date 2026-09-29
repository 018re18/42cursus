#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"

// 実行するとドリル音を鳴らし、50% の確率でロボトミーに成功する。
// 署名 72 / 実行 45。
class RobotomyRequestForm : public AForm
{
	private:
		std::string const	_target;

	protected:
		virtual void	_executeAction(void) const;

	public:
		// 直交正準形 (Orthodox Canonical Form)
		RobotomyRequestForm(void);
		RobotomyRequestForm(RobotomyRequestForm const &src);
		RobotomyRequestForm &operator=(RobotomyRequestForm const &rhs);
		virtual ~RobotomyRequestForm(void);

		RobotomyRequestForm(std::string const &target);

		std::string const	&getTarget(void) const;
};

#endif
