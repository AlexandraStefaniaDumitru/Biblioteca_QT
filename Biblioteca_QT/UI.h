#pragma once
#include "Service.h"
class Consola_UI {
private:
	Catalog_carti& service;
public:
	Consola_UI(Catalog_carti& service) noexcept :service{ service } {};
	Consola_UI(const Consola_UI& constructor) = delete;
	void printeaza_meniu();
	void printeaza_meniu_cumparaturi();
	void adaugare();
	void cautare();
	void modificare();
	void stergere();
	void filtrare_titlu();
	void filtrare_an();
	void sortare_titlu();
	void sortare_autor();
	void sortare_an_gen();
	void printeaza_toate_cartile(const vector<Carte>& toate_cartile);
	void cos_inchirieri();
	void adaugare_inchiriere();
	void adaugare_inchirieri_random();
	void golire_inchirieri();
	void export_cumparaturi();
	void undo();
	void run();
};