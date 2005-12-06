#include "unit++.h"
#include "pulsador.h"
#include "lampara.h"
#include "elemento.h"
#include "biestable.h"
#include "constantes.h"


using namespace unitpp;

namespace
{
	class PruebaConexiones: public suite
	{
		void PruebaPulsadorLampara()
		{
			/*	Creamos un pulsador que si no esta activado emite 0.0V
				y que si esta activado emite 5.0V */
			Conexion* c1=new Conexion (CONEXION_INACTIVA);	
			Conexion* c2=new Conexion (CONEXION_ACTIVA);
			Voltaje*  v1=new Voltaje  (0.0);
			Voltaje*  v2=new Voltaje  (5.0);
			
			Pulsador* p1=new Pulsador (c1,v1,c2,v2);
			p1->setNombreElemento ("Pulsador1");
			/*	Creamos una lampara que cuando recibe 0.0V está en negro
				y cuando recibe 5.0V esta VERDE */
			
			Luminosidad* l1=new Luminosidad ("NEGRO");
			Luminosidad* l2=new Luminosidad ("VERDE");
			
			Lampara* lamp=new Lampara(v1,l1,v2,l2);
			lamp->setNombreElemento("Lampara1");
			/*	Hacemos que la lampara "escuche" al pulsador convirtiendose
				en suscriptor de dicho pulsador */
			
			int codigo_error=p1->anadirSuscriptor (lamp);
#ifdef DEBUG
			printf ("Al conectar la lampara al pulsador salio %i\n",
				codigo_error);
#endif			
			bool error_de_tipos=(codigo_error==TIPOS_NO_COINCIDEN);
			assert_eq ("Error de tipos", false, codigo_error);
			
			bool pos_entrada_invalida=(codigo_error==POS_ENTRADA_INVALIDA);
			assert_eq ("Fallo pos entrada", false, pos_entrada_invalida);
			
			bool pos_salida_invalida=(codigo_error==POS_SALIDA_INVALIDA);
			assert_eq ("Fallo pos salida", false, pos_salida_invalida);
			
			bool elem_invalido=(codigo_error==ELEMENTO_INVALIDO);
			assert_eq ("Elemento NULL", false, elem_invalido);
			
			int num_suscriptores=p1->getTotalSuscripciones();
			assert_eq ("Suscripcion realizada",1,num_suscriptores);
			
			/*	Ahora cambiamos la entrada en el pulsador y comprobamos
				si la lampara se enciende */
				
			p1->setEntrada(c2); /*c2 contiene la activacion*/
			
			Luminosidad *resultado= (Luminosidad* )lamp->getSalidaPorPosicion();
			int comparacion=strcmp("VERDE", resultado->getValor() );
			assert_eq ("Conexion correcta", 0, comparacion);
		}
		
