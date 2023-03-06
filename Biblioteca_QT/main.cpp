#include "Biblioteca_QT.h"
#include "Catalog_carti_GUI.h"
#include <QtWidgets/QApplication>
//#include "UI.h"
#include <iostream>
using std::cout;
using std::endl;
void toate_testele() {
	teste_domain();
	teste_repo();
	teste_repo_fisiere();
	teste_service();
	cout << "S-au efectuat toate testele." << endl;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	Carte_repozitorii_fisiere repo_fisiere{ "carti.txt" };
	Carte_validator validator;
	Catalog_carti service{ repo_fisiere, validator };
	Catalog_carti_GUI gui{ service };
    gui.show();
    return a.exec();
}
