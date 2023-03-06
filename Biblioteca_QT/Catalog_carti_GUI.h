#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include "Service.h"
#include <QListWidget>
#include "Cos_cumparaturi_GUI.h"

using std::vector;
using std::string;
class Catalog_carti_GUI : public QWidget {
private:

	Catalog_carti& service;
	Cos_GUI cosWindow{ service };

	QLabel* label_titlu = new QLabel{ "Titlul cartii:" };
	QLabel* label_autor = new QLabel{ "Autorul cartii:" };
	QLabel* label_gen = new QLabel{ "Genul cartii:" };
	QLabel* label_durata = new QLabel{ "Anul aparitiei:" };

	QLineEdit* edit_titlu;
	QLineEdit* edit_autor;
	QLineEdit* edit_gen;
	QLineEdit* edit_an;

	QPushButton* buton_adauga;
	QPushButton* buton_sterge;
	QPushButton* buton_modifica;

	QGroupBox* group_box_sortare = new QGroupBox(tr("Optiuni sortare"));

	QRadioButton* radio_sortare_titlu = new QRadioButton(QString::fromStdString("Titlu"));
	QRadioButton* radio_sortare_autor = new QRadioButton(QString::fromStdString("Autor"));
	QRadioButton* radio_sortare_gen_an = new QRadioButton(QString::fromStdString("An+gen"));
	QPushButton* buton_sortare;

	QGroupBox* group_box_filtrare = new QGroupBox(tr("Optiuni filtrare"));
	QLabel* label_filtru_titlu = new QLabel{ "Titlu dupa care se filtreaza:" };
	QLineEdit* edit_filtru_titlu;
	QPushButton* buton_filtru_titlu;

	QLabel* label_filtru_an1 = new QLabel{ "An inceput: " };
	QLineEdit* edit_filtru_an1;
	QLabel* label_filtru_an2 = new QLabel{ "An final: " };
	QLineEdit* edit_filtru_an2;
	QPushButton* buton_filtru_an;

	QPushButton* buton_refacere_date;
	QPushButton* buton_undo;
	QPushButton* buton_exit;

	//QGroupBox* group_box_cos = new QGroupBox(tr("Cos de cumparaturi"));
	//QPushButton* buton_adauga_cos;
	//QPushButton* buton_goleste_cos;
	//QLabel* label_genereaza_cos = new QLabel{ "Numar carti adaugate in cos:" };
	//QLineEdit* edit_genereaza_cos;
	//QPushButton* buton_genereaza_cos;
	//QLabel* label_exporta_cos = new QLabel{ "Fisier pentru exportarea cosului:" };
	//QLineEdit* edit_exporta_cos;
	//QPushButton* buton_exporta_cos;

	QTableWidget* tabel_carti;
	QTableWidget* tabel_cos;

	QPushButton* buton_roman;
	QPushButton* buton_nuvela;
	QPushButton* buton_SF;
	QPushButton* buton_fictiune;

	QListWidget* lista_carti;

	QPushButton* buton_cos;

	void initializare_componente_gui();

	void conectare();
	void reincarca_carti(vector<Carte> carti);
	void reincarca_carti_lista(vector<Carte> carti);
	//void reincarca_cos(vector<Carte> carti);
public:
	Catalog_carti_GUI(Catalog_carti& service) : service{ service } {
		initializare_componente_gui();
		conectare();
		reincarca_carti(service.get_toate_cartile());
		reincarca_carti_lista(service.get_toate_cartile());
		//reincarca_cos(service.get_carti_inchiriate());
	}
	void adauga_carte_gui();
	void sterge_carte_gui();
	void modifica_carte_gui();
	void undo_gui();
	/*void adauga_carte_cos_gui();
	void goleste_cos_gui();
	void genereaza_cos_gui();
	void exporta_cos_gui();*/
	void numara_gen_roman();
	void numara_gen_nuvela();
	void numara_gen_fictiune();
	void numara_gen_SF();
};
