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
	int sizeOpcoesPrincipais;		// tamanho do vetor com as opções principais
	int sizeTextoAjuda;				// tamanho do vetor com os textos de ajuda
	int sizetextoOpcoes;			// tamanho do vetor com os textos das opcoes
	int sizeOpcoesSecundarias;		// tamando do vetor com os textos das opcoes secundarias
									//	(pra não ficar chamando size() desnecessariamente, sem usar iteradores...)
	int xMenu, yBase;				// usados nas coordenadas dos objetos texto nos menus principal e secundário
	bool obteveEscolha = false;		// valor retornado pela função escolheu(), significa que o menu cumpriu sua função e o jogo deve começar
	EstadoMenu estadoInterno = esperando;	// armazena o método em uso
	EstadoMenuSecundario estadoExterno = menuzando;	// armazena o método de jogo ativo

	// tantos vais não-genéricos poderiam ser evitados, mas quem explicaria tal coisa?
	void vaiCima();
	void vaiBaixo();
	void vaiTopo();
	void vaiBase();
	void vaiIndice(int);
	void vaiCimaSecundario();
	void vaiBaixoSecundario();
	void vaiTopoSecundario();
	void vaiBaseSecundario();
	void vaiOpcaoSecundario();
	void vaiIndiceSecundario(int);
	void vaiCimaOpcoes();
	void vaiBaixoOpcoes();
	void vaiDireitaOpcoes();
	void vaiEsquerdaOpcoes();
	void vaiTopoOpcoes();
	void vaiBaseOpcoes();
	void vaiIndiceOpcoes(int);
	void vaiOpcao();
	void resetarMenuPrincipal();
	void prepararTextoOpcoes();
	void prepararTextoCreditos();
	void prepararTextoAjuda();
	void gerenciarMenuOpcoes();
public:
	MenuPrincipal();
	~MenuPrincipal();
	void desenhar();
	void inicializar();
	bool escolheu();

	std::vector<int> getOpcoes();
};

