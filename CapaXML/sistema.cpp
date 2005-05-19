#include "sistema.h"
#include "constantes.h"

/*	Definicion de un sistema */
Sistema::Sistema () 
{
	for (int i=0;i<MAX_TAM_VECTOR;i++)
	{
		listaComponentes[i]=NULL;
		listaRelaciones[i]=NULL;
	}
	numComponentes=numRelaciones=0;
}

/*	Si se puede insertar un componente, se hace y se
	devuelve un 0, y si no se puede añadir se devuelve -1*/
int Sistema::anadirRelacion(Relacion* relacion)
{
	Elemento* 	primario;
	Elemento* 	secundario;
	XMLCh*		nombrePrimario;
	XMLCh*		nombreSecundario;
	XMLCh*		nombreElementoActual;
	
	primario=secundario=NULL;
	nombrePrimario=nombreSecundario=nombreElementoActual=NULL;
	if (numRelaciones<MAX_TAM_VECTOR)
	{
		/*	Despues de insertar la relacion en el sistema
			tenemos que hacer que el elemento secundario
			de la relacion sea un observador del primario*/
		
		/*	Para ello buscamos los elementos...*/
		nombrePrimario	=relacion->getNombrePrimario();
		nombreSecundario=relacion->getNombreSecundario();
		for (int i=0;i<numComponentes;i++)
		{
			nombreElementoActual=listaComponentes[i]->getNombreElemento();
			char* elem=XMLString::transcode (nombreElementoActual);
			cout << "Comparando " << elem << endl ;
			if (XMLString::equals(nombrePrimario, nombreElementoActual))
			{
				primario=listaComponentes[i];
			}
			
			if (XMLString::equals(nombreSecundario, nombreElementoActual))
			{
				secundario=listaComponentes[i];
			}
		}
		/*	... y si los dos elementos existen se "encadenan"*/
		if ( (primario!=NULL) && (secundario!=NULL) )
		{
			primario->anadirSuscriptor(secundario);
			listaRelaciones[numRelaciones++]=relacion;
			return 0;
		}
	} /*Fin del if global*/
	
	/*Si algo ha fallado...*/
	return -1;
}

int Sistema::anadirComponente(Elemento* componente)
{
	if (numComponentes<MAX_TAM_VECTOR)
	{
		listaComponentes[numComponentes++]=componente;
		char* nombre=XMLString::transcode (componente->getNombreElemento());
		cout << "Anadiendo " << nombre << endl;
		XMLString::release (&nombre);
		return 0;
	}
	return -1;
}
void Sistema::construir (DOMNode* nodo)
{
}

int	Sistema::getComponentes (Elemento* vectorElementos[])
{
	for (int i=0;i<numComponentes;i++)
	{
		vectorElementos[i]=listaComponentes[i];
	}
	return numComponentes;
}

int Sistema::getRelaciones (Relacion* vectorRelaciones[])
{
	for (int i=0;i<numRelaciones;i++)
	{
		vectorRelaciones[i]=listaRelaciones[i];
	}
	return numRelaciones;
}

int Sistema::getNumComponentes()
{
	return numComponentes;
}

int Sistema::getNumRelaciones()
{
	return numRelaciones;
}

Elemento* Sistema::getRefElemento (XMLCh* nombre)
{
	for (int i=0;i<numComponentes;i++)
	{
		if (XMLString::equals 
			(nombre, listaComponentes[i]->getNombreElemento()) )
		{
			return listaComponentes[i];
		} 
	} //Fin del for
	
	/*Si el elemento no ha aparecido...*/
	return NULL;
}


Elemento* Sistema::getRefElemento (char* nombre)
{
	XMLCh* nombreAux;
	nombreAux=XMLString::transcode (nombre);
	return (getRefElemento(nombreAux));
}

DOMNode* getNodo()
{
}
