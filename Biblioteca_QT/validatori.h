#pragma once
#include "Carte.h"
#include <vector>
#include <string>
using std::string;
using std::vector;
class Exceptie_validare {
	vector<string> mesaj_eroare;
public:
	Exceptie_validare(vector<string> mesaj_eroare) : mesaj_eroare{ mesaj_eroare } {};

	string get_mesaj_eroare() {
		string mesaj_complet = "";
		if (&mesaj_eroare != nullptr) {
			for (const string eroare : mesaj_eroare) {
				mesaj_complet += eroare + "\n";
			}
		}
		return mesaj_complet;
	}
};

class Carte_validator {
public:
	void valideaza(const Carte& carte) {
		vector<string> erori;
		if (carte.get_titlu().length() < 2)
			erori.push_back("Titlul trebuie sa aiba cel putin 2 caractere.");
		if (carte.get_autor().length() < 2)
			erori.push_back("Autorul trebuie sa aiba cel putin 2 caractere.");
		if (carte.get_gen().compare("roman") != 0 && carte.get_gen().compare("nuvela") != 0 && carte.get_gen().compare("SF") != 0 && carte.get_gen().compare("fictiune istorica")) {
			erori.push_back("Genul trebuie sa fie roman/nuvela/SF/fictiune istorica.");
		}
		if (carte.get_anul_aparitiei() < 0 || carte.get_anul_aparitiei() > 2022) {
			erori.push_back("Anul aparitiei trebuie sa fie intre 0 si 2022.");
		}
		if (erori.size() > 0)
			throw Exceptie_validare(erori);
	}
};