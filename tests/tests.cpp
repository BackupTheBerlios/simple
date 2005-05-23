#include <cstdlib>
#include <iostream>
#include <string>

#include "parser.h"
#include "sistema.h"
#include <unit++.h>	

using namespace std;
using namespace unitpp;

//Todas las pruebas están situadas en un espacio
//de nombre anónimo y totalmente aparte
namespace {
	class pruebaParser : public suite
	{
		Parser* p;
		vector <Elemento*> v;
		vector <Relacion*> r;
		Sistema* s;
		//En general se tienen que hacer las pruebas en este orden
		void pruebaFicheroTest()
		{
			p=new Parser();
			s=new Sistema();
			//El fichero test.xml está "diseñado" para ser valido
			//Cualquier error de parser tiene que saltar aqui
			assert_eq ("Fichero de test", true, p->esValido("test.xml") );
			
		}
		void pruebaRecuperaElementos()
		{
			v=p->extraerElementos();
			assert_eq ("Vector vacio?", false, v.empty() );
			assert_eq ("Tamano 8?", 8, v.size() );
		}
		void pruebaMotor()
		{
			XMLCh* 	cadena;
			float 	entradaGiro1,	entradaGiro2, 	entradaReposo;
			XMLCh*	salidaGiro1;
			XMLCh* 	salidaGiro2;
			XMLCh*	salidaReposo;
			/*Codificamos los valores esperados*/
			cadena=			XMLString::transcode ("motor1");
			salidaGiro1=	XMLString::transcode ("cw");
			salidaGiro2=	XMLString::transcode ("ccw");
			salidaReposo=	XMLString::transcode ("stop");

			//Recuperamos los valores leidos
			Motor* m=(Motor*) v.at(5);
			entradaGiro1	=	m->getEntradaGiro1();
			entradaGiro2	=	m->getEntradaGiro2();
			entradaReposo	=	m->getEntradaReposo();

			/*Y comparamos los valores leidos con los esperados*/
			assert_eq ("Entradagiro1",9 , entradaGiro1 );
			assert_eq ("Entradagiro2",-9 , entradaGiro2 );
			assert_eq ("Entradagiro1",0 , entradaReposo );
			/*Hay que comparar si es true la comparacion de cadenas
			  y no comprobar la igualdad de punteros (nunca serán iguales)*/
			assert_eq ("Salidagiro1",true, 
				XMLString::equals(salidaGiro1, m->getSalidaGiro1()) );
			assert_eq ("Salidagiro2", true, 
				XMLString::equals (salidaGiro2, m->getSalidaGiro2()) );
			assert_eq ("Salidareposo", true, 
				XMLString::equals (salidaReposo,m->getSalidaReposo()) );
			
			XMLString::release (&cadena);
		}
		
		void pruebaLampara()
		{
			XMLCh*	color;
			
			Lampara* l= (Lampara*) v.at(3);
			color=XMLString::transcode ("ffaadd");
			
			assert_eq ("Entradaactivacion",	0,l->getEntradaActivacion());
			assert_eq ("Entradareposo",		9,l->getEntradaReposo());
			assert_eq ("Salidaactivacion",	0,l->getSalidaActivacion());
			assert_eq ("Salidareposo",		1,l->getSalidaReposo());
			assert_eq ("Color ffaadd",		true,
				XMLString::equals (color, l->getColor()));
			
		}
		
		void pruebaReed()
		{
			XMLCh*	nombre;
			
			Reed* r=(Reed*) v.at (1);
			
			nombre=XMLString::transcode ("reed2");
			
			assert_eq ("Entradareposo",		0,r->getEntradaReposo		()	);
			assert_eq ("Salidareposo",		4,r->getSalidaReposo		()	);
			assert_eq ("Entradaactivacion",	1,r->getEntradaActivacion	()	);
			assert_eq ("Salidaactivacion",	0,r->getSalidaActivacion	()	);
			assert_eq ("Nombre",			true,
				XMLString::equals (nombre,r->getNombreElemento()));
		}
		void pruebaPulsador()
		{
			XMLCh*	nombre;
			
			Pulsador* p=(Pulsador*) v.at (0);
			
			nombre=XMLString::transcode ("Pulsador1");
			
			assert_eq ("Entradareposo",		0,p->getEntradaReposo		()	);
			assert_eq ("Salidareposo",		0,p->getSalidaReposo		()	);
			assert_eq ("Entradaactivacion",	1,p->getEntradaActivacion	()	);
			assert_eq ("Salidaactivacion",	9,p->getSalidaActivacion	()	);
			assert_eq ("Nombre",			true,
				XMLString::equals (nombre,p->getNombreElemento()));
		}
		