		/*	En este ejemplo se conecta un pulsador p1 al Reset
			de un biestable b1, se conecta un pulsador p2 al Set
			del biestable b1. La salida Q del biestable se conecta 
			a una lampara por lo que al pulsar P2 se tiene que encender
			la lampara. La lampara debe seguir encendida al dejar de
			pulsar P2 y tiene que apagarse al pulsar P1. Aunque dejemos
			de pulsar P1 debe seguir apagada*/
		void PruebaPulsadorBiestableLampara()
		{
			/*	Creamos un pulsador p1 que si no esta activado emite 0.0V
				y que si esta activado emite 5.0V */
			Conexion* c1=new Conexion (CONEXION_INACTIVA);	
			Conexion* c2=new Conexion (CONEXION_ACTIVA);
			Voltaje*  v1=new Voltaje  (0.0);
			Voltaje*  v2=new Voltaje  (5.0);
			
			Pulsador* p1=new Pulsador (c1,v1,c2,v2);
			p1->setNombreElemento ("Pulsador1");
			
			/*	Creamos un pulsador p2 que si no esta activado emite 0.0V
				y que si esta activado emite 5.0V */
			Pulsador* p2=new Pulsador (c1,v1,c2,v2);
			p2->setNombreElemento ("Pulsador2");
			
			Voltaje*  activar1	=	new Voltaje (5.0);
			Voltaje*  desactivar1=	new Voltaje (0.0);
			Voltaje*  activar2	=	new Voltaje (5.0);
			Voltaje*  desactivar2=	new Voltaje (0.0);
			Voltaje*  activar3	=	new Voltaje (5.0);
			Voltaje*  desactivar3=	new Voltaje (0.0);
			Voltaje*  activar4	=	new Voltaje (5.0);
			Voltaje*  desactivar4=	new Voltaje (0.0);
			
			Biestable* b1=new Biestable(activar1, desactivar1, 
				activar2,desactivar2, activar3, desactivar3,
				activar4,desactivar4);
			b1->setNombreElemento ("Biestable1");
			
			/* 	El biestable tiene que convertirse en observador
				de P1 conectando la salida de P1 a la entrada R
				del biestable*/
			p1->anadirSuscriptor(b1,POS_ENTRADA,POS_SALIDA);
			
			/*	Igual con p2 pero conectando a S*/
			p2->anadirSuscriptor(b1, POS_ENTRADA+1,POS_SALIDA);
			
			/*	Se crea la lampara*/
			Luminosidad* l1=new Luminosidad ("NEGRO");
			Luminosidad* l2=new Luminosidad ("VERDE");
			
			Lampara* lamp=new Lampara(v1,l1,v2,l2);
			lamp->setNombreElemento("Lampara1");
			
			/*	Y la lampara se convierte en suscriptor del biestable*/
			b1->anadirSuscriptor(lamp);
			
			
			/*	Si pulsamos el pulsador p1 la lampara debe estar en negro*/
			Conexion *activa=new Conexion (CONEXION_ACTIVA);
			Conexion *inactiva=new Conexion (CONEXION_INACTIVA);
			p1->setEntrada(activa);
			Luminosidad* luzActual=(Luminosidad*) lamp->getSalidaPorPosicion();
			Luminosidad* luzReposo= lamp->getLuminosidadReposo();
			int comparacion=strcmp (luzReposo->getValor() , 
									luzActual->getValor() );
			assert_eq ("Lampara apagada con biestable", 0, comparacion);
			
			/* Soltamos p1 y la lampara debe seguir activada */
			p1->setEntrada(inactiva);
			luzActual=(Luminosidad*) lamp->getSalidaPorPosicion();
			luzReposo= lamp->getLuminosidadReposo();
			comparacion=strcmp (luzReposo->getValor() , 
									luzActual->getValor() );
			assert_eq ("Lampara sigue apagada con biestable", 0, comparacion);	
			
			/*	Si pulsamos p2 la lampara debe encenderse*/
			p2->setEntrada(activa);
			luzActual=(Luminosidad*) lamp->getSalidaPorPosicion();
			Luminosidad* luzActivacion=lamp->getLuminosidadActivacion();
			comparacion=strcmp (luzActivacion->getValor(), 
								luzActual->getValor() );
			assert_eq ("Lampara encendida con biestable", 0, comparacion);
			
			/*	Soltamos p2 y la lampara debe seguir encendida*/
			p2->setEntrada(inactiva);
			luzActual=(Luminosidad*) lamp->getSalidaPorPosicion();
			luzActivacion=lamp->getLuminosidadActivacion();
			comparacion=strcmp (luzActivacion->getValor(), 
								luzActual->getValor() );
			assert_eq ("Lampara sigue encendida con biestable", 0, comparacion);
			
		}
		public:
		PruebaConexiones(): suite ("Prueba de conexiones")
		{
			add ("Prueba Pulsador-Lampara", testcase 
			(this, "PruebaPulsadorLampara", 
			&PruebaConexiones::PruebaPulsadorLampara));
			add ("Prueba Pulsador-Biestable-Lampara", testcase 
			(this, "PruebaPulsadorBiestableLampara", 
			&PruebaConexiones::PruebaPulsadorBiestableLampara));
			suite::main().add("PruebaConexiones", this);	
		}
	};
	
	PruebaConexiones *conecta=new PruebaConexiones();	
}
