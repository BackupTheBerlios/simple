#include <cstdlib>
#include <iostream>
#include <string>

#include "elementos.h"
#include "parser.h"
#include "elementos.h"
#include <unit++.h>	

using namespace std;
using namespace unitpp;

//Todas las pruebas est�n situadas en un espacio
//de nombre an�nimo y totalmente aparte
namespace {
	class pruebaParser : public suite
	{
		Parser* p;
		vector <Elemento*> v;
		
		//En general se tienen que hacer las pruebas en este orden
		void pruebaFicheroTest()
		{
			p=new Parser();
			//El fichero test.xml est� "dise�ado" para ser valido
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
			vector<Elemento*>::iterator i;
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
			Motor* m=(Motor*) v.at(0);
			entradaGiro1	=	m->getEntradaGiro1();
			entradaGiro2	=	m->getEntradaGiro2();
			entradaReposo	=	m->getEntradaReposo();

			/*Y comparamos los valores leidos con los esperados*/
			assert_eq ("Entradagiro1",9 , entradaGiro1 );
			assert_eq ("Entradagiro2",-9 , entradaGiro2 );
			assert_eq ("Entradagiro1",0 , entradaReposo );
			/*Hay que comparar si es true la comparacion de cadenas
			  y no comprobar la igualdad de punteros (nunca ser�n iguales)*/
			assert_eq ("Salidagiro1",true, 
				XMLString::equals(salidaGiro1, m->getSalidaGiro1()) );
			assert_eq ("Salidagiro2", true, 
				XMLString::equals (salidaGiro2, m->getSalidaGiro2()) );
			assert_eq ("Salidareposo", true, 
				XMLString::equals (salidaReposo,m->getSalidaReposo()) );
			
			XMLString::release (&cadena);
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
			suite::main().add ("pruebaFicheroTest", this);
				
		}
	}; // Fin de la clase
	
	pruebaParser *laPruebaDelParser=new pruebaParser();
}
