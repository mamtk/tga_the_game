#include "Jogo.h"

Jogo::Jogo()
{
	// inicializar o rand no construtor, já que ele tem menos chances de rodar de novo que o inicializar()
	srand(time(time_t()));	// isso aqui o professor não explicou, mas pelo menos ele já disse pra usar
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
		fonte*			-	para fontes, ex. fonteNormal
		fundo_\1\2		-	para fundos, \1 é o jogo/classe, \2 QUALQUER identificador; ex. fundo_Halter01, fundo_HalterCenaLago, ...
		per_\1\2		-	para personagens (tudo que age/tem vontade), ex. per_HalterMosca1, per_TiroPato, ...
		obj_\1\2		-	para objetos (mesmo com animação), ex. obj_HalterRochaDoLago, obj_JudoAnelDeFogo, ...
		fx_\1\2			-	para imateriais/efeitos, ex. fx_TiroFumaca, fx_ArcoSangue, ...
		somfx_\1\2		-	para imateriais/efeitos, somex. fx_Tiro, somfx_SangueJorrando, ...
		somfundo_\1\2	-	para fundos, ex. somfundo_Campo, somfundo_Vento, ...
	*/
	// fontes
	recursos.carregarFonte("fonteNormal", "UbuntuMono-R.ttf", 17);
	recursos.carregarFonte("fonteNormalSombra", "UbuntuMono-B.ttf", 19);
	recursos.carregarFonte("fonteGrande", "UbuntuMono-R.ttf", 27);
	recursos.carregarFonte("fonteGrandeSombra", "UbuntuMono-B.ttf", 29);
	// sons
	/*recursos.carregarAudio("somfundo_HalterFazenda", "audio/somfundo/somfundo_HalterFazenda.ogg");
	recursos.carregarAudio("somfundo_HalterEsgoto", "audio/somfundo/somfundo_HalterEsgoto.ogg");
	recursos.carregarAudio("somfundo_HalterCanil", "audio/somfundo/somfundo_HalterCanil.ogg");
	recursos.carregarAudio("somfundo_HalterAcademiaSuburbio", "audio/somfundo/somfundo_HalterAcademiaSuburbio.ogg");
	recursos.carregarAudio("somfundo_HalterAcademiaCentro", "audio/somfundo/somfundo_HalterAcademiaCentro.ogg");
	recursos.carregarAudio("somfundo_HalterOlimpiadas", "audio/somfundo/somfundo_HalterOlimpiadas.ogg");
	recursos.carregarAudio("somfx_BebeChorando", "audio/somfx/somfx_BebeChorando.ogg");
	recursos.carregarAudio("somfx_GrunhidosBolaBilhar", "audio/somfx/somfx_GrunhidosBolaBilhar.ogg");
	recursos.carregarAudio("somfx_CavaloDoido", "audio/somfx/somfx_CavaloDoido.ogg");
	recursos.carregarAudio("somfx_CarroLigando", "audio/somfx/somfx_CarroLigando.ogg");
	recursos.carregarAudio("somfx_Ovelhas", "audio/somfx/somfx_Ovelhas.ogg");
	recursos.carregarAudio("somfx_Enxame", "audio/somfx/somfx_Enxame.ogg");
	recursos.carregarAudio("somfx_Trovao", "audio/somfx/somfx_Trovao.ogg");
	recursos.carregarAudio("somfx_Espirro", "audio/somfx/somfx_Espirro.ogg");
	recursos.carregarAudio("somfx_OssosQuebrando", "audio/somfx/somfx_OssosQuebrando.ogg");
	recursos.carregarAudio("somfx_VozNoRadio", "audio/somfx/somfx_VozNoRadio.ogg");
	// menus
	recursos.carregarAudio("somfundo_MenuPrincipal", "audio/music_02_Menu.ogg");
	recursos.carregarAudio("somfundo_MenuOpcoes", "audio/music_03_Opcoes.ogg");
	recursos.carregarAudio("somfundo_MenuAjuda", "audio/music_04_Ajuda.ogg");
	recursos.carregarAudio("somfundo_MenuCreditos", "audio/music_05_Creditos.ogg");*/
	// sprites
	recursos.carregarSpriteSheet("fx_Esmaecer", "img/fx/fx_esmaecer.png", 1, 100);
	recursos.carregarSpriteSheet("fx_Dot", "img/fx/fx_Dot.png", 1, 1);
	recursos.carregarSpriteSheet("fundo_teste", "img/fundos/fundo_teste.jpg");
	// menuPrincipal
	recursos.carregarSpriteSheet("fundo_MenuPrincipal01", "img/fundos/fundo_MenuPrincipal01.png");
	recursos.carregarSpriteSheet("fundo_MenuPrincipal02", "img/fundos/fundo_MenuPrincipal02.png");
	recursos.carregarSpriteSheet("fundo_MenuPrincipal03", "img/fundos/fundo_MenuPrincipal03.png");
	recursos.carregarSpriteSheet("fundo_MenuPrincipal04", "img/fundos/fundo_MenuPrincipal04.png");
	recursos.carregarSpriteSheet("fundo_MenuPrincipal05", "img/fundos/fundo_MenuPrincipal05.png");
	// outros menus
	recursos.carregarSpriteSheet("fundo_MenuOpcoes", "img/fundos/fundo_MenuOpcoes.png");
	recursos.carregarSpriteSheet("fundo_MenuAjuda", "img/fundos/fundo_MenuAjuda.png");
	recursos.carregarSpriteSheet("fundo_MenuCreditos", "img/fundos/fundo_MenuCreditos.png");
	// halterofilismo
	recursos.carregarSpriteSheet("fundo_Halter01", "img/fundos/halter_01.png");
	recursos.carregarSpriteSheet("fx_Letras", "img/fx/fx_Letras.png", 1, 30);
	recursos.carregarSpriteSheet("fx_LetrasIluminadas", "img/fx/fx_LetrasIluminadas.png", 1, 30);
	recursos.carregarSpriteSheet("per_HalterHomem0", "img/per/per_HalterHomem0.png", 0, 13);
	recursos.carregarSpriteSheet("per_HalterMosca", "img/per/per_HalterMosca.png");
	//recursos.carregarSpriteSheet("per_HalterPomba", "img/per/per_HalterMosca.png");
	recursos.carregarSpriteSheet("obj_HalterBarra", "img/obj/obj_HalterBarraFofa.png");
	recursos.carregarSpriteSheet("fx_HalterBarra", "img/fx/fx_HalterBar.png", 1, 11);

	//********* MENUS
	// inicializar menu principal
	vector<string> fundosPrincipal = { "fundo_MenuPrincipal01", "fundo_MenuPrincipal02", "fundo_MenuPrincipal03", /*"fundo_MenuPrincipal04",*/ "fundo_MenuPrincipal05" };
	int fundoMaisBom = rand() % fundosPrincipal.size();
	vector<wstring> opcoesPrincipais = { L"Iniciar Jogo", L"Opções", L"Ajuda", L"Créditos", L"Sair" };
	int xCabecalho = janela.getLargura() * .5;
	int yCabecalho = janela.getAltura() * .97;
	// algumas funções não podem ser executadas no construtor daquela classe (pois jogo ainda possui tipo incompleto), por isso inicializamos aqui
	principal.inicializar(opcoesPrincipais, L"Algoritmos e C++ (2015/1) - Professor Pinho Marson", fundosPrincipal[fundoMaisBom], "somfundo_MenuPrincipal", { xCabecalho, yCabecalho });

	// inicializar menu de seleção de tipo de jogo
	vector<wstring> textoSecundario = { L"Halterofilismo (campanha)", L"Halterofilismo (sandbox)", \
		/* talvez no GB //L"Tiro (campanha)", L"Tiro (sandbox)",*/ L"Voltar" };
	secundario.inicializar(textoSecundario, L"", "fundo_MenuPrincipal04");

	// inicializar menu de créditos
	vector<wstring> opcoesSecundarias = { L"Halterofilismo (Campanha)", L"Halterofilismo (Sandbox)", L"Tiro (Campanha)", L"Tiro (Sandbox)", L"Voltar" };
	vector<wstring> opcoesCreditos = { L"TGA - The Game é um jogo sério, muito sério;\n mas não deve ser levado muito a sério, \
	já que é um jogo.\n\nCriado por Jean Lucca, Mattheus Menezes, Morris.\nSão Leopoldo, abril de 2015." };
	wstring cabecalhoCreditos = L"Aperte [ENTER], [ESPAÇO] ou clique com o botão esquerdo para voltar.";
	creditos.inicializar(opcoesCreditos, cabecalhoCreditos, "fundo_MenuCreditos", "somfundo_MenuCreditos");
	
	// inicializar menu de ajuda
	vector<wstring> textoAjuda = { L"blablabla\n\n\nParabéns! Você está pronto para ir para a próxima página!", \
		L"Halterofilismo\nPressione alternadamente as teclas W,S e Cima,Baixo.\nFaça isso o mais rápido que puder.\n\nO objetivo é completar o levantamento dentro do tempo.\n \
		No entanto algumas dificuldades podem surgir.",
		L"Significato de algumas palavras (1 de 2)\n\nAulista = frequenta aulas, Bulista = copiador de bulas,\nSelista = colecionador de selos, Biblista = versado na Bíblia,\n\
		 		Coralista = parte de coro, Violista = tocador de viola,\nGaulista = partidário do gaulismo",
		L"Significato de algumas palavras (2 de 2)\n\naneiro = inconstante, boeiro = tipo de pássaro,\n\
		geeiro = que traz geada,\n\
		nieiro = lugar onde a galinha vai pôr os ovos,\n\
		oveiro = vendedor de ovos, rueiro = gosta de andar na rua,\n\
		useiro = reincidente em algum comportamento\n\
		agosteiro = nascido em agosto,\n\
		capeiro = que leva capa em procissões de igreja\n\
		dureiro = Que sofre prisão de ventre\n\
		fateiro = vendedor de miúdos de gado, fiteiro = vendedor de fitas\n\
		foreiro = pagador de foro, guieiro = que serve de guia\n\
		sineiro = que toca os sinos,\n\
		assadeiro = próprio para ser assado"
	};
	wstring cabecalhoAjuda = L"Aperte W ou [CIMA] para prosseguir,\nou aperte [ENTER], [ESPAÇO] ou clique esquerdo para voltar.";
	// TODO: a classe menu precisa de uma forma de desativar a seleção com o mouse, e de setar a cor do cabeçalho
	// { 0 } significa que queremos a cor padrão
	ajuda.inicializar(textoAjuda, cabecalhoAjuda, "fundo_MenuAjuda", "somfundo_MenuAjuda", { 0 }, 0, -1, -1, 0, 0, { 0, 0, 0, 0 }, { 51, 0, 151, 255 }, { 51, 255, 177, 255 }, false);

	// inicializar menu de opções
	wstring textoCabecalhoOpcoes = L"Pressione [CIMA] ou [BAIXO], ou [W] ou [S], ou passe o mouse, para mudar a opção destacada.\n\
	Pressione <- e ->, ou passe o mouse para alterar os valores da opção destacada.\n\
	\nPressione [ESPAÇO] para voltar. Todas os valores destacades serão armazenados.";
	vector<wstring> textoOpcoes = { L"Nível de dificuldade:", // [0]
		L"Desativar eventos aleatórios:",	// [1]
		L"Desativar desafios:", // [2]
		L"Desativar som:", // [3]
		L"Desativar musicas:", // [4]
		L"Pular história:", // [5]
	};
	int sizeTextoOpcoes = textoOpcoes.size();
	vector<vector<wstring>> stringsValores;
	stringsValores.resize(sizeTextoOpcoes);
	// inicializar valores para cada nível de opção
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
		case 4: // variáveis possíveis para a opção [2] do textoOpcoes
			stringsValores[nivel] = { L"Não", L"Sim" }; // opções para [4] (desativar musicas)
			break;
		case 5: // variáveis possíveis para a opção [2] do textoOpcoes
			stringsValores[nivel] = { L"Não", L"Sim" }; // opções para [5] (pular história)
			break;
		}
	}
	opcoes.inicializar(textoOpcoes, stringsValores, textoCabecalhoOpcoes, "fundo_MenuOpcoes", "somfundo_MenuOpcoes", { 0 }, 0, { 0 }, -1, -1, 0, 27, 550, -1, 21, 0, 1, 0, { 91, 101, 11, 255 }, 
		{ 255, 51, 101, 255 }, { 91, 101, 11, 255 }, { 255, 51, 101, 255 }, { 255, 51, 101, 255 }, true, "fonteNormalSombra");

	vector<wstring> textoInstantaneo = { L"Continuar o jogo", L"Sair do jogo" };
	instantaneo.inicializar(textoInstantaneo, L"", "");
	instantaneo.setEsmaecer(true);
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
	// antes de iniciar o jogo fazemos nossa intro estilosa
	//	detalhe que isso tá errado, era pra ser orientado a objeto, mas quem ia explicar as refs?
	// TODO: abrir menu ao apertar esc (Continuar Jogo, Voltar ao Menu Principal, Fechar Jogo), talvez permitir mudar opções durante o jogo tb

	// começar a tocar música do menu principal
	principal.tocarMusica();
	while (!aplicacao.sair) {
		uniIniciarFrame();

		//	Seu cigo vem aqui!
		//	...
		gerenciarEstado();	// gerenciar menus e modos de jogo

		if (teclado.soltou[TECLA_ESC]) {	// se a tecla esc foi pressionada
			if (estado == jogoHalterofilismoSandbox || estado == jogoHalterofilismoCampanha) {	// no meio do jogo, abrir menu instaneo
				if (menuInstantaneoAtivo == true) {	// e o menu instantâneo já estiver ativado
					menuInstantaneoAtivo = false;	// desativá-lo
					halterofilia.prosseguir();		// e despausar o jogo
				}
				else {								// do contrário
					menuInstantaneoAtivo = true;	// ativá-lo
					halterofilia.pausar();			// e pausar o jogo
				}
			}
			else if (estado == menuPrincipal) {	// esc no menu principal ainda deve sair
				aplicacao.sair = true;	// facilidade da libUnicornio
			}
		}
		if (menuInstantaneoAtivo) {	// se o menu instantâneo estiver ativo
			instantaneo.desenhar();	// desenhá-lo
			if (instantaneo.finalizado())	// se uma escolha tiver sido feita
				gerenciarMenuInstantaneo();	// gerenciar escolhas
		}

		uniTerminarFrame();
	}
}

