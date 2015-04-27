#pragma once
#include "libUnicornio.h"
#include <vector>
#include <string>

class Menu
{
	enum EstadoMenu { escolhendo, escolheu };
	enum TipoMenu { unico, duplo };

	Sprite fundo, fundoEsmaecer;
	Som somFundo;

	//vector<wstring> opcoesPrincipais;			// Sabe como é, eu realmente gosto de acentos, mas quem é que vai explicar isso aqui depois?
	vector<Texto> textosMenu;					// objetos Texto das opções do menu
	vector<vector<Texto>> textosMenuValores;	// objetos Texto dos valores do menu
	Texto cabecalho;			// objeto usado para escrever textos simples, como os créditos e ajuda
	vector<wstring> stringsOpcoesMenu;			// vetor com as wstrings (cadeias de caracteres) de cada opção do menu unico
														//	DICA: se o professor perguntar, wstring aceita acentos! (no Windows) (mas a implementação nativa varia por plataforma)
	vector<vector<wstring>> stringValoresMenu;	// vetor que contem vetores, cada um destes correspondendo aos valores possíveis para cada opção do menu duplo
	wstring stringCabecalho;
	wstring textoMenu;						// wstring texto dos créditos
	wstring textoRodapeMenu;			// wstring texto rodape para menus
	string nomeFonte;

	// valores ativos/selecionados
	int ativo;					// opcao ativa na tela (seleção)
	int ativoPadrao = 0;		// opcao de ativo padrao (para poder resetar menu)
	vector<int> valoresAtivos;	// vetor com cada valor ativo do menu opções, e.g. ({0,0,1} == {normal,nao,sim})

	// cores das opções
	vector<int> corDestaque;
	vector<int> corNormal;
	vector<int> corCabecalho;
	vector<int> corDestaqueValores;
	vector<int> corNormalValores;

	// coordenadas de desenho das opções/valores/cabeçalho dos menus
	vector<int> xOpcoesMenu;			// vetores usados para colidir mouse, coordenadas X
	vector<int> yOpcoesMenu;			// vetores usados para colidir mouse, coordenadas Y
	vector<vector<int>> xValoresMenu;	// vetores usados para colidir mouse, coordenadas X
	vector<vector<int>> yValoresMenu;	// vetores usados para colidir mouse, coordenadas Y
	vector<int> xyCabecalho;	// coordenadas para desenhar o cabecalho

	// tamanho dos vetores com as opções dos menus
	vector<int> sizeValoresMenu;	// tamanhos de cada vetor contendo os valores correspondendo a cada opção
	int sizeValores = 0;			// tamanho total de elementos que são valores
	int sizeOpcoesMenu = 0;			// tamanho do vetor com as opções
								//	(pra não ficar chamando size() desnecessariamente, sem usar iteradores...)

	// âncora X e base Y para o fundo e as opções dos menus
	int xCentral, yCentral;
	int xBase, yBase;				// usados nas coordenadas dos objetos texto nos menus principal e secundário
	int xValores, yValores;			// usados nas coordenadas dos objetos texto em menus complexos
	int mouseX, mouseY;				// usados para determinar se o mouse se moveu

	// espaçamentos hotizontal e vertical ( x|y = base + (numero da opcao * espacamento) )
	int espacamentoOpcoesX = 27;		// espaçamento entre cada opção dos menus (valor totalmente arbritrário)
	int espacamentoOpcoesY = 0;		// espaçamento entre cada opção dos menus (valor totalmente arbritrário)
	int espacamentoValoresX = 71;		// espaçamento entre cada opção do menu de opções (valor totalmente arbritrário)
	int espacamentoValoresY = 0;		// espaçamento entre cada opção do menu de opções (valor totalmente arbritrário)
	int espacamentoValoresOpcoesX = 105;	// espaçamento entre cada valor do menu de opções (valor totalmente arbritrário)
	int espacamentoValoresOpcoesY = 0;	// espaçamento entre cada valor do menu de opções (valor totalmente arbritrário)

	EstadoMenu estadoInterno = escolhendo;	// valor retornado pela função escolheu(), especifica se o menu atual cumpriu sua função e deve terminar
	TipoMenu tipoMenu;						// usado para desenhar o menu corretamente

	bool possuiCabecalho = false;			// para não chamar desenhar() sem necessidade
	bool menuDuplo = false;					// para não chamar desenhar() sem necessidade
	bool mouseAtivo = true;
	bool mouseMoveu = false;
	bool possuiSomFundo = false;
	bool possuiFundo = false;
	bool esmaecerFundo = false;

	// tantos vais não-genéricos poderiam ser evitados, mas quem explicaria tal coisa?
	void vaiOpcao();
	void vaiIndice(int i);
	void vaiIndiceValor(int nivel, int elemento);
	void vaiCima();
	void vaiBaixo();
	void vaiDireita();
	void vaiEsquerda();
	void vaiTopo();
	void vaiBase();
	bool mouseSeMoveu();
	bool mouseSobre(Texto objetoTexto, int x, int y);
	void destacar(int i);
	void esmaecer(int i);
	void destacarValor(int nivel, int elemento);
	void esmaecerValor(int nivel, int elemento);

public:
	Menu();
	~Menu();
	void desenhar();
	// inicializar para menu único iniciado de uma origem
	void inicializar(vector<wstring> vetorOpcoes, wstring cabecalhoParam = L"", string fundilho = "fundo_MenuPrincipal01", string som = "", \
		vector<int> cabecalhoXY = { 0 }, int selecaoPadrao = 0, int origemX = -1, int origemY = -1, int xEspacamento = 0, int yEspacamento = 31, \
		vector<int> corNormalParam = { 0 }, vector<int> corDestaqueParam = { 0 }, vector<int> corCabecalhoParam = { 0 }, bool mouse = true, \
		string fonte = "fonteGrandeSombra", float espacoLinhas = 1.5f, int alinhamento = TEXTO_CENTRALIZADO, bool esmaecer = false);
	// inicializar (sobrecarregada/overloaded) para menu único com coordenadas x e y para cada elemento
	// inicializar (sobrecarregada/overloaded) para menu duplo desenhado de uma origem
	void inicializar(vector<wstring> vetorOpcoes, vector<vector<wstring>> vetorValores, wstring cabecalhoParam = L"", string fundilho = "fundo_MenuPrincipal01", \
		string som = "", vector<int> cabecalhoXY = { 0 }, int selecaoPadrao = 0, vector<int> valoresPadrao = { 0 }, int origemX = -1, int origemY = -1, \
		int xEspacamento = 0, int yEspacamento = 27, int origemXValores = -1, int origemYValores = -1, int xEspacamentoValores = 11, int yEspacamentoValores = 0,\
		int xEspacamentoValoresOpcoes = 1, int yEspacamentoValoresOpcoes = 0, vector<int> corNormalParam = { 0 }, vector<int> corDestaqueParam = { 0 }, \
		vector<int> corNormalValoresParam = { 0 }, vector<int> corDestaqueValoresParam = { 0 }, vector<int> corCabecalhoParam = { 0 }, bool mouse = true, \
		string fonte = "fonteNormal", float espacoLinhas = 1.5f, int alinhamento = TEXTO_CENTRALIZADO, bool esmaecer = false);
	// inicializar (sobrecarregada/overloaded) para menu duplo com coordenadas x e y para cada elemento
	void resetarMenu();		// também para somFundo
	void tocarMusica();		// toca a música de fundo do menu (se existir)
	void setEsmaecer(bool opcao);	// altera a função de esmaecer o menu

	vector<int> getValores();
	int getOpcao();
	bool finalizado();
};

