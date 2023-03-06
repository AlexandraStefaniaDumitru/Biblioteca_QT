#pragma once
#include<iostream>
#include<string>
using std::string;
using std::cout;
using std::endl;
class Carte {
private:
	string titlu;
	string autor;
	string gen;
	int anul_aparitiei;
public:
	Carte() = default;
	Carte(string titlu, string autor, string gen, int anul_aparitiei) : titlu{ titlu }, autor{ autor }, gen{ gen }, anul_aparitiei{ anul_aparitiei }{};
	Carte(const Carte& constructor) : titlu{ constructor.titlu }, autor{ constructor.autor }, gen{ constructor.gen }, anul_aparitiei{ constructor.anul_aparitiei }{};
	string get_titlu() const;
	string get_autor() const;
	string get_gen() const;
	int get_anul_aparitiei() const noexcept;
	string print_carte();

	void set_titlu(string titlu_nou);
	void set_autor(string autor_nou);
	void set_gen(string gen_nou);
	void set_anul_aparitiei(int anul_aparitiei_nou) noexcept;
};

bool comparare_titlu(const Carte& carte1, const Carte& carte2);
bool comparare_autor(const Carte& carte1, const Carte& carte2);
bool comparare_anul_aparitiei_gen(const Carte& carte1, const Carte& carte2);
bool operator==(const Carte& carte1, const Carte& carte2);
void teste_domain();