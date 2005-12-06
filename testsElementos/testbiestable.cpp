#include "unit++.h"
#include "biestable.h"

using namespace unitpp;

namespace
{
	class PruebaBiestable: public suite
	{
		void pruebaBasicaBiestable()
		{
			int codigo1, codigo2;
			codigo1=codigo2=-100;
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
			bool biestable_nulo=(b==NULL);
			assert_eq ("Biestable bien construido", false, biestable_nulo);
			
			/* 	Examinamos los estados del biestable*/
#ifdef DEBUG
			printf ("Intentando modificar biestable en reset...\n");
#endif
			/*	Probamos a resetearlo*/
			codigo1=b->setReset(activar1);
			codigo2=b->setSet(desactivar1);
			assert_eq ("Reset2 se activo correctamente", 0,codigo1);
			assert_eq ("Set2 se desactivo correctamente", 0, codigo2);
			
			/*	Ahora la salida de Q deberia ser "inactivo"*/
			Voltaje *v1=b->getQ();
			Voltaje* v2=b->getQneg();
			assert_eq ("Funciona el reset del biestable para Q", 
				desactivar1->getValor(), v1->getValor() );
			assert_eq ("Funciona el reset del biestable para Qneg",
				activar1->getValor(), v2->getValor() );
				
			Voltaje *vv=new Voltaje(0.0);
			/*	Probamos a activarlo*/
			codigo1=b->setReset(vv);
			
			assert_eq ("Reset3 se desactivo correctamente", 0,codigo1);
			assert_eq ("Set3 se desactivo correctamente", 0, codigo2);
			
#ifdef DEBUG
			printf ("Intentando modificar biestable en set...\n");
#endif			
			v1=b->getQ();
			v2=b->getQneg();
#ifdef DEBUG
			printf ("Se han recuperado los voltajes correctamente ");
			printf (" con los valores v1(Q)=%f y v2(Qneg)=%f\n",
				v1->getValor(), v2->getValor() );
#endif
			b->setSet(activar1);
			v1=b->getQ();
			v2=b->getQneg();
			assert_eq ("Funciona el set del biestable para Q", 
				activar1->getValor(), v1->getValor() );
			assert_eq ("Funciona el set del biestable para Qneg",
				desactivar1->getValor(),v2->getValor() );
							
		}
		
		void pruebaValores()
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
			
			Voltaje* resul1=b->getActivacionR();
			assert_eq ("Valor de R de prueba", 0.0, resul1->getValor() );
			
			Voltaje* resul2=b->getActivacionS();
			assert_eq ("Valor de S de prueba", 0.0, resul2->getValor() );
			
			Voltaje* v1=b->getQ();
			assert_eq ("Valor de voltaje de Q", 0.0, v1->getValor() );
			
			Voltaje* v2=b->getQneg();
			assert_eq ("Valor de voltaje de Qneg", 0.0, v2->getValor() );
			
			int codigo;
			
			codigo=b->setReset(new Voltaje(5.0));
			assert_eq ("Reset funcionando con 5.0 ...", 0, codigo);
#ifdef DEBUG
			printf ("Llamando al setReset rebelde...\n");
#endif			
			codigo=b->setReset(new Voltaje(0.0));
			assert_eq ("Reset funcionando con 0.0 ...", 0, codigo);
		}
		
		void pruebaBiestablePorDefecto()
		{
			int codigo1, codigo2;
			codigo1=codigo2=-100;
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
			bool biestable_nulo=(b==NULL);
			assert_eq ("Biestable bien construido", false, biestable_nulo);
			
			Voltaje *v;
			Voltaje* voltajeNulo=new Voltaje(0.0);
						
			/*	Obtenemos el valor de la R en un biestable recien creado*/
			v=(Voltaje*)b->getEntradaPorPosicion();
			assert_eq ("R por defecto del biestable",
				v->getValor(), voltajeNulo->getValor() );
			
			/*	Obtenemos el valor de la S*/
			v=(Voltaje*)b->getEntradaPorPosicion(POS_ENTRADA+1);
			assert_eq ("S por defecto del biestable",
				v->getValor(), voltajeNulo->getValor() );
			
			/*	Obtenemos el valor de la Q*/
			v=(Voltaje*)b->getSalidaPorPosicion();
			assert_eq ("R por defecto del biestable",
				v->getValor(), voltajeNulo->getValor() );
			
			/*	Obtenemos el valor de la S*/
			v=(Voltaje*)b->getSalidaPorPosicion(POS_SALIDA+1);
			assert_eq ("S por defecto del biestable",
				v->getValor(), voltajeNulo->getValor() );
			
		}
		public:
			 PruebaBiestable():suite ("PruebaBiestable")
			 {
					add ("pruebaValores", testcase (this,
						"pruebaValores", 
						&PruebaBiestable::pruebaValores));
					add ("pruebaBasicaBiestable", testcase (this,
						"pruebaBasicaBiestable", 
						&PruebaBiestable::pruebaBasicaBiestable));
					add ("pruebaBiestablePorDefecto", testcase (this,
						"prueba Biestable por defecto", 
						&PruebaBiestable::pruebaBiestablePorDefecto));
					suite::main().add("PruebaBiestable", this);
			}
	};
	
	PruebaBiestable* pb=new PruebaBiestable();
}
