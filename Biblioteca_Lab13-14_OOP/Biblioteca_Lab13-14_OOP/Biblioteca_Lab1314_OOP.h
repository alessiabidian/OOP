#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Biblioteca_Lab1314_OOP.h"

class Biblioteca_Lab1314_OOP : public QMainWindow
{
    Q_OBJECT

public:
    Biblioteca_Lab1314_OOP(QWidget *parent = Q_NULLPTR);

private:
    Ui::Biblioteca_Lab1314_OOPClass ui;
};
