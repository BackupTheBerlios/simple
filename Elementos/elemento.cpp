#include "elemento.h"
#include "math.h"
#include "senal.h"

Elemento::Elemento()
{
	Senal* senalVacia=new Senal();
	for (int i=0;i<MAX_LONG_VECTOR_ENTRADAS;i++)
	{
		entradas[i]=senalVacia;
	}
	
	for (int i=0;i<MAX_LONG_VECTOR_SALIDAS;i++)
	{
		salidas[i]=senalVacia;
	}
	/* Esto debe cambiar en otros constructores de clases hija*/
	totalEntradas     = POS_ENTRADA+1;
	totalSalidas  	  = POS_SALIDA+1;
	totalSuscripciones = 0;
	
	strcpy (nombreElemento, "Elemento-sin-nombre");
}

int Elemento::setEntrada(Senal* entrada, int posicion)
{
	if ( (posicion<0) || (posicion>MAX_LONG_VECTOR_ENTRADAS) )	
	{
		/*Error, se puso un valor incorrecto como posicion*/
		return POS_ENTRADA_INVALIDA; 
	}
	
	
	if (entrada->getTipo()!=entradas[posicion]->getTipo() )
	{
		/*Error, se introdujo p.ej un voltaje cuando se esperaba un magnetismo*/
		return TIPOS_NO_COINCIDEN;
	}
	
	/*	Si todo está bien se apunta la nueva entrada y se notifica 
		a quien corresponda*/
	entradas[posicion]=entrada;
	notificar();
	return 0;
}

/*	Si alguien intenta introducir un nombre demasiado largo se truncara */
void Elemento::setNombreElemento (char *nombre)
{
	if (nombre==NULL) return ;
	
	if (strlen(nombre)>MAX_LONG_NOMBRE_ELEMENTO)
	{
		strncpy (nombreElemento,nombre, MAX_LONG_NOMBRE_ELEMENTO);
	}
	else {
		strcpy (nombreElemento, nombre);
	}
}

const char* Elemento::getNombreElemento ()
{
	return nombreElemento;
}

int Elemento::getTotalEntradas ()
{
	return totalEntradas;
}

int Elemento::getTotalSalidas ()
{
	return totalSalidas;
}

int Elemento::getTotalSuscripciones ()
{
	return totalSuscripciones;
}


int Elemento::getTipoEntrada (int posicion)
{
	if ((posicion>=0) && (posicion<totalEntradas))
	{
		return entradas[posicion]->getTipo();
	}
	else
	{
		return -1;
	}
}

int Elemento::getTipoSalida (int posicion)
{
	if ( (posicion>=0) && (posicion<totalSalidas) )
	{
		return salidas[posicion]->getTipo();
	}
	else
	{
		return -1;
	}
}


Senal* Elemento::getEntradaPorPosicion(int posicion)
{
	
	if ( (posicion>=0) && (posicion<totalEntradas) )
	{
		return entradas[posicion];
	}
	else
	{
		return NULL;
	}
	
}
Senal* Elemento::getSalidaPorPosicion(int posicion)
{
	if ( (posicion>=0) && (posicion<totalSalidas) )
	{
		return salidas[posicion];
	}
	else
	{
		return NULL;
	}
	
}

int Elemento::getPrimeraEntradaUtil()
{
	int primeraEntradaUtil=POS_ENTRADA;
	return primeraEntradaUtil;
}

int Elemento::getPrimeraSalidaUtil()
{
	int primeraSalidaUtil=POS_SALIDA;
	return primeraSalidaUtil;
}

/*	Si los nombre pedidos coinciden con el nombre de este elemento
	devolvemos las entradas utiles*/
int Elemento::getPrimeraEntrada(const char* nombre)
{
	int cod_comparacion;
	cod_comparacion=strcmp(nombre, nombreElemento);
	if (cod_comparacion==0)
	{
		return POS_RESET;
	}
	else {
		return ELEMENTO_NO_ENCONTRADO;
	}
}

int Elemento::getPrimeraSalida (const char* nombre)
{
	int cod_comparacion;
	cod_comparacion=strcmp(nombre, nombreElemento);
	if (cod_comparacion==0)
	{
		return POS_SALIDA;
	}
	else {
		return ELEMENTO_NO_ENCONTRADO;
	}
}

/*	Si los nombre pedidos coinciden con el nombre de este elemento
	devolvemos las entradas utiles*/
int Elemento::getPrimeraEntradaUtil(const char* nombre)
{
	int cod_comparacion;
	cod_comparacion=strcmp(nombre, nombreElemento);
	if (cod_comparacion==0)
	{
		return POS_ENTRADA;
	}
	else {
		return ELEMENTO_NO_ENCONTRADO;
	}
}

int Elemento::getPrimeraSalidaUtil (const char* nombre)
{
	int cod_comparacion;
	cod_comparacion=strcmp(nombre, nombreElemento);
	if (cod_comparacion==0)
	{
		return POS_SALIDA;
	}
	else {
		return ELEMENTO_NO_ENCONTRADO;
	}
}
	
