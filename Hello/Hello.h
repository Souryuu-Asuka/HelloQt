#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets>
#include "ui_Hello.h"
#include "Calc.h"

class Hello : public QMainWindow
{
    Q_OBJECT

public:
    Hello(QWidget *parent = Q_NULLPTR);

private:
    Ui::HelloClass ui;
    Calculator calc;
    
    void connectNumberPad(QPushButton*, int, QLabel*);
};
