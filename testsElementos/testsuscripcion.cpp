#include <cstdlib>
#include <iostream>

/* Hay que incluir todas las cabeceras de los objetos y funciones que usemos*/
#include "unit++.h"
#include "elemento.h"


/*	Aqui se hacen las pruebas de unidad de los elementos
	
	Solo es necesario linkar con la libreria unit.a
	
	Todas las clases deben ir en un namespace anonimo y no hace falta
	poner una funcion main, es añadida automaticamente por la libreria */
using namespace std;
using namespace unitpp;

namespace {
	class PruebaSuscripcion : public suite
	{
		void SuscriptorNULL()
		{
			Suscripcion s;
			int codigo_error;
			
			codigo_error=s.setElementoSuscriptor (NULL);
			assert_eq ("Suscriptor NULL en Suscripcion",codigo_error,-1);
		}
		
		void AvisadorNULL ()
		{
			Suscripcion s;
			int codigo_error;
			
			codigo_error=s.setElementoAvisador (NULL);
			assert_eq ("Avisador NULL en Suscripcion", codigo_error,-1);
		}
		void entradaInvalida()
		{
			Suscripcion s;
			int codigo_error;
			codigo_error=s.setEntradaSuscriptor(0);
			assert_eq ("Entrada 0", codigo_error, 0);
			
			codigo_error=s.setEntradaSuscriptor(400);
			assert_eq ("Entrada grande", codigo_error, -1);
		}
		void salidaInvalida()
		{
			Suscripcion s;
			int codigo_error;
			
			codigo_error=s.setSalidaAvisador(0);
			assert_eq ("Salida 0", codigo_error, 0);
			
			codigo_error=s.setSalidaAvisador(300);
			assert_eq ("Salida grande", codigo_error,-1);
		}
		public:
			PruebaSuscripcion() : suite ("Prueba de las suscripciones")
			{
				add ("Suscriptor NULL", testcase
					(this, "SuscriptorNULL", &PruebaSuscripcion::SuscriptorNULL));
				add ("Avisador NULL", testcase
					(this, "AvisadorNULL", &PruebaSuscripcion::AvisadorNULL));
				add ("entradaInvalida", testcase
					(this, "entradaInvalida", &PruebaSuscripcion::entradaInvalida));
				add ("salidaInvalida", testcase
					(this, "salidaInvalida", &PruebaSuscripcion::salidaInvalida));
				suite::main().add ("PruebaSuscripcion", this);
			}
	}; /* Fin de la suite que prueba las suscripciones*/
	
	PruebaSuscripcion* p= new PruebaSuscripcion();
	
} /*Fin del espacio de nombre anonimo */
