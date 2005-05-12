/*Fichero elementos.cpp
	Contiene la implementación de los elementos que forman parte de un
	sistema que se quiere simular
*/

#include "elementos.h"
#include <iostream>


#ifdef XERCES_CPP_NAMESPACE_USE
XERCES_CPP_NAMESPACE_USE
#endif	


/*	Este es el valor inicial que por defecto adoptan
	todas las constantes. Usado para depurar, por lo que a
	si te lo encuentras en la depuración y ningún fichero XML
	lo contiene es porque algún objeto no se ha inicializado a partir
	del XML*/
#define VALOR_INICIAL -7.65


/*En este fichero definimos las clases (objetos funcion) de los
 *distintos elementos*/

using namespace std;

/*Esta funcion la utilizo para no repetir la forma de comparar cadenas
  ya que a menudo he necesitado cambiar los objetos usados para comparar
  asi como la representación interna de las cadenas.
  Simplemente se usa para saber si dos cadenas son iguales*/
bool iguales (const XMLCh* cad1, const XMLCh* cad2)
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
	}
}

/*	Cuando alguien modifica la entrada hay que tomar nota de 
	la entrada actual. Si la entrada corresponde a la entrada
	de activacion hay que notificar a todos los observadores*/
void Elemento::setEntrada(float entrada)
{
	entradaActual=entrada;
}
float Elemento::getSalida()
{
	return salidaActual;
}
//El constructor solo inicializa*/
Reed::Reed ()
{
	/*Se llama al inicializador generico*/
	inicializar ();
	
	/*Y se inicializan el resto de miembros*/
	entradaReposo		=	salidaReposo		=	VALOR_INICIAL;
	entradaActivacion	=	salidaActivacion	=	VALOR_INICIAL;
	
	
}

void Reed::construir (DOMNode *nodo){
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    XMLCh* elementoXMLabuscar;
    /*Recorremos las propiedades del Reed*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad= hijo->getNodeName();
              valor_propiedad=  hijo->getTextContent() ;
              
              /*.. y a extraer propiedades*/
              elementoXMLabuscar=XMLString::transcode ("nombreelemento");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					nombreElemento=XMLString::replicate (valor_propiedad);
					XMLString::removeWS(nombreElemento);
			  }
              
              elementoXMLabuscar=XMLString::transcode ("entradareposo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaReposo=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidareposo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaReposo=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("entradaactivacion");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaActivacion=XMLString::parseInt (valor_propiedad);
			  }
			  elementoXMLabuscar=XMLString::transcode ("salidaactivacion");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaActivacion=XMLString::parseInt (valor_propiedad);
			  }
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }
}

/*Metodos getter del Reed*/
float Reed::getEntradaReposo()
{
	return entradaReposo;
}
float Reed::getSalidaReposo()
{
	return salidaReposo;
}
float Reed::getEntradaActivacion()
{
	return entradaActivacion;
}
float Reed::getSalidaActivacion()
{
	return salidaActivacion;
}

Pulsador::Pulsador()
{
	inicializar();
	entradaReposo		=	entradaActivacion	=	VALOR_INICIAL;
	salidaReposo		=	salidaActivacion	=	VALOR_INICIAL;
}

float Pulsador::getEntradaReposo()
{
	return entradaReposo;
}

float Pulsador::getSalidaReposo()
{
	return salidaReposo;
}

float Pulsador::getEntradaActivacion()
{
	return entradaActivacion;
}

float Pulsador::getSalidaActivacion()
{
	return salidaActivacion;
}