void Jogo::gerenciarEstado()
{
	switch (estado) {
		case menuPrincipal:
			principal.desenhar();	// desenhar o menu? a verdade é que o menu se desenha sozinho! haha, piada idiota.
			if (principal.finalizado()) {	// verificar se o jogador fez uma escolha
				opcoesDeJogo = opcoes.getValores();	// melhor pegar a mais, do que a menos
				gerenciarMenuPrincipal();
			}
			break;
		case menuJogos:
			secundario.desenhar();	// desenhar o menu? a verdade é que o menu se desenha sozinho! haha, piada idiota.
			if (secundario.finalizado()) {	// verificar se o jogador decidiu
				gerenciarMenuSecundario();
			}
			break;
		case menuOpcoes:
			opcoes.desenhar();	// desenhar o menu? a verdade é que o menu se desenha sozinho! haha, piada idiota.
			if (opcoes.finalizado()) {	// verificar se o jogador decidiu voltar
				principal.resetarMenu();
				opcoes.resetarMenu();
				estado = menuPrincipal;
				principal.tocarMusica();
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
		case jogoHalterofilismoCampanha:
			halterofilia.campanha();
			break;
		case jogoHalterofilismoSandbox:
			halterofilia.sandbox();
			break;
	}
}

void Jogo::gerenciarMenuPrincipal()
{
	int opcaoEscolhida = principal.getOpcao(); // ober opção escolhida
	// resetar estado do menu principal (se não ele não desenha)
	principal.resetarMenu();

	// mudar estado do jogo, ou sair
	switch (opcaoEscolhida) {
	case escolhaJogar:
		estado = menuJogos;
		secundario.tocarMusica();
		break;
	case escolhaAjuda:
		estado = menuAjuda;
		ajuda.tocarMusica();
		break;
	case escolhaOpcoes:
		estado = menuOpcoes;
		opcoes.tocarMusica();
		break;
	case escolhaCreditos:
		estado = menuCreditos;
		creditos.tocarMusica();
		break;
	case escolhaSair:
		aplicacao.sair = true;	// facilidade da libUnicornio
		break;
	}
}

void Jogo::gerenciarMenuSecundario()
{
	int opcaoEscolhida = secundario.getOpcao(); // ober opção escolhida
	// resetar estado do menu principal (se não ele não desenha mais)
	principal.resetarMenu();

	// mudar estado do jogo, ou sair
	switch (opcaoEscolhida) {
	case escolhaHalterCampanha:
		estado = jogoHalterofilismoCampanha;
		halterofilia.inicializar(estado, opcoesDeJogo);
		halterofilia.preparaCampanha();
		break;
	case escolhaHalterSandbox:
		estado = jogoHalterofilismoSandbox;
		halterofilia.inicializar(estado, opcoesDeJogo);
		halterofilia.preparaSandbox();
		break;
	default:
		estado = menuPrincipal;
		principal.tocarMusica();
		break;
	}

	// resetar menu secundário (se não ele não desenha mais)
	secundario.resetarMenu();
}

void Jogo::gerenciarMenuInstantaneo()
{
	int opcaoEscolhida = instantaneo.getOpcao(); // ober opção escolhida
	// resetar estado do menu principal (se não ele não desenha)
	principal.resetarMenu();

	// mudar estado do jogo, ou sair
	switch (opcaoEscolhida) {
	case escolhaContinuarJogo:
		instantaneo.resetarMenu();
		menuInstantaneoAtivo = false;	// desativar menu instantaneo
		halterofilia.prosseguir();	// e despausar o jogo
		break;
	case escolhaSairDoJogo:
		aplicacao.sair = true;	// facilidade da libUnicornio
		break;
	}
}
