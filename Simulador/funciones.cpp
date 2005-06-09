#include "sistema.h"

void escribe_componentes (Sistema *s)
{
	int numComponentes,numRelaciones;
	Elemento* vectorElementos[20];
	numComponentes=s->getNumComponentes();
	numRelaciones=s->getNumRelaciones ();
	
	cout << "Hay los siguientes " << numComponentes << "componentes." << endl;
	
	char* nombre;
	s->getComponentes(vectorElementos);
	for (int i=0;i<numComponentes;i++)
	{
		nombre=XMLString::transcode (vectorElementos[i]->getNombreElemento());
		cout << "(" << i << ") " << nombre << endl;
		XMLString::release (&nombre);
	}
	
}

void escribe_relaciones (Sistema* s)
{
	int numRelaciones;
	Relacion* vectorRelaciones[20];
	numRelaciones=s->getNumRelaciones();
	
	cout << "Hay " << numRelaciones << " relaciones." << endl ;
	
	s->getRelaciones (vectorRelaciones);
	
	char* nombrePrimario;
	char* nombreSecundario;
	
	for (int i=0;i<numRelaciones;i++)
	{
		nombrePrimario=	XMLString::transcode
			(vectorRelaciones[i]->getNombrePrimario() );
		nombreSecundario= XMLString::transcode
			(vectorRelaciones[i]->getNombreSecundario() );
		cout << "La salida de " << nombrePrimario <<
			" va conectada a " << nombreSecundario << "." << endl;
	}
}
