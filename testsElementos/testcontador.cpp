#include "unit++.h"
#include "contador.h"
#include "biestable.h"

using namespace unitpp;

namespace
{
	class PruebaContador: public suite
	{
		void PruebaValoresContador()
		{
			Voltaje *v1=new Voltaje(0.0);
			Voltaje *v2=new Voltaje(5.0);
			int numPulsos=3;
			Contador *c=new Contador(numPulsos, v1,v2,v1,v2);
			bool noesNuloC=(c==NULL);
			assert_eq ("Contador construido", false, noesNuloC);
			
			int n=c->getNumPulsos();
			assert_eq ("Pulsos 0", 0 , n);
			
			Voltaje* ventradareposo=c->getVoltajeEntradaReposo();
			assert_eq ("V entrada reposo", 0.0, ventradareposo->getValor() );
			
			Voltaje* ventradactivacion=c->getVoltajeEntradaActivacion();
			assert_eq ("V entrada activacion", 
				5.0, ventradactivacion->getValor() );
				
			Voltaje* vsalidareposo=c->getVoltajeSalidaReposo();
			assert_eq ("V salida reposo", 
				0.0, vsalidareposo->getValor() );
			
			Voltaje* vsalidaactivacion=c->getVoltajeSalidaActivacion();
			assert_eq ("V salida activacion", 
				5.0, vsalidaactivacion->getValor() );
		}
		void PruebaCuentaEnContador()
		{
			Voltaje *v1=new Voltaje(0.0);
			Voltaje *v2=new Voltaje(5.0);
			int numPulsos=3;
			Contador *c=new Contador(numPulsos, v1,v2,v1,v2);
			
			/*	Probamos a hacer tres cambios de flanco*/
			
			for (int i=1;i<=numPulsos;i++)
			{
				c->setEntrada(v1); /*Flanco bajo...*/
				c->setEntrada(v2); /*...seguido de flanco alto*/
			}
			
			/*	En este punto deberia haberse activado la salida del contador*/
			
			Voltaje* salidaContador=(Voltaje*)c->getSalidaPorPosicion();
			assert_eq("Salida del contador tras 3 pulsos...",
				v2->getValor(), salidaContador->getValor() );
		}
		
		/*	Comprueba si el contador conectado a un biestable hace
			que el biestable se active. Solamente por aumentar
			las comprobaciones usamos valores distintos de V (3.2)*/
		void PruebaContadorBiestable()
		{
			/*	Creamos el contador */
			Voltaje *v1=new Voltaje(0.0);
			Voltaje *v2=new Voltaje(3.2);
			int numPulsos=3;
			Contador *c=new Contador(numPulsos, v1,v2,v1,v2);
			
			/*	Creamos el biestable*/
			Voltaje*  activar1	=	new Voltaje (3.2);
			Voltaje*  desactivar1=	new Voltaje (0.0);
			Voltaje*  activar2	=	new Voltaje (3.2);
			Voltaje*  desactivar2=	new Voltaje (0.0);
			Voltaje*  activar3	=	new Voltaje (3.2);
			Voltaje*  desactivar3=	new Voltaje (0.0);
			Voltaje*  activar4	=	new Voltaje (3.2);
			Voltaje*  desactivar4=	new Voltaje (0.0);
			
			Biestable* b=new Biestable(activar1, desactivar1, 
				activar2,desactivar2, activar3, desactivar3,
				activar4,desactivar4);
				
			/*	Hacemos que el biestable conecte su entrada S al contador*/
			c->anadirSuscriptor(b,POS_ENTRADA+1);

			/*	Comprobamos si la suscripcion se hizo correctamente*/
			int numSuscripciones=c->getTotalSuscripciones();
			assert_eq ("Suscripciones al biestable", 
				1, numSuscripciones);
				
			/*	La salida Q del biestable debe ser 0 al principio*/
			Voltaje *salidaQ=(Voltaje*) b->getSalidaPorPosicion();
			assert_eq ("Q=0 antes de contar", 
				0.0, salidaQ->getValor() );			
				
			/*	Probamos a hacer los cambios de flanco*/
			for (int i=1;i<=numPulsos;i++)
			{
				c->setEntrada(v1); /*Flanco bajo...*/
				c->setEntrada(v2); /*...seguido de flanco alto*/
			}
			
			/*	En este punto deberia haberse activado la salida del biestable*/
			
			Voltaje* salidaBiestable=(Voltaje*)b->getSalidaPorPosicion();
			assert_eq("Salida del contador tras 3 pulsos...",
				activar3->getValor(), salidaBiestable->getValor() );
		}
		public:
			PruebaContador():suite ("Prueba Contador")
			{
				add ("Prueba valores del contador", testcase (this,
					"Prueba val. contador", 
					&PruebaContador::PruebaValoresContador));
				add ("Prueba cuenta del contador", testcase (this,
					"Prueba cuenta del contador",
					 &PruebaContador::PruebaCuentaEnContador));
				add ("Prueba contador-biestable", testcase (this,
					"Prueba contador-biestable",
					 &PruebaContador::PruebaContadorBiestable));
				suite::main().add("Prueba Contador", this);
			}
		
	};
	
	PruebaContador* asdcc=new PruebaContador();
}
