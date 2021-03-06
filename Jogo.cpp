﻿#include "Jogo.h"
#include "Temporizador.h"

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
	// sons da historia
	recursos.carregarAudio("somfundo_HalterFazenda", "audio/somfundo/somfundo_HalterFazenda.ogg");
	recursos.carregarAudio("somfundo_HalterEsgoto", "audio/somfundo/somfundo_HalterEsgoto.ogg");
	recursos.carregarAudio("somfundo_HalterCanil", "audio/somfundo/somfundo_HalterCanil.ogg");
	recursos.carregarAudio("somfundo_HalterAcademiaSuburbio", "audio/somfundo/somfundo_HalterAcademiaSuburbio.ogg");
	recursos.carregarAudio("somfundo_HalterAcademiaCentro", "audio/somfundo/somfundo_HalterAcademiaCentro.ogg");
	recursos.carregarAudio("somfundo_HalterOlimpiadas", "audio/somfundo/somfundo_HalterOlimpiadas.ogg");
	recursos.carregarAudio("somfx_Intro", "audio/somfx/somfx_Intro.ogg");
	recursos.carregarAudio("somfx_BebeChorando", "audio/somfx/somfx_BebeChorando.ogg");
	recursos.carregarAudio("somfx_GrunhidosBolaBilhar", "audio/somfx/somfx_GrunhidosBolaBilhar.ogg");
	recursos.carregarAudio("somfx_GrunhidosBolaBilharMulher", "audio/somfx/somfx_GrunhidosBolaBilharMulher.ogg");
	recursos.carregarAudio("somfx_CavaloDoido", "audio/somfx/somfx_CavaloDoido.ogg");
	recursos.carregarAudio("somfx_CarroLigando", "audio/somfx/somfx_CarroLigando.ogg");
	recursos.carregarAudio("somfx_Ovelhas", "audio/somfx/somfx_Ovelhas.ogg");
	recursos.carregarAudio("somfx_Enxame", "audio/somfx/somfx_Enxame.ogg");
	recursos.carregarAudio("somfx_Trovao", "audio/somfx/somfx_Trovao.ogg");
	recursos.carregarAudio("somfx_Espirro", "audio/somfx/somfx_Espirro.ogg");
	recursos.carregarAudio("somfx_OssosQuebrando", "audio/somfx/somfx_OssosQuebrando.ogg");
	recursos.carregarAudio("somfx_VozNoRadio", "audio/somfx/somfx_VozNoRadio.ogg");
	// efeitos sonoros do jogo
	recursos.carregarAudio("somfx_HalterImpossivelDuranteMulher", "audio/somfx/somfx_HalterImpossivelDuranteMulher.ogg");
	recursos.carregarAudio("somfx_HalterTodosDesafiosMorte", "audio/somfx/somfx_HalterTodosDesafiosMorte.ogg");
	recursos.carregarAudio("somfx_HalterMoscaVindo", "audio/somfx/somfx_HalterMoscaVindo.ogg");
	recursos.carregarAudio("somfx_HalterTodasNaoDesafioMorte", "audio/somfx/somfx_HalterTodasNaoDesafioMorte.ogg");
	recursos.carregarAudio("somfx_HalterPombosVindo", "audio/somfx/somfx_HalterPombosVindo.ogg");
	recursos.carregarAudio("somfx_HalterEspantarPragas", "audio/somfx/somfx_HalterEspantarPragas.ogg");
	recursos.carregarAudio("somfx_HalterDesafioImpossivelSucesso", "audio/somfx/somfx_HalterDesafioImpossivelSucesso.ogg");
	recursos.carregarAudio("somfx_HalterImpossivelSucesso", "audio/somfx/somfx_HalterImpossivelSucesso.ogg");
	recursos.carregarAudio("somfx_HalterMedioSucesso", "audio/somfx/somfx_HalterMedioSucesso.ogg");
	recursos.carregarAudio("somfx_HalterDesafioImpossivelMorte", "audio/somfx/somfx_HalterDesafioImpossivelMorte.ogg");
	recursos.carregarAudio("somfx_HalterDesafioMorte", "audio/somfx/somfx_HalterDesafioMorte.ogg");
	recursos.carregarAudio("somfx_HalterImpossivelMorte", "audio/somfx/somfx_HalterImpossivelMorte.ogg");
	recursos.carregarAudio("somfx_HalterMedioMorte", "audio/somfx/somfx_HalterMedioMorte.ogg");
	recursos.carregarAudio("somfx_HalterImpossivelDurante", "audio/somfx/somfx_HalterImpossivelDurante.ogg");
	recursos.carregarAudio("somfx_HalterDesafioDurante", "audio/somfx/somfx_HalterDesafioDurante.ogg");
	recursos.carregarAudio("somfx_HalterDesafioDuranteMulher", "audio/somfx/somfx_HalterDesafioDuranteMulher.ogg");
	recursos.carregarAudio("somfx_HalterDificilDurante", "audio/somfx/somfx_HalterDificilDurante.ogg");
	recursos.carregarAudio("somfx_HalterMedioDurante", "audio/somfx/somfx_HalterMedioDurante.ogg");
	recursos.carregarAudio("somfx_HalterAssovio1", "audio/somfx/somfx_HalterAssovio1.ogg");
	recursos.carregarAudio("somfx_HalterAssovio2", "audio/somfx/somfx_HalterAssovio2.ogg");
	recursos.carregarAudio("somfx_HalterAssovio3", "audio/somfx/somfx_HalterAssovio3.ogg");
	recursos.carregarAudio("somfx_HalterAssovio4", "audio/somfx/somfx_HalterAssovio4.ogg");
	recursos.carregarAudio("somfx_HalterAssovio5", "audio/somfx/somfx_HalterAssovio5.ogg");
	recursos.carregarAudio("somfx_HalterAssovio6", "audio/somfx/somfx_HalterAssovio6.ogg");
	recursos.carregarAudio("somfx_HalterSoluco", "audio/somfx/somfx_HalterSoluco.ogg");
	recursos.carregarAudio("somfx_HalterFinaleFogosArtificio", "audio/somfx/somfx_HalterFinaleFogosArtificio.ogg");
	// menus
	recursos.carregarAudio("somfx_MenuInstantaneo", "audio/somfx/somfx_MenuInstantaneo.ogg");
	recursos.carregarAudio("somfundo_MenuPrincipal", "audio/music_02_Menu.ogg");
	recursos.carregarAudio("somfundo_MenuOpcoes", "audio/music_03_Opcoes.ogg");
	recursos.carregarAudio("somfundo_MenuAjuda", "audio/music_04_Ajuda.ogg");
	recursos.carregarAudio("somfundo_MenuCreditos", "audio/music_05_Creditos.ogg");
	recursos.carregarAudio("somfundo_MenuFinale", "audio/music_0X_ending.ogg");
	// sprites
	recursos.carregarSpriteSheet("fx_Esmaecer", "img/fx/fx_esmaecer.png", 1, 100);
	recursos.carregarSpriteSheet("fx_Dot", "img/fx/fx_Dot.png", 1, 1);
	recursos.carregarSpriteSheet("fundo_teste", "img/fundos/fundo_teste.jpg");
	recursos.carregarSpriteSheet("fx_IntroBunsOfSteel", "img/fx/fx_IntroBunsOfSteel.png", 0, 6);
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
	recursos.carregarSpriteSheet("fundo_HalterMenuSandbox", "img/fundos/fundo_HalterMenuSandbox.png");
	// halterofilismo
	recursos.carregarSpriteSheet("fundo_Halter01", "img/fundos/halter_01.png");
	recursos.carregarSpriteSheet("fx_Letras", "img/fx/fx_Letras.png", 1, 30);
	recursos.carregarSpriteSheet("fx_LetrasIluminadas", "img/fx/fx_LetrasIluminadas.png", 1, 30);
	recursos.carregarSpriteSheet("per_HalterHomem0", "img/per/per_HalterHomem0.png", 0, 13);
	recursos.carregarSpriteSheet("per_HalterMulher", "img/per/per_HalterMulher.png", 0, 15);
	recursos.carregarSpriteSheet("per_HalterMosca", "img/per/per_HalterMosca.png");
	recursos.carregarSpriteSheet("per_HalterPombo", "img/per/per_HalterPombo.png", 0, 4);
	recursos.carregarSpriteSheet("fundo_HalterFazenda", "img/fundos/fundo_HalterFazenda.png");
	recursos.carregarSpriteSheet("fundo_HalterEsgoto", "img/fundos/fundo_HalterEsgoto.png");
	recursos.carregarSpriteSheet("fundo_HalterCanil", "img/fundos/fundo_HalterCanil.png");
	recursos.carregarSpriteSheet("fundo_HalterAcademiaSuburbio", "img/fundos/fundo_HalterAcademiaSuburbio.png");
	recursos.carregarSpriteSheet("fundo_HalterAcademiaCentro", "img/fundos/fundo_HalterAcademiaCentro.png");
	recursos.carregarSpriteSheet("fundo_HalterMenuFalha", "img/fundos/fundo_HalterMenuFalha.png");
	recursos.carregarSpriteSheet("fundo_HalterMenuVitoria", "img/fundos/fundo_HalterMenuVitoria.png");
	recursos.carregarSpriteSheet("fundo_HalterFinale", "img/fundos/fundo_HalterFinale.png");
	recursos.carregarSpriteSheet("fundo_HalterEtapaFazenda", "img/fundos/fundo_HalterEtapaFazenda.png");
	recursos.carregarSpriteSheet("fundo_HalterEtapaEsgoto", "img/fundos/fundo_HalterEtapaEsgoto.png");
	recursos.carregarSpriteSheet("fundo_HalterEtapaCanil", "img/fundos/fundo_HalterEtapaCanil.png");
	recursos.carregarSpriteSheet("fundo_HalterEtapaAcademiaSub", "img/fundos/fundo_HalterEtapaAcademiaSub.png");
	recursos.carregarSpriteSheet("fundo_HalterEtapaAcademiaCentro", "img/fundos/fundo_HalterEtapaAcademiaCentro.png");
	recursos.carregarSpriteSheet("fundo_HalterEtapaConclusao", "img/fundos/fundo_HalterEtapaConclusao.png");
	//recursos.carregarSpriteSheet("per_HalterPomba", "img/per/per_HalterPomba.png");
	recursos.carregarSpriteSheet("fx_HalterBarra", "img/fx/fx_HalterBar.png", 1, 11);

	int xCentro = janela.getLargura() * .5;
	int yCentro = janela.getAltura() * .5;

	//********* MENUS
	// inicializar menu principal
	vector<string> fundosPrincipal = { "fundo_MenuPrincipal01", "fundo_MenuPrincipal02", "fundo_MenuPrincipal03", /*"fundo_MenuPrincipal04",*/ "fundo_MenuPrincipal05" };
	int fundoMaisBom = rand() % fundosPrincipal.size();
	vector<wstring> opcoesPrincipais = { L"Iniciar Jogo", L"Opções", L"Ajuda", L"Créditos", L"Sair" };
	int xCabecalho = xCentro;
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
	já que é um jogo.\n\nCriado por Jean Luca, Mattheus Menezes, Morris.\nSão Leopoldo, abril de 2015." };
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
	wstring cabecalhoAjuda = L"Aperte S ou [BAIXO] para prosseguir,\nou aperte [ENTER], [ESPAÇO] ou clique esquerdo para voltar.";
	// TODO: a classe menu precisa de uma forma de desativar a seleção com o mouse, e de setar a cor do cabeçalho
	// { 0 } significa que queremos a cor padrão
	ajuda.inicializar(textoAjuda, cabecalhoAjuda, "fundo_MenuAjuda", "somfundo_MenuAjuda", { 0 }, 0, -1, -1, 0, 0, { 0, 0, 0, 0 }, { 51, 0, 151, 255 }, { 51, 255, 177, 255 }, false);

	// inicializar menu de opções
	wstring textoCabecalhoOpcoes = L"Pressione [CIMA] ou [BAIXO], ou [W] ou [S], ou passe o mouse, para mudar a opção destacada.\n\
	Pressione <- e ->, ou passe o mouse para alterar os valores da opção destacada.\n\
	\nPressione [ESPAÇO] para voltar. Todas os valores destacades serão armazenados.";
	vector<wstring> textoOpcoes = { L"Nível de dificuldade:", // [0]
		L"Desativar pragas aladas:",	// [1]
		L"Desativar desafios:", // [2]
		L"Desativar som:", // [3]
		L"Desativar musicas:", // [4]
		L"Pular história:", // [5]
		L"Sexo do personagem:", // [6]
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
		case 3: // variáveis possíveis para a opção [3] do textoOpcoes
			stringsValores[nivel] = { L"Não", L"Sim" }; // opções para [3] (desativar som)
			break;
		case 4: // variáveis possíveis para a opção [4] do textoOpcoes
			stringsValores[nivel] = { L"Não", L"Sim" }; // opções para [4] (desativar musicas)
			break;
		case 5: // variáveis possíveis para a opção [5] do textoOpcoes
			stringsValores[nivel] = { L"Não", L"Sim" }; // opções para [5] (pular história)
			break;
		case 6: // variáveis possíveis para a opção [6] do textoOpcoes
			stringsValores[nivel] = { L"Homem", L"Mulher" }; // opções para [6] (sexo do personagem)
			break;
		}
	}
	opcoes.inicializar(textoOpcoes, stringsValores, textoCabecalhoOpcoes, "fundo_MenuOpcoes", "somfundo_MenuOpcoes", { 0 }, 0, { 0 }, -1, -1, 0, 27, 550, -1, 21, 0, 1, 0, { 91, 101, 11, 255 }, 
	{ 255, 51, 101, 255 }, { 255, 51, 101, 255 }, { 91, 101, 11, 255 }, { 255, 51, 101, 255 }, true, "fonteNormalSombra");

	vector<wstring> textoInstantaneo = { L"Continuar o jogo", L"Sair do jogo" };
	instantaneo.inicializar(textoInstantaneo, L"", "");
	instantaneo.setEsmaecer(true);

	// menus de modo jogo
	wstring textoCabecalhoSandbox = L"Escolha o mapa desejado\n\nPressione [CIMA] ou [BAIXO] ou passe o mouse para mudar a seleção.\n\
											\nPressione [ENTER] para iniciar o jogo com a opção destacada, ou voltar para voltar ao menu anterior.";
	vector<wstring> textoOpcoesSandbox = { L"Aleatório", // [0]
		L"Fazenda",	// [1]
		L"Esgoto", // [2]
		L"Canil", // [3]
		L"Academia no Suburbio", // [4]
		L"Academia no Centro", // [5]
		L"Olimpiadas", // [6]
		L"Voltar", // [7]
	};
	menuSandbox.inicializar(textoOpcoesSandbox, textoCabecalhoSandbox, "fundo_HalterMenuSandbox", "somfundo_MenuPrincipal", { xCentro, (int)(yCentro*.3) }, 0, xCentro, (int)(yCentro), 0, 31, {}, {}, {}, true, "fonteNormalSombra");
	
	// menu de vitoria campanha
	wstring textoCabecalhoVitoria = L"Parabéns, você ganhou!\nEscolha a opção desejada\n\nPressione [CIMA] ou [BAIXO] ou passe o mouse para mudar a seleção.\n\
		\nPressione [ENTER] para iniciar o jogo com a opção destacada ou Menu Principal para voltar ao menu.";
	vector<wstring> textoOpcoesVitoria = { L"Continuar", // [0]
		L"Menu Principal", // [1]
		L"Sair do jogo", // [2]
	};
	menuVitoria.inicializar(textoOpcoesVitoria, textoCabecalhoVitoria, "fundo_HalterMenuVitoria", "", { xCentro, (int)(yCentro*.3) }, 0, xCentro, (int)(yCentro), 0, 31, {}, {}, {}, true, "fonteNormalSombra");

	// menu de derrota campanha
	wstring textoCabecalhoDerrota = L"Você perdeu!\nEscolha a opção desejada\n\nPressione [CIMA] ou [BAIXO] ou passe o mouse para mudar a seleção.\n\
		\nPressione [ENTER] para iniciar o jogo com a opção destacada ou Menu Principal para voltar ao menu.";
	vector<wstring> textoOpcoesDerrota = { L"Repetir", // [0]
		L"Menu Principal", // [1]
		L"Sair do jogo", // [2]
	};
	menuDerrota.inicializar(textoOpcoesDerrota, textoCabecalhoDerrota, "fundo_HalterMenuFalha", "", { xCentro, (int)(yCentro*.3) }, 0, xCentro, (int)(yCentro), 0, 31, {}, {}, {}, true, "fonteNormalSombra");

	// menu de vitoria sandbox
	wstring textoCabecalhoVitoriaSandbox = L"Parabéns, você ganhou!\nEscolha a opção desejada\n\nPressione [CIMA] ou [BAIXO] ou passe o mouse para mudar a seleção.\n\
		\nPressione [ENTER] para iniciar o jogo com a opção destacada ou Menu Principal para voltar ao menu.";
	vector<wstring> textoOpcoesVitoriaSandbox = { L"Continuar", // [0]
		L"Menu Principal", // [1]
		L"Sair do jogo", // [2]
	};
	menuVitoriaSandbox.inicializar(textoOpcoesVitoriaSandbox, textoCabecalhoVitoriaSandbox, "fundo_HalterMenuVitoria", "", { xCentro, (int)(yCentro*.3) }, 0, xCentro, (int)(yCentro), 0, 31, {}, {}, {}, true, "fonteNormalSombra");

	// menu de derrota sandbox
	wstring textoCabecalhoDerrotaSandbox = L"Você perdeu!\nEscolha a opção desejada\n\n[CIMA] ou [BAIXO] ou passe o mouse para mudar a seleção.\n\
		\nPressione [ENTER] para iniciar o jogo com a opção destacada ou Menu Principal para voltar ao menu.";
	vector<wstring> textoOpcoesDerrotaSandbox = { L"Recomeçar", // [0]
		L"Menu Principal", // [1]
		L"Sair do jogo", // [2]
	};
	menuDerrotaSandbox.inicializar(textoOpcoesDerrotaSandbox, textoCabecalhoDerrotaSandbox, "fundo_HalterMenuFalha", "", { xCentro, (int)(yCentro*.3) }, 0, xCentro, (int)(yCentro), 0, 31, {}, {}, {}, true, "fonteNormalSombra");

	// menu de vitoria rapida
	wstring textoCabecalhoVitoriaRapida = L"Parece que esta partida não o desafio o suficiente, deseja tentar o Desafio ( Não elimina)\nEscolha a opção desejada\n\nPressione [CIMA] ou [BAIXO] ou passe o mouse para mudar a seleção.\n\
		\nPressione [ENTER] para iniciar o jogo com a opção destacada ou Menu Principal para voltar ao menu.";
	vector<wstring> textoOpcoesVitoriaRapida = { L" Tentar Desafio",
		L"Continuar",
		L"Menu Principal",
		L"Sair do jogo",
	};
	menuVitoriaRapida.inicializar(textoOpcoesVitoriaRapida, textoCabecalhoVitoriaRapida, "fundo_HalterMenuVitoria", "", { xCentro, (int)(yCentro*.3) }, 0, xCentro, (int)(yCentro), 0, 31, {}, {}, {}, true, "fonteNormalSombra");

	// menu de vitoria rapida sandbox
	wstring textoCabecalhoVitoriaRapidaSandbox = L"Parece que esta partida não o desafio o suficiente, deseja tentar o Desafio ( Não elimina)\nEscolha a opção desejada\n\nPressione [CIMA] ou [BAIXO] ou passe o mouse para mudar a seleção.\n\
		\nPressione [ENTER] para iniciar o jogo com a opção destacada ou Menu Principal para voltar ao menu.";
	vector<wstring> textoOpcoesVitoriaRapidaSandbox = { L" Tentar Desafio",
		L"Continuar",
		L"Menu Principal",
		L"Sair do jogo",
	};
	menuVitoriaRapidaSandbox.inicializar(textoOpcoesVitoriaRapidaSandbox, textoCabecalhoVitoriaRapidaSandbox, "fundo_HalterMenuVitoria", "", { xCentro, (int)(yCentro*.3) }, 0, xCentro, (int)(yCentro), 0, 31, {}, {}, {}, true, "fonteNormalSombra");
	
	// menu derrota rapida
	wstring textoCabecalhoDerrotaRapida = L"Você perdeu no Desafio!\nEscolha a opção desejada\n\n[CIMA] ou [BAIXO] ou passe o mouse para mudar a seleção.\n\
		\nPressione [ENTER] para iniciar o jogo com a opção destacada ou Menu Principal para voltar ao menu.";
	vector<wstring> textoOpcoesDerrotaRapida = { L"Continuar", // [0]
		L"Menu Principal", // [1]
		L"Sair do jogo", // [2]
	};
	menuDerrotaRapida.inicializar(textoOpcoesDerrotaRapida, textoCabecalhoDerrotaRapida, "fundo_HalterMenuFalha", "", { xCentro, (int)(yCentro*.3) }, 0, xCentro, (int)(yCentro), 0, 31, {}, {}, {}, true, "fonteNormalSombra");
	
	// menu derrota rapida sandbox
	wstring textoCabecalhoDerrotaRapidaSandbox = L"Você perdeu no Desafio!\nEscolha a opção desejada\n\n[CIMA] ou [BAIXO] ou passe o mouse para mudar a seleção.\n\
		\nPressione [ENTER] para iniciar o jogo com a opção destacada ou Menu Principal para voltar ao menu.";
	vector<wstring> textoOpcoesDerrotaRapidaSandbox = { L"Continuar", // [0]
		L"Menu Principal", // [1]
		L"Sair do jogo", // [2]
	};
	menuDerrotaRapidaSandbox.inicializar(textoOpcoesDerrotaRapidaSandbox, textoCabecalhoDerrotaRapidaSandbox, "fundo_HalterMenuFalha", " ", { xCentro, (int)(yCentro*.3) }, 0, xCentro, (int)(yCentro), 0, 31, {}, {}, {}, true, "fonteNormalSombra");

	// menu finale
	wstring textoCabecalhoMenuFinale = L"Parabéns, você conquistou as dificuldades e venceu o jogo.\nEscolha a opção desejada\n\n[CIMA] ou [BAIXO] ou passe o mouse para mudar a seleção.\n\
			\nPressione [ENTER] para iniciar o jogo com a opção destacada ou Menu Principal para voltar ao menu.";
	vector<wstring> textoOpcoesMenuFinale = { L"Menu Principal",
		L"Sair do jogo",
	};
	menuFinale.inicializar(textoOpcoesMenuFinale, textoCabecalhoMenuFinale, "fundo_HalterFinale", "", { xCentro, (int)(yCentro*.3) }, 0, xCentro, (int)(yCentro), 0, 31, {}, {}, {}, true, "fonteNormalSombra");

	// setar audios
	musicaFinale.setAudio("somfundo_MenuFinale");
	efeitosSonorosFinale.setAudio("somfx_HalterFinaleFogosArtificio");
}

