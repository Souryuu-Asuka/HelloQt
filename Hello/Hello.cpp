#include "Hello.h"
#include <QtWidgets>
#include "Calc.h"

#define NB(name) new QPushButton(name)

Hello::Hello(QWidget* parent)
	: QMainWindow(parent)
{
	QWidget* window = new QWidget;
	QPushButton* buttons[4][4] =
	{
		{NB("7"),NB("8"),NB("9"),NB("+")},
		{NB("4"),NB("5"),NB("6"),NB("-")},
		{NB("1"),NB("2"),NB("3"),NB("*")},
		{NB("C"),NB("0"),NB("="),NB("/")}
	};

	auto number = new QLabel("0");
	number->setAlignment(Qt::AlignRight);

	number->setText(calc.render().c_str());

	auto layout = new QGridLayout(window);

	layout->addWidget(number, 0, 0, 1, 4);

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			layout->addWidget(buttons[i][j], i + 1, j);

	for (auto j : { 0, 1, 2 }) {
			connectNumberPad(buttons[0][j], j + 7, number);
			connectNumberPad(buttons[1][j], j + 4, number);
			connectNumberPad(buttons[2][j], j + 1, number);
		}
	connectNumberPad(buttons[3][1], 0, number);

	QObject::connect(buttons[3][0],
		&QPushButton::clicked,
		[this, number]() {
			calc.clear();
			number->setText(calc.render().c_str());
		});

	for (auto i : { 0, 1, 2, 3 })
	{
		Ops ops[] = { Ops::Add, Ops::Sub, Ops::Mul, Ops::Div };
		QObject::connect(buttons[i][3],
			&QPushButton::clicked,
			[this, number, ops, i]() {
				calc.pushOp(ops[i]);
				number->setText(showOps(ops[i]).c_str());
			});
	}

	QObject::connect(buttons[3][2],
		&QPushButton::clicked,
		[this, number]() {
			calc.calculate();
			number->setText(calc.render().c_str());
		});

	ui.setupUi(this);

	setCentralWidget(window);
}

void Hello::connectNumberPad(QPushButton* button, int n, QLabel* number)
{
	QObject::connect(button,
		&QPushButton::clicked,
		[this, number, n]() {
			calc.pushNumber(n);
			number->setText(calc.render().c_str());
		});
}