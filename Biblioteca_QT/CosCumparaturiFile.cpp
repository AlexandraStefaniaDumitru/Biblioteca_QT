//#pragma once
//#include <fstream>
//#include "CosCumparaturiFile.h"
//
//void InchirieriFile::incarca_din_fisier() {
//	std::ifstream intrare(nume_fisier);
//	if (!intrare.is_open()) {
//		throw ("Eroare deschidere: " + nume_fisier);
//	}
//	while (!intrare.eof()) {
//		std::string titlu, autor, gen;
//		int anul_aparitiei;
//		intrare >> titlu;
//		if (intrare.eof()) {
//			break;
//		}
//		intrare >> autor;
//		intrare >> gen;
//		intrare >> anul_aparitiei;
//
//		Carte carte{ titlu.c_str(),autor.c_str(),gen.c_str(),anul_aparitiei };
//		Inchirieri::adauga_inchiriere(carte);
//	}
//	intrare.close();
//}
//
//void InchirieriFile::scrie_in_fisier() {
//	std::ofstream out(nume_fisier);
//	if (!out.is_open()) {
//		throw ("Eroare deschidere: " + nume_fisier);
//	}
//	for (auto& carte : get_carti_inchiriate()) {
//		out << "Titlu: " << carte.get_titlu() << " | Autor: " << carte.get_autor() << " | Gen: " << carte.get_gen() << " | Anul aparitiei: " << carte.get_anul_aparitiei() << endl;
//	}
//	out.close();
//}