void Pulsador::construir (DOMNode *nodo) {
    DOMNode *propiedad 				;
    const XMLCh *nombre_propiedad 	;
    const XMLCh *valor_propiedad 	;
    XMLCh*		elementoXMLabuscar	;
    
    DOMNode *hijo=nodo->getFirstChild () ;
    /*Recorremos las propiedades del Reed*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad= hijo->getNodeName() ;
              valor_propiedad=  hijo->getTextContent() ;
              
              elementoXMLabuscar=XMLString::transcode ("nombreelemento");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					nombreElemento=XMLString::replicate (valor_propiedad);
					XMLString::removeWS(nombreElemento);
			  }
              
              elementoXMLabuscar=XMLString::transcode ("entradaactivacion");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaActivacion=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("entradareposo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaReposo=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidareposo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaReposo=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidaactivacion");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaActivacion=XMLString::parseInt (valor_propiedad);
			  }
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }                   
}
void Pulsador::setEntrada(float entrada)
{
	Elemento::setEntrada(entrada);
	if (entradaActual==entradaReposo)
	{
		notificar();
	}
	if (entradaActual==entradaActivacion)
	{
		notificar();
	}
}
/*Definicion de la implementacion de FotoSensor*/
FotoSensor::FotoSensor()
{
	inicializar();
	entradaReposo		=	entradaActivacion	=	VALOR_INICIAL;
	salidaReposo		=	salidaActivacion	=	VALOR_INICIAL;
}

void FotoSensor::construir (DOMNode* nodo) {
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    XMLCh* elementoXMLabuscar;
    /*Recorremos las propiedades del Reed*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad=hijo->getNodeName()  ;
              valor_propiedad= hijo->getTextContent();
              elementoXMLabuscar=XMLString::transcode ("nombreelemento");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					nombreElemento=XMLString::replicate (valor_propiedad);
					XMLString::removeWS(nombreElemento);
			  }
              
              elementoXMLabuscar=XMLString::transcode ("entradaactivacion");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaActivacion=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("entradareposo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaReposo=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidareposo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaReposo=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidaactivacion");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaActivacion=XMLString::parseInt (valor_propiedad);
			  }
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }                   
}

float FotoSensor::getEntradaReposo()
{
	return entradaReposo;
}

float FotoSensor::getSalidaReposo()
{
	return salidaReposo;
}

float FotoSensor::getEntradaActivacion()
{
	return entradaActivacion;
}

float FotoSensor::getSalidaActivacion()
{
	return salidaActivacion;
}

Electroiman::Electroiman (){
	inicializar();
	entradaReposo	=	salidaReposo	=	VALOR_INICIAL;
	salidaActivacion=	salidaActivacion=	VALOR_INICIAL;
}
void Electroiman::construir (DOMNode* nodo) {
	DOMNode *hijo=nodo->getFirstChild () ;
    DOMNode *propiedad ;
    const XMLCh *nombre_propiedad ;
    const XMLCh *valor_propiedad ;
    XMLCh*		elementoXMLabuscar;
    /*Recorremos las propiedades del Reed*/
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad= hijo->getNodeName();
              valor_propiedad= hijo->getTextContent() ;
              
              elementoXMLabuscar=XMLString::transcode ("nombreelemento");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					nombreElemento=XMLString::replicate (valor_propiedad);
					XMLString::removeWS(nombreElemento);
			  }
			  elementoXMLabuscar=XMLString::transcode ("entradaactivacion");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaActivacion=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("entradareposo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaReposo=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidareposo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaReposo=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidaactivacion");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaActivacion=XMLString::parseInt (valor_propiedad);
			  }
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }                   	
}

/*Metodos getter de Electroiman*/
float Electroiman::getEntradaReposo()
{
	return entradaReposo;
}
float Electroiman::getEntradaActivacion()
{
	return entradaActivacion;
}
float Electroiman::getSalidaReposo()
{
	return salidaReposo;
}
float Electroiman::getSalidaActivacion()
{
	return salidaActivacion;
}


Lampara::Lampara()
{
	inicializar();
	entradaReposo	=	entradaActivacion	=	VALOR_INICIAL;
	salidaReposo	=	salidaActivacion	=	VALOR_INICIAL;
}

void Lampara::construir (DOMNode* nodo) {
    DOMNode*		propiedad ;
    const XMLCh*	nombre_propiedad ;
    const XMLCh*	valor_propiedad ;
    const XMLCh*	elementoXMLabuscar;
    /*Recorremos las propiedades del Reed*/
    
    DOMNode* hijo=nodo->getFirstChild () ;
    while (hijo!=NULL)
     {
           if (hijo->getNodeType()==DOMNode::ELEMENT_NODE){
              /*Recogemos datos...*/
              nombre_propiedad=hijo->getNodeName()  ;
              valor_propiedad= hijo->getTextContent();
			  elementoXMLabuscar=XMLString::transcode ("nombreelemento");

			  /*... y aqui se extraen los valores almacenados en el XML*/
			  if (  iguales (nombre_propiedad, elementoXMLabuscar ) ){
					nombreElemento= XMLString::replicate (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("color");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					color=XMLString::replicate (valor_propiedad);
					XMLString::removeWS(color);
			  }
			  elementoXMLabuscar=XMLString::transcode ("entradaactivacion");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaActivacion=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("entradareposo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaReposo=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidareposo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaReposo=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidaactivacion");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaActivacion=XMLString::parseInt (valor_propiedad);
			  }
			}
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     } 
}