void Jogo::finalizar()
{
	//	O resto da finaliza鈬o vem aqui (provavelmente, em ordem inversa a inicializa鈬o)!
	//	...
	recursos.descarregarTudo();

	uniFinalizar();
}

void Jogo::executar()
{
	// antes de iniciar o jogo fazemos nossa intro estilosa
	Som somIntroIncrivelmenteDemais, somMenuInstaneo;
	Texto maisDemaisAindaSuperTexto;
	maisDemaisAindaSuperTexto.setWstring(L"Buns of Steel 2: A Herança de Família");
	maisDemaisAindaSuperTexto.setCor(14, 99, 254);
	maisDemaisAindaSuperTexto.setFonte("fonteGrandeSombra");

	Sprite sprIntro;
	somMenuInstaneo.setAudio("somfx_MenuInstantaneo");
	sprIntro.setSpriteSheet("fx_IntroBunsOfSteel");
	somIntroIncrivelmenteDemais.setAudio("somfx_Intro");
	somIntroIncrivelmenteDemais.tocar();

	while (somIntroIncrivelmenteDemais.estaTocando()) {
		uniIniciarFrame();
		sprIntro.avancarAnimacao();
		sprIntro.desenhar(janela.getLargura() * .5, janela.getAltura() * .5);
		maisDemaisAindaSuperTexto.desenhar(janela.getLargura() * .5, janela.getAltura() * .11);
		uniTerminarFrame();
	}

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
					if (!opcoesDeJogo[valorDesativarSom]) {	// se o som não estiver desativado
						somMenuInstaneo.tocar();	// tocar efeito sonoro do menu instantâneo
					}
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
				opcoesDeJogo = opcoes.getValores();	// melhor pegar a mais, do que a menos
				opcoes.resetarMenu();
				estado = menuPrincipal;
				if (opcoesDeJogo[valorDesativarMusicas] == 0)
					principal.tocarMusica();
			}
			break;
		case menuAjuda:
			ajuda.desenhar();	// desenhar o menu? a verdade é que o menu se desenha sozinho! haha, piada idiota.
			if (ajuda.finalizado()) {	// verificar se o jogador decidiu voltar
				principal.resetarMenu();
				opcoesDeJogo = opcoes.getValores();
				ajuda.resetarMenu();
				estado = menuPrincipal;
				if (opcoesDeJogo[valorDesativarMusicas] == 0)
					principal.tocarMusica();
			}
			break;
		case menuCreditos:
			creditos.desenhar();	// desenhar o menu? a verdade é que o menu se desenha sozinho! haha, piada idiota.
			if (creditos.finalizado()) {	// verificar se o jogador decidiu voltar
				principal.resetarMenu();
				opcoesDeJogo = opcoes.getValores();
				creditos.resetarMenu();
				estado = menuPrincipal;
				if (opcoesDeJogo[valorDesativarMusicas] == 0)
					principal.tocarMusica();
			}
			break;
		case menuHalterofilismoSandbox:
			menuSandbox.desenhar();
			if (menuSandbox.finalizado()) {	// verificar se o jogador decidiu voltar
				gerenciarMenuSandbox();
			}
			break;
		case jogoHalterofilismoCampanha:
			// checamos do menu mais específico para o menos específico
			if (halterofilia.desenharMenuFinale()) {
				estado = menuFinaleEstado;
				if (!opcoesDeJogo[valorDesativarSom]) {	// se o som estiver ativado
					bool repetir = true;
					efeitosSonorosFinale.tocar(repetir);
				}
				if (!opcoesDeJogo[valorDesativarMusicas]) {	// se a música estiver ativada
					bool repetir = true;
					musicaFinale.tocar(repetir);
				}
			}
			else if (halterofilia.desenharMenuVitoriaRapida()) {
				estado = menuVitoriaRapidaEstado;
			}
			else if (halterofilia.desenharMenuVitoria()) { // exibir o menu de vitoria
				estado = menuVitoriaEstado;
			}
			else if (halterofilia.desenharMenuDerrotaRapida()) {
				estado = menuDerrotaRapidaEstado;
			}
			else if (halterofilia.desenharMenuDerrota()) { // exibir o menu de derrota
				estado = menuDerrotaEstado;
			}
			else
				halterofilia.campanha();
			break;
		case jogoHalterofilismoSandbox:
			// checamos do menu mais específico para o menos específico
			if (halterofilia.desenharMenuVitoriaRapidaSandbox()) {
				estado = menuVitoriaRapidaSandboxEstado;
			}
			else if (halterofilia.desenharMenuVitoriaSandbox()) {
				estado = menuVitoriaSandboxEstado;
			}
			else if (halterofilia.desenharMenuDerrotaRapidaSandbox()) {
				estado = menuDerrotaRapidaSandboxEstado;
			}
			else if (halterofilia.desenharMenuDerrotaSandbox()) {
				estado = menuDerrotaSandboxEstado;
			}
			else 
				halterofilia.sandbox();
			break;
		case menuVitoriaEstado: 
			menuVitoria.desenhar();
			if (menuVitoria.finalizado())
				gerenciarMenuVitoria();
			break;
		case menuDerrotaEstado:
			menuDerrota.desenhar();
			if (menuDerrota.finalizado())
				gerenciarMenuDerrota();
			break;
		case menuVitoriaSandboxEstado:
			menuVitoriaSandbox.desenhar();
			if (menuVitoriaSandbox.finalizado())
				gerenciarMenuVitoriaSandbox();
			break;
		case menuDerrotaSandboxEstado:
			menuDerrotaSandbox.desenhar();
			if (menuDerrotaSandbox.finalizado())
				gerenciarMenuDerrotaSandbox();
			break;
		case menuVitoriaRapidaEstado:
			menuVitoriaRapida.desenhar();
			if (menuVitoriaRapida.finalizado())
				gerenciarMenuVitoriaRapida();
			break;
		case menuVitoriaRapidaSandboxEstado:
			menuVitoriaRapidaSandbox.desenhar();
			if (menuVitoriaRapidaSandbox.finalizado())
				gerenciarMenuVitoriaRapidaSandbox();
			break;
		case menuDerrotaRapidaEstado:
			menuDerrotaRapida.desenhar();
			if (menuDerrotaRapida.finalizado())
				gerenciarMenuDerrotaRapida();
			break;
		case menuDerrotaRapidaSandboxEstado:
			menuDerrotaRapidaSandbox.desenhar();
			if (menuDerrotaRapidaSandbox.finalizado())
				gerenciarMenuDerrotaRapidaSandbox();
			break;
		case menuFinaleEstado:
			menuFinale.desenhar();
			if (menuFinale.finalizado()) {	// a escolha foi feita
				// parar sons
				efeitosSonorosFinale.parar();
				musicaFinale.parar();

				gerenciarMenuFinale();
			}
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
		if (opcoesDeJogo[valorDesativarMusicas] == 0)
			secundario.tocarMusica();
		break;
	case escolhaAjuda:
		estado = menuAjuda;
		if (opcoesDeJogo[valorDesativarMusicas] == 0)
			ajuda.tocarMusica();
		break;
	case escolhaOpcoes:
		estado = menuOpcoes;
		if (opcoesDeJogo[valorDesativarMusicas] == 0)
			opcoes.tocarMusica();
		break;
	case escolhaCreditos:
		estado = menuCreditos;
		if (opcoesDeJogo[valorDesativarMusicas] == 0)
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
		halterofilia.prepararCampanha();
		break;
	case escolhaHalterSandbox:
		estado = menuHalterofilismoSandbox;
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

