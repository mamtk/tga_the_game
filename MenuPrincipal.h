#pragma once
#include "libUnicornio.h"
#include <vector>
#include <string>

class MenuPrincipal
{
	enum EstadoMenu { jogar, opcoes, ajuda, creditos, sair, esperando }; // desnecessário usar enums em outro contexto
	enum EstadoMenuSecundario { halterofilismoCampanha, halterofilismoSandbox, tiroCampanha, tiroSandbox, menuzando }; // desnecessário usar enums em outro contexto

	std::vector<Texto> textosMenuPrincipal;	// textos (palavras) das opções do menuPrincipal
	std::vector<Texto> textosMenuSecundario;	// textos (palavras) das opções do menuSecundario (tipos de jogos)
	std::vector<Texto> textosMenuOpcoes;	// textos (opcoes, valores possíveis) das opções do menuPrincipal
	Texto textoHandler;		// objeto usado para escrever textos simples, como os créditos e ajuda
	//std::vector<std::wstring> opcoesPrincipais;	// Sabe como é, eu realmente gosto de acentos, mas quem é que vai explicar isso aqui depois?
	std::vector<std::wstring> opcoesPrincipais;		// vetor com as wstrings (cadeias de caracteres) de cada opção do menu principal;
													//	DICA: se o professor perguntar, wstring aceita acentos! (no Windows) (mas a implementação nativa varia por plataforma)
	std::vector<std::wstring> opcoesSecundarias;	// vetor com as wstrings (cadeias de caracteres) de cada opção do menu secundário (tipos de jogos)
	std::vector<std::wstring> textoAjuda;			// sim, eu pretendo fazer uma ajuda tipo tutorial com páginas, sim a 1ª página vai conter 'blablabla'
	std::vector<std::wstring> textoOpcoes;			// wstring texto de cada opção
	std::vector<std::vector<std::wstring>> opcoesOpcoes;	// vetor contendo os vetores com os textos dos valores correspondentes a cada opção
	std::wstring textoCreditos;						// wstring texto dos créditos
	std::wstring textoCabecalhoOpcoes;				// wstring texto cabecalho pro menu de opções
	int ativo = 0;					// opcao ativa na tela (seleção)
	std::vector<int> valoresAtivos;	// vetor com cada valor ativo do menu opções, e.g. ({0,0,1} == {normal,nao,sim})

	// coordenadas de desenho das opções dos menus
	std::vector<int> textosMenuPrincipalX;	// vetores usados para colidir mouse, coordenadas X
	std::vector<int> textosMenuPrincipalY;	// vetores usados para colidir mouse, coordenadas Y
	std::vector<int> textosMenuSecundarioX;	// vetores usados para colidir mouse, coordenadas X
	std::vector<int> textosMenuSecundarioY;	// vetores usados para colidir mouse, coordenadas Y
	std::vector<int> textosMenuOpcoesX;	// vetores usados para colidir mouse, coordenadas X
	std::vector<int> textosMenuOpcoesY;	// vetores usados para colidir mouse, coordenadas Y

	// tamanho dos vetores com as opções dos menus
	int sizeOpcoesPrincipais;		// tamanho do vetor com as opções principais
	int sizeTextoAjuda;				// tamanho do vetor com os textos de ajuda
	int sizeOpcoesSecundarias;		// tamando do vetor com os textos das opcoes secundarias
	int sizeOpcoesOpcoes;			// tamando do vetor com os textos das opcoes e valores (textoOpcoes + opcoesOpcoes)
	int sizeTextoOpcoes;			// tamanho do vetor com os textos das opcoes
									//	(pra não ficar chamando size() desnecessariamente, sem usar iteradores...)

	// âncora X e base Y para as opções dos menus
	int xMenu, yBase;				// usados nas coordenadas dos objetos texto nos menus principal e secundário
	int xOpcoes, xValores, yOpcoes;	// usados nas coordenadas dos objetos texto no menu de opções

	int espacamentoOpcoes = 27;			// espaçamento entre cada opção dos menus (valor totalmente arbritrário)
	int espacamentoMenuOpcoes = 71;		// espaçamento entre cada opção do menu de opções (valor totalmente arbritrário)
	int espacamentoValoresOpcoes = 105;	// espaçamento entre cada valor do menu de opções (valor totalmente arbritrário)

	bool obteveEscolha = false;		// valor retornado pela função escolheu(), significa que o menu cumpriu sua função e o jogo deve começar
	EstadoMenu estadoInterno = esperando;	// armazena o método em uso
	EstadoMenuSecundario estadoExterno = menuzando;	// armazena o método de jogo ativo

	// tantos vais não-genéricos poderiam ser evitados, mas quem explicaria tal coisa?
	void resetarMenuPrincipal();
	void prepararTextoOpcoes();
	void prepararTextoCreditos();
	void prepararTextoAjuda();
	void gerenciarMenuOpcoes();
	void vaiOpcao();
	void vaiIndice(int);
	void vaiIndiceSecundario(int);
	void vaiIndiceOpcoes(int);
	void vaiCima();
	void vaiBaixo();
	void vaiTopo();
	void vaiBase();
	void vaiCimaSecundario();
	void vaiBaixoSecundario();
	void vaiTopoSecundario();
	void vaiBaseSecundario();
	void vaiOpcaoSecundario();
	void vaiCimaOpcoes();
	void vaiBaixoOpcoes();
	void vaiDireitaOpcoes();
	void vaiEsquerdaOpcoes();
	void vaiTopoOpcoes();
	void vaiBaseOpcoes();
	bool mouseSobre(Texto objetoTexto, int x, int y);

public:
	MenuPrincipal();
	~MenuPrincipal();
	void desenhar();
	void inicializar();
	bool escolheu();

	std::vector<int> getOpcoes();
};

