#pragma once
#include "Service.h"
#include <QtWidgets/QApplication>
#include <QWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QFormLayout>
#include <QMessageBox>
#include <string>
#include <set>
#include <vector>
#include <QDebug>
#include <QPainter>
#include <cstdlib>
using std::to_string;
using std::set;
using std::vector;

class Cos_GUI : public QWidget, public Observer {
private:
	Catalog_carti& service;
	QHBoxLayout* layout_principal;
	QListWidget* lista_carti;

	QLabel* label_titlu;
	QLabel* label_autor;
	QLineEdit* edit_titlu;
	QLineEdit* edit_autor;

	QPushButton* buton_adauga;
	QPushButton* buton_genereaza;
	QPushButton* buton_goleste;
	QPushButton* buton_exporta;
	QPushButton* buton_inchide;
	QPushButton* buton_lable;
	QPushButton* buton_tabel;
	QPushButton* buton_deseneaza;


	QLineEdit* edit_numar_slider;
	QLabel* label_slider;
	QSlider* slider_genereaza;

	void initializeaza_GUI();
	void conectare();

	void reincarca_cos();
	void adauga_cos();

	void update() override {
		reincarca_cos();
	}
public:
	Cos_GUI(Catalog_carti& carti) : service{ carti } {
		initializeaza_GUI();
		conectare();
	}

};
class PlaylistGUILabel :public QWidget, public Observer {
private:
	Inchirieri& cos;
	QLabel* label_numar_carti;
	QLineEdit* edit_numar_carti;
	void initializeaza_GUI() {
		QHBoxLayout* layout = new QHBoxLayout{};
		this->setLayout(layout);
		label_numar_carti = new QLabel{ "Numar de carti:" };
		edit_numar_carti = new QLineEdit{};
		layout->addWidget(label_numar_carti);
		layout->addWidget(edit_numar_carti);
		setAttribute(Qt::WA_DeleteOnClose);
		cos.adauga_observer(this);
	};
	void update() override {
		this->edit_numar_carti->setText(QString::number(cos.get_carti_inchiriate().size()));
	};
	~PlaylistGUILabel() {
		cos.elimina_observer(this);
	}

public:
	PlaylistGUILabel(Inchirieri& cos_carti) :cos{ cos_carti } {
		initializeaza_GUI();
	};

};
class Cos_GUI_tabel :public QWidget, public Observer {
private:
	Inchirieri& cos;
	QTableWidget* table;
	QPushButton* buton_goleste;
	void initializeaza_GUI() {
		QHBoxLayout* layout = new QHBoxLayout{};
		this->setLayout(layout);
		table = new QTableWidget{};
		buton_goleste = new QPushButton{ "Goleste cos" };
		layout->addWidget(table);
		layout->addWidget(buton_goleste);
		setAttribute(Qt::WA_DeleteOnClose);
		cos.adauga_observer(this);
	};
	void reloadTableData(const vector<Carte>& carti) {
		this->table->setColumnCount(4);
		this->table->setRowCount(static_cast<int>(carti.size()));
		for (int i = 0; i < carti.size(); i++) {
			table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(carti[i].get_titlu())));
			table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(carti[i].get_autor())));
			table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(carti[i].get_gen())));
			table->setItem(i, 3, new QTableWidgetItem(QString::number(carti[i].get_anul_aparitiei())));
		}

	};

	void conectare() {
		cos.adauga_observer(this);

		QObject::connect(buton_goleste, &QPushButton::clicked, [&]() {
			cos.goleste_inchirieri();
			reloadTableData(cos.get_carti_inchiriate());
			});
	}


public:
	Cos_GUI_tabel(Inchirieri& cos) :cos{ cos } {
		initializeaza_GUI();
		conectare();
	};

	void update() override {
		this->reloadTableData(cos.get_carti_inchiriate());
	}
	~Cos_GUI_tabel() {
		cos.elimina_observer(this);
	}

};

class Cos_GUI_deseneaza :public QWidget, public Observer {
private:
	Inchirieri& cos_carti;
	void paintEvent(QPaintEvent*) override {
		QPainter cos{ this };
		int x = 0;
		int y = 0;
		for (auto carte : cos_carti.get_carti_inchiriate()) {
			x = rand() % 400 + 1;
			y = rand() % 400 + 1;
			qDebug() << x << " " << y;
			QRectF target(x, y, 100, 94);
			QRectF source(0, 0, 732, 720);
			QImage image("bear.jpg");

			cos.drawImage(target, image, source);

			x += 40;

		}
	}

	void update() override {
		repaint();
	};
	~Cos_GUI_deseneaza() {
		cos_carti.elimina_observer(this);
	}

public:
	Cos_GUI_deseneaza(Inchirieri& cos_carti) :cos_carti{ cos_carti } {
		cos_carti.adauga_observer(this);
	};

};
