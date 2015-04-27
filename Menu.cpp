#include "Menu.h"
#include "util.h"

/* TODO
	1. adicionar opção para desenhar quadro esmaecedor atrás (facilitar leitura do menu)
*/


// inicializar menu unitário com espaçamento fixo (i.e. sem especificar a posição de cada item no menu)
Menu::Menu()
{
	fundoEsmaecer.setEscala(700, 100);
	fundoEsmaecer.setVelocidadeAnimacao(50);

}

// inicializar menu único (fazemos as coisas aqui por que setFonte exige um tipo completo para a classe Jogo)
// TODO: versão com origemX|Y em vetores, verificar tamanho, e usar regras de espaçamento pras opções que restarem
void Menu::inicializar(vector<wstring> vetorOpcoes, wstring cabecalhoParam, string fundilho, string som, vector<int> cabecalhoXY, int selecaoPadrao, int origemX, \
	int origemY, int xEspacamento, int yEspacamento, vector<int> corNormalParam, vector<int> corDestaqueParam, vector<int> corCabecalhoParam, bool mouse, \
	string fonte, float espacoLinhas, int alinhamento)
{
	// sprite para efeito esmaecer dessa calsse
	fundoEsmaecer.setSpriteSheet("fx_Esmaecer");

	// inicializar menu unico
	tipoMenu = unico;
	xCentral = janela.getLargura() * .5;
	yCentral = janela.getAltura() * .5;
	if (fundilho.size() > 0) {
		possuiFundo = true;
		fundo.setSpriteSheet(fundilho);
	}
	stringsOpcoesMenu = vetorOpcoes;
	espacamentoOpcoesX = xEspacamento;
	espacamentoOpcoesY = yEspacamento;
	if (som.size() > 0) {
		possuiSomFundo = true;
		somFundo.setAudio(som);
	}
	if (corNormalParam.size() == 4)			// verificar se cor destaque possui 4 elementos
		corNormal = corNormalParam;
	else
		corNormal = { 0, 91, 255, 255 };		// do contrário usar a padrão
	if (corDestaqueParam.size() == 4)			// verificar se cor normal possui 4 elementos
		corDestaque = corDestaqueParam;
	else
		corDestaque = { 0, 200, 255, 255 };	// do contrário usar a padrão
	if (corCabecalhoParam.size() == 4)			// verificar se cor destaque possui 4 elementos
		corCabecalho = corCabecalhoParam;
	else
		corCabecalho = { 0, 200, 255, 255 };		// do contrário usar a padrão

	// setamos o cabeçalho, se existir
	if (cabecalhoParam.size() > 1) {
		stringCabecalho = cabecalhoParam;
		possuiCabecalho = true;

		// inicializar cabecalho/rodape
		cabecalho.setCor(corCabecalho[0], corCabecalho[1], corCabecalho[2], corCabecalho[3]);
		cabecalho.setAlinhamento((TipoAlinhamentoTexto)alinhamento);
		cabecalho.setEspacamentoLinhas(espacoLinhas);
		cabecalho.setWstring(stringCabecalho);
		cabecalho.setFonte(fonte);

		if (cabecalhoXY.size() == 2)			// verificar se cabecalhoXY possui 2 elementos
			xyCabecalho = cabecalhoXY;
		else {									// do contrário usar x, y padrão (50%, 95%)
			int x = janela.getLargura() * .5;
			int y = janela.getAltura() * .95;
			xyCabecalho = { x, y };
		}
	}

	// armazenar tamanho do vetor das opcoes
	sizeOpcoesMenu = stringsOpcoesMenu.size();	// assim não precisamos ficar chamando size(), e nem usar iteradores...
	textosMenu.resize(sizeOpcoesMenu);		// iniciamos a memória, pois já sabemos o que vamos utilizar
	xOpcoesMenu.resize(sizeOpcoesMenu);	// iniciamos a memória, pois já sabemos o que vamos utilizar
	yOpcoesMenu.resize(sizeOpcoesMenu);	// iniciamos a memória, pois já sabemos o que vamos utilizar

	nomeFonte = fonte;
	mouseAtivo = mouse;

	// inicializar objetos Texto para cada uma das opções do menu único (antes das coordenadas pra poder usar largura/altura)
	// x ou y == -1, significa centro da tela
	for (int i = 0; i < sizeOpcoesMenu; i++) {
		textosMenu[i].setCor(corNormal[0], corNormal[1], corNormal[2], corNormal[3]);
		textosMenu[i].setAlinhamento((TipoAlinhamentoTexto)alinhamento);
		textosMenu[i].setEspacamentoLinhas(espacoLinhas);
		textosMenu[i].setWstring(stringsOpcoesMenu[i]);
		textosMenu[i].setFonte(fonte);
	}
	// setar opção ativa e destacá-la
	ativoPadrao = ativo = selecaoPadrao;
	textosMenu[ativo].setCor(corDestaque[0], corDestaque[1], corDestaque[2], corDestaque[3]);

	// setamos as coordenadas de acordo com os parametros dados; origemX|Y == -1 significa centro da tela
	if (espacamentoOpcoesX == 0) {	// não queremos espaçamento no vetor x
		if (origemX == -1) {
			// elemento zero: x = centro da tela
			for (int i = 0; i < sizeOpcoesMenu; i++) {
				// x = centro da tela
				xOpcoesMenu[i] = xCentral;
			}
		}
		else {
			// elemento zero: x é fornecido
			for (int i = 0; i < sizeOpcoesMenu; i++) {
				// x = x fornecido
				xOpcoesMenu[i] = origemX;
			}
		}
	}
	else {
		if (origemX == -1) {
			// elemento zero: x = centro da tela
			xOpcoesMenu[0] = xCentral;
			for (int i = 1; i < sizeOpcoesMenu; i++) {
				// x = centro da tela + (SOMA(largura de cada opção anterior * .5)) + (espaçamento fornecido * numero da opcao)
				int soma = 0;
				for (int j = 0; j < i; j++) {
					soma += textosMenu[j].getLargura();	// somamos a metade da largura de cada uma das opções anteriores
				}
				xOpcoesMenu[i] = origemX + soma + espacamentoOpcoesX * i;
			}
		}
		else {
			// elemento zero: x = base fornecida
			xOpcoesMenu[0] = origemX;
			for (int i = 1; i < sizeOpcoesMenu; i++) {
				// x = base fornecida + (SOMA(largura de cada opção anterior * .5)) + (espaçamento fornecido * numero da opcao)
				int soma = 0;
				for (int j = 0; j < i; j++) {
					soma += textosMenu[j].getLargura();	// somamos a metade da largura de cada uma das opções anteriores
				}
				xOpcoesMenu[i] = origemX + soma + espacamentoOpcoesX * i;
			}
		}
	}
	if (espacamentoOpcoesY == 0) {	// não queremos espaçamento no vetor y
		if (origemY == -1) {
			// elemento zero: y = centro da tela
			for (int i = 0; i < sizeOpcoesMenu; i++) {
				// y = centro da tela
				yOpcoesMenu[i] = yCentral;
			}
		}
		else {
			// elemento zero: y = centro da tela
			for (int i = 0; i < sizeOpcoesMenu; i++) {
				// y = centro da tela
				yOpcoesMenu[i] = origemY;
			}
		}
	}
	else {
		if (origemY == -1) {
			// elemento zero: y = centro da tela
			yOpcoesMenu[0] = yCentral;
			for (int i = 1; i < sizeOpcoesMenu; i++) {
				// y = centro da tela + (i * altura da opção anterior * .5) + (espaçamento fornecido * numero da opcao)
				yOpcoesMenu[i] = yCentral + (i * textosMenu[i - 1].getAltura() * .5) + espacamentoOpcoesY * i;
			}
		}
		else {
			// elemento zero: y = base fornecida
			yOpcoesMenu[0] = origemY;
			for (int i = 1; i < sizeOpcoesMenu; i++) {
				// y = base fornecida + (i * largura da opção anterior * .5) + (espaçamento fornecido * numero da opcao)
				yOpcoesMenu[i] = origemY + (i * textosMenu[i - 1].getAltura() * .5) + espacamentoOpcoesY * i;
			}
		}
	}
}