void Jogo::gerenciarMenuSandbox()
{
	int opcaoEscolhida = menuSandbox.getOpcao(); // obter opção escolhida
	// resetar estado do menu principal (se não ele não desenha)
	menuSandbox.resetarMenu();

	// mudar estado do jogo, ou sair
	switch (opcaoEscolhida) {
	case escolhaVoltar:	// caso a escolha seja voltar ao menu de jogos
		estado = menuJogos;
		secundario.tocarMusica();
		break;
	default:			// as outras opções são mapas
		estado = jogoHalterofilismoSandbox;
		menuSandbox.resetarMenu();
		halterofilia.inicializar(estado, opcoesDeJogo);
		halterofilia.prepararSandbox(opcaoEscolhida);
		break;
	}
}

void Jogo::gerenciarMenuVitoria()
{
	int opcaoEscolhida = menuVitoria.getOpcao(); // obter opção escolhida
	// resetar estado do menu principal (se não ele não desenha)
	menuVitoria.resetarMenu();

	switch (opcaoEscolhida) {
	case escolhaContinuar:
		halterofilia.resetarLevantamento();
		halterofilia.avancarEtapa();
		estado = jogoHalterofilismoCampanha;
		break;
	case escolhaMenuPrincipalVitoria:
		halterofilia.resetarLevantamento();
		estado = menuPrincipal;
		if (opcoesDeJogo[valorDesativarMusicas] == 0)
			principal.tocarMusica();
		break;
	default:
	case escolhaSairMenuVitoria:
		aplicacao.sair = true;
		break;
	}
}