int Elemento::anadirSuscriptor (Elemento* e,int pos_entrada,int pos_salida)
{
	/* Se comprueban todas las circunstancias...*/
	if ( (pos_entrada<0) || (pos_entrada>MAX_LONG_VECTOR_ENTRADAS) )
	{
		return POS_ENTRADA_INVALIDA;
	}
	
	if ( (pos_salida<0) || (pos_salida>MAX_LONG_VECTOR_SALIDAS) )
	{
		return POS_SALIDA_INVALIDA;
	}
	
	if (e==NULL) return ELEMENTO_INVALIDO;
	
	/*if (e->getTipoEntrada(pos_entrada)!=this->getTipoSalida(pos_salida))
		return TIPOS_NO_COINCIDEN;*/
		
	if (totalSuscripciones==MAX_SUSCRIPCIONES) return DEMASIADAS_SUSCRIPCIONES;
	
	/*	Si se dan todas las condiciones necesarias se toma nota de la nueva
		suscripcion en el vector de suscripciones */
	
	Suscripcion *s=new Suscripcion();
	s->setElementoSuscriptor(e);
	s->setElementoAvisador (this);
	s->setEntradaSuscriptor (pos_entrada);
	s->setSalidaAvisador (pos_salida);
	
	suscripciones[totalSuscripciones++]=s;
#ifdef DEBUG_SISTEMA
	printf ("Nueva suscripcion: Emisor %s(%i) y receptor %s(%i)\n",
			this->getNombreElemento(),pos_salida,
			e->getNombreElemento(),pos_entrada);
#endif 
	return 0;
}

int Elemento::eliminarSuscriptor (Elemento* e,int pos_entrada,int pos_salida)
{
	Elemento* elementoActual;
	int salidaDelElemento;
	int entradaDelElemento;
	Suscripcion* suscripcionActual;
	
	/*	Para cada suscripción*/
	for (	int posSuscripcion=0;
			posSuscripcion < totalSuscripciones;
			posSuscripcion++ )
	{
		suscripcionActual = suscripciones[posSuscripcion];
		
		/*	Obtenemos el elemento suscriptor*/
		elementoActual = suscripcionActual->getElementoSuscriptor();
		
		/*	Obtenemos la posicion por donde le entra el aviso*/
		entradaDelElemento = suscripcionActual->getPosEntradaSuscriptor();
		
		/*	Obtenemos la salida del elemento */
		salidaDelElemento = suscripcionActual->getPosSalidaAvisador();
		
		/*	Comprobamos si el suscriptor es el que nos han pasado*/
		bool suscriptorCorrecto= (elementoActual==e);
		
		/*	Comprobamos si la posicion de entrada es la misma*/
		bool entradaCorrecta= (entradaDelElemento==pos_entrada);
		
		/*	Comprobar si la salida del avisador es la misma*/
		bool salidaCorrecta= (salidaDelElemento==pos_salida);
		
		/*	Se comprueba si todo coincide*/
		bool todoCoincide=(	suscriptorCorrecto && entradaCorrecta &&
							salidaCorrecta);
		
		/*Si todo coincide...*/
		if (todoCoincide)
		{
			/*Se borra esta suscripcion*/
			borrarSuscripcion(posSuscripcion);
			return SUSCRIPCION_BORRADA;
		}
	} /*Fin del for*/
	
	/*	No se encontro la suscripcion*/
	return SUSCRIPCION_NO_EXISTIA;
}
void Elemento::notificar()
{
	Elemento* elem_a_notificar;
	int pos_entrada_a_notificar;
	int pos_salida_a_notificar;
	
	for (int i=0;i<totalSuscripciones;i++)
	{
		elem_a_notificar		=suscripciones[i]->getElementoSuscriptor();
		pos_entrada_a_notificar	=suscripciones[i]->getPosEntradaSuscriptor();
		pos_salida_a_notificar	=suscripciones[i]->getPosSalidaAvisador();
		elem_a_notificar->setEntrada
			(salidas[pos_salida_a_notificar], pos_entrada_a_notificar);
#ifdef DEBUG_BIESTABLE
		printf ("Aviso de %s(sal.%i) hacia %s(ent.%i) con valor %s!\n",
			this->getNombreElemento(), pos_salida_a_notificar,
			elem_a_notificar->getNombreElemento(),pos_entrada_a_notificar,
			salidas[pos_salida_a_notificar]->toString());
#endif 
	}
}

void Elemento::pintarSuscripciones()
{
	printf ("%s tiene %i suscripciones\n", nombreElemento, totalSuscripciones);
	for (int i=0;i<totalSuscripciones;i++)
	{
		Elemento* avisador=this->suscripciones[i]->getElementoAvisador();
		Elemento* suscriptor=this->suscripciones[i]->getElementoSuscriptor();
		const char *nombreAvisador=avisador->getNombreElemento();
		const char *nombreSuscriptor=suscriptor->getNombreElemento();
		int entradaSuscriptor=this->suscripciones[i]->getPosEntradaSuscriptor();
		int salidaAvisador =this->suscripciones[i]->getPosSalidaAvisador();
		printf ("\t--%s saca por la salida %i una señal a la entrada %i de %s\n",
			nombreAvisador, salidaAvisador, nombreSuscriptor, entradaSuscriptor);
	}
	
}
bool Elemento::iguales(float x, float y)
{
	if (fabs (x-y)<MARGEN_ACEPTABLE) return true;
	return false;	
}

void Elemento::borrarSuscripcion (int posicion)
{
	/*	Este borrado no interfiere con el liberado de memoria de WxWidgets*/
	delete suscripciones[posicion]; 
	
	/*	Se desplazan todas las suscripciones hacia la izquierda*/
	for (int posVectorSuscripciones=posicion;
			posVectorSuscripciones<totalSuscripciones;
			posVectorSuscripciones++)
	{
		suscripciones[posicion]=suscripciones[posicion+1];
	}
	
	totalSuscripciones--;
			
}

/*	Por realizar */
DOMElement* Elemento::getNodo()
{
}

void Elemento::construir (DOMNode*)
{
}