// inicializar menu duplos (fazemos as coisas aqui por que setFonte exige um tipo completo para a classe Jogo)
// TODO: versão com origemX|Y em vetores, verificar tamanho, e usar regras de espaçamento pras opções que restarem
void Menu::inicializar(vector<wstring> vetorOpcoes, vector<vector<wstring>> vetorValores, wstring cabecalhoParam, string fundilho, string som, \
	vector<int> cabecalhoXY, int selecaoPadrao, vector<int> valoresPadrao, int origemX, int origemY, int xEspacamento, int yEspacamento, \
	int origemXValores, int origemYValores, int xEspacamentoValores, int yEspacamentoValores, int xEspacamentoValoresOpcoes, \
	int yEspacamentoValoresOpcoes, vector<int> corNormalParam, vector<int> corDestaqueParam, vector<int> corNormalValoresParam, \
	vector<int> corDestaqueValoresParam, vector<int> corCabecalhoParam, bool mouse,	string fonte, float espacoLinhas, int alinhamento)
{
	// sprite para efeito esmaecer dessa calsse
	//fundo.setSpriteSheet(fundilho);
	fundoEsmaecer.setSpriteSheet("fx_Esmaecer");

	// inicializar menu unico
	tipoMenu = duplo;
	xCentral = janela.getLargura() * .5;
	yCentral = janela.getAltura() * .5;
	if (fundilho.size() > 0) {
		possuiFundo = true;
		fundo.setSpriteSheet(fundilho);
	}
	stringsOpcoesMenu = vetorOpcoes;
	stringValoresMenu = vetorValores;
	espacamentoOpcoesX = xEspacamento;
	espacamentoOpcoesY = yEspacamento;
	espacamentoValoresX = xEspacamentoValores;
	espacamentoValoresY = yEspacamentoValores;
	espacamentoValoresOpcoesX = xEspacamentoValoresOpcoes;
	espacamentoValoresOpcoesY = yEspacamentoValoresOpcoes;

	if (som.size() > 0) {
		possuiSomFundo = true;
		somFundo.setAudio(som);
	}
	if (corNormalParam.size() == 4)			// verificar se cor destaque das opcoes possui 4 elementos
		corNormal = corNormalParam;
	else
		corNormal = { 0, 255, 0, 255 };		// do contrário usar a padrão
	if (corDestaqueParam.size() == 4)		// verificar se cor normal das opcoes possui 4 elementos
		corDestaque = corDestaqueParam;
	else
		corDestaque = { 255, 255, 0, 255 };	// do contrário usar a padrão
	if (corDestaqueValoresParam.size() == 4)	// verificar se cor destaque dos valores possui 4 elementos
		corNormalValores = corDestaqueValoresParam;
	else
		corNormalValores = { 0, 255, 0, 255 };		// do contrário usar a padrão
	if (corNormalValoresParam.size() == 4)		// verificar se cor normal dos valores possui 4 elementos
		corDestaqueValores = corNormalValoresParam;
	else
		corDestaqueValores = { 255, 255, 0, 255 };	// do contrário usar a padrão
	if (corCabecalhoParam.size() == 4)		// verificar se cor cabecalho possui 4 elementos
		corCabecalho = corCabecalhoParam;
	else
		corCabecalho = { 255, 255, 0, 255 };	// do contrário usar a padrão

	// setamos o cabeçalho, se existir
	if (cabecalhoParam.size() > 1) {
		stringCabecalho = cabecalhoParam;
		possuiCabecalho = true;

		// inicializar cabecalho/rodape
		cabecalho.setCor(corCabecalho[0], corCabecalho[1], corCabecalho[2], corCabecalho[3]);
		cabecalho.setAlinhamento((TipoAlinhamentoTexto)alinhamento);
		cabecalho.setEspacamentoLinhas(espacoLinhas);
		cabecalho.setWstring(stringCabecalho);
		cabecalho.setFonte(fonte);

		if (cabecalhoXY.size() == 2)			// verificar se cabecalhoXY possui 2 elementos
			xyCabecalho = cabecalhoXY;
		else {									// do contrário usar x, y padrão (50%, 10%)
			int x = janela.getLargura() * .5;
			int y = janela.getAltura() * .9;
			xyCabecalho = { x, y };
		}
	}

	// armazenar tamanho do vetor das opcoes
	sizeOpcoesMenu = stringsOpcoesMenu.size();	// assim não precisamos ficar chamando size(), e nem usar iteradores...
	textosMenu.resize(sizeOpcoesMenu);			// iniciamos a memória, pois acabamos de descobrir quanto vamos utilizar
	textosMenuValores.resize(sizeOpcoesMenu);	// iniciamos a memória, pos já sabemos o que vamos utilizar
	xOpcoesMenu.resize(sizeOpcoesMenu);			// iniciamos a memória, pois já sabemos o que vamos utilizar
	yOpcoesMenu.resize(sizeOpcoesMenu);			// iniciamos a memória, pois já sabemos o que vamos utilizar
	xValoresMenu.resize(sizeOpcoesMenu);		// iniciamos a memória, pois já sabemos o que vamos utilizar
	yValoresMenu.resize(sizeOpcoesMenu);		// iniciamos a memória, pois já sabemos o que vamos utilizar
	sizeValoresMenu.resize(sizeOpcoesMenu);		// iniciamos a memória, pois já sabemos o que vamos utilizar
	for (int nivel = 0; nivel < sizeOpcoesMenu; nivel++){	// para cada opção do menu
		sizeValoresMenu[nivel] = stringValoresMenu[nivel].size();	// armazenamos o numero de valores de cada nivel
		sizeValores += sizeValoresMenu[nivel];						// contabilizamos o total de todos os elementos em sizeValores

		xValoresMenu[nivel].resize(sizeValoresMenu[nivel]);			// iniciamos a memória, pois já sabemos o que vamos utilizar
		yValoresMenu[nivel].resize(sizeValoresMenu[nivel]);			// iniciamos a memória, pois já sabemos o que vamos utilizar
		textosMenuValores[nivel].resize(sizeValoresMenu[nivel]);	// iniciamos a memória, pois já sabemos o que vamos utilizar
	}
	// inicializar valores padrão
	if (valoresPadrao.size() == sizeOpcoesMenu)
		valoresAtivos = valoresPadrao;
	else {	// tamanho dos valores difere do total de opções, tratar como valor único para todos
		valoresAtivos.resize(sizeOpcoesMenu);		// iniciamos a memória, pois já sabemos o que vamos usar
		for (int i = 0; i < sizeOpcoesMenu; i++) {
			valoresAtivos[i] = valoresPadrao[0];
		}
	}

	// x ou y == -1, significa padrão
	int xPadrao = janela.getLargura() * .25;
	int yPadrao = janela.getAltura() * .3;

	nomeFonte = fonte;
	mouseAtivo = mouse;

	// inicializar objetos Texto para cada uma das opções do menu duplo (antes das coordenadas para poder usar o getAltura/Largura)
	for (int i = 0; i < sizeOpcoesMenu; i++) {
		textosMenu[i].setAlinhamento((TipoAlinhamentoTexto)alinhamento);
		textosMenu[i].setEspacamentoLinhas(espacoLinhas);
		textosMenu[i].setWstring(stringsOpcoesMenu[i]);
		textosMenu[i].setCor(corNormal[0], corNormal[1], corNormal[2], corNormal[3]);
		textosMenu[i].setFonte(fonte);
	}
	// setar opção ativa e destacá-la
	ativoPadrao = ativo = selecaoPadrao;
	textosMenu[ativo].setCor(corDestaque[0], corDestaque[1], corDestaque[2], corDestaque[3]);
	int sizeValoresAtivo = valoresAtivos.size();	// para evitar acesso a memória não inicializada

	// inicializar objetos Texto para cada um dos valores do menu duplo (antes das coordenadas para poder usar o getAltura/Largura)
	for (int nivel = 0; nivel < sizeOpcoesMenu; nivel++) {	// vamos destacar um valor por opção do menu
		for (int elemento = 0; elemento < sizeValoresMenu[nivel]; elemento++) {
			textosMenuValores[nivel][elemento].setAlinhamento((TipoAlinhamentoTexto)alinhamento);
			textosMenuValores[nivel][elemento].setEspacamentoLinhas(espacoLinhas);
			textosMenuValores[nivel][elemento].setWstring(stringValoresMenu[nivel][elemento]);
			textosMenuValores[nivel][elemento].setFonte(fonte);
			if (elemento == valoresAtivos[nivel])	// destacar valores ativos
				textosMenuValores[nivel][elemento].setCor(corDestaqueValores[0], corDestaqueValores[1], corDestaqueValores[2], corDestaqueValores[3]);
			else	// usar cor normal nos não ativos
				textosMenuValores[nivel][elemento].setCor(corNormalValores[0], corNormalValores[1], corNormalValores[2], corNormalValores[3]);
		}
	}

	// setamos as coordenadas das opções de acordo com os parametros dados; origemX|Y == -1 significa padrão
	if (espacamentoOpcoesX == 0) {	// não queremos espaçamento no vetor x
		if (origemY == -1) {
			// elemento zero: y = centro da tela
			for (int i = 0; i < sizeOpcoesMenu; i++) {
				// y = centro da tela
				xOpcoesMenu[i] = xPadrao;
			}
		}
		else {
			// elemento zero: y = centro da tela
			for (int i = 0; i < sizeOpcoesMenu; i++) {
				// y = centro da tela
				xOpcoesMenu[i] = origemX;
			}
		}
	}
	else {
		if (origemX == -1) {
			// elemento zero: x = centro da tela
			xOpcoesMenu[0] = xPadrao;
			for (int i = 1; i < sizeOpcoesMenu; i++) {
				// x = centro da tela + (SOMA(largura de cada opção anterior * .5)) + (espaçamento fornecido * numero da opcao)
				int soma = 0;
				for (int j = 0; j < i; j++) {
					soma += textosMenu[j].getLargura();	// somamos a metade da largura de cada uma das opções anteriores
				}
				xOpcoesMenu[i] = origemX + soma + espacamentoOpcoesX * i;
			}
		}
		else {
			// elemento zero: x = base fornecida
			xOpcoesMenu[0] = origemX;
			for (int i = 1; i < sizeOpcoesMenu; i++) {
				// x = base fornecida + (SOMA(largura de cada opção anterior * .5)) + (espaçamento fornecido * numero da opcao)
				int soma = 0;
				for (int j = 0; j < i; j++) {
					soma += textosMenu[j].getLargura();	// somamos a metade da largura de cada uma das opções anteriores
				}
				xOpcoesMenu[i] = origemX + soma + espacamentoOpcoesX * i;
			}
		}
	}
	if (espacamentoOpcoesY == 0) {	// não queremos espaçamento no vetor y
		if (origemY == -1) {
			// elemento zero: y = centro da tela
			for (int i = 0; i < sizeOpcoesMenu; i++) {
				// y = centro da tela
				yOpcoesMenu[i] = yPadrao;
			}
		}
		else {
			// elemento zero: y = centro da tela
			for (int i = 0; i < sizeOpcoesMenu; i++) {
				// y = centro da tela
				yOpcoesMenu[i] = origemY;
			}
		}
	}
	else {
		if (origemY == -1) {
			// elemento zero: y = centro da tela
			yOpcoesMenu[0] = yPadrao;
			for (int i = 1; i < sizeOpcoesMenu; i++) {
				// y = centro da tela + (i * altura da opção anterior * .5) + (espaçamento fornecido * numero da opcao)
				yOpcoesMenu[i] = yPadrao + (i * textosMenu[i - 1].getAltura() * .5) + espacamentoOpcoesY * i;
			}
		}
		else {
			// elemento zero: y = base fornecida
			yOpcoesMenu[0] = origemY;
			for (int i = 1; i < sizeOpcoesMenu; i++) {
				// y = base fornecida + (i * largura da opção anterior * .5) + (espaçamento fornecido * numero da opcao)
				yOpcoesMenu[i] = origemY + (i * textosMenu[i - 1].getAltura() * .5) + espacamentoOpcoesY * i;
			}
		}
	}

	// setamos as coordenadas dos valores de acordo com os parametros dados; origemX|Y == -1 significa origem em cima da opção
	for (int nivel = 0; nivel < sizeOpcoesMenu; nivel++) { // vamos percorrer todos os niveis/opcoes do menu para configurar cada valor possível
		if (espacamentoValoresOpcoesX == 0) {	// queremos espaçamento no vetor x
			if (origemXValores == -1) {
				// elemento zero: y = centro da tela
				for (int i = 1; i < sizeValoresMenu[nivel]; i++) {
					// x = x da opção nesse nivel
					xValoresMenu[nivel][i] = xOpcoesMenu[nivel];
				}
			}
			else {
				// elemento zero: y = centro da tela
				for (int i = 0; i < sizeOpcoesMenu; i++) {
					// y = centro da tela
					xValoresMenu[nivel][i] = origemXValores;
				}
			}
		}
		else {
			if (origemXValores == -1) {
				// elemento zero do nível: x = x da opção + (largura da opção desse nível * .5) + espacamento entre valores e opções
				xValoresMenu[nivel][0] = xOpcoesMenu[nivel] + (textosMenu[nivel].getLargura()) + espacamentoValoresOpcoesX;
				int ancora = xValoresMenu[nivel][0];	// ancora (valor base) dos próximos elementos
				for (int i = 1; i < sizeValoresMenu[nivel]; i++) {	// 
					// ancora = x da opção + (largura da opção desse nível * .5) + espacamento entre valores e opções
					// x = ancora + (SOMA(largura de cada opção anterior * .5)) + (espaçamento fornecido * numero da opcao)
					int soma = 0;
					for (int j = 0; j < i; j++) {
						soma += textosMenuValores[nivel][j].getLargura();	// somamos a metade da largura de cada uma das opções anteriores
					}
					xValoresMenu[nivel][i] = ancora + soma + i * espacamentoValoresX;
				}
			}
			else {
				// elemento zero do nível: x = base fornecida + espacamento entre valores e opções
				xValoresMenu[nivel][0] = origemXValores + espacamentoValoresOpcoesX;
				int ancora = xValoresMenu[nivel][0];	// ancora (valor base) dos próximos elementos
				for (int i = 1; i < sizeValoresMenu[nivel]; i++) {	// 
					// ancora = base fornecida + (largura da opção desse nível * .5) + espacamento entre valores e opções 
					// x = ancora + (SOMA(largura de cada opção anterior * .5)) + (i * espacamento entre valores)
					int soma = 0;
					for (int j = 0; j < i; j++) {
						soma += textosMenuValores[nivel][j].getLargura();	// somamos a metade da largura de cada uma das opções anteriores
					}
					xValoresMenu[nivel][i] = ancora + soma + espacamentoValoresX * i;
				}
			}
		}
		if (espacamentoValoresOpcoesY == 0) {	// queremos espaçamento no vetor x
			if (origemYValores == -1) {
				// elemento zero: y = centro da tela
				for (int i = 0; i < sizeValoresMenu[nivel]; i++) {
					// x = centro da tela
					yValoresMenu[nivel][i] = yOpcoesMenu[nivel];
				}
			}
			else {
				// elemento zero: y = centro da tela
				for (int i = 0; i < sizeValoresMenu[nivel]; i++) {
					// y = centro da tela
					yValoresMenu[nivel][i] = origemYValores;
				}
			}
		}
		else {
			if (origemYValores == -1) {
				// elemento zero do nível: y = y da opção + (largura da opção desse nível * .5) + espacamento entre valores e opções
				yValoresMenu[nivel][0] = yOpcoesMenu[nivel] + (textosMenu[nivel].getAltura() * .5) + espacamentoValoresOpcoesY;
				int ancora = yValoresMenu[nivel][0];	// ancora (valor base) dos próximos elementos
				for (int i = 1; i < sizeValoresMenu[nivel]; i++) {	// 
					// y = centro da tela + (largura da desse nível * .5) + espacamento entre valores e opções + (largura do valor anterior * .5)
					yValoresMenu[nivel][i] = ancora + espacamentoValoresOpcoesY + espacamentoValoresY * i;
				}
			}
			else {
				// elemento zero do nível: y = base fornecida + espacamento entre valores e opções
				yValoresMenu[nivel][0] = origemYValores + espacamentoValoresOpcoesY;
				int ancora = yValoresMenu[nivel][0];	// ancora (valor base) dos próximos elementos
				for (int i = 1; i < sizeValoresMenu[nivel]; i++) {	// 
					// y = base fornecida + (largura da desse nível * .5) + espacamento entre valores e opções + (largura do valor anterior * .5)
					yValoresMenu[nivel][i] = ancora + espacamentoValoresY * i;
				}
			}
		}
	}
}

