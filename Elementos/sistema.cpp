#include "sistema.h"
#include "conector.h"

Sistema::Sistema()
{
	MaxElementos=0;
	for (int i=0;i<MAX_NUM_ELEMENTOS_POR_SISTEMA;i++)
	{
		elemento[i]=NULL;
	}
	for (int i=0;i<MAX_LONG_VECTOR_ENTRADAS;i++)
	{
		conectorEntrada[i]=NULL;
	}
	for (int i=0;i<MAX_LONG_VECTOR_SALIDAS;i++)
	{
		conectorSalida[i]=NULL;
	}
}

/*	En los sistemas, las suscripciones se hacen a los conectores de
	salida y no al sistema directamente*/
int Sistema::anadirSuscriptor   (Elemento* e,int pos_entrada, 
							int pos_salida)
{
	#ifdef DEBUG_SISTEMA
	printf ("Al sistema %s(salida %i) se le suscribe %s(entrada %i)\n",
		this->getNombreElemento(), pos_salida, e->getNombreElemento(),
		pos_entrada);
	#endif
	conectorSalida[pos_salida]->anadirSuscriptor(e,pos_entrada);
}
int Sistema::eliminarSuscriptor (Elemento* e,int pos_entrada, 
							int pos_salida)
{
	conectorSalida[pos_salida]->eliminarSuscriptor(e,pos_entrada);
}
int Sistema::setEntrada (Senal* s, int posicion)
{
	entradas[posicion]=s;
	#ifdef DEBUG_SISTEMA
	printf ("En el sistema %s se ha activado el conector %i\n",
		this->getNombreElemento(), posicion);
	printf ("Se recibio una señal %s en el elemento %s\n", s->toString(),
		this->getNombreElemento() );
	#endif
	if (conectorEntrada[posicion]==NULL) 
	{
		#ifdef DEBUG_SISTEMA
		printf ("Conector NULL!!!\n");
		#endif
	}
	conectorEntrada[posicion]->setEntrada(s);
	Elemento::setEntrada(s,posicion);
}

/*	La implementacion interna añade un conector que va "enganchado"
	al elemento que añadimos mediante una suscripcion de forma que cuando
	alguien modifica la entrada, esa entrada se propaga al conector y de ahi
	al elemento concreto. Esto permite crear sistemas "de caja blanca" y
	"de caja negra" */
int Sistema::anadirElemento(Elemento* e)
{
	elemento[MaxElementos]=e;
	string nombre(e->getNombreElemento());
	posicionDelElemento[nombre]=MaxElementos;
	MaxElementos++;
	
	/*	Hay que añadir una suscripcion para cada una de las entradas 
		del elemento*/
	primeraEntradaDelElemento[nombre]=totalEntradas;
	
	#ifdef DEBUG_SISTEMA
	printf ("El elemento %s ocupa la entrada %i\n", 
		e->getNombreElemento(), totalEntradas);
	#endif
	
	int totalEntradasDelElemento=e->getTotalEntradas();
	
	for (int pos_entrada=0; 
			 pos_entrada<totalEntradasDelElemento ;
			 pos_entrada++)
	{
		#ifdef DEBUG_SISTEMA
		printf ("Haciendo la conexion a la entrada %i del sistema\n",
			totalEntradas);
		#endif
		conectorEntrada[totalEntradas]=new Conector();
		conectorEntrada[totalEntradas]->setNombreElemento ("Entrada");
		int i=conectorEntrada[totalEntradas]->anadirSuscriptor(e,pos_entrada);
		if (i!=0)
		{
			#ifdef DEBUG_SISTEMA
			printf ("No se hizo la suscripcion: Codigo %i\n",i);
			#endif
		}
		totalEntradas++;
	}
	
	/*	Apuntamos la posicion de la primera salida del elemento*/
	primeraSalidaDelElemento[nombre]=totalSalidas;
	
	#ifdef DEBUG_SISTEMA
	printf ("\n\nEl elemento %s ocupa la salida %i\n", 
		e->getNombreElemento(), totalSalidas);
	#endif
	int totalSalidasDelElemento=e->getTotalSalidas();
	for (int pos_salida=0;
			 pos_salida<totalSalidasDelElemento;
			 pos_salida++)
	{
		/*	Otro hack para conectar las salidas del elemento a las salidas
		del sistema*/
		conectorSalida[totalSalidas]=new Conector();
		conectorSalida[totalSalidas]->setNombreElemento ("Salida");
		e->anadirSuscriptor(conectorSalida[totalSalidas],
			POS_ENTRADA,pos_salida);
		totalSalidas++;
	}	
	
	#ifdef DEBUG_SISTEMA
	printf ("%s tiene %i entradas y %i salidas\n", e->getNombreElemento(),
		totalEntradasDelElemento, totalSalidasDelElemento);
	printf ("_________________________\n\n");
	#endif
}

