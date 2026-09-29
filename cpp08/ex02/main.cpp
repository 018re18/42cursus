#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <vector>

#include "MutantStack.hpp"

// 課題の PDF にある例
static void	subjectTest(void)
{
	std::cout << "=== subject test (MutantStack) ===" << std::endl;
	MutantStack<int>	mstack;

	mstack.push(5);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	mstack.pop();
	std::cout << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);
	MutantStack<int>::iterator	it = mstack.begin();
	MutantStack<int>::iterator	ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::stack<int>	s(mstack);
}

// 同じ操作を std::list で行ったもの。subjectTest と同じ出力になるはず
// (push -> push_back, top -> back, pop -> pop_back に置き換えている)
static void	listTest(void)
{
	std::cout << "=== subject test (std::list) ===" << std::endl;
	std::list<int>	mstack;

	mstack.push_back(5);
	mstack.push_back(17);
	std::cout << mstack.back() << std::endl;
	mstack.pop_back();
	std::cout << mstack.size() << std::endl;
	mstack.push_back(3);
	mstack.push_back(5);
	mstack.push_back(737);
	//[...]
	mstack.push_back(0);
	std::list<int>::iterator	it = mstack.begin();
	std::list<int>::iterator	ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::list<int>	s(mstack);
}

template <typename Stack>
static void	printStack(std::string const &label, Stack const &st)
{
	std::cout << label << " (size " << st.size() << "): ";
	for (typename Stack::const_iterator it = st.begin(); it != st.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

static void	iteratorTest(void)
{
	std::cout << "=== iterators ===" << std::endl;
	MutantStack<int>	ms;

	for (int i = 1; i <= 5; i++)
		ms.push(i);
	printStack("const_iterator", ms);

	std::cout << "reverse_iterator (top -> bottom): ";
	for (MutantStack<int>::reverse_iterator it = ms.rbegin(); it != ms.rend(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	// イテレータ経由で中身を書き換える
	for (MutantStack<int>::iterator it = ms.begin(); it != ms.end(); ++it)
		*it *= 10;
	printStack("after *= 10", ms);
	std::cout << "top: " << ms.top() << std::endl;

	MutantStack<int> const	cms(ms);
	std::cout << "const reverse_iterator: ";
	for (MutantStack<int>::const_reverse_iterator it = cms.rbegin(); it != cms.rend(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

static void	copyTest(void)
{
	std::cout << "=== copy ===" << std::endl;
	MutantStack<std::string>	a;

	a.push("hello");
	a.push("world");

	MutantStack<std::string>	b(a);
	MutantStack<std::string>	c;
	c = a;
	a.pop();
	a.push("42");		// a だけ変更し、b, c に影響しないことを確認する
	printStack("a", a);
	printStack("b", b);
	printStack("c", c);
}

static void	emptyTest(void)
{
	std::cout << "=== empty ===" << std::endl;
	MutantStack<int>	ms;

	std::cout << "empty: " << (ms.empty() ? "true" : "false") << std::endl;
	std::cout << "begin == end: " << (ms.begin() == ms.end() ? "true" : "false") << std::endl;
}

// 第 2 テンプレート引数で、中身のコンテナを std::vector や std::list に変えられる
static void	otherContainerTest(void)
{
	std::cout << "=== underlying container ===" << std::endl;
	MutantStack<int, std::vector<int> >	vs;
	MutantStack<int, std::list<int> >	ls;

	for (int i = 0; i < 4; i++)
	{
		vs.push(i);
		ls.push(-i);
	}
	printStack("vector based", vs);
	printStack("list based", ls);
}

int	main(void)
{
	subjectTest();
	listTest();
	iteratorTest();
	copyTest();
	emptyTest();
	otherContainerTest();
	return (0);
}
