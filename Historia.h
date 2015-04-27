#pragma once
#include "libUnicornio.h"
#include "Temporizador.h"

#include <vector>

using namespace std;	// de novo, já que o MVS parece não entender

class Historia
{
	enum QuandoABandaToca {tocarComecoDaLinha, tocarMeioDaLinha, tocarFinalDaLinha};

	// sprites usadas para elementos, incluindo efeitos
	Sprite sprFundo, sprSobreCamada, sprEsmaecer;
	// elementos que serao desenhados
	vector<vector<Sprite>> sprElementos;	// isso vai ter vários espaços vazios, já que só podemos usar vetores
	vector<vector<int>> elementosXY;		// coordenadas para desenhar as sprites
	vector<Texto> textoLinhas;				// fica mais fácil (pra mim) gerenciar um objeto texto pra cada linha
		// especialmente ao usar ajustarStringParaLargura, pois precisaremos da altura de cada "linha"

	Temporizador tempoPrint, tempoClique;		// controla o intervalo entre cada letra desenhada, e usamos um
												//	intervalo para não detectar cliques de menus anteriores

	vector<vector<wstring>> historiaLinhas;	// a.b.c: a = etapa, b = linha, c = texto
	vector<vector<vector<Som>>> historiaSons;	// a.b.c.d: a = etapa, b = linha, c = quando, d = som
												//	quando = 0 = inicio da linha, 1 = meio da linha, 2 = fim da linha
	vector<vector<vector<bool>>> historiaSonsDefinidos;	// a classe Som retorna endereços inválidos para soms não carregados...
														//	por isso é preciso checar se há som definido por aqui
	vector<Som> historiaSonsDeFundo;	// inicializados no construtor
	vector<int> sizeLinhas;				// armazena o tamanho das linhas da etapaAtual
	vector<int> yLinhas;				// armazena a altura adequada para desenhar cada linha
	vector<bool> linhasDesenhadas;	// armazena as linhas ja desenhadas na etapa atual

	int etapaAtual, linhaAtual, letraAtual, totalEtapas, totalLinhasEtapaAtual;	// para controlar o progresso no desenho
	int xLinhas;			// x não muda em nenhuma linha
	int xCentro, yCentro;	// pra não precisar ficar chamando gets desnecessariamente
public:
	Historia();
	void inicializar (vector<vector<wstring>> historia, string fundo = "", vector<string> sonsDeFundo = {}, vector<vector<vector<string>>> sonsDaHistoria = {}, \
		vector<vector<Sprite>> sprites = {},\
		vector<vector<int>> spritesXY = {});
	~Historia();

	void desenhar(int etapa);	// se etapa != etapaAtual, significa que devemos reiniciar coisas
	bool terminouEtapa();		// se todas as linhas foram desenhadas completamente: retorna true
};