		void pruebaElectroiman()
		{
			XMLCh*	nombre;
			
			Electroiman* e=(Electroiman*) v.at (4);
			
			nombre=XMLString::transcode ("electroiman2");
			
			assert_eq ("Entradareposo",		9,e->getEntradaReposo		()	);
			assert_eq ("Salidareposo",		1,e->getSalidaReposo		()	);
			assert_eq ("Entradaactivacion",	0,e->getEntradaActivacion	()	);
			assert_eq ("Salidaactivacion",	0,e->getSalidaActivacion	()	);
			assert_eq ("Nombre",			true,
				XMLString::equals (nombre,e->getNombreElemento()));
		}
		
		void pruebaFotoSensor()
		{
			XMLCh*	nombre;
			
			FotoSensor* f=(FotoSensor*) v.at (2);
			
			nombre=XMLString::transcode ("fotosensor1");
			
			assert_eq ("Entradareposo",		0,f->getEntradaReposo		()	);
			assert_eq ("Salidareposo",		9,f->getSalidaReposo		()	);
			assert_eq ("Entradaactivacion",	1,f->getEntradaActivacion	()	);
			assert_eq ("Salidaactivacion",	9,f->getSalidaActivacion	()	);
			assert_eq ("Nombre",			true,
				XMLString::equals (nombre,f->getNombreElemento()));
		}
		void pruebaZumbador()
		{
			XMLCh*	nombre;
			
			Zumbador* z=(Zumbador*) v.at (7);
			
			nombre=XMLString::transcode ("ZumbadorA");
			
			assert_eq ("Entradareposo",		0,z->getEntradaReposo		()	);
			assert_eq ("Salidareposo",		0,z->getSalidaReposo		()	);
			assert_eq ("Entradaactivacion",	9,z->getEntradaActivacion	()	);
			assert_eq ("Salidaactivacion",	4000,z->getSalidaActivacion	()	);
			assert_eq ("Nombre",			true,
				XMLString::equals (nombre,z->getNombreElemento()));
		}
		void pruebaRelacion ()
		{
			r=p->extraerRelaciones();
			/*	El vector no puede estar vacío. En el fichero de test hay
				exactamente una relacion*/
			assert_eq ("Vector de relaciones", false, r.empty());
		}
		void pruebaInsertaRelaciones()
		{
			assert_eq ("Relaciones inexistentes", 2, r.size());
			for (int i=0;i<r.size();i++)
			{
				assert_eq ("Insercion de r", 
					0, s->anadirRelacion( (Relacion*) r.at(i)) );
			}
		}
		
		void pruebaInsertaComponentes()
		{
			for (int i=0;i<v.size();i++)
			{
				assert_eq ("Insercion de v",
					0, s->anadirComponente ( (Elemento*) v.at(i) ));
			}			
		}
		void pruebaListaComponentes()
		{
			Elemento* vectorComponentes[20];
			int numComponentes;
			numComponentes=s->getComponentes(vectorComponentes);
			assert_eq ("numComponentes", 8, numComponentes);
		}
		
		void pruebaListaRelaciones()
		{
			Relacion* vectorRelaciones[40];
			int numRelaciones;
			numRelaciones=s->getRelaciones (vectorRelaciones);
			assert_eq ("numRelaciones", 2, numRelaciones);
		}
		
