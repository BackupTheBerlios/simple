/*Fichero elementos.cpp
	Contiene la implementación de los elementos que forman parte de un
	sistema que se quiere simular
*/

#include "elementos.h"
#include "sistema.h"
#include <iostream>
#include <stdio.h>

#ifdef XERCES_CPP_NAMESPACE_USE
XERCES_CPP_NAMESPACE_USE
#endif	




/*En este fichero definimos las clases (objetos funcion) de los
 *distintos elementos*/

using namespace std;

/*Esta funcion la utilizo para no repetir la forma de comparar cadenas
  ya que a menudo he necesitado cambiar los objetos usados para comparar
  asi como la representación interna de las cadenas.
  Simplemente se usa para saber si dos cadenas son iguales*/
bool Elemento::iguales (const XMLCh* cad1, const XMLCh* cad2)
{
	return XMLString::equals (cad1, cad2);
}


/*	Inicializador generico para todos los elementos
	Cualquier clase hija puede modificarlo*/
	
void Elemento::inicializar ()
{
	nombreElemento=NULL;
	
	for (int i=0;i<MAX_SUSCRIPTORES;i++)
		listaSuscriptores[i]=NULL;
	totalSuscriptores=0;
	nombreElemento=NULL;
	entradaActual=salidaActual=0;
}
void Elemento::anadirSuscriptor (Elemento* e)
{
	listaSuscriptores[totalSuscriptores++]=e;
}

void Elemento::eliminarSuscriptor (Elemento* e)
{
	int posicionParaEliminar=-1;
	
	/*	Buscamos la posicion del elemento a eliminar*/
	for (int i=0;i<totalSuscriptores;i++)
	{
		if (listaSuscriptores[i]==e) posicionParaEliminar=i;
	}
	
	/*	Si hemos encontrado el elemento que se desea eliminar
		se desplaza todo el resto de la lista hacia la izquiera
		borrando así el elemento concreto */
	if (posicionParaEliminar!=-1)
	{
		for (int i=posicionParaEliminar+1;i<totalSuscriptores;i++)
		{
			listaSuscriptores[i]=listaSuscriptores[i+1];
		}
	}
}
XMLCh* Elemento::getNombreElemento ()
{
	return nombreElemento;
}
void Elemento::notificar()
{
	for (int i=0;i<totalSuscriptores;i++)
	{
		listaSuscriptores[i]->setEntrada(salidaActual);
		char *nombre=XMLString::transcode 
			(listaSuscriptores[i]->getNombreElemento() );
		cout << "Notificando a " << nombre <<endl	;
		XMLString::release (&nombre);
	}
}

/*	Cuando alguien modifica la entrada hay que tomar nota de 
	la entrada actual. Si la entrada corresponde a la entrada
	de activacion hay que notificar a todos los observadores*/
void Elemento::setEntrada(float entrada)
{
	cout << "La entrada se ha modificado y vale "<<entrada << endl;
	entradaActual=entrada;
}
float Elemento::getSalida()
{
	return salidaActual;
}

XMLCh*	convertir (float entrada)
{
	char cadAux[40];
	XMLCh* valorNodo;
	
	sprintf (cadAux, "%f", entrada);
	valorNodo=XMLString::transcode (cadAux);
	return valorNodo;
}







/*	Desarrollamos las relaciones */
Relacion::Relacion()
{
	nombrePrimario		=	NULL;
	nombreSecundario	=	NULL;
}
void Relacion::construir (DOMNode* nodo)
{
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    const XMLCh* elementoXMLabuscar;
     
    /*Recorremos las propiedades del Reed...*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad= hijo->getNodeName()  ;
              valor_propiedad=  hijo->getTextContent() ;
              elementoXMLabuscar=XMLString::transcode ("primario");
              /*... y aqui e extraen los valores almacenados en el XML*/
			  if (  XMLString::equals (nombre_propiedad, elementoXMLabuscar) ){
					nombrePrimario= XMLString::replicate (valor_propiedad);
					XMLString::removeWS(nombrePrimario);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("secundario");
			  if ( XMLString::equals (nombre_propiedad, elementoXMLabuscar) ){
					nombreSecundario=XMLString::replicate (valor_propiedad);
					XMLString::removeWS(nombreSecundario);
			  }
			}
			
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }
}
XMLCh*	Relacion::getNombrePrimario()
{
	return nombrePrimario;
}

XMLCh*	Relacion::getNombreSecundario()
{
	return nombreSecundario;
}
