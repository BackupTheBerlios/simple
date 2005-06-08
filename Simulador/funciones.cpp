#include "sistema.h"

void escribe_componentes (Sistema *s)
{
	int numComponentes,numRelaciones;
	
	numComponentes=s->getNumComponentes();
	numRelaciones=s->getNumRelaciones ();
	
	cout << "Hay los siguientes " << numComponentes << "componentes" << endl;
	
}
