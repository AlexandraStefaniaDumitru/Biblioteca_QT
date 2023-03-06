#pragma once
#include "Repository.h"
#include "Undo.h"
#include "validatori.h"
#include "CosCumparaturi.h"
#include <functional>
#include <memory>
#include <fstream>
using std::function;
class Catalog_carti {
private:
	Carte_repozitorii& repo;
	Carte_validator& validator;
	Inchirieri cos_curent;
	vector<std::unique_ptr<ActiuneUndo>> actiuni_undo;
	vector<Carte> filtru(function<bool(const Carte&)> functie);
	vector<Carte> sortare_generala(bool(*functie_mai_mic)(const Carte&, const Carte&));
public:
	Catalog_carti(Carte_repozitorii& repo_carti, Carte_validator& validator) noexcept : repo{ repo_carti }, validator{ validator }{};
	Catalog_carti(const Catalog_carti& constructor) = delete;
	void adauga_carte(string titlu, string autor, string gen, int anul_aparitiei);
	void modifica_carte(string titlu, string autor, string gen_nou, int anul_aparitiei_nou);
	void sterge_carte(string titlu, string autor);
	const Carte& cautare_carte(string titlu, string autor);
	vector <Carte> filtrare_titlu(string titlu);
	vector <Carte> filtrare_an(int an_minim, int an_maxim);
	vector <Carte> sortare_titlu();
	vector <Carte> sortare_autor();
	vector <Carte> sortare_an_gen();
	void adauga_inchiriere(string titlu, string autor);
	size_t adauga_inchirieri_random(int);
	void goleste_inchirieri();
	const vector<Carte>& get_carti_inchiriate();
	void undo();
	void export_cumparaturi(string nume_fisier);
	const vector<Carte> get_toate_cartile() {
		return this->repo.get_toate_cartile();
	}
	int get_carti_gen(string gen);
	string string_carte(Carte& carte);
	Inchirieri& get_cos() {
		return this->cos_curent;
	}
};

void teste_service();