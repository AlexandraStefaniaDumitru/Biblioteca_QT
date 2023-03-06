#pragma once
#include "Carte.h"
#include <vector>
#include <algorithm>
#include <random>
using std::vector;

class Exceptie_repo {
private:
	string mesaj_eroare;
public:
	Exceptie_repo(string mesaj_eroare) : mesaj_eroare{ mesaj_eroare } {};
	string get_mesaj_eroare() {
		return this->mesaj_eroare;
	}
};

class Carte_repozitorii { 
private:
	vector<Carte> toate_cartile;
public:
	Carte_repozitorii() noexcept = default;
	Carte_repozitorii(const Carte_repozitorii& constructor) = delete;
	virtual void adauga_carte_repo(const Carte& carte);
	virtual void sterge_carte_repo(const Carte& carte);
	const vector<Carte> get_toate_cartile();
	const Carte& cauta(string titlu, string autor);
	bool carte_existenta(const Carte& carte);
};

class Carte_repozitorii_fisiere :public Carte_repozitorii {
private:
	string nume_fisier;
	void incarca_din_fisier();
	void salveaza_in_fisier();
public:
	Carte_repozitorii_fisiere(string nume_fisier) :Carte_repozitorii(), nume_fisier{ nume_fisier } {
		incarca_din_fisier(); 
	};
	void adauga_carte_repo(const Carte& carte) override;
	void sterge_carte_repo(const Carte& carte) override;
};
void teste_repo();
void teste_repo_fisiere();