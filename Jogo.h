#pragma once
#include "MenuPrincipal.h"
#include "Halterofilismo.h"
#include "libUnicornio.h"

enum EstadoDeJogo { menuPrincipal, halterofilismo };

class Jogo
{
	Texto texto;
	MenuPrincipal menu;
	Halterofilismo halterofilia;
	EstadoDeJogo estado = menuPrincipal;

	std::vector<int> opcoesDeJogo;
	int jogo = 0;

	void gerenciarEstado();
public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();

	void executar();
	void setEstado(int);
};

