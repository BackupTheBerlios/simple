#include "unit++.h"
#include "fotosensor.h"
#include "lampara.h"

using namespace unitpp;

namespace
{
	class PruebaFotoSensor: public suite
	{
		void PruebaValoresFotoSensor()
		{
			Luminosidad* lReposo			=new Luminosidad ("OFF");
			Luminosidad* lActivacion		=new Luminosidad ("Magenta oscuro");
			Voltaje*	 vSalidaReposo		=new Voltaje (0.0);
			Voltaje*	 vSalidaActivacion	=new Voltaje (5.0);
			
			FotoSensor* fs=new FotoSensor (lReposo, lActivacion,
				vSalidaReposo, vSalidaActivacion);
			
			/*	Comprobamos si los valores que devuelve el fotosensor
				son los que introdojimos*/	
			Luminosidad* lReposoLeido=fs->getLuminosidadEntradaReposo();
			assert_eq ("Luminosidad en reposo", 
				lReposo->getValor(), lReposoLeido->getValor() );
			
			Luminosidad* lActivacionLeida=fs->getLuminosidadEntradaActivacion();
			assert_eq ("Lumiosidad en activacion",
				lActivacion->getValor(), lActivacionLeida->getValor() );
			
			Voltaje* vReposoLeido=fs->getVoltajeSalidaReposo();
			assert_eq ("Voltaje reposo", 
				vSalidaReposo->getValor(), vReposoLeido->getValor() );
			
			Voltaje* vActivacionLeido=fs->getVoltajeSalidaActivacion();
			assert_eq ("Voltaje activacion",
				vSalidaActivacion->getValor(), vActivacionLeido->getValor() );
			
		}
		void PruebaConLampara()
		{
			/* 	Creamos el fotosensor*/
			Luminosidad* lReposo			=new Luminosidad ("OFF");
			Luminosidad* lActivacion		=new Luminosidad ("Magenta");
			Voltaje*	 vSalidaReposo		=new Voltaje (0.0);
			Voltaje*	 vSalidaActivacion	=new Voltaje (5.0);
			
			FotoSensor* fs=new FotoSensor (lReposo, lActivacion,
				vSalidaReposo, vSalidaActivacion);
				
			/*	Creamos la Lampara*/
			Voltaje*	v1=new Voltaje (0.0);
			Voltaje*	v2=new Voltaje (5.0);
			Luminosidad*l1=new Luminosidad("OFF");
			Luminosidad*l2=new Luminosidad("Magenta");
			
			Lampara* lamp=new Lampara(v1,l1,v2,l2);
			
			/*	Hacemos que el fotosensor "atienda" a la lampara*/
			lamp->anadirSuscriptor (fs);
			
			/*	Encendemos la lampara introduciendo 5V*/
			lamp->setEntrada(v2);
			
			/*	Y el fotosensor deberia haberse activado y ser el 
				voltaje de activacion*/
			Voltaje *vDelFotoSensor=(Voltaje*) fs->getSalidaPorPosicion();
			bool esNulo=(vDelFotoSensor==NULL);
			assert_eq ("Voltaje leido", false, esNulo);
			assert_eq ("Fotosensor disparado por lampara",
				vSalidaActivacion->getValor(), vDelFotoSensor->getValor() );
			
		}
		void PruebaValoresPorDefecto()
		{
			Luminosidad* lReposo			=new Luminosidad ("OFF");
			Luminosidad* lActivacion		=new Luminosidad ("Magenta oscuro");
			Voltaje*	 vSalidaReposo		=new Voltaje (0.0);
			Voltaje*	 vSalidaActivacion	=new Voltaje (5.0);
			
			FotoSensor* fs=new FotoSensor (lReposo, lActivacion,
				vSalidaReposo, vSalidaActivacion);
				
			Luminosidad *l;
			l=(Luminosidad*) fs->getEntradaPorPosicion();
			int cod_comparacion=strcmp(lReposo->getValor(), l->getValor() );
			assert_eq ("Luminosidad por defecto del fotosensor", 
					0, cod_comparacion);
			
			Voltaje* v;
			v=(Voltaje*) fs->getSalidaPorPosicion();
			assert_eq ("Voltaje por defecto del fotosensor",
				v->getValor(), vSalidaReposo->getValor() );
				
		}
		void PruebaMetodosHeredados()
		{
			Luminosidad* lReposo			=new Luminosidad ("OFF");
			Luminosidad* lActivacion		=new Luminosidad ("Magenta oscuro");
			Voltaje*	 vSalidaReposo		=new Voltaje (0.0);
			Voltaje*	 vSalidaActivacion	=new Voltaje (5.0);
			
			FotoSensor* fs=new FotoSensor (lReposo, lActivacion,
				vSalidaReposo, vSalidaActivacion);
				
			int entradas	=	fs->getTotalEntradas();
			int salidas		=	fs->getTotalSalidas();
			
			assert_eq ("Total de entradas del elemento", 
				POS_ENTRADA+1, entradas);
			assert_eq ("Total de salidas del elemento",
				POS_SALIDA+1, salidas);
		}
		public:
			PruebaFotoSensor():suite ("Prueba Contador")
			{
				add ("Prueba valores del fotosensor", testcase (this,
					"Prueba valores del fotosensor", 
					&PruebaFotoSensor::PruebaValoresFotoSensor));
				add ("Prueba con Lampara", testcase (this,
					"Prueba con Lampara", 
					&PruebaFotoSensor::PruebaConLampara));
					add ("Prueba valores por defecto del fs", testcase (this,
					"Prueba valores por defecto en fotosensor", 
					&PruebaFotoSensor::PruebaValoresPorDefecto));
				add ("Prueba de los metodos heredados", testcase (this,
					"Prueba de metodos heredados", 
					&PruebaFotoSensor::PruebaMetodosHeredados));
				suite::main().add("Prueba Contador", this);
			}
		
	};
	
	PruebaFotoSensor* pfs=new PruebaFotoSensor();
}
