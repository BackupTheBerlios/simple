#include <cstdlib>
#include <iostream>
#include "sistema.h"
#include "parser.h"


#include "funciones.h"

using namespace std;

int main(int argc, char *argv[])
{
	char* nombre_fichero="test.xml";
	Sistema *s;
	vector<Elemento*> elementos;
	vector<Relacion*> relaciones;
	Parser* elParser= new Parser ();
	
	if (!elParser->esValido (nombre_fichero) ) 
	{
		cout << "El fichero no es XML valido" << endl;
		return -1;
	}
	
	elementos=elParser->extraerElementos();
	relaciones=elParser->extraerRelaciones();
	
	
	s=new Sistema();
	for (int i=0;i<elementos.size();i++)
	{
		s->anadirComponente(elementos.at(i));
	}
	for (int i=0;i<relaciones.size();i++)
	{
		s->anadirRelacion(relaciones.at(i));
	}
	for (int x=0;x<6;x++)
	{
	escribe_componentes (s);	
	cout << endl;
	escribe_relaciones (s);
	cout << "Escriba el nombre del elemento para modificar su entrada" << endl;
	char nombre[40];
	cin >> nombre;
	cout << "Introduzca la nueva entrada." << endl;
	int entrada;
	cin >> entrada;
	Elemento* e=s->getRefElemento (nombre);
	e->setEntrada(entrada);
}
    system("PAUSE");
    return EXIT_SUCCESS;
}
