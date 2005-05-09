#include <cstdlib>
#include <iostream>
#include <string>

#include "parser.h"
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
		
		//En general se tienen que hacer las pruebas en este orden
		void pruebaFicheroTest()
		{
			p=new Parser();
			//El fichero test.xml está "diseñado" para ser valido
			//Cualquier error de parser tiene que saltar aqui
			assert_eq ("Fichero de test", true, p->esValido("test.xml") );
			
		}
		void pruebaRecuperaElementos()
		{
			v=p->extraerElementos();
			assert_eq ("Vector vacio?", false, v.empty() );
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
		void pruebaRelacion ()
		{
			vector <Relacion*> v;
			v=p->extraerRelaciones();
			/*	El vector no puede estar vacío. En el fichero de test hay
				exactamente una relacion*/
			assert_eq ("Vector de relaciones", false, v.empty());
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
			add ("Comprobacion de la extraccion de relaciones", testcase
				(this, "Relacion 1", &pruebaParser::pruebaRelacion));
			suite::main().add ("pruebaFicheroTest", this);
				
		}
	}; // Fin de la clase
	
	pruebaParser *laPruebaDelParser=new pruebaParser();
}
