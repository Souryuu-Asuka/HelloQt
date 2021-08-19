#include "Calc.h"
#include <string>
#include <algorithm>
#include <charconv>

std::string showOps(Ops op)
{
	switch (op) {
	case Ops::Add:
		return "+";
	case Ops::Sub:
		return "-";
	case Ops::Mul:
		return "*";
	case Ops::Div:
		return "/";
	}
}

Calculator::Calculator()
{
	std::vector<int> x;
	current = x;
	previous = std::nullopt;
	op = std::nullopt;
	neg = false;
}

std::string Calculator::render() const
{
	return std::to_string(vecToInt(current, neg));
}

void Calculator::pushNumber(const int i)
{
	current.push_back(i);
}

void Calculator::pushOp(const Ops p)
{
	if (previous != std::nullopt) {
		calculate();
	}
	else {
		if (op != std::nullopt) {
			previous = vecToInt(current, neg);
			std::vector<int> tmp;
			current = tmp;
		}
	}
	op = p;
	neg = false;
}

void Calculator::calculate()
{
	if (op == std::nullopt || previous == std::nullopt)
		return;

	long result = vecToInt(current, neg);

	switch (op.value())
	{
	case Ops::Add:
		result = result + previous.value();
		break;
	case Ops::Sub:
		result = previous.value() - result;
		break;
	case Ops::Mul:
		result = result * previous.value();
		break;
	case Ops::Div:
		result = previous.value() / result;
		break;
	}

	previous = std::nullopt;
	op = std::nullopt;

	if (result < 0)
	{
		result = -result;
		neg = true;
	}

	current = intToVec(result);
}

void Calculator::clear()
{
	previous = std::nullopt;
	op = std::nullopt;
	current.clear();
}

long vecToInt(const std::vector<int>& v, bool neg)
{
	if (v.size() == 0)
		return 0;

	auto pw = [](int x) -> long {
		int acc = 1;
		for (int i = x - 1; i > 0; i--)
			acc *= 10;
		return acc;
	};

	long acc = 0;
	for (int i = 0; i < v.size(); i++)
		acc += v[i] * pw(v.size() - i);

	return neg ? -acc : acc;
}

std::vector<int> intToVec(const long i)
{
	std::vector<int> tmp;
	long x = i;
	int c = 0;
	while (x != 0)
	{
		c = x % 10;
		x = x / 10;
		tmp.push_back(c);
	}
	std::reverse(tmp.begin(), tmp.end());
	if (tmp.size() == 0)
		tmp.push_back(0);
	return tmp;
}
