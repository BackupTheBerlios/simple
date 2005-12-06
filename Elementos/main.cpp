#include <cstdlib>
#include <iostream>
#include "sistema.h"
#include "pulsador.h"
#include "lampara.h"
#include "fotosensor.h"

using namespace std;
void PruebaSistemaSimple()
		{
			/*	Esto esta cortado y copiado de testconexiones.cpp*/
			
			
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
			
			/*	Hasta aqui llega el cortado y copiado, ahora estos 
				elementos se añaden al sistema*/
			Sistema* s=new Sistema();
			s->anadirElemento(p1);
			s->anadirElemento(lamp);
			printf ("Modificando pulsador1");			
			/*	Probamos a modificar la entrada del pulsador*/
			s->setEntrada(c2, "Pulsador1");
			printf ("Pulsador modificado\n");
			/*	Y ahora comprobamos si la entrada introducida a traves
				del sistema s ha modificado la lampara*/
			Luminosidad *resultado= (Luminosidad* )lamp->getSalidaPorPosicion();
			int comparacion=strcmp("VERDE", resultado->getValor() );
			/*assert_eq ("Conexion correcta del sistema (directa)",
				 0, comparacion);*/
			
			/*	Lo comprobamos tambien a traves del interfaz de
				la clase de sistema*/
			resultado= (Luminosidad* )s->getSalidaPorNombre("Lampara1");
			comparacion=strcmp("VERDE", resultado->getValor() );
			/*assert_eq ("Conexion correcta (por interfaz)",
				 0, comparacion);*/
			
			/*	Volvemos a "despulsar" y comprobamos si se pone en NEGRO*/
			s->setEntrada(c1, "Pulsador1");
			resultado=(Luminosidad*) lamp->getSalidaPorPosicion();
			comparacion=strcmp("NEGRO", resultado->getValor() );
			//assert_eq ("Conexion correcta", 0, comparacion);
			printf ("Vamos a modificar la entrada\n");
			/*	Repetimos la comprobacion a traves del interfaz de
				la clase sistema*/
			s->setEntrada(c2,"Pulsador1"); /* Pulsamos el boton*/
			resultado=(Luminosidad*)s->getSalidaPorNombre("Lampara1");
			comparacion=strcmp("VERDE", resultado->getValor() );
			/*assert_eq (
			"Conexion correcta a través del interfaz de la clase sistema", 
				0, comparacion);*/
		}
		
		/*	En este test se va a meter un sistema dentro de otro
			El sistema S1 contiene un pulsador conectado a una lampara
			El sistema S2 contiene un fotosensor
			El sistema Sgrande contendra a S1 y S2*/
		void PruebaSistemaRecursivo()
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
			
			p1->anadirSuscriptor(lamp);
			printf ("\n\n----Depurando el sistema recursivo\n\n\n");
			Sistema* S1=new Sistema();
			S1->setNombreElemento ("Sistema S1");
			S1->anadirElemento(p1);
			S1->anadirElemento(lamp);
			
			/*	Antes de hacer comprobaciones comprobamos cuantas
				entradas y salidas tiene el sistema S1. Hay 12 entradas
				debido a las 4 originales del sistema mas las 4 del
				pulsador mas las 4 de la lampara*/
			int totalEntradas=S1->getTotalEntradas();
			//assert_eq ("Entradas totales de S1", 12, totalEntradas);
			
			/* En total esta la salida del sistema mas las 2 de los elementos*/
			int totalSalidas=S1->getTotalSalidas();
			//assert_eq ("Salidas totales de S1", 3, totalSalidas);
			
			/*	Comprobamos las posiciones de las entradas de p1
				(que tiene 4 entradas (del 0 al 3) para POS_ENABLE,
				POS_KEEP, POS_RESET y entrada), sin embargo el sistema
				tiene las 4 primeras entradas para sus propias entradas
				asi que la primera debe ser 4*/
				
			int primeraEntradaDelPulsador=S1->getPrimeraEntrada("Pulsador1");
			//assert_eq ("Primera entrada P1", 4, primeraEntradaDelPulsador);
			
			/*	Las siguientes entradas seran de la 4 a 7*/
			int primeraEntradaDeLampara=S1->getPrimeraEntrada("Lampara1");
			//assert_eq ("Primera entrada L1", 8, primeraEntradaDeLampara);
			
			int primeraSalidaPulsador=S1->getPrimeraSalida("Pulsador1");
			//assert_eq ("Primera salida p1", 1, primeraSalidaPulsador);
			
			int primeraSalidaLampara=S1->getPrimeraSalida("Lampara1");
			//assert_eq ("Primera salida l1", 2, primeraSalidaLampara);
			
			/*	Ahora creamos un fotosensor sensible al verde */
			Luminosidad* lReposo			=new Luminosidad ("NEGRO");
			Luminosidad* lActivacion		=new Luminosidad ("VERDE");
			Voltaje*	 vSalidaReposo		=new Voltaje (0.0);
			Voltaje*	 vSalidaActivacion	=new Voltaje (5.0);
			FotoSensor* fs=new FotoSensor (lReposo, lActivacion,
				vSalidaReposo, vSalidaActivacion);
			fs->setNombreElemento ("FotoSensor1");
			Sistema *S2=new Sistema();
			S2->setNombreElemento ("Sistema S2");
			S2->anadirElemento(fs);
			
			/*	Ahora viene lo importante:
				Vamos a obtener la primera salida del sistema S1 que
				se refiera a Lampara1 y la vamos a conectar a la
				primera entrada del sistema S2 que se refiera al
				Fotosensor1. Asi podremos comprobar si podemos
				tratar los sistemas como cajas negras simplemente
				conectando las entradas a las salidas*/
			
			int posSalidaLampara     = S1->getPrimeraSalida("Lampara1");
			int posEntradaFotosensor = S2->getPrimeraEntrada ("FotoSensor1");
			
			#ifdef DEBUG_SISTEMA
			printf ("Salida lamp1 en S1:%i\tEntrada Fs1 en S2:%i\n",
				posSalidaLampara, posEntradaFotosensor);
			#endif
			
			/* 	La primera entrada de fotosensor es su RESET,siempre
				hay que sumar POSENTRADA!!*/
			S1->anadirSuscriptor(S2, POS_ENTRADA+posEntradaFotosensor, 
				posSalidaLampara);
			
			#ifdef DEBUG
			printf ("Sistema S2 es suscriptor de S1\n");
			#endif
			/*	Vamos a intentar modificar la entrada de S1 para activar
				el pulsador que lleva dentro*/
			
			int posEntradaPulsador = S1->getPrimeraEntrada ("Pulsador1");
			printf ("La primera entrada del pulsador es %i\n", posEntradaPulsador);
			/*	¿Si metemos un voltaje de 5V en esa entrada se activa el
				fotosensor que estaba en el sistema S2?*/
			Conexion *entrada=new Conexion(CONEXION_ACTIVA);
			S1->setEntrada(entrada,posEntradaPulsador+POS_ENTRADA);
			Luminosidad* resultado= 
				(Luminosidad* )S1->getSalidaPorNombre("Lampara1");
			printf ("La lampara tiene %s\n",resultado->toString() );
			int comparacion=strcmp("VERDE", resultado->getValor() );
			/*assert_eq ("Conexion correcta (por interfaz)",
				 0, comparacion);*/
			
			#ifdef DEBUG_SISTEMA
			printf ("\n\n----Prueba refinitiva---\n\n");
			#endif
			int posSalidaFotoSensor=S2->getPrimeraSalida ("FotoSensor1");
			printf ("En S2 el fotoSensor1 tiene la salida %i\n",
						posSalidaFotoSensor);
			
			/*Otra comprobacion rutinaria*/
			Voltaje* prueba=(Voltaje*)fs->getSalidaPorPosicion();
			printf ("El voltaje obtenido es %f\n",prueba->getValor());
			Voltaje *salidaFotoSensor=(Voltaje*) S2->getSalidaPorPosicion(
											posSalidaFotoSensor);
			bool esVoltNulo=(salidaFotoSensor==NULL);
			printf ("El voltaje por posicion es %f\n",
				salidaFotoSensor->getValor() );
			//assert_eq ("Voltaje no localizado", false, esVoltNulo);
			/*assert_eq ("Voltaje de salida del fotosensor en S2",
				5.0, salidaFotoSensor->getValor() );*/
		}
int main(int argc, char *argv[])
{
    PruebaSistemaSimple();
    PruebaSistemaRecursivo();
}
