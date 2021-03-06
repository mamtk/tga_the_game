﻿#pragma once
#include "libUnicornio.h"
#include "Temporizador.h"
#include "Historia.h"

#include <ctime>	// deveria ser chrono, mas quem ia explicar isso?

class Halterofilismo
{
	// estado do jogo, valores pretendem ser universais (entre as classes)
	enum EstadoDoJogo {
		menuPrincipal, menuJogos, menuOpcoes, menuAjuda, menuCreditos, menuHalterofilismoSandbox, jogoHalterofilismoCampanha, jogoHalterofilismoSandbox,
		menuVitoriaEstado, menuDerrotaEstado
	};

	// valores do menu de opcoes
	enum ValoresMenuOpcoes { valorDificuldade, valorDesativarPragas, valorDesativarDesafios, valorDesativarSom, valorDesativarMusicas, valorDesativarHistoria, valorSexo };
	enum ValoresSexo { protagonistaHomem, protagonistaMulher };
	// valores do menu sandbox
	enum OpcoesMenuSandbox { escolhaAleatorio, escolhaFazenda, escolhaEsgoto, escolhaCanil, escolhaAcademiaSuburbio, escolhaAcademiaCentro, escolhaOlimpiadas, escolhaVoltar };
	// tipo de levantamento
	enum TipoDeLevantamento { levantamentoNormal, levantamentoFatality };
	// posições de som no vetor de sons da história
	enum QuandoABandaToca { tocarComecoDaLinha, tocarMeioDaLinha, tocarFinalDaLinha };
	// sprites do proganista
	enum SpritesProtagonista { spriteDeHomem, spriteDeMulher };
	// locais de ataque de pragas
	enum LocaisPragas { direitaBarra, centroBarra, esquerdaBarra, testaProtagonista, ombrosProtagonista };
	// fica mais fácil usar um enum para acessar o frame de cada letra
	enum FramesDasLetrasSprite { letraA, letraB, letraC, letraD, letraE, letraF, letraG, letraH, letraI, letraJ, letraK, letraL, letraM, letraN, letraO, letraP,\
		letraQ, letraR, letraS, letraT, letraU, letraV, letraW, letraX, letraY, letraZ, letraVirgulina };
	// fica mais fácil acessar todos os efeitos sonoros com um enum
	enum TodosOsEfeitosSonoros { somfx_HalterImpossivelDuranteMulher, somfx_HalterTodosDesafiosMorte, somfx_HalterMoscaVindo, somfx_HalterTodasNaoDesafioMorte, \
		somfx_HalterPombosVindo, somfx_HalterEspantarPragas, somfx_HalterDesafioImpossivelSucesso, somfx_HalterImpossivelSucesso, somfx_HalterMedioSucesso, \
		somfx_HalterDesafioImpossivelMorte, somfx_HalterDesafioMorte, somfx_HalterImpossivelMorte, somfx_HalterMedioMorte, somfx_HalterImpossivelDurante, \
		somfx_HalterDesafioDurante, somfx_HalterDesafioDuranteMulher, somfx_HalterDificilDurante, somfx_HalterMedioDurante, somfx_HalterAssovio1, somfx_HalterAssovio2, \
		somfx_HalterAssovio3, somfx_HalterAssovio4, somfx_HalterAssovio5, somfx_HalterAssovio6, somfx_HalterSoluco };
	enum TodosOsSonsDeFundo {  };

	// Sprites usadas pela classe
	Sprite fundo, protagonista, barraProgresso;
	vector<Sprite> pragasAladas, letrasAladas;

	vector<Som> sonsEfeitos;			// vetor com os efeitos sonoros usados pela classe
	vector<Som> sonsDeFundo;			// vetor com os sons de fundo
	vector<string> nomesSonsDeFundo;	// vetor com strings contendo o nome dos sons de fundo
	// Textos usados pela class
	Texto textoTemporizador, textoTemporizadorSombra;
	Texto textoMensagem, textoAvisoPragas, textoAvisoPragasSombra;
	// texto do placar máximo e atual
	Texto placarMaximo, placarAtual, placarMaximoSombra, placarAtualSombra;
	// Tipo do levantamento sendo feito (normal, fatality)
	TipoDeLevantamento tipo;
	// história do modo campanha
	Historia historiaCampanha;

	// menus de vitória
	//Menu vitoriaFatalityAtivo, vitoriaFatalityInativo;
	// menus de derrota
	//Menu derrota, derrotaFatality;	// fatality permite continuar

	// temporizadores usados na classe
	Temporizador temporizador, tempoMorte, tempoDificultar, tempoPragas, tempoAvisoPragas, tempoMovimentoLetras;
	Temporizador tempoAssovios, tempoSonsDeLevantamento;		// não queremos sons tocando absolutamente 100% do tempo

	// escolha feita no menuSandbox
	OpcoesMenuSandbox mapaSandbox;

