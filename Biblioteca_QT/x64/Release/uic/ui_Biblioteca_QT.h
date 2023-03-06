/********************************************************************************
** Form generated from reading UI file 'Biblioteca_QT.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BIBLIOTECA_QT_H
#define UI_BIBLIOTECA_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Biblioteca_QTClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Biblioteca_QTClass)
    {
        if (Biblioteca_QTClass->objectName().isEmpty())
            Biblioteca_QTClass->setObjectName(QString::fromUtf8("Biblioteca_QTClass"));
        Biblioteca_QTClass->resize(600, 400);
        menuBar = new QMenuBar(Biblioteca_QTClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Biblioteca_QTClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Biblioteca_QTClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Biblioteca_QTClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Biblioteca_QTClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Biblioteca_QTClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Biblioteca_QTClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Biblioteca_QTClass->setStatusBar(statusBar);

        retranslateUi(Biblioteca_QTClass);

        QMetaObject::connectSlotsByName(Biblioteca_QTClass);
    } // setupUi

    void retranslateUi(QMainWindow *Biblioteca_QTClass)
    {
        Biblioteca_QTClass->setWindowTitle(QCoreApplication::translate("Biblioteca_QTClass", "Biblioteca_QT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Biblioteca_QTClass: public Ui_Biblioteca_QTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BIBLIOTECA_QT_H
