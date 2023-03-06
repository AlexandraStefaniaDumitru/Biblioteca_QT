#include "Cos_cumparaturi_GUI.h"



void Cos_GUI::initializeaza_GUI() {
	layout_principal = new QHBoxLayout{};
	this->setLayout(layout_principal);

	QWidget* partea_stanga = new QWidget{};
	QVBoxLayout* layout_stang = new QVBoxLayout{};
	partea_stanga->setLayout(layout_stang);

	QWidget* form_widget = new QWidget{};
	QFormLayout* layout_edits = new QFormLayout{};
	label_titlu = new QLabel{ "Titlu" };
	label_autor = new QLabel{ "Autor" };
	edit_titlu = new QLineEdit{};
	edit_autor = new QLineEdit{};

	label_slider = new QLabel{ "Nr. carti de generat" };
	edit_numar_slider = new QLineEdit{};
	layout_edits->addRow(label_titlu, edit_titlu);
	layout_edits->addRow(label_autor, edit_autor);
	layout_edits->addRow(label_slider, edit_numar_slider);
	form_widget->setLayout(layout_edits);


	buton_adauga = new QPushButton{ "Adauga in cos" };
	buton_genereaza = new QPushButton{ "Genereaza random" };
	buton_goleste = new QPushButton{ "Goleste cos" };
	buton_exporta = new QPushButton{ "Export cos" };
	buton_inchide = new QPushButton{ "Inchide" };

	buton_lable = new QPushButton{ "Fereastra label" };

	buton_tabel = new QPushButton{ "Fereastra tabel" };

	buton_deseneaza = new QPushButton{ "Fereastra desen" };


	slider_genereaza = new QSlider{};
	slider_genereaza->setMinimum(1);
	slider_genereaza->setMaximum(static_cast<int>(service.get_toate_cartile().size()));

	layout_stang->addWidget(form_widget);
	layout_stang->addWidget(buton_adauga);
	layout_stang->addWidget(buton_genereaza);
	layout_stang->addWidget(buton_goleste);
	layout_stang->addWidget(buton_exporta);
	layout_stang->addWidget(buton_deseneaza);
	layout_stang->addWidget(buton_inchide);

	QWidget* partea_dreapta = new QWidget{};
	QVBoxLayout* layout_drept = new QVBoxLayout{};
	partea_dreapta->setLayout(layout_drept);

	lista_carti = new QListWidget{};
	lista_carti->setFixedWidth(320);
	lista_carti->setSelectionMode(QAbstractItemView::SingleSelection);

	layout_drept->addWidget(lista_carti);


	layout_principal->addWidget(partea_stanga);
	layout_principal->addWidget(slider_genereaza);
	layout_principal->addWidget(partea_dreapta);


}

void clearLayout(QLayout* layout) {
	if (layout == NULL)
		return;
	QLayoutItem* item;
	while ((item = layout->takeAt(0))) {
		if (item->layout()) {
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget()) {
			delete item->widget();
		}
		delete item;
	}
}

void Cos_GUI::conectare() {
	service.get_cos().adauga_observer(this);
	QObject::connect(buton_adauga, &QPushButton::clicked, this, &Cos_GUI::adauga_cos);
	QObject::connect(slider_genereaza, &QSlider::sliderReleased, [&]() {
		qDebug() << slider_genereaza->value();
		});
	QObject::connect(buton_genereaza, &QPushButton::clicked, [&]() {
		int numar_carti = this->slider_genereaza->value();
		edit_numar_slider->setText(QString::number(numar_carti));
		qDebug() << "Atatea carti se adauga:" << numar_carti;
		service.adauga_inchirieri_random(numar_carti);
		this->reincarca_cos();
		});
	QObject::connect(buton_goleste, &QPushButton::clicked, [&]() {
		service.goleste_inchirieri();
		this->reincarca_cos();
		});
	QObject::connect(buton_exporta, &QPushButton::clicked, [&]() {

		});
	QObject::connect(buton_inchide, &QPushButton::clicked, this, &Cos_GUI::close);

	QObject::connect(buton_lable, &QPushButton::clicked, this, [&]() {
		auto labelWindow = new PlaylistGUILabel{ service.get_cos() };
		labelWindow->show();
		});
	QObject::connect(buton_tabel, &QPushButton::clicked, this, [&]() {
		auto tableWindow = new Cos_GUI_tabel{ service.get_cos() };
		tableWindow->show();
		});

	QObject::connect(buton_deseneaza, &QPushButton::clicked, this, [&]() {
		auto drawWindow = new Cos_GUI_deseneaza{ service.get_cos() };
		drawWindow->show();
		});

	QObject::connect(lista_carti, &QListWidget::itemSelectionChanged, [&]() {
		auto selItms = lista_carti->selectedItems();
		for (auto item : selItms) {
			qDebug() << item->text();
			item->setBackground(Qt::green); // sets green background
		}

		});




}


void Cos_GUI::reincarca_cos() {

	this->lista_carti->clear();

	const vector<Carte>& carti = service.get_carti_inchiriate();
	for (auto& carte : carti) {
		QString element_curent = QString::fromStdString(carte.get_titlu() + "\t" + carte.get_autor() + "\t" + carte.get_gen() + "\t" + to_string(carte.get_anul_aparitiei()));
		this->lista_carti->addItem(element_curent);
	}
}


void Cos_GUI::adauga_cos() {
	try {
		string titlu = edit_titlu->text().toStdString();
		string artist = edit_autor->text().toStdString();

		edit_titlu->clear();
		edit_autor->clear();


		this->service.adauga_inchiriere(titlu, artist);
		this->reincarca_cos();

		//afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
		QMessageBox::information(this, "Info", QString::fromStdString("Melodie adaugata cu succes."));

	}
	catch (Exceptie_repo& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.get_mesaj_eroare()));
	}
	catch (Exceptie_validare& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.get_mesaj_eroare()));
	}

}


