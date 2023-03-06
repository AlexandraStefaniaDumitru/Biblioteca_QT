#pragma once
#include "UI.h"
#include <iostream>
using namespace std;
void Consola_UI::printeaza_meniu() {
	cout << endl << endl;
	cout << "1. Adaugare carte" << endl;
	cout << "2. Stergere carte" << endl;
	cout << "3. Modificare carte" << endl;
	cout << "4. Afisare carti" << endl;
	cout << "5. Cautare carte" << endl;
	cout << "6. Filtrare dupa titlu" << endl;
	cout << "7. Filtrare dupa anul aparitiei" << endl;
	cout << "8. Sortare dupa titlu" << endl;
	cout << "9. Sortare dupa autor" << endl;
	cout << "10. Sortare dupa anul aparitiei si dupa gen" << endl;
	cout << "11. Printare meniu" << endl;
	cout << "12. Cos cumparaturi" << endl;
	cout << "13. Undo" << endl;
	cout << "0. Exit" << endl << endl;
}
void Consola_UI::printeaza_meniu_cumparaturi(){
	cout << "MENIU INCHIRIERI" << endl;
	cout << "1. Adauga carte in cos" << endl;
	cout << "2. Adauga carti random in cos" << endl;
	cout << "3. Goleste cos" << endl;
	cout << "4. Afiseaza cos curent" << endl;
	cout << "5. Afiseaza meniu inchirieri" << endl;
	cout << "6. Export cos de cumparaturi" << endl;
	cout << "0. Inapoi la meniul principal" << endl;
}
void Consola_UI::adaugare() {
	string titlu, autor, gen;
	int anul_aparitiei;
	cout << "Titlul cartii este: ";
	getline(cin >> ws, titlu);
	cout << "Autorul cartii este: ";
	getline(cin >> ws, autor);
	cout << "Genul cartii este: ";
	getline(cin >> ws, gen);
	cout << "Anul aparitiei cartii este: ";
	cin >> anul_aparitiei;
	try {
		service.adauga_carte(titlu, autor, gen, anul_aparitiei);
	}
	catch (Exceptie_repo& exceptie) {
		cout << exceptie.get_mesaj_eroare();
	}
	catch (Exceptie_validare& exceptie) {
		cout << "Cartea nu este valida!" << endl;
		cout << exceptie.get_mesaj_eroare();
	}
}
void Consola_UI::modificare() {
	string titlu, autor, gen;
	int anul_aparitiei;
	cout << "Titlu cartii care se modifica: ";
	cin >> titlu;
	cout << "Autorul cartii care se modifica: ";
	cin >> autor;
	cout << "Noul gen: ";
	cin >> gen;
	cout << "Noul an al aparitiei: ";
	cin >> anul_aparitiei;
	try {
		service.modifica_carte(titlu, autor, gen, anul_aparitiei);
	}
	catch (Exceptie_repo& exceptie) {
		cout << exceptie.get_mesaj_eroare();
	}
	catch (Exceptie_validare& exceptie) {
		cout << "Cartea nu este valida!" << endl;
		cout << exceptie.get_mesaj_eroare();
	}
}
void Consola_UI::stergere() {
	string titlu, autor;
	cout << "Titlu cartii care se sterge: ";
	cin >> titlu;
	cout << "Autorul cartii care se sterge: ";
	cin >> autor; 
	try {
		service.sterge_carte(titlu, autor);
	}
	catch (Exceptie_repo& exceptie) {
		cout << exceptie.get_mesaj_eroare();
	}
}
void Consola_UI::cautare() {
	string titlu, autor;
	cout << "Titlul cartii cautate este: ";
	getline(cin >> ws, titlu);
	cout << "Autorul cartii cautate este: ";
	getline(cin >> ws, autor);
	try {
		Carte carte = service.cautare_carte(titlu, autor);
		cout << "Titlu: " << carte.get_titlu() << " | Autor: " << carte.get_autor() << " | Gen: " << carte.get_gen() << " | Anul aparitiei: " << carte.get_anul_aparitiei() << endl;
	}
	catch (Exceptie_repo& exceptie) {
		cout << exceptie.get_mesaj_eroare();
	}
}
void Consola_UI::filtrare_titlu() {
	string titlu_cautat;
	cout << "Titlul dupa care se filtreaza: ";
	cin >> titlu_cautat;
	printeaza_toate_cartile(service.filtrare_titlu(titlu_cautat));
}
void Consola_UI::filtrare_an() {
	int an_minim, an_maxim;
	cout << "Carti scrise dupa anul: ";
	cin >> an_minim; 
	cout << "Carti scrise pana in anul: ";
	cin >> an_maxim;
	printeaza_toate_cartile(service.filtrare_an(an_minim, an_maxim));
}
void Consola_UI::sortare_titlu() {
	printeaza_toate_cartile(service.sortare_titlu());
}
void Consola_UI::sortare_autor() {
	printeaza_toate_cartile(service.sortare_autor());
}
void Consola_UI::sortare_an_gen() {
	printeaza_toate_cartile(service.sortare_an_gen());
}
void Consola_UI::printeaza_toate_cartile(const vector<Carte>& toate_cartile) {
	if (toate_cartile.size() == 0) {
		cout << "Nu exista carti." << endl;
	}
	else {
		for (const auto& carte : toate_cartile) {
			if (&carte != nullptr) {
				cout << "Titlu: " << carte.get_titlu() << " | Autor: " << carte.get_autor() << " | Gen: " << carte.get_gen() << " | Anul aparitiei: " << carte.get_anul_aparitiei() << endl;
			}
		}
	}

}
void Consola_UI::adaugare_inchiriere() {
	string titlu, autor;
	cout << "Titlul cartii este: ";
	getline(cin >> ws, titlu);
	cout << "Autorul cartii este: ";
	getline(cin >> ws, autor);
	try {
		service.adauga_inchiriere(titlu, autor);
	}
	catch (Exceptie_repo& exceptie) {
		cout << exceptie.get_mesaj_eroare();
	}
	catch (Exceptie_validare& exceptie) {
		cout << "Cartea nu este valida!" << endl;
		cout << exceptie.get_mesaj_eroare();
	}
	cout << "Cosul de cumparaturi contine " << size(service.get_carti_inchiriate()) << " carti" << endl;
}
void Consola_UI::adaugare_inchirieri_random() {
	int numar_inchirieri;
	cout << "Cate carti se adauga? ";
	cin >> numar_inchirieri;
	try {
		const size_t numar_adaugate = service.adauga_inchirieri_random(numar_inchirieri);
		cout << "S-au adaugat " << numar_adaugate << " carti in cos." << endl;
	}
	catch (Exceptie_repo& exceptie) {
		cout << exceptie.get_mesaj_eroare();
	}
	cout << "Cosul de cumparaturi contine " << size(service.get_carti_inchiriate()) << " carti" << endl;
}
void Consola_UI::golire_inchirieri() {
	service.goleste_inchirieri();
	cout << "Cosul a fost golit" << endl;
	cout << "Cosul de cumparaturi contine " << size(service.get_carti_inchiriate()) << " carti" << endl;
}
void Consola_UI::export_cumparaturi() {
	cout << "Export cos de cumparaturi in fisierul: ";
	string nume_fisier;
	getline(cin >> ws, nume_fisier);
	service.export_cumparaturi(nume_fisier);
}
void Consola_UI::cos_inchirieri() {
	int comanda, rulare = 1;
	printeaza_meniu_cumparaturi();
	while (rulare) {
		cout << "Comanda este: ";
		cin >> comanda;
		switch (comanda) {
		case 1:
			adaugare_inchiriere();
			break;
		case 2:
			adaugare_inchirieri_random();
			break;
		case 3:
			golire_inchirieri();
			break;
		case 4:
			printeaza_toate_cartile(service.get_carti_inchiriate());
			break;
		case 5:
			printeaza_meniu_cumparaturi();
			break;
		case 6:
			export_cumparaturi();
			break;
		case 0:
			rulare = 0;
			break;
		default:
			break;
		}
	}
}
void Consola_UI::undo() {
	try {
		service.undo();
	}
	catch (Exceptie_repo& exceptie) {
		cout << exceptie.get_mesaj_eroare();
	}
}
void Consola_UI::run() {
	int comanda = 0, continua_rularea = 1;
	printeaza_meniu();
	while (continua_rularea) {
		cout << endl << "Comanda este: ";
		cin >> comanda;
		switch (comanda)
		{
		case 1:
			adaugare();
			break;
		case 2:
			stergere();
			break;
		case 3:
			modificare();
			break;
		case 4:
			printeaza_toate_cartile(service.get_toate_cartile());
			break;
		case 5:
			cautare();
			break;
		case 6:
			filtrare_titlu();
			break;
		case 7:
			filtrare_an();
			break;
		case 8:
			sortare_titlu();
			break;
		case 9:
			sortare_autor();
			break;
		case 10:
			sortare_an_gen();
			break;
		case 11:
			printeaza_meniu();
			break;
		case 12:
			cos_inchirieri();
			break;
		case 13:
			undo();
			break;
		case 0:
			continua_rularea = 0;
			break;
		default:
			break;
		}
	}
}