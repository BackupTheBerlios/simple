#include "unit++.h"
#include "biestable.h"
#include "pulsador.h"
#include "lampara.h"
#include "sistema.h"

using namespace unitpp;

namespace
{
	class PruebaEliminacion: public suite
	{
		/*	Funcion que crea un pulsador y nos los devuelve*/
		Pulsador* getPulsador()
		{
			Conexion* c1=new Conexion (CONEXION_INACTIVA);
			Conexion* c2=new Conexion (CONEXION_ACTIVA);
			Voltaje*  v1=new Voltaje  (0.0);
			Voltaje*  v2=new Voltaje  (5.0);
			
			Pulsador* p=new Pulsador(c1,v1,c2,v2);
			
			return p;
		}
		
		/*	Crea y nos devuelve un biestable*/
		Biestable* getBiestable()
		{
			Voltaje*  activar1	=	new Voltaje (5.0);
			Voltaje*  desactivar1=	new Voltaje (0.0);
			Voltaje*  activar2	=	new Voltaje (5.0);
			Voltaje*  desactivar2=	new Voltaje (0.0);
			Voltaje*  activar3	=	new Voltaje (5.0);
			Voltaje*  desactivar3=	new Voltaje (0.0);
			Voltaje*  activar4	=	new Voltaje (5.0);
			Voltaje*  desactivar4=	new Voltaje (0.0);
			
			Biestable* b=new Biestable(activar1, desactivar1, 
				activar2,desactivar2, activar3, desactivar3,
				activar4,desactivar4);
			
			return b;
		}
		Lampara* getLampara()
		{
			Voltaje*	v1=new Voltaje (0.0);
			Voltaje*	v2=new Voltaje (5.0);
			Luminosidad*l1=new Luminosidad("OFF");
			Luminosidad*l2=new Luminosidad("Rojo");
			
			Lampara* lamp=new Lampara(v1,l1,v2,l2);
			
			return lamp;
		}
		
		void pruebaEliminarSimple()
		{
			/*	Se crean los elementos del sistema*/
			Pulsador*	pulsador1;
			Pulsador*	pulsador2;
			Biestable* 	biestable1;
			Lampara* 	lampara1;
			
			pulsador1	=	getPulsador();
			pulsador2	=	getPulsador();
			biestable1	=	getBiestable();
			lampara1	=	getLampara();

			pulsador1->setNombreElemento ( "Pulsador1" );			
			pulsador2->setNombreElemento ( "Pul2" );
			biestable1->setNombreElemento ( "Biestable1" );
			lampara1->setNombreElemento ( "Lampara1" );
			
			/*pulsador1 va conectado a reset*/
			pulsador1->anadirSuscriptor(biestable1);
			
			/*pulsador2 va conectado a set y a la lampara*/
			pulsador2->anadirSuscriptor(biestable1,POS_ENTRADA+1);
			pulsador2->anadirSuscriptor (lampara1);
			/*Biestable va conectado a lampara*/
			biestable1->anadirSuscriptor(lampara1);
			
			/*	Creamos el sistema y añadimos los elementos*/
			Sistema* sistema=new Sistema();
			sistema->setNombreElemento ("Sistema para eliminar cosas");
			sistema->anadirElemento ( pulsador1 );
			sistema->anadirElemento ( biestable1 );
			sistema->anadirElemento ( pulsador2 );
			sistema->anadirElemento ( lampara1 );
			
			/*	Comprobamos algunas posiciones de entrada y de salida
				de algunos elementos. Mas tarde comprobaremos si 
				las entradas y salidas son correctas*/
			int e1Pulsador=sistema->getPrimeraEntrada ( "Pulsador1" );
			assert_eq ("Eliminando: Pos ent. Pulsador1", 4, e1Pulsador );
			int s1Pulsador=sistema->getPrimeraSalida( "Pulsador1" );
			assert_eq ("Eliminando: Pos sal. Pulsador1", 1, s1Pulsador );
			
			int e1Lampara=sistema->getPrimeraEntrada("Lampara1");
			assert_eq ("Eliminando: Pos ent. lampara", 17, e1Lampara );
			int s1Lampara=sistema->getPrimeraSalida ( "Lampara1" );
			assert_eq ("Eliminando: Pos sal. lampara", 5, s1Lampara );
			
			int e1Biestable=sistema->getPrimeraEntrada ( "Biestable1" );
			assert_eq ("Eliminando: Pos ent. biestable1", 8, e1Biestable );
			int s1Biestable=sistema->getPrimeraSalida ( "Biestable1" );
			assert_eq ("Eliminando: Pos sal. biestable", 2, s1Biestable );
			
			/*Probamos a eliminar biestable1*/
			sistema->eliminarElemento ( biestable1 );
			
			/*	Y comprobamos que los elementos se han desplazado*/
			
			e1Lampara=sistema->getPrimeraEntrada("Lampara1");
			assert_eq ("Eliminando: Pos ent. lampara", 12, e1Lampara );
			s1Lampara=sistema->getPrimeraSalida ( "Lampara1" );
			assert_eq ("Eliminando: Pos sal. lampara", 3, s1Lampara );
			
			/*	Probamos a pulsar pulsador2. Lampara deberia encenderse*/
			int e2Pulsador=sistema->getPrimeraEntradaUtil ( "Pul2" );
			Conexion* encender=new Conexion (CONEXION_ACTIVA);
			sistema->setEntrada(encender,e2Pulsador);
			
			s1Lampara=sistema->getPrimeraSalidaUtil ( "Lampara1" );
			Luminosidad* luz=(Luminosidad*)
				sistema->getSalidaPorNombre("Lampara1");
			int comparacion=strcmp ("Rojo", luz->getValor() );
			assert_eq ("Lampara encendida (despues de eliminar)", 
							0, comparacion);
			
		}
		public:
			PruebaEliminacion():suite ("Prueba Contador")
			{
				add ("Prueba ejemplo eliminacion", testcase (this,
					"Prueba ejemplo eliminacion",
					 &PruebaEliminacion::pruebaEliminarSimple));
				suite::main().add("Prueba eliminacion", this);
			}
		
	};
	
	PruebaEliminacion* eliminar=new PruebaEliminacion();
}