int Sistema::eliminarElemento (Elemento* e)
{
	/*	Para cada conector de entrada... */
	int ultimoConectorEntradaEliminado;
	int ultimoConectorSalidaEliminado;
	int	codigo;
	for ( 	int posEntrada=0;
			posEntrada<totalEntradas;
			posEntrada++)
	{
		/*	...intentamos eliminar la suscripcion entre conectores
			de entrada y el elemento que nos han pasado*/
		if (conectorEntrada[posEntrada]!=NULL)
		{
			int MaxEntradas	=	e->getTotalEntradas();
			for (	int entrada=0; 	entrada < MaxEntradas; entrada++)
			{
				
				codigo=conectorEntrada[posEntrada]->eliminarSuscriptor
													(e,entrada);
													
				/*	Si se borra una suscripcion se borra el conector */
				if (codigo==SUSCRIPCION_BORRADA)
				{
					delete conectorEntrada[posEntrada];
					conectorEntrada[posEntrada]=NULL;
					ultimoConectorEntradaEliminado=posEntrada;
					break;
				} /*	Fin del if*/
			} /* Fin del for para todas las entradas*/
		} /*Fin del if que comprueba conectorEntrada!=NULL*/
	}	/*	Fin del for para los conectores de entrada */
	
	
	/*	Para cada conector de salida...*/
	for ( 	int posSalida=0;
			posSalida<totalSalidas;
			posSalida++)
	{
		if (conectorSalida[posSalida]!=NULL)
		{
			int MaxSalidas	=	e->getTotalSalidas();
			for (	int salida=0; salida < MaxSalidas; salida++)
			{
				
				/*	...se intenta eliminar la suscripcion entre el elemento
					y ese conector de salida*/
				codigo=e->eliminarSuscriptor ( conectorSalida[posSalida],
												POS_ENTRADA, salida );
		
		
				/*	Si se borra una suscripcion tambien borramos el conector */
				if (codigo==SUSCRIPCION_BORRADA)
				{
					delete conectorEntrada[posSalida];
					conectorSalida[posSalida]=NULL;
					ultimoConectorSalidaEliminado=posSalida;
					break;
				} /*	Fin del if*/
			} /* Fin del for para todas las salidas */
		} /*Fin del if que comprueba conectorSalida!=NULL*/
	} /* Fin del for para conectores de salida */
	
	/*	Se intentan eliminar todas las suscripciones que afecten a
		ese elemento en concreto, tanto si es avisador como si es
		suscriptor */
	for (	int posElemento=0;
			posElemento < MaxElementos;
			posElemento++)
	{
		codigo=elemento[posElemento]->eliminarSuscriptor ( e );
		codigo=e->eliminarSuscriptor ( elemento[posElemento] );
	}
	
	/*	Hay que reordenar los vectores de conectores*/
	
	/*	A partir de la ultima posicion borrada, todos los conectores
		de entrada tienen que copiarse x entradas mas atras (siendo x
		el numero de entradas que tenia el elemento*/
	ultimoConectorEntradaEliminado++;
	int numEntradasDelElemento=e->getTotalEntradas();
	
	for (	int posEntrada=
				ultimoConectorEntradaEliminado-numEntradasDelElemento;
			posEntrada<totalEntradas;
			posEntrada++)
	{
		conectorEntrada[posEntrada]=
			conectorEntrada[posEntrada+numEntradasDelElemento];
	} /*	Fin del for para los conectores de entrada*/
	
	/*	Hacemos lo mismo con los conectores de salida*/
	ultimoConectorSalidaEliminado++;
	int numSalidasDelElemento=e->getTotalSalidas();
	for (	int posSalida=ultimoConectorSalidaEliminado-numSalidasDelElemento;
			posSalida<totalSalidas;
			posSalida++)
	{
		conectorSalida[posSalida]=
			conectorSalida[posSalida+numSalidasDelElemento];
	} /*	Fin del for*/
	
	/*	El map que indica donde esta la primera entrada de
		un elemento o su primera salida tiene que actualizar
		sus contenidos restando las posiciones que hay aqui*/
	int numEntradasAReducir	=	e->getTotalEntradas();
	int numSalidasAReducir	=	e->getTotalSalidas();
	
	/*	Cogemos el elemento conectado ahora al ultimo conector de
		entrada eliminado (serviria tambien el de salida)*/
	/*	Apuntamos cual era la posicion que tenia en el vector
		de elementos*/
	const char* nombreDelElemento=e->getNombreElemento();
	string nombrecpp(nombreDelElemento);
	int primerElementoParaActualizar=posicionDelElemento[nombrecpp];
	
	/* 	Tambien se tienen que actualizar las primeras entradas y 
		salidas de los elementos que se han visto desplazdos*/
	for (	int posElemento=primerElementoParaActualizar;
			posElemento<MaxElementos;
			posElemento++)
	{
		Elemento* elemVisitado=elemento[posElemento];
		string nombreDelElementoVisitado ( elemVisitado->getNombreElemento() );
		primeraEntradaDelElemento[nombreDelElementoVisitado]-=
			numEntradasAReducir;
		primeraSalidaDelElemento[nombreDelElementoVisitado]-=
			numSalidasAReducir;
	}
}
int Sistema::setEntrada (Senal* s, const char* nombre, int posicion)
{
	/* 	Se busca el elemento concreto, se recupera y luego se introduce
		esa señal en ese elemento en la posicion correspondiente*/
	string nombrecpp(nombre);
	int pos=posicionDelElemento[nombrecpp];
	Elemento* e=elemento[pos];
	e->setEntrada(s, posicion);
	int salidaDelElemento=primeraSalidaDelElemento[nombre];
	
	#ifdef DEBUG_SISTEMA
	printf ("\nLa salida de %s es la posicion:%i\n", nombre, salidaDelElemento);
	#endif
}

