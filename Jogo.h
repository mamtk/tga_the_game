#pragma once
#include "Menu.h"
#include "Halterofilismo.h"
#include "libUnicornio.h"

#include <ctime>	// nem precisaria
#include <stdlib.h>	// seria random, mas quem ia explicar depois?

class Jogo
{
	// estado do jogo, valores pretendem ser universais (entre as classes)
	enum EstadoDoJogo {
		menuPrincipal, menuJogos, menuOpcoes, menuAjuda, menuCreditos, menuHalterofilismo, jogoHalterofilismoCampanha, \
		jogoHalterofilismoSandbox, jogoTirofilismoCampanha, jogoTirofilismoSandbox
	};

	// opções dos menus
	enum OpcoesMenuPrincipal { escolhaJogar, escolhaOpcoes, escolhaAjuda, escolhaCreditos, escolhaSair };
	enum OpcoesMenuSecundario { escolhaHalterCampanha, escolhaHalterSandbox, escolhaTiroCampanha, escolhaTiroSandbox, Retornar };

	// valores dos menus
	enum ValoresMenuOpcoes { valorDificuldade, valorDesativarEventos, valorDesativarFatality, valorDesativarSom, valorDesativarMusicas, valorDesativarHistoria };

	Texto texto;
	Menu principal;
	Menu secundario;
	Menu ajuda;
	Menu opcoes;
	Menu creditos;
	Menu menu;
	Halterofilismo halterofilia;
	EstadoDoJogo estado = menuPrincipal;

	std::vector<int> opcoesDeJogo;
	int jogo = 0;

	void gerenciarEstado();
	void gerenciarMenuPrincipal();
	void gerenciarMenuSecundario();
public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();

	void executar();
	void setEstado(int);
};

