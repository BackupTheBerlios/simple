#include "unit++.h"
#include "sistema.h"
#include "pulsador.h"
#include "lampara.h"
#include "fotosensor.h"
#include "biestable.h"
#include "rele.h"

using namespace unitpp;

namespace
{
	class PruebaSistema: public suite
	{
		void PruebaSistemaSimple()
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
			
			/*	Hasta aqui llega el cortado y copiado, ahora estos 
				elementos se añaden al sistema*/
			Sistema* s=new Sistema();
			s->anadirElemento(p1);
			s->anadirElemento(lamp);
			/*	Probamos a modificar la entrada del pulsador*/
			s->setEntrada(c2, "Pulsador1");
			/*	Y ahora comprobamos si la entrada introducida a traves
				del sistema s ha modificado la lampara*/
			Luminosidad *resultado= (Luminosidad* )lamp->getSalidaPorPosicion();
			int comparacion=strcmp("VERDE", resultado->getValor() );
			assert_eq ("Conexion correcta del sistema (directa)",
				 0, comparacion);
			
			/*	Lo comprobamos tambien a traves del interfaz de
				la clase de sistema*/
			resultado= (Luminosidad* )s->getSalidaPorNombre("Lampara1");
			comparacion=strcmp("VERDE", resultado->getValor() );
			assert_eq ("Conexion correcta en S(por interfaz)",
				 0, comparacion);
			
			/*	Volvemos a "despulsar" y comprobamos si se pone en NEGRO*/
			s->setEntrada(c1, "Pulsador1");
			resultado=(Luminosidad*) lamp->getSalidaPorPosicion();
			comparacion=strcmp("NEGRO", resultado->getValor() );
			assert_eq ("Conexion correcta", 0, comparacion);
			/*	Repetimos la comprobacion a traves del interfaz de
				la clase sistema*/
			s->setEntrada(c2,"Pulsador1"); /* Pulsamos el boton*/
			resultado=(Luminosidad*)s->getSalidaPorNombre("Lampara1");
			comparacion=strcmp("VERDE", resultado->getValor() );
			assert_eq (
			"Conexion correcta a través del interfaz de la clase sistema", 
				0, comparacion);
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
			
			
			Sistema* S1=new Sistema();
			S1->setNombreElemento ("Sistema S1");
			S1->anadirElemento(p1);
			S1->anadirElemento(lamp);
			
			/*	Antes de hacer comprobaciones comprobamos cuantas
				entradas y salidas tiene el sistema S1. Hay 12 entradas
				debido a las 4 originales del sistema mas las 4 del
				pulsador mas las 4 de la lampara*/
			int totalEntradas=S1->getTotalEntradas();
			assert_eq ("Entradas totales de S1", 12, totalEntradas);
			
			/* En total esta la salida del sistema mas las 2 de los elementos*/
			int totalSalidas=S1->getTotalSalidas();
			assert_eq ("Salidas totales de S1", 3, totalSalidas);
			
			/*	Comprobamos las posiciones de las entradas de p1
				(que tiene 4 entradas (del 0 al 3) para POS_ENABLE,
				POS_KEEP, POS_RESET y entrada), sin embargo el sistema
				tiene las 4 primeras entradas para sus propias entradas
				asi que la primera debe ser 4*/
			int primeraEntradaDelPulsador=S1->getPrimeraEntradaUtil("Pulsador1");
			assert_eq ("Primera entrada P1", 7, primeraEntradaDelPulsador);
			/*	Las siguientes entradas seran de la 4 a 7*/
			int primeraEntradaDeLampara=S1->getPrimeraEntradaUtil
										("Lampara1");
			assert_eq ("Primera entrada L1", 11, primeraEntradaDeLampara);
			
			int primeraSalidaPulsador=S1->getPrimeraSalidaUtil("Pulsador1");
			assert_eq ("Primera salida p1", 1, primeraSalidaPulsador);
			
			int primeraSalidaLampara=S1->getPrimeraSalidaUtil("Lampara1");
			assert_eq ("Primera salida l1", 2, primeraSalidaLampara);
			/*	Ahora creamos un fotosensor sensible al verde */
			Luminosidad* lReposo			=new Luminosidad ("OFF");
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
			