/*Metodos getter de Lampara*/
float Lampara::getEntradaReposo()
{
	return entradaReposo;
}
float Lampara::getEntradaActivacion()
{
	return entradaActivacion;
}
float Lampara::getSalidaReposo()
{
	return salidaReposo;
}
float Lampara::getSalidaActivacion()
{
	return salidaActivacion;
}
XMLCh* Lampara::getColor()
{
	return color;
}

Motor::Motor()
{
	inicializar();
	entradaGiro1	=	entradaGiro2	=	entradaReposo	=	VALOR_INICIAL;
	salidaGiro1		=	salidaGiro2		=	salidaReposo	=	NULL;
}

/*	El destructor de la clase Motor debe liberar
	las cadenas que fueron asignadas directamente por Xerces*/
Motor::~Motor()
{
	XMLString::release	(&salidaGiro1);
	XMLString::release	(&salidaGiro2);
	XMLString::release	(&salidaReposo);
}
void Motor::construir (DOMNode* nodo) {
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
              elementoXMLabuscar=XMLString::transcode ("nombreelemento");
              /*... y aqui e extraen los valores almacenados en el XML*/
			  if (  iguales (nombre_propiedad, elementoXMLabuscar ) ){
					nombreElemento= XMLString::replicate (valor_propiedad);
					XMLString::removeWS(nombreElemento);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("entradagiro1");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaGiro1=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidagiro1");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaGiro1=XMLString::replicate (valor_propiedad);
					XMLString::removeWS(salidaGiro1);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("entradagiro2");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaGiro2=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidagiro2");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaGiro2=XMLString::replicate (valor_propiedad);
					XMLString::removeWS(salidaGiro2);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("entradareposo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					entradaReposo=XMLString::parseInt (valor_propiedad);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("salidareposo");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
					salidaReposo=XMLString::replicate (valor_propiedad);
					XMLString::removeWS (salidaReposo);
			  }
           }
           
           /*Se pasa al siguiente nodo XML hermano*/
           hijo=hijo->getNextSibling();
     }                   
}

float Motor::getEntradaGiro1 () const 
{
	return entradaGiro1;	
}
float Motor::getEntradaGiro2 () const 
{
	return entradaGiro2;	
}
float Motor::getEntradaReposo () const 
{
	return entradaReposo;	
}

XMLCh* Motor::getSalidaGiro1 () const
{
	return salidaGiro1;
}
XMLCh* Motor::getSalidaGiro2 () const
{
	return salidaGiro2;
}
XMLCh* Motor::getSalidaReposo() const
{
	return salidaReposo;
}

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
			if (XMLString::equals(nombrePrimario, nombreElementoActual))
			{
				cout << "Encontrado el primario" << endl;
				primario=listaComponentes[i];
			}
			
			if (XMLString::equals(nombreSecundario, nombreElementoActual))
			{
				cout << "encontrado el secundario" << endl;
				secundario=listaComponentes[i];
			}
		}
		/*	... y si los dos elementos existen se "encadenan"*/
		if ( (primario!=NULL) && (secundario!=NULL) )
		{
			cout << "Anadiendo suscriptor" << endl;
			primario->anadirSuscriptor(secundario);
			cout << "Suscriptor anadido"<< endl;
			listaRelaciones[numRelaciones++]=relacion;
			cout << "Relacion anadida" << endl;
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
			  if (  iguales (nombre_propiedad, elementoXMLabuscar ) ){
					nombrePrimario= XMLString::replicate (valor_propiedad);
					XMLString::removeWS(nombrePrimario);
			  }
			  
			  elementoXMLabuscar=XMLString::transcode ("secundario");
			  if ( iguales (nombre_propiedad, elementoXMLabuscar ) ){
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
