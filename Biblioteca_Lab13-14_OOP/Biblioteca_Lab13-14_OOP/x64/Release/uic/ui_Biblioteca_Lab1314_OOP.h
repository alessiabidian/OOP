/********************************************************************************
** Form generated from reading UI file 'Biblioteca_Lab1314_OOP.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BIBLIOTECA_LAB1314_OOP_H
#define UI_BIBLIOTECA_LAB1314_OOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Biblioteca_Lab1314_OOPClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Biblioteca_Lab1314_OOPClass)
    {
        if (Biblioteca_Lab1314_OOPClass->objectName().isEmpty())
            Biblioteca_Lab1314_OOPClass->setObjectName(QString::fromUtf8("Biblioteca_Lab1314_OOPClass"));
        Biblioteca_Lab1314_OOPClass->resize(600, 400);
        menuBar = new QMenuBar(Biblioteca_Lab1314_OOPClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Biblioteca_Lab1314_OOPClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Biblioteca_Lab1314_OOPClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Biblioteca_Lab1314_OOPClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Biblioteca_Lab1314_OOPClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Biblioteca_Lab1314_OOPClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Biblioteca_Lab1314_OOPClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Biblioteca_Lab1314_OOPClass->setStatusBar(statusBar);

        retranslateUi(Biblioteca_Lab1314_OOPClass);

        QMetaObject::connectSlotsByName(Biblioteca_Lab1314_OOPClass);
    } // setupUi

    void retranslateUi(QMainWindow *Biblioteca_Lab1314_OOPClass)
    {
        Biblioteca_Lab1314_OOPClass->setWindowTitle(QCoreApplication::translate("Biblioteca_Lab1314_OOPClass", "Biblioteca_Lab1314_OOP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Biblioteca_Lab1314_OOPClass: public Ui_Biblioteca_Lab1314_OOPClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BIBLIOTECA_LAB1314_OOP_H