			#ifdef DEBUG_SISTEMA
			printf ("La primera entrada del pulsador en el sistema es %i\n", 
					posEntradaPulsador);
			#endif
			
			/*	¿Si metemos un voltaje de 5V en esa entrada se activa el
				fotosensor que estaba en el sistema S2?*/
			Conexion *entrada=new Conexion(CONEXION_ACTIVA);
			S1->setEntrada(entrada,posEntradaPulsador+POS_ENTRADA);
			Luminosidad* resultado= 
				(Luminosidad* )S1->getSalidaPorNombre("Lampara1");
			
			#ifdef DEBUG_SISTEMA
			printf ("La lampara tiene %s\n",resultado->toString() );
			#endif
			
			int comparacion=strcmp("VERDE", resultado->getValor() );
			assert_eq ("Conexion correcta en el sistema S1(por interfaz)",
				 0, comparacion);
			
			#ifdef DEBUG_SISTEMA
			printf ("\n\n----Prueba refinitiva---\n\n");
			#endif
			
			int posSalidaFotoSensor=S2->getPrimeraSalida ("FotoSensor1");
			
			#ifdef DEBUG_SISTEMA
			printf ("En S2 el fotoSensor1 tiene la salida %i\n",
						posSalidaFotoSensor);
			#endif
			
			/*Otra comprobacion rutinaria*/
			Voltaje* prueba=(Voltaje*)fs->getSalidaPorPosicion();
			
			#ifdef DEBUG_SISTEMA
			printf ("El voltaje obtenido es %i\n",prueba->getValor());
			#endif
			
			Voltaje *salidaFotoSensor=(Voltaje*) S2->getSalidaPorPosicion(
											posSalidaFotoSensor);
			bool esVoltNulo=(salidaFotoSensor==NULL);
			assert_eq ("Voltaje no localizado", false, esVoltNulo);
			assert_eq ("Voltaje de salida del fotosensor en S2",
				5.0, salidaFotoSensor->getValor() );
			
			/*	Buscamos un elemento inexistente*/
			int posElemInexistente=S2->getPrimeraEntrada("Metallica");
			assert_eq ("Elemento inexistente", 
					ELEMENTO_NO_ENCONTRADO, posElemInexistente);
			
			posElemInexistente=S2->getPrimeraSalida("Master of Puppets");
			assert_eq ("Elemento inexistente", 
					ELEMENTO_NO_ENCONTRADO, posElemInexistente);
		}
		/*	En este metodo se conecta un biestable a un rele, el rele
			a un pulsador y el pulsador a una lampara. La salida de la 
			lampara debe ser correcta*/
			 
