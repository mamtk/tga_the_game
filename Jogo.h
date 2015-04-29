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
		menuPrincipal, menuJogos, menuOpcoes, menuAjuda, menuCreditos, menuHalterofilismoSandbox, jogoHalterofilismoCampanha, jogoHalterofilismoSandbox,
		menuVitoriaEstado, menuDerrotaEstado, menuVitoriaSandboxEstado, menuDerrotaSandboxEstado, menuVitoriaRapidaEstado, menuVitoriaRapidaSandboxEstado
	};

	// opções dos menus
	enum OpcoesMenuPrincipal { escolhaJogar, escolhaOpcoes, escolhaAjuda, escolhaCreditos, escolhaSair };
	enum OpcoesMenuSecundario { escolhaHalterCampanha, escolhaHalterSandbox, escolhaTiroCampanha, escolhaTiroSandbox, Retornar };
	enum OpcoesMenuSandbox { escolhaAleatorio, escolhaFazenda, escolhaEsgoto, escolhaCanil, escolhaAcademiaSuburbio, escolhaAcademiaCentro, escolhaOlimpiadas, escolhaVoltar };
	enum OpcoesMenuVitoria { escolhaContinuar, escolhaMenuPrincipalVitoria, escolhaSairMenuVitoria };
	enum opcoesMenuDerrota { escolhaRepetir, escolhaMenuPrincipalDerrota, escolhaSairMenuDerrota };
	enum OpcoesMenuVitoriaSandbox { escolhaContinuarSandbox, escolhaMenuPrincipalVitoriaSandbox, escolhaSairVitoriaSandbox };
	enum OpcoesMenuDerrotaSandbox { escolhaRecomecarSandbox, escolhaMenuPrincipalDerrotaSandbox, escolhaSairDerrotaSandbox };
	enum OpcoesMenuVitoriaRapida { tentarDesafio, escolhaContinuarRapida, escolhaMenuPrincipalVitoriaRapida, escolhaSairMenuVitoriaRapida };
	enum OpcoesMenuVitoriaRapidaSandbox {tentarDesafio, escolhaContinuarRapidaSandbox, escolhaMenuPrincipalVitoriaRapidaSandbox, escolhaSairVitoriaRapidaSandbox };
	enum OpcoesMenuInstantaneo { escolhaContinuarJogo, escolhaSairDoJogo };

	// valores dos menus
	enum ValoresMenuOpcoes { valorDificuldade, valorDesativarPragas, valorDesativarDesafios, valorDesativarSom, valorDesativarMusicas, valorDesativarHistoria, valorSexo };

	Texto texto;
	Menu principal;
	Menu secundario;
	Menu ajuda;
	Menu opcoes;
	Menu creditos;
	Menu menu;
	Menu instantaneo;
	// menus de modo de jogo
	Menu menuSandbox;
	Menu menuVitoria;
	Menu menuDerrota;
	Menu menuVitoriaSandbox;
	Menu menuDerrotaSandbox;
	Menu menuVitoriaRapida;
	Menu menuVitoriaRapidaSandbox;

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
	void gerenciarMenuSandbox();
	void gerenciarMenuVitoria();
	void gerenciarMenuDerrota();
	void gerenciarMenuVitoriaSandbox();
	void gerenciarMenuDerrotaSandbox();
	void gerenciarMenuVitoriaRapida();
	void gerenciarMenuVitoriaRapidaSandbox();

public:
	Jogo();
	~Jogo();


	void inicializar();
	void finalizar();

	void executar();
	void setEstado(int);
};

