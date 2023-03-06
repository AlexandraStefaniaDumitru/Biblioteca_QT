#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Biblioteca_QT.h"

class Biblioteca_QT : public QMainWindow
{
    Q_OBJECT

public:
    Biblioteca_QT(QWidget *parent = Q_NULLPTR);

private:
    Ui::Biblioteca_QTClass ui;
};