Menu::~Menu()
{
}

void Menu::desenhar()
{
	uniDepurar("Ativo", ativo);
	uniDepurar("Y[ativo]", yOpcoesMenu[ativo]);
	uniDepurar("X[ativo]", xOpcoesMenu[ativo]);

	// primeiro desenhar o fundo (antes de tudo)
	if(possuiFundo)
		fundo.desenhar(xCentral, yCentral);

	if (possuiCabecalho)	// aqui desenhamos o cabecalho, se existir
		cabecalho.desenhar(xyCabecalho[0], xyCabecalho[1]);
	
	if (mouseAtivo)
		mouseMoveu = mouseSeMoveu();	// precisamos saber se o mouse efetivamente se moveu, pra não bagunçar as opções
	else
		mouseMoveu = false;				// _não_ precisamos saber se o mouse efetivamente se moveu

	switch (tipoMenu) { // aqui senhamos as opções
	case unico:
		for (int i = 0; i < sizeOpcoesMenu; i++) {	// iteramos pelas opções principais
			textosMenu[i].desenhar(xOpcoesMenu[i], yOpcoesMenu[i]);		// desenhamos cada opção principal
			int tamanhoTexto = textosMenu[i].getWstring().size();	// usamos o tamanho do texto para determinar suas coordenadas máximas no eixo x
			if (mouseMoveu && mouseSobre(textosMenu[i], xOpcoesMenu[i], yOpcoesMenu[i])) {	// se o mouse se moveu, e agora está sobre a opção atual
				// o compilador nos garante que se a primeira condição for falsa, a segunda não deve executar
				vaiIndice(i);	//	então usamos a função vaiIndice com a opção atual (i) como argumento, para destacá-la
			}
		}

		if (teclado.soltou[TECLA_CIMA] || teclado.soltou[TECLA_W]) {			// vai cima ao apertar ↑ ou W
			vaiCima();
		}
		else if (teclado.soltou[TECLA_BAIXO] || teclado.soltou[TECLA_S]) {		// vai baixo ao apertar ↓ ou S
			vaiBaixo();
		}
		else if (teclado.soltou[TECLA_END] || teclado.soltou[TECLA_PAGEDOWN]) {	// vai base ao apertar end
			vaiBase();
		}
		else if (teclado.soltou[TECLA_HOME] || teclado.soltou[TECLA_PAGEUP]) {	// vai topo ao apertar home
			vaiTopo();
		}
		else if (teclado.soltou[TECLA_ENTER] || teclado.soltou[TECLA_ESPACO] || mouse.pressionou[0]) {	// [0] = primeiro botao do mouse
			vaiOpcao();	// a escolha foi feita!
		}
		break;
	case duplo:
		for (int nivel = 0; nivel < sizeOpcoesMenu; nivel++) {	// iteramos pelas opções/niveis do menu
			textosMenu[nivel].desenhar(xOpcoesMenu[nivel], yOpcoesMenu[nivel]);		// desenhamos cada opção principal

			if (mouseMoveu && mouseSobre(textosMenu[nivel], xOpcoesMenu[nivel], yOpcoesMenu[nivel])) {	// se o mouse estiver sobre a opção atual
				vaiIndice(nivel);	//	então usamos a função vaiIndice com a opção atual (i) como argumento, para destacá-la
			}
			for (int elemento = 0; elemento < sizeValoresMenu[nivel]; elemento++) {
				textosMenuValores[nivel][elemento].desenhar(xValoresMenu[nivel][elemento], yValoresMenu[nivel][elemento]);		// desenhamos cada opção principal

				if (mouseMoveu && mouseSobre(textosMenuValores[nivel][elemento], xValoresMenu[nivel][elemento], yValoresMenu[nivel][elemento])) {	// se o mouse estiver sobre a opção atual
					vaiIndiceValor(nivel, elemento);	//	então usamos a função vaiIndice com a opção atual (i) como argumento, para destacá-la
				}
			}
		}

		if (teclado.soltou[TECLA_CIMA] || teclado.soltou[TECLA_W]) {			// vai cima ao apertar ↑ ou W
			vaiCima();
		}
		else if (teclado.soltou[TECLA_BAIXO] || teclado.soltou[TECLA_S]) {		// vai baixo ao apertar ↓ ou S
			vaiBaixo();
		}
		else if (teclado.soltou[TECLA_DIR] || teclado.soltou[TECLA_D]) {		// vai cima ao apertar ↑ ou W
			vaiDireita();
		}
		else if (teclado.soltou[TECLA_ESQ] || teclado.soltou[TECLA_A]) {		// vai baixo ao apertar ↓ ou S
			vaiEsquerda();
		}
		else if (teclado.soltou[TECLA_END] || teclado.soltou[TECLA_PAGEDOWN]) {	// vai base ao apertar end
			vaiBase();
		}
		else if (teclado.soltou[TECLA_HOME] || teclado.soltou[TECLA_PAGEUP]) {	// vai topo ao apertar home
			vaiTopo();
		}
		else if (teclado.soltou[TECLA_ENTER] || teclado.soltou[TECLA_ESPACO]) { // mouse.pressionou[0]) // ficaria confuso clicar e voltar em menu duplo
			vaiOpcao();	// a escolha foi feita!
		}
		break;
	}
}

