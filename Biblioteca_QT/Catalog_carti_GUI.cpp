#include "Catalog_carti_GUI.h"
#include <string> 
void Catalog_carti_GUI::initializare_componente_gui() {

	QHBoxLayout* layout_principal = new QHBoxLayout;
	this->setLayout(layout_principal);

	QWidget* functionalitati = new QWidget;
	QVBoxLayout* functionalitati_layout = new QVBoxLayout;
	functionalitati->setLayout(functionalitati_layout);

	QWidget* form_carte = new QWidget;
	QFormLayout* layout_carte = new QFormLayout;
	form_carte->setLayout(layout_carte);
	edit_titlu = new QLineEdit;
	edit_autor = new QLineEdit;
	edit_gen = new QLineEdit;
	edit_an = new QLineEdit;

	layout_carte->addRow(label_titlu, edit_titlu);
	layout_carte->addRow(label_autor, edit_autor);
	layout_carte->addRow(label_gen, edit_gen);
	layout_carte->addRow(label_durata, edit_an);

	QWidget* operatii = new QWidget;
	QHBoxLayout* layout_operatii = new QHBoxLayout(operatii);
	buton_adauga = new QPushButton("Adauga carte");
	layout_operatii->addWidget(buton_adauga);
	buton_sterge = new QPushButton("Sterge carte");
	layout_operatii->addWidget(buton_sterge);
	buton_modifica = new QPushButton("Modifica carte");
	layout_operatii->addWidget(buton_modifica);

	functionalitati_layout->addWidget(form_carte);
	functionalitati_layout->addWidget(operatii);

	QHBoxLayout* radio_layout_sortare = new QHBoxLayout;
	this->group_box_sortare->setLayout(radio_layout_sortare);
	radio_layout_sortare->addWidget(radio_sortare_titlu);
	radio_layout_sortare->addWidget(radio_sortare_autor);
	radio_layout_sortare->addWidget(radio_sortare_gen_an);

	buton_sortare = new QPushButton("Sorteaza carti");
	radio_layout_sortare->addWidget(buton_sortare);

	functionalitati_layout->addWidget(group_box_sortare);

	
	QFormLayout* filtru_titlu_layout = new QFormLayout;
	this->group_box_filtrare->setLayout(filtru_titlu_layout);
	edit_filtru_titlu = new QLineEdit();
	filtru_titlu_layout->addRow(label_filtru_titlu, edit_filtru_titlu);
	buton_filtru_titlu = new QPushButton("Filtreaza carti dupa titlu");
	filtru_titlu_layout->addWidget(buton_filtru_titlu);

	QFormLayout* filtru_an_layout = new QFormLayout;
	this->group_box_filtrare->setLayout(filtru_an_layout);
	edit_filtru_an1 = new QLineEdit();
	filtru_titlu_layout->addRow(label_filtru_an1, edit_filtru_an1);
	edit_filtru_an2 = new QLineEdit();
	filtru_titlu_layout->addRow(label_filtru_an2, edit_filtru_an2);
	buton_filtru_an = new QPushButton("Filtreaza carti dupa an");
	filtru_titlu_layout->addWidget(buton_filtru_an);

	functionalitati_layout->addWidget(group_box_filtrare);

	
	//QFormLayout* cos_edit = new QFormLayout;
	//this->group_box_cos->setLayout(cos_edit);
	//buton_adauga_cos = new QPushButton("Adauga in cos");
	//cos_edit->addWidget(buton_adauga_cos);
	//buton_goleste_cos = new QPushButton("Golire cos");
	//cos_edit->addWidget(buton_goleste_cos);
	//group_box_cos->setLayout(cos_edit);
	//edit_genereaza_cos = new QLineEdit();
	//cos_edit->addRow(label_genereaza_cos, edit_genereaza_cos);
	//buton_genereaza_cos = new QPushButton("Genereaza cos");
	//cos_edit->addWidget(buton_genereaza_cos);
	//edit_exporta_cos = new QLineEdit();
	//cos_edit->addRow(label_exporta_cos, edit_exporta_cos);
	//buton_exporta_cos = new QPushButton("Exporta cos");
	//cos_edit->addWidget(buton_exporta_cos);
	//functionalitati_layout->addWidget(group_box_cos);

	buton_refacere_date = new QPushButton("Refacere date");
	functionalitati_layout->addWidget(buton_refacere_date);

	buton_undo = new QPushButton("Undo");
	functionalitati_layout->addWidget(buton_undo);

	buton_cos = new QPushButton("Cos de cumparaturi");
	functionalitati_layout->addWidget(buton_cos);

	buton_exit = new QPushButton("Exit");
	functionalitati_layout->addWidget(buton_exit);


	QWidget* date_carti = new QWidget;
	QVBoxLayout* date_carti_layout = new QVBoxLayout;
	date_carti->setLayout(date_carti_layout);

	int numar_linii = 10;
	int numar_coloane = 4;
	this->tabel_carti = new QTableWidget{ numar_linii, numar_coloane };
	QStringList antet_tabel;
	antet_tabel << "Titlu" << "Autor" << "Gen" << "An aparitie";
	this->tabel_carti->setHorizontalHeaderLabels(antet_tabel);
	this->tabel_carti->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	date_carti_layout->addWidget(tabel_carti);

	QWidget* genuri = new QWidget;
	QHBoxLayout* layout_genuri = new QHBoxLayout(genuri);
	buton_roman = new QPushButton("Romane");
	layout_genuri->addWidget(buton_roman);
	buton_nuvela = new QPushButton("Nuvele");
	layout_genuri->addWidget(buton_nuvela);
	buton_SF = new QPushButton("SF-uri");
	layout_genuri->addWidget(buton_SF);
	buton_fictiune = new QPushButton("Fictiune");
	layout_genuri->addWidget(buton_fictiune);
	date_carti_layout->addWidget(genuri);


	/*int numar_linii_cos = 10;
	int numar_coloane_cos = 2;
	this->tabel_cos = new QTableWidget{ numar_linii_cos, numar_coloane_cos };
	QStringList antet_tabel_cos;
	antet_tabel_cos << "Titlu carti inchiriate" << "Autor";
	this->tabel_cos->setHorizontalHeaderLabels(antet_tabel_cos);
	this->tabel_cos->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	date_carti_layout->addWidget(tabel_cos);*/


	layout_principal->addWidget(functionalitati);
	layout_principal->addWidget(date_carti);

	this->lista_carti = new QListWidget;
	date_carti_layout->addWidget(lista_carti);
}
void Catalog_carti_GUI::reincarca_carti(vector<Carte> carti) {
	this->tabel_carti->clearContents();
	this->tabel_carti->setRowCount(carti.size());

	int numar_linie = 0;
	for (auto& carte : carti) {
		this->tabel_carti->setItem(numar_linie, 0, new QTableWidgetItem(QString::fromStdString(carte.get_titlu())));
		this->tabel_carti->setItem(numar_linie, 1, new QTableWidgetItem(QString::fromStdString(carte.get_autor())));
		this->tabel_carti->setItem(numar_linie, 2, new QTableWidgetItem(QString::fromStdString(carte.get_gen())));
		this->tabel_carti->setItem(numar_linie, 3, new QTableWidgetItem(QString::number(carte.get_anul_aparitiei())));
		numar_linie++;
	}
}
void Catalog_carti_GUI::reincarca_carti_lista(vector<Carte> carti) {
	this->lista_carti->clear();
	int row = 0;
	for (auto& carte : carti) {
		QListWidgetItem* carte_noua = new QListWidgetItem;
		carte_noua->setText(QString::fromStdString(carte.print_carte()));
		lista_carti->insertItem(row, carte_noua);
		row++;
	}
}
//void Catalog_carti_GUI::reincarca_cos(vector<Carte> carti) {
//	this->tabel_cos->clearContents();
//	this->tabel_cos->setRowCount(carti.size());
//
//	int numar_linie = 0;
//	for (auto& carte : carti) {
//		this->tabel_cos->setItem(numar_linie, 0, new QTableWidgetItem(QString::fromStdString(carte.get_titlu())));
//		this->tabel_cos->setItem(numar_linie, 1, new QTableWidgetItem(QString::fromStdString(carte.get_autor())));
//		this->tabel_cos->setItem(numar_linie, 2, new QTableWidgetItem(QString::fromStdString(carte.get_gen())));
//		this->tabel_cos->setItem(numar_linie, 3, new QTableWidgetItem(QString::number(carte.get_anul_aparitiei())));
//		numar_linie++;
//	}
//}
void Catalog_carti_GUI::conectare() {
	QObject::connect(buton_adauga, &QPushButton::clicked, this, &Catalog_carti_GUI::adauga_carte_gui);
	QObject::connect(buton_sterge, &QPushButton::clicked, this, &Catalog_carti_GUI::sterge_carte_gui);
	QObject::connect(buton_modifica, &QPushButton::clicked, this, &Catalog_carti_GUI::modifica_carte_gui);
	/*QObject::connect(buton_adauga_cos, &QPushButton::clicked, this, &Catalog_carti_GUI::adauga_carte_cos_gui);
	QObject::connect(buton_goleste_cos, &QPushButton::clicked, this, &Catalog_carti_GUI::goleste_cos_gui);
	QObject::connect(buton_exporta_cos, &QPushButton::clicked, this, &Catalog_carti_GUI::exporta_cos_gui);
	QObject::connect(buton_genereaza_cos, &QPushButton::clicked, this, &Catalog_carti_GUI::genereaza_cos_gui);*/
	QObject::connect(buton_undo, &QPushButton::clicked, this, &Catalog_carti_GUI::undo_gui);
	QObject::connect(buton_exit, &QPushButton::clicked, this, QApplication::quit);
	QObject::connect(buton_cos, &QPushButton::clicked, [&]() {
		cosWindow.show();
		});

	QObject::connect(buton_sortare, &QPushButton::clicked, [&]() {
		if (this->radio_sortare_titlu->isChecked()) {
			this->reincarca_carti(service.sortare_titlu());
			this->reincarca_carti_lista(service.sortare_titlu());
		}
			
		else if (this->radio_sortare_autor->isChecked()) {
			this->reincarca_carti(service.sortare_autor());
			this->reincarca_carti_lista(service.sortare_autor());
		}
			
		else if (this->radio_sortare_gen_an->isChecked()) {
			this->reincarca_carti(service.sortare_an_gen());
			this->reincarca_carti_lista(service.sortare_an_gen());
		}
			
		});

	QObject::connect(buton_filtru_titlu, &QPushButton::clicked, [&]() {
		string titlu_filtru = this->edit_filtru_titlu->text().toStdString();
		this->reincarca_carti(service.filtrare_titlu(titlu_filtru));
		this->reincarca_carti_lista(service.filtrare_titlu(titlu_filtru));
		edit_filtru_titlu->clear();
		});

	QObject::connect(buton_filtru_an, &QPushButton::clicked, [&]() {
		int an_inceput_filtru = this->edit_filtru_an1->text().toInt();
		int an_sfarsit_filtru = this->edit_filtru_an2->text().toInt();
		this->reincarca_carti(service.filtrare_an(an_inceput_filtru, an_sfarsit_filtru));
		this->reincarca_carti_lista(service.filtrare_an(an_inceput_filtru, an_sfarsit_filtru));
		edit_filtru_an1->clear();
		edit_filtru_an2->clear();
		});

	QObject::connect(buton_refacere_date, &QPushButton::clicked, [&]() {
		this->reincarca_carti(service.get_toate_cartile());
		this->reincarca_carti_lista(service.get_toate_cartile());
		});

	QObject::connect(buton_roman, &QPushButton::clicked, this, &Catalog_carti_GUI::numara_gen_roman);
	QObject::connect(buton_nuvela, &QPushButton::clicked, this, &Catalog_carti_GUI::numara_gen_nuvela);
	QObject::connect(buton_SF, &QPushButton::clicked, this, &Catalog_carti_GUI::numara_gen_SF);
	QObject::connect(buton_fictiune, &QPushButton::clicked, this, &Catalog_carti_GUI::numara_gen_fictiune);
}