		void pruebaRefElemento ()
		{
			Elemento *e,*f;
			bool esNulo;
			e=s->getRefElemento("asdasdasd");
			f=NULL;
			assert_eq ("getRefElemento NULL", f,e );
			
			e=s->getRefElemento ("Pulsador1");
			esNulo=(e==NULL);
			assert_eq ("getRefElemento valido", false, esNulo );
			
			e=s->getRefElemento ("reed2");
			esNulo=(e==NULL);
			assert_eq ("getRefElemento valido para reed2",false, esNulo);
			
			e=s->getRefElemento ("ZumbadorA");
			esNulo=(e==NULL);
			assert_eq ("getRefElemento valido para ZumbadorA",false, esNulo);
		}
		void pruebaRelacionConNotificacion()
		{
			Pulsador *p;
			Lampara *l;
			p=(Pulsador*) s->getRefElemento("Pulsador1");
			l=(Lampara*)  s->getRefElemento("lampara3");
			
			assert_eq ("Pulsador no nulo", 	false, 	(p==NULL) );
			assert_eq ("Lampara no nula", 	false, 	(l==NULL) );
			
			/*	Al activar el pulsador se APAGA la lampara
				Así es como está definido en el fichero*/
			p->setEntrada(1);
			
			assert_eq ("Salida de la lampara", 1, l->getSalida() );
			
			/*	Obtenemos un puntero a la otra lampara y comprobamos
				que tambien ha sido activada y que hay un uno a su salida
				Recordemos que en principio las lamparas se crean
				con una salida 0 (no activada) */
			l=(Lampara*) s->getRefElemento ("Lampara1");
			assert_eq ("Lampara1 encendida?", 1, l->getSalida() );
			
		}
		
		void pruebaDevolucionNodoElectroiman()
		{
			Elemento* 		e;
			Electroiman* 	iman;
			bool 			esRefNula;
			DOMElement*		elementoElectroiman;
			e=s->getRefElemento ("electroiman2");
			esRefNula=(e==NULL);
			assert_eq ("Electroiman nulo?", false, esRefNula);
			iman=(Electroiman*) e;
			elementoElectroiman=iman->getNodo();
			esRefNula=(elementoElectroiman==NULL);
			assert_eq ("¿DOMElement electroiman2?", false, esRefNula);
		}
		
		void pruebaDevolucionNodoLampara()
		{
			Elemento* 		e;
			Lampara*		lampara;
			bool 			esRefNula;
			DOMElement*		elementoLampara;
			e=s->getRefElemento ("lampara3");
			esRefNula=(e==NULL);
			assert_eq ("Lampara nula?", false, esRefNula);
			lampara=(Lampara*) e;
			elementoLampara=lampara->getNodo();
			esRefNula=(elementoLampara==NULL);
			assert_eq ("¿DOMElement lampara3?", false, esRefNula);
		}
		
		void pruebaDevolucionNodoFotoSensor()
		{
			Elemento* 		e;
			FotoSensor*		f;
			bool 			esRefNula;
			DOMElement*		elementoFotoSensor;
			e=s->getRefElemento ("fotosensor1");
			esRefNula=(e==NULL);
			assert_eq ("FotoSensor nulo?", false, esRefNula);
			f=(FotoSensor*) e;
			elementoFotoSensor=f->getNodo();
			esRefNula=(elementoFotoSensor==NULL);
			assert_eq ("¿DOMElement lampara3?", false, esRefNula);
		}
		
		void pruebaDevolucionNodoReed()
		{
			Elemento* 		e;
			Reed*			r;
			bool 			esRefNula;
			DOMElement*		elementoReed;
			e=s->getRefElemento ("reed2");
			esRefNula=(e==NULL);
			assert_eq ("Reed nulo?", false, esRefNula);
			r=(Reed*) e;
			elementoReed=r->getNodo();
			esRefNula=(elementoReed==NULL);
			assert_eq ("¿DOMElement lampara3?", false, esRefNula);
		}
		
		
		
		void pruebaDevolucionNodoPulsador()
		{
			Elemento* 		e;
			Pulsador*		p;
			bool 			esRefNula;
			DOMElement*		elementoPulsador;
			
			e=s->getRefElemento ("Pulsador1");
			esRefNula=(e==NULL);
			assert_eq ("FotoSensor nulo?", false, esRefNula);
			p=(Pulsador*) e;
			elementoPulsador=p->getNodo();
			esRefNula=(elementoPulsador==NULL);
			assert_eq ("¿DOMElement lampara3?", false, esRefNula);
		}
		
		void pruebaDevolucionNodoZumbador()
		{
			Elemento* 		e;
			Zumbador*		z;
			bool 			esRefNula;
			DOMElement*		elementoZumbador;
			
			e=s->getRefElemento ("ZumbadorA");
			esRefNula=(e==NULL);
			assert_eq ("Zumbador nulo?", false, esRefNula);
			z=(Zumbador*) z;
			elementoZumbador=z->getNodo();
			esRefNula=(elementoZumbador==NULL);
			assert_eq ("¿DOMElement lampara3?", false, esRefNula);
		}		
		
