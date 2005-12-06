#include "unit++.h"
#include "electroiman.h"

using namespace unitpp;

namespace
{
	class PruebaElectroiman: public suite
	{
		void PruebaValores()
		{
			Voltaje* vReposo		=	new Voltaje (0.0);
			Voltaje* vActivacion	=	new Voltaje(5.0);
			Magnetismo* mReposo		=	new Magnetismo (false);
			Magnetismo* mActivacion	=	new Magnetismo (true);
			
			/*Creamos el electroiman*/
			Electroiman* e			=	new Electroiman(vReposo, vActivacion,
				mReposo, mActivacion);
				
			Voltaje* vReposoLeido= e->getVoltajeEntradaReposo();
			assert_eq ("Voltaje en reposo", 
				vReposo->getValor(), vReposoLeido->getValor() );
				
			Voltaje* vActivacionLeido= e->getVoltajeEntradaActivacion();
			assert_eq ("Voltaje de activacion", 
				vActivacion->getValor(), vActivacionLeido->getValor() );
				
			Magnetismo* mReposoLeido= e->getMagSalidaReposo();
			assert_eq ("Magnetismo en reposo", 
				mReposo->getValor(), mReposoLeido->getValor() );
			
			Magnetismo* mActivacionLeido= e->getMagSalidaActivacion();
			assert_eq ("Magnetismo en activacion", 
				mActivacion->getValor(), mActivacionLeido->getValor() );
		}
		
		public:
			PruebaElectroiman(): suite ("Prueba del sistema")
			{
				add ("Prueba Eletroiman", testcase (this, 
					"PruebaElectroiman", &PruebaElectroiman::PruebaValores));
				suite::main().add ("Prueba electroiman", this);
			}
	};
	
	PruebaElectroiman* pel=new PruebaElectroiman();	
}
