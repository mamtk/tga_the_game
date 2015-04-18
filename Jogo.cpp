#include "Jogo.h"

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
	uniInicializar(1024, 768, false, "TGA - The Game");

	//	O resto da inicializa鈬o vem aqui!
	//	...
	//	1)	Carregar as fontes (passando o tamanho da fonte como parametro)
	/* tentaremos uma nomenclatura padronizada --- edit 01
		fonte*		-	para fontes, ex. fonteNormal
		fundo_\1\2	-	para fundos, \1 é o jogo, \2 QUALQUER identificador; ex. fundo_Halter01, fundo_HalterCenaLago, ...
		per_\1\2	-	para personagens (tudo que age/tem vontade), ex. per_HalterMosca1, per_TiroPato, ...
		obj_\1\2	-	para objetos (mesmo com animação), ex. obj_HalterRochaDoLago, obj_JudoAnelDeFogo, ...
		fx_\1\2		-	para imateriais/efeitos, ex. fx_TiroFumaca, fx_ArcoSangue, ...
	*/
	recursos.carregarFonte("fonteNormal", "UbuntuMono-R.ttf", 17);
	// halterofilismo
	recursos.carregarSpriteSheet("fundo_Halter01", "img/fundos/halter_01.png");
	recursos.carregarSpriteSheet("per_Halter01", "img/per/lucas1.png", 3, 9);
	recursos.carregarSpriteSheet("fx_HalterBarra", "img/fx/fx_HalterBar.png", 1, 11);
	// especificar numeros de frames diferentes do maior
	recursos.getSpriteSheet("per_Halter01")->setNumFramesDaAnimacao(0, 3);
	recursos.getSpriteSheet("per_Halter01")->setNumFramesDaAnimacao(1, 8);

	// inicializar menus
	vector<wstring> opcoesPrincipais = { L"Iniciar Jogo", L"Opções", L"Ajuda", L"Créditos", L"Sair" };
	principal.inicializar(opcoesPrincipais, L"TESTE TESTE TESTE TESTE TESTE TESTE "); // algumas funções não podem ser executadas no construtor daquela classe (pois jogo ainda possui tipo incompleto)

	vector<wstring> opcoesSecundarias = { L"Halterofilismo (Campanha)", L"Halterofilismo (Sandbox)", L"Tiro (Campanha)", L"Tiro (Sandbox)", L"Voltar" };
	vector<wstring> opcoesCreditos = { L"TGA - The Game é um jogo sério, muito sério; mas não deve ser levado a sério, \
	já que é apenas um jogo.\n\nCriado por Jean Lucca, Mattheus Menezes, Morris.\nSão Leopoldo, abril de 2015." };
	wstring cabecalhoCreditos = L"Aperte [ENTER], [ESPAÇO] ou clique com o botão esquerdo para voltar.";
	creditos.inicializar(opcoesCreditos, cabecalhoCreditos);
	
	vector<wstring> textoAjuda = { L"blablabla\n\n\nParabéns! Você está pronto para ir para a próxima página!" };
	wstring cabecalhoAjuda = L"Aperte D ou -> para prosseguir, ou aperte [ENTER], [ESPAÇO] ou clique esquerdo para voltar.";
	ajuda.inicializar(textoAjuda, cabecalhoAjuda);

	wstring textoCabecalhoOpcoes = L"Pressione ↑ ou ↓, ou coloque o mouse em cima, para mudar a opção destacada.\n\
	Pressione <- e -> para alterar os valores da opção destacada.\n\
	\nPressione [ESPAÇO] para voltar. Todas as opções destacadas serão ativadas.";
	vector<wstring> textoOpcoes = { L"Nível de dificuldade:", // [0]
		L"Desativar eventos aleatórios:",	// [1]
		L"Desativar fatality:", // [2]
		L"Desativar som:", // [3]
		//L"Pular história:", // [4]
	};
	int sizeTextoOpcoes = textoOpcoes.size();
	vector<vector<wstring>> stringsValores;
	stringsValores.resize(sizeTextoOpcoes);

	for (int nivel = 0; nivel < sizeTextoOpcoes; nivel++) {	// aqui setamos os valores possíveis para cada uma das opções (níveis)
		switch (nivel) { // talvez fique mais fácil de entender se eu usar um loop for (embora fique mais lento, só roda uma vez)
		case 0: // variáveis possíveis para a opção [0] do textoOpcoes
			stringsValores[nivel] = { L"Normal", L"Difícil", L"Impossível", L"Impossível?" }; // opções para [0] (dificuldade)
			break;
		case 1: // variáveis possíveis para a opção [1] do textoOpcoes
			stringsValores[nivel] = { L"Não", L"Sim" }; // opções para [1] (desativar eventos pseudoaleatórios)
			break;
		case 2: // variáveis possíveis para a opção [2] do textoOpcoes
			stringsValores[nivel] = { L"Não", L"Sim" }; // opções para [2] (desativar fatality)
			break;
		case 3: // variáveis possíveis para a opção [2] do textoOpcoes
			stringsValores[nivel] = { L"Não", L"Sim" }; // opções para [3] (desativar som)
			break;
		}
	}
	opcoes.inicializar(textoOpcoes, stringsValores, textoCabecalhoOpcoes, { 0 }, 0, { 0 }, -1, -1, 0, 27, 550, -1, 21);
}