		void PruebaSistemaBiestable()
		{
			/* Se crea el biestable*/
			Voltaje*  activarR		=	new Voltaje (5.0);
			Voltaje*  desactivarR	=	new Voltaje (0.0);
			Voltaje*  activarS		=	new Voltaje (5.0);
			Voltaje*  desactivarS	=	new Voltaje (0.0);
			Voltaje*  activarQ		=	new Voltaje (5.0);
			Voltaje*  desactivarQ	=	new Voltaje (0.0);
			Voltaje*  activarQneg	=	new Voltaje (5.0);
			Voltaje*  desactivarQneg=	new Voltaje (0.0);
			Biestable* b=new Biestable(activarR, desactivarR, 
				activarS,desactivarS, activarQ, desactivarQ,
				activarQneg,desactivarQneg);
			b->setNombreElemento("Biestable1");
			
			/*Se crea el rele y se conecta al biestable*/
			Conexion* cRele1=new Conexion (CONEXION_INACTIVA);
			Conexion* cRele2=new Conexion (CONEXION_ACTIVA);
			Voltaje*  vRele1=new Voltaje  (0.0);
			Voltaje*  vRele2=new Voltaje  (5.0);
			Rele *r=new Rele (vRele1,cRele1,vRele2,cRele2);
			r->setNombreElemento("Rele1");
			b->anadirSuscriptor(r);
			
			/*Se crea el pulsador y se conecta al rele*/			
			Conexion* cPulsador1=new Conexion (CONEXION_INACTIVA);	
			Conexion* cPulsador2=new Conexion (CONEXION_ACTIVA);
			Voltaje*  vPulsador1=new Voltaje  (0.0);
			Voltaje*  vPulsador2=new Voltaje  (5.0);
			Pulsador* p1=new Pulsador 
					(cPulsador1,vPulsador1,cPulsador2,vPulsador2);
			p1->setNombreElemento ("Pulsador1");
			r->anadirSuscriptor(p1);
			
			/*Se crea la lampara y se conecta al pulsador*/
			Luminosidad* l1=new Luminosidad ("NEGRO");
			Luminosidad* l2=new Luminosidad ("VERDE");			
			Lampara* lamp=new Lampara(vPulsador1,l1,vPulsador2,l2);
			lamp->setNombreElemento("Lampara1");
			p1->anadirSuscriptor(lamp);
			
			/*La luminosidad inicial de la lampara debe ser NEGRO*/
			Luminosidad *lumLeidaLampara1=
				(Luminosidad*)lamp->getSalidaPorPosicion();
			int codComparacion=strcmp (lumLeidaLampara1->getValor(),"NEGRO");
			assert_eq ("Lampara inicializada", 0,codComparacion);
			
			/*Metemos 5V a la entrada set*/
			Voltaje *voltajeActivoEnBiestable=new Voltaje (5.0);
			b->setSet(voltajeActivoEnBiestable);
			
			/*La lampara deberia haber cambiado*/
			lumLeidaLampara1=(Luminosidad*)lamp->getSalidaPorPosicion();
			codComparacion=strcmp (lumLeidaLampara1->getValor(),"VERDE");
			assert_eq ("Lampara activada", 0,codComparacion);
			
			/*	Dejamos todo como estaba*/
			Voltaje* voltajeInactivoEnBiestable=new Voltaje(0.0);
			b->setSet(voltajeInactivoEnBiestable);
			
			/*	El primer reseteo es para resetear Q y el segundo
				es para dejar las entradas R y S del biestable al estado
				anterior*/
			b->setReset (voltajeActivoEnBiestable);
			b->setReset (voltajeInactivoEnBiestable);
			
			/*	La lampara deberia volver a estar en NEGRO*/
			lumLeidaLampara1=(Luminosidad*)lamp->getSalidaPorPosicion();
			codComparacion=strcmp (lumLeidaLampara1->getValor(),"NEGRO");
			assert_eq ("Lampara desactivada", 0,codComparacion);

			/*	Metemos todos los elementos al sistema y tratamos
				de manipular el sistema completo*/
			Sistema *s=new Sistema();
			s->anadirElemento(b);
			s->anadirElemento(r);
			s->anadirElemento(p1);
			s->anadirElemento(lamp);
			s->setNombreElemento("Sistema Biest.");
			int totalEntradasDelSistema=s->getTotalEntradas();
			int totalSalidasDelSistema= s->getTotalSalidas();
			
			/*	Debe haber 17 entradas de los 4 elementos (5 entradas
				del biestable + (4 elementos iguales*4entradas) mas las 4
				entradas del sistema */
			assert_eq ("Entradas del sistema", 21, totalEntradasDelSistema);
			/*	Debe haber 6 salidas. La del sistema mas 
				4 salidas de 4 elementos+1 extra del biestable*/
			assert_eq ("Salidas del sistema s", 6, totalSalidasDelSistema);
			
			int posRdelBiestableEnElSistema=s->getPrimeraEntrada("Biestable1");
			bool esCero=(posRdelBiestableEnElSistema==0);
			assert_eq ("No encontrado", esCero, false);
			
			
			/*	Metemos un voltaje activo en la posicion siguiente que
				el la S del biestable. Le sumamos POS_ENTRADA porque
				el biestable tambien tiene RESET, KEEP, etc...*/
			s->setEntrada	( voltajeActivoEnBiestable,
							POS_ENTRADA+posRdelBiestableEnElSistema+1);
			
			/*Comprobamos la lampara a mano*/
			lumLeidaLampara1=(Luminosidad*)lamp->getSalidaPorPosicion();
			codComparacion=strcmp (lumLeidaLampara1->getValor(),"VERDE");
			assert_eq ("Lampara activada", 0,codComparacion);
			
			/* Comprobamos las entradas utiles*/
			int entradaUtilBiestable	=	
						s->getPrimeraEntradaUtil ("Biestable1");
			assert_eq ("Entrada util biestable", 7, entradaUtilBiestable);
			
			int entradaUtilRele			=
						s->getPrimeraEntradaUtil ("Rele1");
			assert_eq ("Entrada util del rele", 12, entradaUtilRele);
			
			int entradaUtilPulsador		=
						s->getPrimeraEntradaUtil("Pulsador1");
			assert_eq ("Entrada util del pulsador", 16, entradaUtilPulsador);
			
			int entradaUtilLampara		=
						s->getPrimeraEntradaUtil("Lampara1");
			assert_eq ("Entrada util de la lampara", 20, entradaUtilLampara);
			
			/*	Comprobamos la salida de la lampara a traves del sistema*/
			int salidaUtilLampara=s->getPrimeraSalidaUtil("Lampara1");
			Luminosidad *l=(Luminosidad*) 
							s->getSalidaPorPosicion(salidaUtilLampara);
			codComparacion=strcmp (lumLeidaLampara1->getValor(),"VERDE");
			assert_eq ("Nueva prueba de la lampara",
				 0,codComparacion);
			
			/*	Dejamos todo como estaba*/
			/*	Metemos un 0 en S...*/
			s->setEntrada	( voltajeInactivoEnBiestable,
							POS_ENTRADA+posRdelBiestableEnElSistema+1);
			/*	...metemos un 1 en R para resetear...*/
			s->setEntrada	( voltajeActivoEnBiestable,
							POS_ENTRADA+posRdelBiestableEnElSistema);
			/* ...metemos un 0 en R para volver al estado inicial...*/
			s->setEntrada	( voltajeInactivoEnBiestable,
							POS_ENTRADA+posRdelBiestableEnElSistema);
			/*... y en este punto esta todo reinicializado*/
			
			/* Vuelvo a comprobar que la lampara esta en negro*/
			salidaUtilLampara=s->getPrimeraSalidaUtil("Lampara1");
			l=(Luminosidad*) s->getSalidaPorPosicion(salidaUtilLampara);
			codComparacion=strcmp (l->getValor(),"NEGRO");
			assert_eq ("Comprobacion de reinicializacion",
				 0,codComparacion);
				 
				 			
			/*	Rizamos el rizo: Creamos un foto-sensor que vaya
				conectado a la salida "Lampara1" del sistema s*/
			Luminosidad* lReposo			=new Luminosidad ("NEGRO");
			Luminosidad* lActivacion		=new Luminosidad ("VERDE");
			Voltaje*	 vSalidaReposo		=new Voltaje (0.0);
			Voltaje*	 vSalidaActivacion	=new Voltaje (5.0);
			FotoSensor* fs=new FotoSensor (lReposo, lActivacion,
				vSalidaReposo, vSalidaActivacion);
			fs->setNombreElemento ("FotoSensor1");
			
			s->anadirSuscriptor(fs, POS_ENTRADA, salidaUtilLampara);
			
			
			/* Al meter un 1 en S...*/
			s->setEntrada	( voltajeActivoEnBiestable,
							entradaUtilBiestable+1);
							
			
			/*	...la salida de lampara 1 deberia estar activa...*/
			salidaUtilLampara=s->getPrimeraSalidaUtil("Lampara1");
			l=(Luminosidad*) s->getSalidaPorPosicion(salidaUtilLampara);
			codComparacion=strcmp (lumLeidaLampara1->getValor(),"VERDE");
			assert_eq ("Lampara activada y leida a traves de S",
				 0,codComparacion);
			
			/*	Y el fotosensor deberia estar activo*/
			Voltaje* vDelFotoSensor=(Voltaje*)fs->getSalidaPorPosicion();
			assert_eq ("Voltaje del fotosensor conectado al sistema",
				5.0, vDelFotoSensor->getValor() );
		}
		/*	En este metodo creamos un fotosensor que irá dentro de su
			propio sistema S2. En el sistema S1 metemos un biestable
			con una lampara y el sistema S2 se suscribe a la salida de la
			lampara. S1 y S2 se meten en un solo sistema grande Sgrande
			a traves del cual interactuaremos*/
		void PruebaSistemaCompuesto()
		{
			/* Se crea el biestable*/
			Voltaje*  activarR		=	new Voltaje (5.0);
			Voltaje*  desactivarR	=	new Voltaje (0.0);
			Voltaje*  activarS		=	new Voltaje (5.0);
			Voltaje*  desactivarS	=	new Voltaje (0.0);
			Voltaje*  activarQ		=	new Voltaje (5.0);
			Voltaje*  desactivarQ	=	new Voltaje (0.0);
			Voltaje*  activarQneg	=	new Voltaje (5.0);
			Voltaje*  desactivarQneg=	new Voltaje (0.0);
			Biestable* b=new Biestable(activarR, desactivarR, 
				activarS,desactivarS, activarQ, desactivarQ,
				activarQneg,desactivarQneg);
			b->setNombreElemento("Biestable1");
			
			/*...y se crea la lampara...*/
			Luminosidad* l1		=	new Luminosidad ("NEGRO");
			Luminosidad* l2		=	new Luminosidad ("VERDE");
			Voltaje* vReposo	=	new Voltaje(0.0);
			Voltaje *vActivar	=	new Voltaje (5.0);			
			Lampara* lamp		=	new Lampara(vReposo,l1,vActivar,l2);
			lamp->setNombreElemento("Lampara1");
			
			/*	Se conecta la lampara al biestable y se meten ambos
				en el sistema S1*/
			
			b->anadirSuscriptor(lamp);
			
			Sistema *S1=new Sistema();
			S1->anadirElemento(b);
			S1->anadirElemento(lamp);
			S1->setNombreElemento ("Sistema 1");
			
			/*	Creamos un fotosensor	*/
			Luminosidad* lReposo			=new Luminosidad ("NEGRO");
			Luminosidad* lActivacion		=new Luminosidad ("VERDE");
			Voltaje*	 vSalidaReposo		=new Voltaje (0.0);
			Voltaje*	 vSalidaActivacion	=new Voltaje (5.0);
			FotoSensor* fs=new FotoSensor (lReposo, lActivacion,
				vSalidaReposo, vSalidaActivacion);
			fs->setNombreElemento ("FotoSensor1");
			
			/*	Y creamos el sistema que lo incluye */
			Sistema *S2=new Sistema();
			S2->anadirElemento(fs);
			S2->setNombreElemento("Sistema2");
			
			/*	Conectamos S2 a S1 de la salida de lampara a entrada
				del fotosensor...*/
			
			/*	...obteniendo una referencia a la entrada del biestable en S1*/
			int posSalidaLampara=S1->getPrimeraSalidaUtil("Lampara1");
			
			/*	...obteniendo una referencia a la salida del fotosensor*/
			int posEntradaFotoSensor=S2->getPrimeraEntradaUtil("FotoSensor1");

			/*	... y ahora sí, realizamos la conexion*/
			S1->anadirSuscriptor(S2, posEntradaFotoSensor, posSalidaLampara);
			
			
			/*Creamos el sistema grande que incluye a ambos*/
			Sistema *SGrande=new Sistema();
			SGrande->anadirElemento(S1);
			SGrande->anadirElemento(S2);
			SGrande->setNombreElemento("Sistema grande");
			/*	Obtenemos una referencia a la entrada del biestable en S1*/
			int posUtilBiestable=S1->getPrimeraEntradaUtil("Biestable1");
			
			/*	Obtenemos una referencia a la salida del fotosensor*/
			int salidaUtilFotoSensor=S2->getPrimeraSalidaUtil("FotoSensor1");
			/*	Ponemos un 5V en la entrada+1 (que es la entrada S)*/
			Voltaje *activarBiestable=new Voltaje(5.0);
			S1->setEntrada(activarBiestable, posUtilBiestable+1);
			/*	Y el fotosensor deberia estar activo*/
			Voltaje* vDelFotoSensor=(Voltaje*)fs->getSalidaPorPosicion();
			assert_eq ("Voltaje en retrocomposicion",
				5.0, vDelFotoSensor->getValor() );
			
			/*	Ahora interactuamos a traves de SGrande*/
			posUtilBiestable	=SGrande->getPrimeraEntradaUtil("Biestable1");
			salidaUtilFotoSensor=SGrande->getPrimeraSalidaUtil("FotoSensor1");
			int entradaUtilFotoS=SGrande->getPrimeraEntradaUtil("FotoSensor1");
			
			SGrande->eliminarElemento(S1);
		}
		void PruebaSistemaImbuido()
		{
			Sistema* vectorSistemas[10];
			Luminosidad* l1		=	new Luminosidad ("NEGRO");
			Luminosidad* l2		=	new Luminosidad ("VERDE");
			Voltaje* vReposo	=	new Voltaje(0.0);
			Voltaje *vActivar	=	new Voltaje (5.0);			
			Lampara* lamp		=	new Lampara(vReposo,l1,vActivar,l2);
			lamp->setNombreElemento("Lampara1");
			
			vectorSistemas[0]=new Sistema();
			vectorSistemas[0]->anadirElemento(lamp);
			
			for (int i=1;i<10;i++)
			{
				vectorSistemas[i]=new Sistema();
				vectorSistemas[i]->anadirElemento(vectorSistemas[i-1]);
			}
			
			Sistema* sGrande=vectorSistemas[9];
			sGrande->setNombreElemento ("Sistema grande");
			int posEntradaLampara=sGrande->getPrimeraEntradaUtil("Lampara1");
			
			bool lampEncontrada=(posEntradaLampara!=ELEMENTO_NO_ENCONTRADO);
			
			assert_eq ("Se encontro la lampara en la multiple recursion",
				true, lampEncontrada);
			
			posEntradaLampara=vectorSistemas[0]->getPrimeraEntradaUtil
										("Lampara1");
			assert_eq ("Pos Lamp en sistema multiple recursivo",
				7, posEntradaLampara);
			
			posEntradaLampara=vectorSistemas[1]->getPrimeraEntradaUtil
										("Lampara1");
			assert_eq ("Pos Lamp en sistema multiple recursivo",
				11, posEntradaLampara);
			
			posEntradaLampara=sGrande->getPrimeraEntradaUtil("Lampara1");
			assert_eq ("SGrande encuentra lamp1", 43, posEntradaLampara);
			
			int posSalidaUtilLampara=vectorSistemas[0]->getPrimeraSalidaUtil 
											("Lampara1");
			assert_eq ("Sgrande encuentra salida lamp", 
					1, posSalidaUtilLampara);

			posSalidaUtilLampara=vectorSistemas[1]->getPrimeraSalidaUtil 
											("Lampara1");
			assert_eq ("Sgrande encuentra salida lamp", 
					2, posSalidaUtilLampara);
					
			posSalidaUtilLampara=sGrande->getPrimeraSalidaUtil 
											("Lampara1");
			assert_eq ("Sgrande encuentra salida lamp", 
					10, posSalidaUtilLampara);
		}				
			
		public:
			PruebaSistema(): suite ("Prueba del sistema")
			{
				add ("Prueba pulsaciones", testcase (this, 
					"Pruebapulsacion", &PruebaSistema::PruebaSistemaSimple));
				add ("Prueba de un sistema compuesto", testcase (this, 
					"PruebaSistemaRecursivo",
					 &PruebaSistema::PruebaSistemaRecursivo));
				add ("Prueba sistema con biestable", testcase (this, 
					"PruebaSistemaConBiestable",
					 &PruebaSistema::PruebaSistemaBiestable));
				add ("Prueba sistema retrocompuesto", testcase (this, 
					"PruebaSistemaConBiestable",
					 &PruebaSistema::PruebaSistemaCompuesto));
				add ("Prueba recursion multiple", testcase (this, 
					"PruebaSistemaImbuido",
					 &PruebaSistema::PruebaSistemaImbuido));
				suite::main().add ("PruebaSistema", this);
			}
	};
	
	PruebaSistema* pps=new PruebaSistema();	
}