void Jogo::gerenciarMenuDerrota()
{
	int opcaoEscolhida = menuDerrota.getOpcao(); // obter opção escolhida
	// resetar estado do menu principal (se não ele não desenha)
	menuDerrota.resetarMenu();

	switch (opcaoEscolhida) {
	case escolhaRepetir:
		halterofilia.resetarLevantamento();
		halterofilia.ativarRepetir();
		estado = jogoHalterofilismoCampanha;
		break;
	case escolhaMenuPrincipalDerrota:
		halterofilia.resetarLevantamento();
		estado = menuPrincipal;
		if (opcoesDeJogo[valorDesativarMusicas] == 0)
			principal.tocarMusica();
		break;
	default:
	case escolhaSairMenuDerrota:
		aplicacao.sair = true;
		break;
	}

}

void Jogo::gerenciarMenuVitoriaSandbox()
{
	int opcaoEscolhida = menuVitoriaSandbox.getOpcao();// obter opção escolhida
	// resetar estado do menu principal (se não ele não desenha)
	menuVitoriaSandbox.resetarMenu();

	switch (opcaoEscolhida)
	{
	case escolhaContinuarSandbox:
		halterofilia.resetarLevantamento();
		halterofilia.avancarEtapa();
		estado = jogoHalterofilismoSandbox;
		break;
	case escolhaMenuPrincipalVitoriaSandbox:
		halterofilia.resetarLevantamento();
		estado = menuPrincipal;
		if (opcoesDeJogo[valorDesativarMusicas] == 0)
			principal.tocarMusica();
		break;
	default:
	case escolhaSairVitoriaSandbox:
		aplicacao.sair = true;
		break;
	}
}

