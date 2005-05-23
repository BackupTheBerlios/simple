#include "pulsador.h"
#include <iostream>
using namespace std;



DOMElement* Pulsador::getNodo()
{
	return ElementoSimple::getNodo("pulsador");
}
