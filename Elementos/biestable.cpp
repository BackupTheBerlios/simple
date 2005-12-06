#include "biestable.h"
#include "constantes.h"

Biestable::Biestable(Voltaje* activar_r, Voltaje* desactivar_r,
			Voltaje* activar_s, Voltaje* desactivar_s,
			Voltaje* activar_q, Voltaje* desactivar_q, 
			Voltaje* activar_qneg, Voltaje* desactivar_qneg)
{
#ifdef DEBUG
	printf ("Se inicia el constructor de biestable\n");
#endif
	//totalEntradas=POS_ENTRADA+1;
	//totalSalidas=POS_SALIDA+1;
	this->activar_R			=	activar_r;
	this->desactivar_R		=	desactivar_r;	
	this->activar_S			=	activar_s;
	this->desactivar_S		=	desactivar_s;
	
	this->activar_Q			=	activar_q;
	this->desactivar_Q		=	desactivar_q;
	this->activar_Qneg		=	activar_qneg;
	this->desactivar_Qneg	=	desactivar_qneg;
	
	entradas[POS_ENTRADA] 	=	desactivar_r;
	entradas[POS_ENTRADA+1]	=	desactivar_s;
	
	salidas[POS_SALIDA]		=	desactivar_Q;
	salidas[POS_SALIDA+1]	=	desactivar_Qneg;
#ifdef DEBUG
	printf ("\nBiestable construido correctamente\n");
#endif
	totalEntradas=POS_ENTRADA+2; /*El biestable tiene dos entradas*/
	totalSalidas =POS_SALIDA+2;
}

/*	En vez de usar cadenas de if se usa una tabla para sacar la logica
	de control del codigo del programa y meterlo en una tabla.
	Un voltaje activo es un 1 y un voltaje inactivo es un 0
	Todo se codifica en la tabla salidasBiestable que indica la salida de Q
	que es lo unico que necesitamos
	salidasbiestable[0][0] indica cual es la salida cuando R=0 y S=0
	salidasbiestable[0][1] indica cual es la salida cuando R=0 y S=1
	salidasbiestable[1][0] indica cual es la salida cuando R=1 y S=0*/
int Biestable::setEntrada(Senal* s, int posicion)
{
	int salidasBiestable[2][2];
	salidasBiestable[0][0]=0;
	salidasBiestable[0][1]=1;
	salidasBiestable[1][0]=2;
	salidasBiestable[1][1]=3;
	
	Voltaje* valor_r	=	(Voltaje*) entradas[POS_ENTRADA];
	Voltaje* valor_s	=	(Voltaje*) entradas[POS_ENTRADA+1];
	Voltaje* entrada	=	(Voltaje*) s;
	
	int entrada_r;
	int entrada_s;
	
	/*	Vamos a calcular los 1 o 0 en R o S en funcion de las entradas*/
	if (posicion==POS_ENTRADA) 
	{
		entrada_r=obtenerValorR(entrada);
		entrada_s=obtenerValorS(valor_s);
	}
	if (posicion==POS_ENTRADA+1) 
	{
		entrada_r=obtenerValorR(valor_r);
		entrada_s=obtenerValorS(entrada);
		
	}
	/*	Dependiendo del caso hacemos una cosa u otra*/
	switch (salidasBiestable[entrada_r][entrada_s])
	{
		case 0: /*	R=0 y S=0 */
			{	
				entradas[POS_ENTRADA]=desactivar_R;
				entradas[POS_ENTRADA+1]=desactivar_S;
				/*printf ("R=%i S=%i  Q=%s Qneg=%s\n",entrada_r, entrada_s, 
					salidas[POS_SALIDA]->toString(), 
					salidas[POS_SALIDA+1]->toString() );*/
				/*No se hace nada, las salidas se propagan*/
				break;
			}
		case 1: /*	R=0 y S=1*/
			{
				entradas[POS_ENTRADA]	=	desactivar_R;
				
				/*Copiamos lo que ha entrado en S*/
				entradas[POS_ENTRADA+1]	=	activar_S;
				
				/*Hay que poner Q a 1 y Qneg a 0*/
				salidas[POS_SALIDA]		=	activar_Q;
				salidas[POS_SALIDA+1]	=	desactivar_Qneg;
				/*printf ("R=%i S=%i  Q=%f Qneg=%f\n",entrada_r, entrada_s, 
					activar_Q->getValor(), 
					desactivar_Qneg->getValor() );*/
				break;
			}
		case 2: /*	R=1 y S=0 */
			{
				/*Copiamos la entrada en R*/
				entradas[POS_ENTRADA]	=	activar_R;
				entradas[POS_ENTRADA]	=	desactivar_S;
				/*Ponemos Q a 0 y Qneg a 1*/
				salidas[POS_SALIDA]		=	desactivar_Q;
				salidas[POS_SALIDA+1]	=	activar_Qneg;
				/*printf ("R=%i S=%i  Q=%f Qneg=%f\n",entrada_r, entrada_s, 
					desactivar_Q->getValor(), 
					activar_Qneg->getValor() );*/
				break;
			}
		case 3: /*	R=1 y S=1 */
			{
				/*printf ("ERROR:::R=%i S=%i  \n",entrada_r, entrada_s);*/
				/*R y S no pueden estar a 1!!!*/
				return ERROR_DE_BIESTABLE;
			}
		default:
			{
				printf ("Ha ocurrido algun error interno\n");
			}
	} /*Fin del switch*/
	return (Elemento::setEntrada(s,posicion));		
}

int Biestable::setReset (Voltaje* c)
{
#ifdef DEBUG
	printf ("El voltaje que recibe setReset es %f\n", c->getValor());
#endif
	return (Biestable::setEntrada((Senal*)c,POS_ENTRADA));	
}

int Biestable::setSet (Voltaje* c)
{
#ifdef DEBUG
	printf ("El voltaje que recibe setSet es %f\n", c->getValor());
#endif

	return (Biestable::setEntrada(c, POS_ENTRADA+1));
}

Voltaje* Biestable::getQ()
{
	return (Voltaje*) salidas[POS_SALIDA];
}

Voltaje* Biestable::getQneg()
{
	return (Voltaje*) salidas[POS_SALIDA+1];
}

Voltaje* Biestable::getActivacionR()
{
	return (Voltaje*) entradas[POS_ENTRADA];
}

Voltaje* Biestable::getActivacionS()
{
	return (Voltaje*) entradas[POS_ENTRADA+1];
}

int Biestable::obtenerValorR(Voltaje* valor_r)
{
	int entrada_r;
	
	if ( valor_r->getValor() == activar_R->getValor() )
	{
		entrada_r=1;
	}
	if (valor_r->getValor() == desactivar_R->getValor() )
	{
		entrada_r=0;
	}
	return entrada_r;
}
int Biestable::obtenerValorS(Voltaje* valor_s)
{
	int entrada_s;
	if ( valor_s->getValor() == activar_S->getValor() )
	{
		entrada_s=1;
	}
	if (valor_s->getValor() == desactivar_S->getValor() )
	{
		entrada_s=0;
	}
	return entrada_s;
}
