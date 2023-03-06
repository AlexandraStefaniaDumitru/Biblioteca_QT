//#pragma once
//#include "CosCumparaturi.h"
//class InchirieriFile :public Inchirieri {
//private:
//	std::string nume_fisier;
//	void incarca_din_fisier();
//	void scrie_in_fisier();
//public:
//	InchirieriFile(std::string nume_fisier) : Inchirieri(), nume_fisier{ nume_fisier }{
//		incarca_din_fisier();
//	}
//	void adauga_inchiriere(const Carte& carte) override {
//		Inchirieri::adauga_inchiriere(carte);
//		scrie_in_fisier();
//	}
//	void adauga_inchirieri_random(vector<Carte> carti_initiale, int numar_inchirieri) override {
//		Inchirieri::adauga_inchirieri_random(carti_initiale, numar_inchirieri);
//		scrie_in_fisier();
//	
//	void goleste_inchirieri() override {
//		Inchirieri::goleste_inchirieri();
//		scrie_in_fisier();
//	}
//};