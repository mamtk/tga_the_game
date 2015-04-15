#pragma once
#include "libUnicornio.h"
#include <vector>
#include <string>

enum EstadoMenu { Jogar, Opcoes, Ajuda, Creditos, Sair, Esperando };

class MenuPrincipal
{
	std::vector<Texto> textosMenuPrincipal;	// textos (palavras) das opções do menuPrincipal
	std::vector<Texto> textosMenuOpcoes;	// textos (opcoes, valores possíveis) das opções do menuPrincipal
	Texto textoHandler;		// objeto usado para escrever textos simples, como os créditos
	//std::vector<std::wstring> opcoesPrincipais;	// Sabe como é, eu realmente gosto de acentos, mas quem é que vai explicar isso aqui depois?
	std::vector<std::wstring> opcoesPrincipais;		// vetor com as wstrings (cadeias de caracteres) de cada opção, DICA:
													//	se o professor perguntar, wstring aceita acentos! (no Windows)
	std::vector<std::wstring> textoAjuda;			// sim, eu pretendo fazer uma ajuda tipo tutorial com páginas, sim a 1ª página vai conter 'blablabla'
	std::vector<std::wstring> textoOpcoes;			// wstring texto de cada opção
	std::vector<std::vector<std::wstring>> opcoesOpcoes;	// vetor contendo os vetores com os textos dos valores correspondentes a cada opção
	std::wstring textoCreditos;						// wstring texto dos créditos
	std::wstring textoCabecalhoOpcoes;				// wstring texto cabecalho pro menu de opcoes
	int ativo = 0;					// opcao ativa na tela (seleção)
	std::vector<int> valoresAtivos;	// vetor com cada valor ativo do menu opções, e.g. ({0,0,1} == {normal,nao,sim})
	int sizeOpcoesPrincipais;		// tamanho do vetor com as opções principais
	int sizeTextoAjuda;				// tamanho do vetor com os textos de ajuda
	int sizetextoOpcoes;			// tamanho do vetor com os textos das opcoes
									//	(pra não ficar chamando size() desnecessariamente, sem usar iteradores...)
	EstadoMenu estadoInterno = Esperando;	// armazena o método em uso

	void vaiCima();
	void vaiBaixo();
	void vaiTopo();
	void vaiBase();
	void vaiIndice(int);
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
};

