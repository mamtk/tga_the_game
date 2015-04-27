﻿#pragma once
#include "Menu.h"
#include "Halterofilismo.h"
#include "libUnicornio.h"

#include <ctime>	// nem precisaria
#include <stdlib.h>	// seria random, mas quem ia explicar depois?

class Jogo
{
	// estado do jogo, valores pretendem ser universais (entre as classes)
	enum EstadoDoJogo {
		menuPrincipal, menuJogos, menuOpcoes, menuAjuda, menuCreditos, menuHalterofilismoSandbox, menuHalterofilismoCampanha, menuHalterofilismo, \
		jogoHalterofilismoCampanha, jogoHalterofilismoSandbox
	};

	// opções dos menus
	enum OpcoesMenuPrincipal { escolhaJogar, escolhaOpcoes, escolhaAjuda, escolhaCreditos, escolhaSair };
	enum OpcoesMenuSecundario { escolhaHalterCampanha, escolhaHalterSandbox, escolhaTiroCampanha, escolhaTiroSandbox, Retornar };
	enum OpcoesMenuInstantaneo { escolhaContinuarJogo, escolhaSairDoJogo };

	// valores dos menus
	enum ValoresMenuOpcoes { valorDificuldade, valorDesativarEventos, valorDesativarFatality, valorDesativarSom, valorDesativarMusicas, valorDesativarHistoria };

	Texto texto;
	Menu principal;
	Menu secundario;
	Menu ajuda;
	Menu opcoes;
	Menu creditos;
	Menu menu;
	Menu instantaneo;
	Halterofilismo halterofilia;
	EstadoDoJogo estado = menuPrincipal;
	EstadoDoJogo estadoAnterior = menuPrincipal;

	std::vector<int> opcoesDeJogo;
	int jogo = 0;

	bool menuInstantaneoAtivo = false;	// essa variável nos diz se o menu instanâneo está ativado

	void gerenciarEstado();
	void gerenciarMenuPrincipal();
	void gerenciarMenuSecundario();
	void gerenciarMenuInstantaneo();
public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();

	void executar();
	void setEstado(int);
};

