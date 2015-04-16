#pragma once
#include "libUnicornio.h"

/***********************************************
PRIMEIRO TERMINA HALTEROFILISMO SANDBOX
DEPOIS TERMINA TIRO SANDBOX,

só então começa a pensar na campanha!
mas o ideal ainda seria terminar os 4 sandbox
e talvez pensar em quais campanhas serão as principais
e dar pista visual no menu secundário, ex. (ROTA PRINCIPAL) e (ROTA REDUZIDA)
************************************************/
class Halterofilismo
{
	Sprite fundo;

	void sandbox();
	void preparaSandbox();
public:
	Halterofilismo();
	~Halterofilismo();

	void desenhar();
	void inicializar();
};