// esmaecer/destacar opção do menu
void Menu::destacar(int i) {
	textosMenu[i].setCor(corDestaque[0], corDestaque[1], corDestaque[2], corDestaque[3]);
}
void Menu::esmaecer(int i) {
	textosMenu[i].setCor(corNormal[0], corNormal[1], corNormal[2], corNormal[3]);
}
// esmaecer/destacar valor do menu
void Menu::destacarValor(int nivel, int elemento) {
	textosMenuValores[nivel][elemento].setCor(corDestaqueValores[0], corDestaqueValores[1], corDestaqueValores[2], corDestaqueValores[3]);
}
void Menu::esmaecerValor(int nivel, int elemento) {
	textosMenuValores[nivel][elemento].setCor(corNormalValores[0], corNormalValores[1], corNormalValores[2], corNormalValores[3]);
}

// essas funções gerenciam os movimentos de seleção do menu principal
void Menu::vaiBaixo()
{
	esmaecer(ativo);
	ativo = modulo(ativo + 1, sizeOpcoesMenu);	// não usamos size - 1 por que o módulo nunca chega no número
	destacar(ativo);
}
void Menu::vaiCima()
{
	esmaecer(ativo);
	ativo = modulo(ativo - 1, sizeOpcoesMenu);	// não usamos size - 1 por que o módulo nunca chega no número
	destacar(ativo);
}
void Menu::vaiDireita()
{
	esmaecerValor(ativo, valoresAtivos[ativo]);
	valoresAtivos[ativo] = modulo(valoresAtivos[ativo] + 1, sizeValoresMenu[ativo]);	// não usamos size - 1 por que o módulo nunca chega no número
	destacarValor(ativo, valoresAtivos[ativo]);
}
void Menu::vaiEsquerda()
{
	esmaecerValor(ativo, valoresAtivos[ativo]);
	valoresAtivos[ativo] = modulo(valoresAtivos[ativo] - 1, sizeValoresMenu[ativo]);	// não usamos size - 1 por que o módulo nunca chega no número
	destacarValor(ativo, valoresAtivos[ativo]);
}
void Menu::vaiTopo()
{
	esmaecer(ativo);
	ativo = 0;
	destacar(ativo);
}
void Menu::vaiBase()
{
	esmaecer(ativo);
	ativo = sizeOpcoesMenu - 1;	// usamos size - 1 por que o vetor começa em 0, então
										//	o vetor termina uma posição antes do tamanho
	destacar(ativo);
}
void Menu::vaiIndice(int i)
{
	esmaecer(ativo);
	ativo = i;
	destacar(ativo);
}
void Menu::vaiIndiceValor(int nivel, int elemento)
{
	esmaecerValor(nivel, valoresAtivos[nivel]);
	valoresAtivos[nivel] = elemento;	// não usamos size - 1 por que o módulo nunca chega no número
	destacarValor(nivel, valoresAtivos[nivel]);
}
// aqui removemos o destaque da opção do índice (ativo), depois retornamos o índice para a primeira opção,
//	e finalmente destacamos o texto correspondente ao novo índice (0)
void Menu::resetarMenu()
{
	estadoInterno = escolhendo;
	esmaecer(ativo);
	ativo = ativoPadrao;
	destacar(ativo);
	if (possuiSomFundo)
		somFundo.parar();
}