		void pruebaEscritura()
		{
			Elemento*	e;
			Pulsador*	pulsador1;
			
			e=s->getRefElemento("Pulsador1");
			
			pulsador1=(Pulsador*) e;
			DOMNode* nodo=pulsador1->getNodo();
			bool nulo=(nodo==NULL);
			assert_eq ("Nodo devuelto por pulsador 1 es nulo?",	
				false, nulo);
			//p->escribir (pulsador1->getNodo(), "puls.xml");
			
		}	
	public:
		pruebaParser() : suite ("Prueba de clase parser")
		{
			/*	Importante: se debe probar primero el fichero y luego
				la recuperacion de elementos */
			add ("Fichero de test", testcase 
				(this, "pruebaCreacion", &pruebaParser::pruebaFicheroTest));
			add ("Recuperacion de elementos", testcase 
				(this, "Recuperando elementos", &pruebaParser::pruebaRecuperaElementos));
			add ("Comprobacion de motor1", testcase 
				(this, "Motor1", &pruebaParser::pruebaMotor));
			add ("Comprobacion de lampara1", testcase
				(this, "Lampara1", &pruebaParser::pruebaLampara));
			add ("Comprobacion de reed2", testcase
				(this, "Reed2", &pruebaParser::pruebaReed));
			add ("Comprobacion de Pulsador1", testcase
				(this, "Pulsador1", &pruebaParser::pruebaPulsador));
			add ("Comprobacion de Electroiman", testcase
				(this, "Electroiman", &pruebaParser::pruebaElectroiman));
			add ("Comprobacion de FotoSensor", testcase
				(this, "FotoSensor1", &pruebaParser::pruebaFotoSensor));
			add ("Comprobacion de Zumbador", testcase
				(this, "ZumbadorA", &pruebaParser::pruebaZumbador));
			add ("Comprobacion de la extraccion de relaciones", testcase
				(this, "Relacion 1", &pruebaParser::pruebaRelacion));
			add ("Prueba insercion componentes", testcase
				(this, "Vector componentes", &pruebaParser::pruebaInsertaComponentes));
			add ("Prueba insercion relaciones", testcase
				(this, "Vector relaciones", &pruebaParser::pruebaInsertaRelaciones));
			add ("getListaComponentes", testcase
				(this, "Vector componentes", &pruebaParser::pruebaListaComponentes));
			add ("getListaRelaciones", testcase
				(this, "listaRelaciones", &pruebaParser::pruebaListaRelaciones));
			add ("getRefElemento", testcase
				(this, "Referencias a elementos", &pruebaParser::pruebaRefElemento));	
			add ("RelacionConNotificacion", testcase
				(this, "Notificador pulsador->lampara", &pruebaParser::pruebaRelacionConNotificacion));	
			add ("Devolucion de un nodo electroiman", testcase
				(this, "Electroiman devuelve DOMDocument?", &pruebaParser::pruebaDevolucionNodoElectroiman));	
			add ("Devolucion de un nodo lampara", testcase
				(this, "Lampara devuelve DOMDocument?", &pruebaParser::pruebaDevolucionNodoLampara));	
			add ("Devolucion de un nodo fotosensor", testcase
				(this, "FotoSensor devuelve DOMDocument?", &pruebaParser::pruebaDevolucionNodoFotoSensor));	
			add ("Devolucion de un nodo Pulsador", testcase
				(this, "Pulsador devuelve DOMDocument?", &pruebaParser::pruebaDevolucionNodoPulsador));					
			add ("Devolucion de un nodo Reed", testcase
				(this, "Reed devuelve DOMDocument?", &pruebaParser::pruebaDevolucionNodoReed));									
			add ("Devolucion de un nodo Zumbador", testcase
				(this, "Zumbador devuelve DOMDocument?", &pruebaParser::pruebaDevolucionNodoZumbador));
			add ("Escritura del pulsador", testcase
				(this, "¿Se escribe pulsador1?", &pruebaParser::pruebaEscritura));	
			suite::main().add ("pruebaFicheroTest", this);
				
		}
	}; // Fin de la clase
	
	pruebaParser *laPruebaDelParser=new pruebaParser();
}
