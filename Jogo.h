#pragma once
#include "Menu.h"
#include "Halterofilismo.h"
#include "libUnicornio.h"

enum EstadoDoJogo { menuPrincipal, menuJogos, menuOpcoes, menuAjuda, menuCreditos, menuHalterofilismo, jogoHalterofilismo };

class Jogo
{
	enum OpcoesMenuPrincipal { escolhaJogar, escolhaOpcoes, escolhaAjuda, escolhaCreditos, escolhaSair };

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
public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();

	void executar();
	void setEstado(int);
};

