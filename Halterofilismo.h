﻿#pragma once
#include "libUnicornio.h"
#include "Menu.h"
#include "Temporizador.h"
#include "Historia.h"

#include <ctime>	// deveria ser chrono, mas quem ia explicar isso?

class Halterofilismo
{
	// estado do jogo, valores pretendem ser universais (entre as classes)
	enum EstadoDoJogo {
		menuPrincipal, menuJogos, menuOpcoes, menuAjuda, menuCreditos, menuHalterofilismo, jogoHalterofilismoCampanha, \
		jogoHalterofilismoSandbox, jogoTirofilismoCampanha, jogoTirofilismoSandbox
	};

	// valores do menu de opcoes
	enum ValoresMenuOpcoes { valorDificuldade, valorDesativarEventos, valorDesativarFatality, valorDesativarSom, valorDesativarMusicas, valorDesativarHistoria };
	// tipo de levantamento
	enum TipoDeLevantamento { levantamentoNormal, levantamentoFatality };
	// sprites do proganista
	enum SpritesProtagonista { protagonistaHomem, protagonistaMulher };
	// locais de ataque de pragas
	enum LocaisPragas { direitaBarra, centroBarra, esquerdaBarra, testaProtagonista, ombrosProtagonista };
	// fica mais fácil usar um enum para acessar o frame de cada letra
	enum FramesDasLetrasSprite { letraA, letraB, letraC, letraD, letraE, letraF, letraG, letraH, letraI, letraJ, letraK, letraL, letraM, letraN, letraO, letraP,\
		letraQ, letraR, letraS, letraT, letraU, letraV, letraW, letraX, letraY, letraZ, letraVirgulina };

	// Sprites usadas pela classe
	Sprite fundo, protagonista, barra, barraProgresso;
	vector<Sprite> pragasAladas, letrasAladas;
	// Textos usados pela class
	Texto textoTemporizador, textoTemporizadorSombra;
	Texto textoMensagem, textoAvisoPragas, textoAvisoPragasSombra;
	// Tipo do levantamento sendo feito (normal, fatality)
	TipoDeLevantamento tipo;
	// história do modo campanha
	Historia historiaCampanha;

	// menus de vitória
	Menu vitoriaFatalityAtivo, vitoriaFatalityInativo;
	// menus de derrota
	Menu derrota, derrotaFatality;	// fatality permite continuar

	Temporizador temporizador, tempoDificultar, tempoPragas, tempoAvisoPragas, tempoMovimentoLetras;

	// os vetore abaixo serão usados na combinação (a ser digitada) para espantar as moscas
	vector<string> queriaPalavrasLista;	// formato: queria palavraLista, acabei palavraEiro
	vector<string> acabeiPalavrasEiro;
	string fraseAssovio;					// armazena a frase completa escolhida
	vector<vector<int>> letrasXYOriginal;	// vetor coordenadas XY "âncora" das letras
	vector<vector<int>> letrasXYAtual;		// vetor coordenadas XY com barulho
	vector<bool> letrasAtivadas;			// vetor que informa se a letra foi ativada ou não

	// os vetores abaixo armazenam as coordenadas de âncora da sprite do personagem
	vector<int> coordenadasX;	// vetor coordenadas X pra cada fundo
	vector<int> coordenadasY;	// vetor coordenadas Y pra cada fundo
	float progresso = 0;		// progresso rumo aos _100%_ da "rep"
	vector<int> xyBarraProgresso;			// coordenadas para desenhar a barra de progresso
	vector<vector<int>> xyLinhasObjetivo;	// coordenadas para desenhar as "linhas" objetivo, dependendo do progressoMaximo
	vector<int> opcoesDeJogo;				// como setado no menuOpções
	// tetravetor a.b.c.d: nivel a = sprite, b = testa ou ombros, c = frame, d = x e y (em função da origem da sprite)
	vector<vector<vector<vector<int>>>> xyFinaisSpritesPragas;	// x,y alvos para cada sprite, usado para mover as pragas
	// nível 1 = local da barra (d,c,e), nivel 2 = x,y e rotação (se necessário)
	vector<vector<int>> xyFinaisBarraPragas;	// x,y alvos para cada objetivo, usado para mover as pragas
	vector<vector<int>> xyPragas;	// coordenadas de desenho
	vector<bool>	chegouPraga;	// usado para saber se a praga já está incomodando ou não

	int etapaAtual;		// etapa atual no modo campanha ([0,5])
	int xTemporizador, yTemporizador;							// coordenadas do temporizador
	int cena = 0;			// o fundo a ser utilizado
	int dificuldade;		// define a taxa de espera antes de executar dificultar (internamenta fazemos um n maior resultar em um intervalo menor)
	float fatorDificuldade;	// dificuldade efetica (intervalo da função dificultar())
	int xCentro, yCentro;	// coordenadas do centro da tela
	int xBarra, yBarra;		// a barra possui x,y diferentes ao longo das animações
	int progressoMaximo;	// progresso máximo de um levantamento, pode variar de (0, ..., sizeBarraProgressoFrames - 1)
	int chancePraga;		// chance de uma nova pragaAlada aparecer (aumenta com a dificuldade)

	int sizeBarraProgressoFrames;	// numero de quadros da animação da barra de progresso
	int segundosAvisoPragas = 7;	// por padrão exibimos o aviso por 7s
	bool barraSobe = true;			// agora a barra sobe? ou desce?
	bool primeiraPraga = true;		// melhor explicar como se livrar delas!
	bool avisoPrimeiraPraga = false;	// faz com que o aviso seja mostrado por algum tempo

	EstadoDoJogo estadoDoJogo;

	// preparar modalidades de jogo
	void preparaCampanha();
	void preparaSandbox();

	// utilidades
	int Halterofilismo::traduzLetraFrame(char letra);
	void desenhar();
	void desenharHUD();
	void gerenciarLevantamento();
	void moverBarra();
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

public:
	Halterofilismo();
	~Halterofilismo();

	void inicializar(int estado, vector<int> valoresOpcoesDeJogo);
	// modalidades de jogo
	void campanha();
	void sandbox();
};