void Jogo::finalizar()
{
	//	O resto da finaliza鈬o vem aqui (provavelmente, em ordem inversa a inicializa鈬o)!
	//	...
	recursos.descarregarTodasFontes();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!teclado.soltou[TECLA_ESC] && !aplicacao.sair)
	{
		uniIniciarFrame();

		//	Seu cigo vem aqui!
		//	...
		gerenciarEstado();

		uniTerminarFrame();
	}
}

void Jogo::gerenciarEstado()
{
	switch (estado) {
		case menuPrincipal:
			principal.desenhar();	// desenhar o menu? a verdade é que o menu se desenha sozinho! haha, piada idiota.
			if (principal.finalizado()) {	// verificar se o jogador já fez a sua escolha
				gerenciarMenuPrincipal();
			}
			break;
		case menuOpcoes:
			opcoes.desenhar();	// desenhar o menu? a verdade é que o menu se desenha sozinho! haha, piada idiota.
			if (opcoes.finalizado()) {	// verificar se o jogador decidiu voltar
				principal.resetarMenu();
				opcoes.resetarMenu();
				estado = menuPrincipal;
			}
			break;
		case menuAjuda:
			ajuda.desenhar();	// desenhar o menu? a verdade é que o menu se desenha sozinho! haha, piada idiota.
			if (ajuda.finalizado()) {	// verificar se o jogador decidiu voltar
				principal.resetarMenu();
				ajuda.resetarMenu();
				estado = menuPrincipal;
			}
			break;
		case menuCreditos:
			creditos.desenhar();	// desenhar o menu? a verdade é que o menu se desenha sozinho! haha, piada idiota.
			if (creditos.finalizado()) {	// verificar se o jogador decidiu voltar
				principal.resetarMenu();
				creditos.resetarMenu();
				estado = menuPrincipal;
			}
			break;
		case jogoHalterofilismo:
			halterofilia.desenhar();
			break;
	}
}

void Jogo::gerenciarMenuPrincipal()
{
	int opcaoEscolhida = principal.getOpcao(); // ober opção escolhida

	// mudar estado do jogo, ou sair
	switch (opcaoEscolhida) {
	case escolhaJogar:
		estado = menuJogos;
		break;
	case escolhaAjuda:
		estado = menuAjuda;
		break;
	case escolhaOpcoes:
		estado = menuOpcoes;
		break;
	case escolhaCreditos:
		estado = menuCreditos;
		break;
	case escolhaSair:
		aplicacao.sair = true;
		break;
	}

	// resetar estado do menu principal (para que a opção destacada volte para o padrão)
	principal.resetarMenu();
}