Senal* Sistema::getEntradaPorNombre (const char* nombre)
{
	string nombrecpp (nombre);
	int pos=posicionDelElemento[nombrecpp];
	Elemento* e=elemento[pos];
	return (e->getEntradaPorPosicion());	
}


Senal* Sistema::getSalidaPorNombre (const char* nombre)
{
	string nombrecpp (nombre);
	int pos=posicionDelElemento[nombrecpp];
	Elemento* e=elemento[pos];
	return (e->getSalidaPorPosicion());	
}

Elemento* Sistema::getRefElementoPorNombre (const char* nombreElem)
{
	string nombrecpp (nombreElem);
	int pos=posicionDelElemento[nombrecpp];
	Elemento* e=elemento[pos];
	return e;
}

int Sistema::getPrimeraEntrada(const char* nombreElem)
{
	//printf ("Se llama a getPrimeraEntrada con %s\n",nombreElem);
	/*	Se busca primero si es un nombre conocido dentro de este
		sistema.*/
	int cuantosConEseNombre=-1;
	string nombrecpp(nombreElem);
	cuantosConEseNombre=primeraEntradaDelElemento.count(nombrecpp);
	
	/*	Si se encuentra se devuelve esa posicion*/
	if (cuantosConEseNombre>0)
	{
		return primeraEntradaDelElemento[nombrecpp];
	}
	
	/*	Si no se encuentra se busca en todos y cada uno de los elementos
		ya que quizas algun elemento sea un sistema y contenga el elemento
		buscado */
	Elemento* 	elementoExaminado;
	int  		posDeSuEntrada;
	for ( int posElemento=0; posElemento < MaxElementos  ; posElemento++)
	{
		elementoExaminado 	= elemento[posElemento];
		posDeSuEntrada=elementoExaminado->getPrimeraEntrada	(
														nombreElem);	
		/* 	Si no devuelve ELEMENTO_NO_ENCONTRADO es que
			ya se conoce la posicion, por lo ahora solo hay que buscar
			cual es la entrada del sistema que esta suscrito a esa entrada*/
		if (posDeSuEntrada!=ELEMENTO_NO_ENCONTRADO)
		{
			int PosEntradaReal=buscarConector(conectorEntrada, 
				elementoExaminado, posDeSuEntrada,totalEntradas);
			if (PosEntradaReal!=ELEMENTO_NO_ENCONTRADO)
			{
				return PosEntradaReal;
			}
		}
	} /*Fin del for*/
	
	/* Se ha buscado en todos los subcomponentes y no se ha encontrado*/
	return ELEMENTO_NO_ENCONTRADO;
		
}