void Jogo::gerenciarMenuDerrotaSandbox()
{
	int opcaoEscolhida = menuDerrotaSandbox.getOpcao();// obter opção escolhida
	// resetar estado do menu principal (se não ele não desenha)
	menuDerrotaSandbox.resetarMenu();
	switch (opcaoEscolhida)
	{
	case escolhaRecomecarSandbox:
		halterofilia.resetarLevantamento();
		estado = menuHalterofilismoSandbox;
		break;
	case escolhaMenuPrincipalDerrotaSandbox:
		halterofilia.resetarLevantamento();
		estado = menuPrincipal;
		if (opcoesDeJogo[valorDesativarMusicas] == 0)
			principal.tocarMusica();
		break;
	default:
	case escolhaSairDerrotaSandbox:
		aplicacao.sair = true;
		break;
	}
}

void Jogo::gerenciarMenuVitoriaRapida()
{
	int opcoesEscolhidas = menuVitoriaRapida.getOpcao();// obter opção escolhida
	// resetar estado do menu principal (se não ele não desenha)
	menuVitoriaRapida.resetarMenu();
	switch (opcoesEscolhidas)
	{
	case tentarDesafioCampanha:
		halterofilia.resetarLevantamento();
		halterofilia.ativarLevantamentoRapido();
		estado = jogoHalterofilismoCampanha;
		break;
	case escolhaContinuarRapida:
		halterofilia.resetarLevantamento();
		halterofilia.avancarEtapa();
		estado = jogoHalterofilismoCampanha;
		break;
	case escolhaMenuPrincipalVitoriaRapida:
		halterofilia.resetarLevantamento();
		estado = menuPrincipal;
		if (opcoesDeJogo[valorDesativarMusicas] == 0)
			principal.tocarMusica();
		break;
	default:
	case escolhaSairMenuVitoriaRapida:
		aplicacao.sair = true;
		break;
	}
}
void Jogo::gerenciarMenuVitoriaRapidaSandbox()
{
	int opcoesEscolhida = menuVitoriaRapidaSandbox.getOpcao();// obter opção escolhida
	// resetar estado do menu principal (se não ele não desenha)
	menuVitoriaRapidaSandbox.resetarMenu();
	switch (opcoesEscolhida)
	{
	case tentarDesafioSandbox:
		halterofilia.resetarLevantamento();
		halterofilia.ativarLevantamentoRapido();
		estado = jogoHalterofilismoSandbox;
		break;
	case escolhaContinuarRapidaSandbox:
		halterofilia.resetarLevantamento();
		estado = jogoHalterofilismoSandbox;
		break;
	case escolhaMenuPrincipalVitoriaRapidaSandbox:
		halterofilia.resetarLevantamento();
		estado = menuPrincipal;
		if (opcoesDeJogo[valorDesativarMusicas] == 0)
			principal.tocarMusica();
		break;
	default:
	case escolhaSairVitoriaRapidaSandbox:
		aplicacao.sair = true;
		break;
	}
}

