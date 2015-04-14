#pragma once
#include "MenuPrincipal.h"
#include "libUnicornio.h"

enum Estado { menuPrincipal, halterofilismo };

class Jogo
{
	int jogo = 0;
	Texto texto;
	MenuPrincipal menu;
	Estado estado = menuPrincipal;

	void gerenciarEstado();
public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();

	void executar();
	void setEstado(int);
};