int Sistema::getPrimeraSalida (const char* nombreElem)
{
	/*	Igual que antes se busca si es un nombre conocido en ese
		sistema*/
	int cuantosConEseNombre=-1;
	string nombrecpp(nombreElem);
	cuantosConEseNombre=primeraSalidaDelElemento.count(nombrecpp);
	
	/*	Si se encuentra directamente...*/
	if (cuantosConEseNombre>0)
	{
		int pos=primeraSalidaDelElemento[nombrecpp];
		return pos;
	}
	/*	... y si no se hace una busqueda por todos los elementos
		del sistema. Ya que alguno puede ser un subsistema. */
	Elemento* 	elementoExaminado;
	int  		posDeSuSalida;
	
	for ( int posElemento=0; posElemento < MaxElementos  ; posElemento++)
	{
		elementoExaminado 	= elemento[posElemento];
		posDeSuSalida		= elementoExaminado->getPrimeraSalida (
														nombreElem);	
		/* 	Si no devuelve ELEMENTO_NO_ENCONTRADO es que
			ya se conoce la posicion, por lo que podemos terminar*/
		if (posDeSuSalida!=ELEMENTO_NO_ENCONTRADO)
		{
			return posDeSuSalida+1;
		}
	} /*Fin del for*/
	
	/*	Si no se encontro se devuelve un valor nulo*/
	return ELEMENTO_NO_ENCONTRADO;
}
int Sistema::getPrimeraEntradaUtil (const char* nombreElem)
{
	/*	La primera entrada util es la misma pero sumando POS_ENTRADA*/
	return ( this->getPrimeraEntrada(nombreElem)+POS_ENTRADA );
}
int Sistema::getPrimeraSalidaUtil (const char* nombreElem)
{
	/*	Y la primera salida tambien hay que sumar POS_SALIDA*/
	return ( this->getPrimeraSalida(nombreElem)+POS_SALIDA );
}
/*	Estos metodos son heredados de Elemento y son redefinidos
	para que devuelvan la salida del conector correspondiente*/
	
Senal* Sistema::getEntradaPorPosicion(int posicion)
{
	Senal*s=conectorEntrada[posicion]->getEntradaPorPosicion();
	return s;
}

Senal* Sistema::getSalidaPorPosicion (int posicion)
{
	Senal*s=conectorSalida[posicion]->getEntradaPorPosicion();
	return s;
}

int Sistema::buscarConector (Conector* vectorConectores[], Elemento* e, 
				int posicion, int limMaxVector)
{
	int posicionADevolver=ELEMENTO_NO_ENCONTRADO;
	
	for (	int numConector=0;
			numConector < limMaxVector;
			numConector++)
	{
		Conector* conectorExaminado=vectorConectores[numConector];
		/*	Algunos de los conectores podrian no ir conectados a nada
			y por tanto ser NULL, en ese caso los saltamos*/
		if (conectorExaminado!=NULL)
		{
			/*	Ahora buscamos la suscripcion que involucra a ese conector
			como avisador*/
			Elemento* elem_Examinado= 
				conectorExaminado->getElementoSuscriptor();
			int posEntradaDelExaminado=
				conectorExaminado->getPosEntradaSuscriptor();
			
			if ( (posEntradaDelExaminado==posicion) && (elem_Examinado==e) )
			{
				posicionADevolver=numConector;
				return posicionADevolver;
			}
		} /*Fin del if que comprueba si conectorExaminadoEsNULL*/
	} /*Fin del for*/
	
	return posicionADevolver; /*	¡Cuidado, podria ser ELEMENTO_NO_ENCONTRADO*/
}