/* alteramos o estadoInterno ou aplicacao.sair;
	executamos código necessário (se existir) antes da execução voltar pro loop desenhar
*/
void Menu::vaiOpcao()
{
	estadoInterno = escolheu;
}

// aqui retornamos a escolha do jogador
int Menu::getOpcao()
{
	return ativo;
}
// aqui retornamos as escolhas (menu duplo) do jogador
vector<int> Menu::getValores()
{
	return valoresAtivos;
}

/* MenuPrincipal nasceu com um propósito, para responder a grande questão de sua vida!!!
	O jogador escolheu?
*/
bool Menu::finalizado()
{
	return estadoInterno;
}

bool Menu::mouseSobre(Texto objetoTexto, int x, int y)	// eu usaria referência pro const, mas quem explicaria tal coisa?
{
	int metadeAltura = objetoTexto.getAltura() * .5;
	int metadeLargura = objetoTexto.getLargura() * .5;
	if (mouse.y >= (y - metadeAltura) && mouse.y <= (y + metadeAltura) &&	// se o ponteiro está verticalmente próximo a esse objeto texto
		(mouse.x >= (x - metadeLargura) && (mouse.x <= (x + metadeLargura)))) {	// também verificar se ele está horizontalmente próximo
		// caso positivo, o ponteiro provavelmente está sobre a opção atual (textosMenuPrincipal[i])
		return true;	//	então usamos a função vaiIndice com a opção atual (i) como argumento, para destacá-la
	}
	return false;
}

bool Menu::mouseSeMoveu()	// para não bagunçar desnecessariamente o menu
{
	bool moveu;

	if (mouse.x != mouseX || mouse.y != mouseY) {
		mouseX = mouse.x;
		mouseY = mouse.y;
		moveu = true;
	}
	else {
		moveu = false;
	}

	return moveu;
}

void Menu::tocarMusica()
{
	if (possuiSomFundo && !somFundo.estaTocando()) {
		bool repetir = true;
		somFundo.tocar(repetir);
	}
}