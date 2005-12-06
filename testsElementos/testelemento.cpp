#include "unit++.h"
#include "elemento.h"
#include "constantes.h"
#include "biestable.h"
#include "lampara.h"
#include "zumbador.h"

using namespace unitpp;

namespace {
	class PruebaElemento : public suite 
	{
		void pruebaNombre()
		{
			Elemento *e=new Elemento();
			char nombreEscrito[]="Elemento de prueba";
			const char* nombreDevuelto;
			e->setNombreElemento (nombreEscrito);
			nombreDevuelto=e->getNombreElemento();
			int codigo_string=strcmp (nombreEscrito, nombreDevuelto);
			
			assert_eq ("pruebaNombre", codigo_string, 0);
#ifdef DEBUG
			printf ("Intentando pasar un NULL a Elemento::setNombreElemento\n");
#endif
			e->setNombreElemento(NULL);
#ifdef DEBUG
			printf ("NULL pasado a Elemento::setNombre sin consecuencias\n");
#endif
			delete e;
		}
		void pruebaConstruccion()
		{
			Elemento* e=new Elemento();
			int numEntradas, numSalidas, numSuscripciones;
			
			numEntradas		= e->getTotalEntradas();
			numSalidas 		= e->getTotalSalidas();
			numSuscripciones= e->getTotalSuscripciones();
			
			assert_eq ("pruebaConstruccion::TotalEntradas", 
				numEntradas, POS_ENTRADA+1);
			assert_eq ("pruebaConstruccion::TotalSalidas",  
				POS_SALIDA+1,  numSalidas);
			assert_eq ("pruebaConstruccion::Suscriptores",  numSuscripciones,0);
			#ifdef DEBUG
			printf ("pruebaConstruccion en testElemento pasado\n");
			#endif
			delete e;	
		}
		void pruebaAnadirSuscripcion()
		{
			Elemento *e1=new Elemento();
			Elemento *e2=new Elemento();
			int total_suscripciones=0;
			
			#ifdef DEBUG
			printf ("Ejecutando prueba anadirSuscriptor\n");
			#endif
			e1->anadirSuscriptor(e2);
			#ifdef DEBUG
			printf ("Suscriptor añadido\n");
			#endif
			total_suscripciones=e1->getTotalSuscripciones();
			assert_eq ("pruebaAnadirSuscripcion", 1, total_suscripciones);
			
			total_suscripciones=e2->getTotalSuscripciones();
			assert_eq ("pruebaAnadirSuscripcion", 0, total_suscripciones);
			delete e2;
			delete e1;
			#ifdef DEBUG
			printf ("pruebaAnadir en testElemento pasado\n");
			#endif
		}
		
		void busquedaPorNombre()
		{
			Elemento* e=new Elemento();
			e->setNombreElemento("Elemento vacio");
			int posEntrada;
			
			/*	Buscamos con el nombre correcto */
			posEntrada=e->getPrimeraEntradaUtil("Elemento vacio");
			assert_eq ("Prueba metodo virtual de busqueda de entr. por nombre",
				POS_ENTRADA, posEntrada);
			
			int posSalida;
			posSalida=e->getPrimeraSalidaUtil("Elemento vacio");
			assert_eq("Prueba metodo virtual de busqueda de salida. por nombre",
				POS_SALIDA, posSalida);
			
			/*	Buscamos con nombre incorrectos*/
			posEntrada=e->getPrimeraEntradaUtil("SDWEDE");
			assert_eq ("Prueba metodo virtual de busqueda de entr. por nombre",
				ELEMENTO_NO_ENCONTRADO, posEntrada);
			
			posSalida=e->getPrimeraSalidaUtil("Angus Young & AC-DC");
			assert_eq("Prueba metodo virtual de busqueda de salida. por nombre",
				ELEMENTO_NO_ENCONTRADO, posSalida);
		}
		
		void pruebaBorradoSuscripcion()
		{
			/* Se crea un zumbador*/
			Voltaje 	*vReposo	=	new Voltaje(0.0);
			Frecuencia	*fReposo	=	new Frecuencia (0);
			Voltaje		*vActivacion=	new Voltaje (5.0);
			Frecuencia	*fActivacion=	new	Frecuencia (3000);

			Zumbador *z=new Zumbador (vReposo, fReposo, 
				vActivacion, fActivacion);
			
			/*	Se crea una lampara*/
			Voltaje*	v1=new Voltaje (0.0);
			Voltaje*	v2=new Voltaje (5.0);
			Luminosidad*l1=new Luminosidad("OFF");
			Luminosidad*l2=new Luminosidad("Rojo");
			
			Lampara* lamp=new Lampara(v1,l1,v2,l2);
			
			/*Se crea un biestable*/
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
				
			/*	Se "conecta" el biestable a la lampara*/
			int codigoError=b->anadirSuscriptor(lamp);
			assert_eq ("Error al conectar b->lamp", 0, codigoError);
			
			b->setSet (activar1);
			l1=(Luminosidad*)lamp->getSalidaPorPosicion();
			int codComparacion=strcmp ("Rojo", l1->getValor() );
			assert_eq ("La lampara esta encendida en b->lamp",0, codComparacion);
			b->setSet(desactivar1);

			/*	Probamos el borrado*/
			codigoError=b->eliminarSuscriptor(lamp);
			assert_eq ("Error al eliminar suscriptor", SUSCRIPCION_BORRADA,
				codigoError);
				
			/*Probamos a resetear el biestable...*/
			b->setReset(activar1);
			l1=(Luminosidad*)lamp->getSalidaPorPosicion();
			
			/*	Y comprobamos que la lampara sigue encendida*/
			codComparacion=strcmp ("Rojo", l1->getValor() );
			assert_eq ("La lampara sigue encendida en b->lamp",0, codComparacion);
			
		}
		public:
			PruebaElemento() : suite ("PruebaElemento")
			{
				add ("pruebaNombre", testcase (this, 
					"pruebaNombre", &PruebaElemento::pruebaNombre));
				add ("pruebaConstruccion", testcase (this, 
					"pruebaConstruccion", &PruebaElemento::pruebaConstruccion));
				add ("pruebaAnadirSuscripcion", 
					testcase (this, "pruebaAnadirSuscripcion", 
					&PruebaElemento::pruebaAnadirSuscripcion));
				add ("pruebaBusquedaPorNombre", 
					testcase (this, "Busqueda por nombre (metodo virtual)", 
					&PruebaElemento::busquedaPorNombre));
					
				add ("pruebaBusquedaPorNombre", 
					testcase (this, "Busqueda por nombre (metodo virtual)", 
					&PruebaElemento::pruebaBorradoSuscripcion));
				suite::main().add("PruebaElemento",this);	
			}
	}; /*Fin de la clase PruebaElemento*/
	
	PruebaElemento *p=new PruebaElemento();
}