	// os vetores abaixo serão usados na combinação (a ser digitada) para espantar as moscas
	vector<string> queriaPalavrasLista;	// formato: queria palavraLista, acabei palavraEiro
	vector<string> acabeiPalavrasEiro;
	string fraseAssovio;					// armazena a frase completa escolhida
	vector<vector<int>> letrasXYOriginal;	// vetor coordenadas XY "âncora" das letras
	vector<vector<int>> letrasXYAtual;		// vetor coordenadas XY com barulho
	vector<bool> letrasAtivadas;			// vetor que informa se a letra foi ativada ou não

	vector<string> fundos;					// armazena o nome para carregar cada sprite de fundo
	vector<vector<int>> coordenadasXY;		// armazenam as coordenadas x,y da sprite do personagem para cada fundo
	float progresso = 0;					// progresso rumo aos _100%_ da repetição
	vector<int> xyBarraProgresso;			// coordenadas para desenhar a barra de progresso
	vector<vector<int>> xyLinhasObjetivo;	// coordenadas para desenhar as "linhas" objetivo, dependendo do progressoMaximo
	vector<int> opcoesDeJogo;				// como setado no menuOpções
	// vetor a.b.c.d: nivel a = sprite, b = frame, c = x e y (em função da origem da sprite)
	vector<vector<vector<int>>> xyFinaisSpritesPragas;	// Xmin,Ymin,Xmax,Ymax para as pragas para cada sprite, usado para mover as pragas
	vector<vector<int>> xyPragas;	// coordenadas de desenho
	vector<bool> direcaoPragas;	// true = direita; false = esquerda (devido à falsidade do igualitarismo)
	vector<bool> chegouPraga;	// usado para saber se a praga já está incomodando ou não
	vector<bool> etapasDificuldadeAdicionada;


	int xTemporizador, yTemporizador;		// coordenadas do temporizador
	int xPlacarMaximo, yPlacarMaximo, xPlacarAtual, yPlacarAtual;		// coordenadas do placar
	int etapaAtual;			// etapa atual no modo campanha ([0,5])
	int cena;				// cena [0,5], mapa atualizado nas funções sandbox ou campanha
	int dificuldade;		// define a taxa de espera antes de executar dificultar (internamenta fazemos um n maior resultar em um intervalo menor)
	float fatorDificuldade;	// dificuldade efetiva (intervalo da função dificultar())
	int pontuacaoMaxima = 0, pontuacaoAtual = 0;		// pontuações do modo sandbox
	int xCentro, yCentro;	// coordenadas do centro da tela
	int progressoMaximo;	// progresso máximo de um levantamento, pode variar de (0, ..., sizeBarraProgressoFrames - 1)
	int chancePraga;		// chance de uma nova pragaAlada aparecer (aumenta com a dificuldade)

	int sizeBarraProgressoFrames;	// numero de quadros da animação da barra de progresso
	int segundosAvisoPragas = 7;	// por padrão exibimos o aviso por 7s
	bool primeiraPraga = true;		// melhor explicar como se livrar delas!
	bool avisoPrimeiraPraga = false;	// faz com que o aviso seja mostrado por algum tempo
	bool pausado = false;			// registra se o jogo está pausado
	bool estaJogando = false; // registra se esta jogando
	bool terminouLevantamento = false; // se o jogador terminou o levantamento
	bool venceu = false; // registra se venceu
	bool repetirEtapa = false;
	bool repetir = false;
	bool pragasAtivas = true;		// não ativamos as pragas até o segundo mapa na campanha
									//	pois é quando o protagonista recebe seu pingente
	bool espantandoPragas = false;	// ativo enquanto as pragas são espantadas

	EstadoDoJogo estadoDoJogo;

	// utilidades
	int Halterofilismo::traduzLetraFrame(char letra);
	void desenhar();
	void desenharHUD();
	void gerenciarLevantamento();
	void dificultar();
	void pragaAlada();
	void gerenciarPragas();
	void assoviarPalavras();
	void inicializarPalavrasDoPoder();
	void desenharPalavrasDoPoder();
	bool pressionouErrado(char letra);
	bool pressionouCerto(char letra);
	void desativarLetra(int indice);
	void ativarLetra(int indice);
	void limparFrase();
	void ativarEspantarMoscas();
	void desativarEspantarMoscas();
	void mudarFundo(int novoFundo);
	void espantarPragas();
	void atualizarDificuldade();
	void tocarEfeitosDeMorte();
public:
	Halterofilismo();
	~Halterofilismo();

	void inicializar(int estado, vector<int> valoresOpcoesDeJogo);
	// modalidades de jogo
	void campanha();
	void sandbox();
	// preparar modalidades de jogo
	void prepararCampanha();
	void prepararSandbox(int selecaoMapa);
	// des/pausar jogo
	void pausar();
	void prosseguir();

	bool desenharMenuVitoria();
	bool desenharMenuDerrota();

	bool desenharMenuVitoriaSandbox();
	bool desenharMenuDerrotaSandbox();

	bool desenharMenuVitoriaRapida();
	bool desenharMenuDerrotaRapida();

	bool desenharMenuVitoriaRapidaSandbox();
	bool desenharMenuDerrotaRapidaSandbox();

	bool desenharMenuFinale();

	void resetarLevantamento();
	void avancarEtapa();
	void ativarRepetir();
	void ativarJogando();
	void ativarLevantamentoRapido();
};
