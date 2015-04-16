#pragma once
#include "libUnicornio.h"

/***********************************************
PRIMEIRO TERMINA HALTEROFILISMO SANDBOX
DEPOIS TERMINA TIRO SANDBOX,

só então começa a pensar na campanha!
mas o ideal ainda seria terminar os 4 sandbox
e talvez pensar em quais campanhas serão as principais
e dar pista visual no menu secundário, ex. (ROTA PRINCIPAL) e (ROTA REDUZIDA)
************************************************/
class Halterofilismo
{
	Sprite fundo;
	Sprite personagem;
	Sprite barraProgresso;
	// os vetores abaixo armazenam as coordenadas de âncora da sprite do personagem
	std::vector<int> coordenadasX;	// vetor coordenadas X pra nunca mais no jogo precisarmos usar vetor de vetores
	std::vector<int> coordenadasY;	// vetor coordenadas Y pra nunca mais no jogo precisarmos usar vetor de vetores
	float progresso = 0;	// progresso rumo aos _100%_ da "rep"
	int cena = 0;	// o fundo a ser utilizado
	int contadorTeclarA, contadorTeclarB, contadorTeclarMisc;	// conta o intervalo pressionar das teclas
	int dificuldade;	// 0, 1, 2, ..., n (multiplicador no cálculo do intervalo das teclas)
	int xCentro, yCentro;	// coordenadas do centro da tela

	void sandbox();
	void preparaSandbox();
public:
	Halterofilismo();
	~Halterofilismo();

	void desenhar();
	void inicializar();
};