void Jogo::gerenciarMenuDerrotaRapida()
{
	int opcoesEscolhidas = menuDerrotaRapida.getOpcao();// obter opção escolhida
	// resetar estado do menu principal (se não ele não desenha)
	menuDerrotaRapida.resetarMenu();
	switch (opcoesEscolhidas)
	{
	case escolhaContinuarDerrotaRapida:
		halterofilia.resetarLevantamento();
		halterofilia.avancarEtapa();
		estado = jogoHalterofilismoCampanha;
		break;
	case escolhaMenuPrincipalDerrotaRapida:
		halterofilia.resetarLevantamento();
		estado = menuPrincipal;
		if (opcoesDeJogo[valorDesativarMusicas] == 0)
			principal.tocarMusica();
		break;
	default:
	case escolhaSairMenuDerrotaRapida:
		aplicacao.sair = true;
		break;
	}
}

void Jogo::gerenciarMenuDerrotaRapidaSandbox()
{
	int opcoesEscolhidas = menuDerrotaRapidaSandbox.getOpcao();// obter opção escolhida
	// resetar estado do menu principal (se não ele não desenha)
	menuDerrotaRapidaSandbox.resetarMenu();
	switch (opcoesEscolhidas)
	{
	case escolhaContinuarDerrotaRapidaSandbox:
		halterofilia.resetarLevantamento();
		estado = jogoHalterofilismoSandbox;
		break;
	case escolhaMenuPrincipalDerrotaRapidaSandbox:
		halterofilia.resetarLevantamento();
		estado = menuPrincipal;
		if (opcoesDeJogo[valorDesativarMusicas] == 0)
			principal.tocarMusica();
		break;
		default:
		case escolhaSairMenuDerrotaRapidaSandbox:
			aplicacao.sair = true;
			break;
	}
}

void Jogo::gerenciarMenuFinale()
{
	int opcoesEscolhidas = menuFinale.getOpcao();// obter opção escolhida
	// resetar estado do menu principal (se não ele não desenha)
	menuFinale.resetarMenu();
	switch (opcoesEscolhidas)
	{
	case escolhaMenuPrincipalFinale:
		halterofilia.resetarLevantamento();
		estado = menuPrincipal;
		if (opcoesDeJogo[valorDesativarMusicas] == 0)
			principal.tocarMusica();
		break;
	default:
	case escolhaSairMenuFinale:
		aplicacao.sair = true;
		break;
	}
}