void Catalog_carti_GUI::adauga_carte_gui() {
	try {
		string titlu = edit_titlu->text().toStdString();
		string autor = edit_autor->text().toStdString();
		string gen = edit_gen->text().toStdString();
		int an_aparitie = edit_an->text().toInt();

		edit_titlu->clear();
		edit_autor->clear();
		edit_gen->clear();
		edit_an->clear();

		this->service.adauga_carte(titlu, autor, gen, an_aparitie);
		this->reincarca_carti(this->service.get_toate_cartile());
		this->reincarca_carti_lista(this->service.get_toate_cartile());

		QMessageBox::information(this, "Info", QString::fromStdString("Carte adaugata cu succes!"));
	}
	catch (Exceptie_repo& repo_exceptie) {
		QMessageBox::warning(this, "Atentie!", QString::fromStdString(repo_exceptie.get_mesaj_eroare()));
	}
	catch (Exceptie_validare& validare_exceptie) {
		QMessageBox::warning(this, "Atentie!", QString::fromStdString(validare_exceptie.get_mesaj_eroare()));
	}
}
void Catalog_carti_GUI::sterge_carte_gui() {
	try {
		string titlu = edit_titlu->text().toStdString();
		string autor = edit_autor->text().toStdString();

		edit_titlu->clear();
		edit_autor->clear();
		edit_gen->clear();
		edit_an->clear();

		this->service.sterge_carte(titlu, autor);
		this->reincarca_carti(this->service.get_toate_cartile());
		this->reincarca_carti_lista(this->service.get_toate_cartile());

		QMessageBox::information(this, "Info", QString::fromStdString("Carte stearsa cu succes!"));

	}
	catch (Exceptie_validare& validare_exceptie) {
		QMessageBox::warning(this, "Atentie!", QString::fromStdString(validare_exceptie.get_mesaj_eroare()));
	}
	catch (Exceptie_repo& repo_exceptie) {
		QMessageBox::warning(this, "Atentie!", QString::fromStdString(repo_exceptie.get_mesaj_eroare()));
	}
}
void Catalog_carti_GUI::modifica_carte_gui() {
	try {
		string titlu = edit_titlu->text().toStdString();
		string autor = edit_autor->text().toStdString();
		string gen = edit_gen->text().toStdString();
		int an_aparitie = edit_an->text().toInt();

		edit_titlu->clear();
		edit_autor->clear();
		edit_gen->clear();
		edit_an->clear();

		this->service.modifica_carte(titlu, autor, gen, an_aparitie);
		this->reincarca_carti(this->service.get_toate_cartile());
		this->reincarca_carti_lista(this->service.get_toate_cartile());

		QMessageBox::information(this, "Info", QString::fromStdString("Carte modificata cu succes!"));

	}
	catch (Exceptie_validare& validare_exceptie) {
		QMessageBox::warning(this, "Atentie!", QString::fromStdString(validare_exceptie.get_mesaj_eroare()));
	}
	catch (Exceptie_repo& repo_exceptie) {
		QMessageBox::warning(this, "Atentie!", QString::fromStdString(repo_exceptie.get_mesaj_eroare()));
	}
}
void Catalog_carti_GUI::undo_gui() {
	try {
		this->service.undo();
		this->reincarca_carti(this->service.get_toate_cartile());
		this->reincarca_carti_lista(this->service.get_toate_cartile());
		QMessageBox::information(this, "Info", QString::fromStdString("Undo efectuat cu succes!"));
	}
	catch (Exceptie_repo& repo_exceptie) {
		QMessageBox::warning(this, "Atentie!", QString::fromStdString(repo_exceptie.get_mesaj_eroare()));
	}
}
//void Catalog_carti_GUI::adauga_carte_cos_gui(){
//	try {
//		string titlu = edit_titlu->text().toStdString();
//		string autor = edit_autor->text().toStdString();
//
//		edit_titlu->clear();
//		edit_autor->clear();
//		edit_gen->clear();
//		edit_an->clear();
//
//		this->service.adauga_inchiriere(titlu, autor);
//		this->reincarca_cos(this->service.get_carti_inchiriate());
//
//		QMessageBox::information(this, "Info", QString::fromStdString("Carte adaugata cu succes!"));
//
//	}
//	catch (Exceptie_repo& repo_exceptie) {
//		QMessageBox::warning(this, "Atentie!", QString::fromStdString(repo_exceptie.get_mesaj_eroare()));
//	}
//	catch (Exceptie_validare& validare_exceptie) {
//		QMessageBox::warning(this, "Atentie!", QString::fromStdString(validare_exceptie.get_mesaj_eroare()));
//	}
//}
//void Catalog_carti_GUI::goleste_cos_gui(){
//	this->service.goleste_inchirieri();
//	this->reincarca_cos(this->service.get_carti_inchiriate());
//}
//void Catalog_carti_GUI::genereaza_cos_gui() {
//	try {
//		int numar_carti = edit_genereaza_cos->text().toInt();
//		edit_genereaza_cos->clear();
//		this->service.adauga_inchirieri_random(numar_carti);
//		this->reincarca_cos(this->service.get_carti_inchiriate());
//
//		QMessageBox::information(this, "Info", QString::fromStdString("Carti adaugate cu succes!"));
//	}
//	catch (Exceptie_repo& repo_exceptie) {
//		QMessageBox::warning(this, "Atentie!", QString::fromStdString(repo_exceptie.get_mesaj_eroare()));
//	}
//}
//void Catalog_carti_GUI::exporta_cos_gui() {
//	string nume_fisier = edit_exporta_cos->text().toStdString();
//	if (nume_fisier != "") {
//		this->service.export_cumparaturi(nume_fisier);
//		QMessageBox::information(this, "Info", QString::fromStdString("Carti exportate cu succes!"));
//	}
//	else {
//		QMessageBox::warning(this, "Atentie!", QString::fromStdString("Fisierul nu este valid!"));
//	}
//}
void Catalog_carti_GUI::numara_gen_roman() {
	int numar_carti = this->service.get_carti_gen("roman");
	std::string string_numar = std::to_string(numar_carti);
	QMessageBox::information(this, "Contor carti", QString::fromStdString(string_numar+" carti cu genul roman"));
}
void Catalog_carti_GUI::numara_gen_nuvela() {
	int numar_carti = this->service.get_carti_gen("nuvela");
	std::string string_numar = std::to_string(numar_carti);
	QMessageBox::information(this, "Contor carti", QString::fromStdString(string_numar + " carti cu genul nuvela"));
}
void Catalog_carti_GUI::numara_gen_fictiune() {
	int numar_carti = this->service.get_carti_gen("fictiune istorica");
	std::string string_numar = std::to_string(numar_carti);
	QMessageBox::information(this, "Contor carti", QString::fromStdString(string_numar + " carti cu genul fictiune istorica"));
}
void Catalog_carti_GUI::numara_gen_SF() {
	int numar_carti = this->service.get_carti_gen("SF");
	std::string string_numar = std::to_string(numar_carti);
	QMessageBox::information(this, "Contor carti", QString::fromStdString(string_numar + " carti cu genul SF"));
}