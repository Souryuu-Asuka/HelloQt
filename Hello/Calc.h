#pragma once

#include <vector>
#include <optional>
#include <string>

enum class Ops {
	Add,
	Sub,
	Mul,
	Div
};

std::string showOps(Ops);

struct Calculator {
	std::vector<int> current;
	std::optional<long> previous;
	std::optional<Ops> op;
	bool neg;

	Calculator();
	std::string render() const;
	void pushNumber(const int);
	void pushOp(const Ops);
	void calculate();
	void clear();
};

long vecToInt(const std::vector<int>&, bool);

std::vector<int> intToVec(const long);
