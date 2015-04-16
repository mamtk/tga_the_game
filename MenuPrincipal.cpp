#include "MenuPrincipal.h"
#include "util.h"


MenuPrincipal::MenuPrincipal()
{
	// inicializar menu principal
	opcoesPrincipais = { L"Iniciar Jogo", L"Opções", L"Ajuda", L"Créditos", L"Sair" };
	sizeOpcoesPrincipais = opcoesPrincipais.size();	// assim não precisamos ficar chamando size(), e nem usar iteradores...
	textosMenuPrincipal.resize(sizeOpcoesPrincipais);	// iniciamos a memória, pois já sabemos o que vamos utilizar
	textosMenuPrincipalX.resize(sizeOpcoesPrincipais);	// iniciamos a memória, pois já sabemos o que vamos utilizar
	textosMenuPrincipalY.resize(sizeOpcoesPrincipais);	// iniciamos a memória, pois já sabemos o que vamos utilizar

	// inicializar objetos Texto para cada uma das opções do menu principal
	for (int i = 0; i < sizeOpcoesPrincipais; i++) {
		textosMenuPrincipal[i].setCor(0, 255, 0);
		textosMenuPrincipal[i].setAlinhamento(TEXTO_CENTRALIZADO);
		textosMenuPrincipal[i].setEspacamentoLinhas(1.5f);
		textosMenuPrincipal[i].setWstring(opcoesPrincipais[i]);
		textosMenuPrincipal[i].setFonte("fonteNormal");
	}
	textosMenuPrincipal[0].setCor(255, 255, 0);

	// inicializar menu secundário
	opcoesSecundarias = { L"Halterofilismo (Campanha)", L"Halterofilismo (Sandbox)", L"Tiro (Campanha)", L"Tiro (Sandbox)", L"Voltar" };
	sizeOpcoesSecundarias = opcoesSecundarias.size();	// assim não precisamos ficar chamando size(), e nem usar iteradores...
	textosMenuSecundario.resize(sizeOpcoesSecundarias);	// iniciamos a memória, pois já sabemos o que vamos utilizar 
	textosMenuSecundarioX.resize(sizeOpcoesSecundarias);	// iniciamos a memória, pois já sabemos o que vamos utilizar
	textosMenuSecundarioY.resize(sizeOpcoesSecundarias);	// iniciamos a memória, pois já sabemos o que vamos utilizar


	// inicializar objetos Texto para cada uma das opções do menu principal
	for (int i = 0; i < sizeOpcoesPrincipais; i++) {
		textosMenuSecundario[i].setCor(0, 255, 0);
		textosMenuSecundario[i].setAlinhamento(TEXTO_CENTRALIZADO);
		textosMenuSecundario[i].setEspacamentoLinhas(1.5f);
		textosMenuSecundario[i].setWstring(opcoesSecundarias[i]);
		textosMenuSecundario[i].setFonte("fonteNormal");
	}
	textosMenuSecundario[0].setCor(255, 255, 0);

	// inicializar texto dos créditos
	textoCreditos = L"TGA - The Game é um jogo sério, muito sério; mas não deve ser levado a sério, \
		já que é apenas um jogo.\n\nCriado por Jean Lucca, Mattheus Menezes, Morris.\nSão Leopoldo, abril de 2015.\n\n\
		PRESSIONE ENTER, BARRA DE ESPAÇO, OU CLIQUE COM O MOUSE PARA VOLTAR.";
	// inicializar texto de ajuda, ele é um vetor, eu penso em cada elemento como uma "página"
	textoAjuda = { L"blablabla\n\n\nParabéns! Você está pronto para ir para a próxima página!\nAperte Enter, D ou -> para prosseguir, ou aperte espaço para voltar."
		};
	sizeTextoAjuda = textoAjuda.size();
	// inicializar texto das opções
	textoCabecalhoOpcoes = L"Pressione [ESPAÇO] para voltar. Todas as opções destacadas serão ativadas.";
	textoOpcoes = { L"Nível de dificuldade:", // [0]
		L"Desativar eventos aleatórios:",	// [1]
		L"Desativar fatality:", // [2]
		L"Desativar som:", // [3]
		//L"Desativar história:", // [4]
	};
	sizeTextoOpcoes = textoOpcoes.size();	// assim não precisamos ficar chamando size(), e nem usar iteradores...
	opcoesOpcoes.resize(sizeTextoOpcoes);	// iniciamos a memória, pois já sabemos o que vamos utilizar
	textosMenuOpcoesX.resize(sizeTextoOpcoes);	// iniciamos a memória, pois já sabemos o que vamos utilizar
	textosMenuOpcoesY.resize(sizeTextoOpcoes);	// iniciamos a memória, pois já sabemos o que vamos utilizar

	sizeOpcoesOpcoes = sizeTextoOpcoes;	// vamos contar também os elementos texto de variáveis, para inicializar corretamente textosMenuOpcoes
										//	adicionaremos o número de valores ao total das opções, já conhecido, e adicionado agora
	// inicializar os "valores" possiveis para cada texto de opção
	for (int i = 0; i < sizeTextoOpcoes; i++) {
		switch (i) { // talvez fique mais fácil de entender se eu usar um loop for (embora fique mais lento, só roda uma vez)
		case 0: // variáveis possíveis para a opção [0] do textoOpcoes
			opcoesOpcoes[i] = { L"Normal", L"Difícil", L"Impossível", L"Impossível?" }; // opções para [0] (dificuldade)
			sizeOpcoesOpcoes += opcoesOpcoes[i].size(); // fazer a contabilidade corretamente
			break;
		case 1: // variáveis possíveis para a opção [1] do textoOpcoes
			opcoesOpcoes[i] = { L"Não", L"Sim" }; // opções para [2] (desativar eventos pseudoaleatórios)
			sizeOpcoesOpcoes += opcoesOpcoes[i].size(); // fazer a contabilidade corretamente
			break;
		case 2: // variáveis possíveis para a opção [2] do textoOpcoes
			opcoesOpcoes[i] = { L"Não", L"Sim" }; // opções para [3] (desativar fatality)
			sizeOpcoesOpcoes += opcoesOpcoes[i].size(); // fazer a contabilidade corretamente
			break;
		case 3: // variáveis possíveis para a opção [2] do textoOpcoes
			opcoesOpcoes[i] = { L"Não", L"Sim" }; // opções para [4] (desativar som)
			sizeOpcoesOpcoes += opcoesOpcoes[i].size(); // fazer a contabilidade corretamente
			break;
		}
	}
	// agora que temos opcoes+valores, sabemos o tamanho do vetor de textos necessario
	textosMenuOpcoes.resize(sizeOpcoesOpcoes);	// os primeiros n = sizeTextoOpcoes são as opções, os elementos seguintes são variáveis
															//	não precisamos de índice, pois o textosMenuOpcoes nos fornece um de graça
	int cNivelVetor = 0, cElementoVetor = 0;						// contadores necessários para adicionar em ordem as opcoesOpcoes
	for (int i = 0; i < sizeOpcoesOpcoes; i++) { // inicializamos de forma análoga aos itens do menu principal
		textosMenuOpcoes[i].setCor(0, 255, 0);
		textosMenuOpcoes[i].setAlinhamento(TEXTO_CENTRALIZADO);
		textosMenuOpcoes[i].setEspacamentoLinhas(1.5f);
		textosMenuOpcoes[i].setFonte("fonteNormal");

		if (i < sizeTextoOpcoes) // estamos inicializando opções
			textosMenuOpcoes[i].setWstring(textoOpcoes[i]);
		else {					// estamos inicializando valores
			// aqui as coisas ficam um pouco mais complicadas, pois precisamos "transverssar"/atravessar ou iterar por mais de um nível
			//	dentro do vetor, para fazer isso sem usar iteradores, podemos usar dois contadores, para saber o nível e o elemento em que estamos
			textosMenuOpcoes[i].setWstring(opcoesOpcoes[cNivelVetor][cElementoVetor]);

			if (cElementoVetor == 0)	// aqui deixamos destacados os primeiros elementos, já que são os valores padrão das opções
				textosMenuOpcoes[i].setCor(255, 255, 0);
			if ((cElementoVetor + 1) >= opcoesOpcoes[cNivelVetor].size()) { // nível esgotado, ir para o próximo
				cNivelVetor++;		// próximo nível
				cElementoVetor = 0; // começar novamente pelo primeiro elemento
			} else { // tudo OK, apenas avançar elemento para próxima execução do loop
				cElementoVetor++;	// teoricamente, se o contadorTotalElementosTexto tiver sido mal implementado, isso aqui teria comportamento indefinido
			}
		}
	}
	// agora que temos o número de níveis inicializamos o vetor opcoesAtivas com zeros
	valoresAtivos.resize(sizeOpcoesPrincipais, 0);
}

// terminar de inicializar (aqui fazemos coisas que exigem um tipo completo para a classe Jogo)
void MenuPrincipal::inicializar()
{
	// o menu será desenhado no centro da tela
	xMenu = janela.getLargura() * .5;
	yBase = janela.getAltura() * .5;
	// coordenadas do menu de opções
	xOpcoes = janela.getLargura() * 0.21;	// x = 21%
	xValores = janela.getLargura() * 0.43;	// x = 43%
	yOpcoes = janela.getAltura() * 0.3;		// y = 30%

	for (int i = 0; i < sizeOpcoesPrincipais; i++) {		// infelizmente a libUnicornio não consegue setar a fonte no construtor,
		textosMenuPrincipal[i].setFonte("fonteNormal");		//	a classe Jogo só inicializa seus recursos após já estar com o tipo completo
		textosMenuPrincipalX[i] = (xMenu - ( textosMenuPrincipal[i].getLargura() * .5 ));	// todos os textos do menu são centralizados
		textosMenuPrincipalY[i] = (yBase + espacamentoOpcoes * i);	// todos os textos do menu são centralizados
	}
	for (int i = 0; i < sizeOpcoesSecundarias; i++) {		// como acima
		textosMenuSecundario[i].setFonte("fonteNormal");
		textosMenuSecundarioX[i] = (xMenu - (textosMenuPrincipal[i].getLargura() * .5));	// todos os textos do menu são centralizados
		textosMenuSecundarioY[i] = (yBase + espacamentoOpcoes * i);	// todos os textos do menu são centralizados
	}
	for (int i = 0; i < sizeTextoOpcoes; i++) {
		textosMenuOpcoesX[i] = (xOpcoes - (textosMenuPrincipal[i].getLargura() * .5));	// os textos não são centralizados
		textosMenuOpcoesY[i] = (yOpcoes + espacamentoMenuOpcoes * i);	// os textos não são centralizados
	}
}

MenuPrincipal::~MenuPrincipal()
{
}

void MenuPrincipal::desenhar()
{
	switch (estadoInterno) {
	default:
	case esperando:	// Aqui simplesmente desenhamos e esperamos por eventos no menu principal
		uniDepurar("X0", textosMenuPrincipalX[0]);
		uniDepurar("Y0", textosMenuPrincipalY[0]);
		for (int i = 0; i < sizeOpcoesPrincipais; i++) {	// iteramos pelas opções principais
			textosMenuPrincipal[i].desenhar(xMenu, yBase + (i * 27));		// desenhamos cada opção principal
			int tamanhoTexto = textosMenuPrincipal[i].getWstring().size();	// usamos o tamanho do texto para determinar suas coordenadas máximas no eixo x
			if (mouseSobre(textosMenuPrincipal[i], textosMenuPrincipalX[i], textosMenuPrincipalY[i])) {	// se o mouse estiver sobre a opção atual
				vaiIndice(i);	//	então usamos a função vaiIndice com a opção atual (i) como argumento, para destacá-la
			}
		}

		if (teclado.soltou[TECLA_CIMA] || teclado.soltou[TECLA_W]) {			// vai cima ao apertar ↑ ou W
			vaiCima();
		} else if (teclado.soltou[TECLA_BAIXO] || teclado.soltou[TECLA_S]) {	// vai baixo ao apertar ↓ ou S
			vaiBaixo();
		} else if (teclado.soltou[TECLA_END]) {									// vai base ao apertar end
			vaiBase();
		} else if (teclado.soltou[TECLA_HOME]) {								// vai topo ao apertar home
			vaiTopo();
		} else if (teclado.soltou[TECLA_ENTER] || teclado.soltou[TECLA_ESPACO] || mouse.pressionou[0]) {	// [0] = primeiro botao do mouse
			// executa opção ao pertar enter ou espaço
			vaiOpcao();
		}
		break;
	case jogar:	// Aqui simplesmente desenhamos e esperamos por eventos no menu principal
		for (int i = 0; i < sizeOpcoesSecundarias; i++) {
			textosMenuSecundario[i].desenhar(xMenu, yBase + (i * 27));
			int tamanhoTexto = textosMenuSecundario[i].getWstring().size();
			if (mouseSobre(textosMenuSecundario[i], textosMenuSecundarioX[i], textosMenuSecundarioY[i])) {	// se o mouse estiver sobre a opção atual
				vaiIndiceSecundario(i);	//	então usamos a função vaiIndiceSecundario com a opção atual (i) como argumento, para destacá-la
			}
		}

		if (teclado.soltou[TECLA_CIMA] || teclado.soltou[TECLA_W]) {
			vaiCimaSecundario();
		}
		else if (teclado.soltou[TECLA_BAIXO] || teclado.soltou[TECLA_S]) {
			vaiBaixoSecundario();
		}
		else if (teclado.soltou[TECLA_END]) {
			vaiBaseSecundario();
		}
		else if (teclado.soltou[TECLA_HOME]) {
			vaiTopoSecundario();
		}
		else if (teclado.soltou[TECLA_ENTER] || teclado.soltou[TECLA_ESPACO] || mouse.pressionou[0]) {	// [0] = primeiro botao do mouse
			vaiOpcaoSecundario();
		}
		break;
	case opcoes:
			// prefiro fazer a classe mudar de estado (valores) em uma função específica
			gerenciarMenuOpcoes();
		break;
	case creditos:
		resetarMenuPrincipal(); // usabilidade: antes de retornar para o menu principal queremos voltar para a primeira opção
		textoHandler.desenhar(janela.getLargura()*.5, janela.getAltura()*.5);
		if (teclado.soltou[TECLA_ENTER] || teclado.soltou[TECLA_ESPACO] || mouse.pressionou[0]) {	// [0] = primeiro botao do mouse
			estadoInterno = esperando;
		}
		break;
	case ajuda:
		resetarMenuPrincipal(); // usabilidade: antes de retornar para o menu principal queremos voltar para a primeira opção
		// não esquecer de só colocar 'blablabla', como naquele trabalho que o professor gostou tanto,
		//	que chegou a mostrar pra nós
		textoHandler.desenhar(janela.getLargura()*.5, janela.getAltura()*.5);
		if (teclado.soltou[TECLA_ENTER] || teclado.soltou[TECLA_ESPACO] || mouse.pressionou[0]) {	// [0] = primeiro botao do mouse
			resetarMenuPrincipal(); // usabilidade: antes de retornar para o menu principal queremos voltar para a primeira opção
			estadoInterno = esperando;
		}
		break;
	case sair:
			// libUnicornio deve fazer isso pra nós
		break;
	}
}
// essas funções gerenciam os movimentos de seleção do menu principal
void MenuPrincipal::vaiBaixo()
{
	textosMenuPrincipal[ativo].setCor(0, 255, 0);
	ativo = modulo((ativo + 1), sizeOpcoesPrincipais);
	textosMenuPrincipal[ativo].setCor(255, 255, 0);
}
void MenuPrincipal::vaiCima()
{
	textosMenuPrincipal[ativo].setCor(0, 255, 0);
	ativo = modulo((ativo - 1), sizeOpcoesPrincipais);
	textosMenuPrincipal[ativo].setCor(255, 255, 0);
}
void MenuPrincipal::vaiTopo()
{
	textosMenuPrincipal[ativo].setCor(0, 255, 0);
	ativo = 0; // 0 = primeiro elemento
	textosMenuPrincipal[ativo].setCor(255, 255, 0);
}
void MenuPrincipal::vaiBase()
{
	textosMenuPrincipal[ativo].setCor(0, 255, 0);
	ativo = sizeOpcoesPrincipais - 1; // sizeOpcoesPrincipais = tamanho, como começa em zero reduzimos 1
	textosMenuPrincipal[ativo].setCor(255, 255, 0);
}
void MenuPrincipal::vaiIndice(int i)
{
	textosMenuPrincipal[ativo].setCor(0, 255, 0);
	ativo = i; // recebemos o índice i
	textosMenuPrincipal[ativo].setCor(255, 255, 0);
}
// essas funções gerenciam os movimentos de seleção do menu secundário (modos de jogo)
void MenuPrincipal::vaiBaixoSecundario()
{
	textosMenuSecundario[ativo].setCor(0, 255, 0);
	ativo = modulo((ativo + 1), sizeOpcoesSecundarias);
	textosMenuSecundario[ativo].setCor(255, 255, 0);
}
void MenuPrincipal::vaiCimaSecundario()
{
	textosMenuSecundario[ativo].setCor(0, 255, 0);
	ativo = modulo((ativo - 1), sizeOpcoesSecundarias);
	textosMenuSecundario[ativo].setCor(255, 255, 0);
}
void MenuPrincipal::vaiTopoSecundario()
{
	textosMenuSecundario[ativo].setCor(0, 255, 0);
	ativo = 0; // 0 = primeiro elemento
	textosMenuSecundario[ativo].setCor(255, 255, 0);
}
void MenuPrincipal::vaiBaseSecundario()
{
	textosMenuSecundario[ativo].setCor(0, 255, 0);
	ativo = sizeOpcoesSecundarias - 1; // sizeOpcoesPrincipais = tamanho, como começa em zero reduzimos 1
	textosMenuSecundario[ativo].setCor(255, 255, 0);
}
void MenuPrincipal::vaiIndiceSecundario(int i)
{
	textosMenuSecundario[ativo].setCor(0, 255, 0);
	ativo = i; // recebemos o índice i
	textosMenuSecundario[ativo].setCor(255, 255, 0);
}
// essas gerenciam os movimentos de seleção do menu de opções
void MenuPrincipal::vaiBaixoOpcoes()
{
	/* nas classes vai{direção} basicamente mudamos a cor da opção selecionada
		anteriormente, alteramos o valor do índice ativo, e por fim
		alteramos a cor da nova opcão correspondente a essa novo índice	*/
	textosMenuOpcoes[ativo].setCor(0, 255, 0);
	ativo = modulo((ativo + 1), sizeTextoOpcoes);
	textosMenuOpcoes[ativo].setCor(255, 255, 0);
}
void MenuPrincipal::vaiCimaOpcoes()
{
	/* nas classes vai{direção} basicamente mudamos a cor da opção selecionada
	anteriormente, alteramos o valor do índice ativo, e por fim
	alteramos a cor da nova opcão correspondente a essa novo índice	*/
	textosMenuOpcoes[ativo].setCor(0, 255, 0);
	ativo = modulo((ativo - 1), sizeTextoOpcoes);
	textosMenuOpcoes[ativo].setCor(255, 255, 0);
}
void MenuPrincipal::vaiTopoOpcoes()
{
	/* nas classes vai{direção} basicamente mudamos a cor da opção selecionada
	anteriormente, alteramos o valor do índice ativo, e por fim
	alteramos a cor da nova opcão correspondente a essa novo índice	*/
	textosMenuOpcoes[ativo].setCor(0, 255, 0);
	ativo = 0; // 0 = primeiro elemento
	textosMenuOpcoes[ativo].setCor(255, 255, 0);
}
void MenuPrincipal::vaiBaseOpcoes()
{
	/* nas classes vai{direção} basicamente mudamos a cor da opção selecionada
	anteriormente, alteramos o valor do índice ativo, e por fim
	alteramos a cor da nova opcão correspondente a essa novo índice	*/
	textosMenuOpcoes[ativo].setCor(0, 255, 0);
	ativo = sizeTextoOpcoes - 1; // sizeTextoOpcoes = tamanho, como começa em zero reduzimos 1
	textosMenuOpcoes[ativo].setCor(255, 255, 0);
}
void MenuPrincipal::vaiIndiceOpcoes(int i)
{
	textosMenuOpcoes[ativo].setCor(0, 255, 0);
	ativo = i; // recebemos o índice i
	textosMenuOpcoes[ativo].setCor(255, 255, 0);
}
void MenuPrincipal::vaiDireitaOpcoes()
{
	/* nas classes vai{direção} basicamente mudamos a cor da opção selecionada
	anteriormente, alteramos o valor do índice ativo, e por fim
	alteramos a cor da nova opcão correspondente a essa novo índice	*/

	/****** textosMenuOpcoes é um vetor, de 0 a (sizeOpcoesPrincipais - 2) ele contém opções,
	de sizeOpcoesPrincipais até sizeOpcoesPrincipais.size() ele contém valores.

	o valor destacado atual é um composto de:
	sizeOpcoesPrincipais-1 ([0] dos valores) + numero de elementos dos niveis superiores + valoresAtivos[ativo]
	decompondo: sizeOpcoesPrincipais-1 equivale ao elemento [0], ao primeiro valor,
	numero de elementos dos niveis superiores é obtido através da soma dos sizes() dos níveis inferiores,
	e finalmente valoresAtivos[ativo] indica qual dos valores na "linha atual" estava destacado
	*******/
	int numeroElementosAnteriores = sizeOpcoesPrincipais - 1;	// instanciamos nosso contador, iniciado no "0" (sizeOpcoesPrincipais)
	for (int i = 0; i < ativo; i++) {	// nesse loop contabilizamos os elementos dos niveis anteriores
		numeroElementosAnteriores += opcoesOpcoes[i].size();	//	ou nenhum se o nível for 0
	}
	textosMenuOpcoes[(numeroElementosAnteriores + valoresAtivos[ativo])].setCor(0, 255, 0);
	valoresAtivos[ativo] = modulo((valoresAtivos[ativo] + 1), opcoesOpcoes[ativo].size());
	textosMenuOpcoes[(numeroElementosAnteriores + valoresAtivos[ativo])].setCor(255, 255, 0);
}
void MenuPrincipal::vaiEsquerdaOpcoes()
{
	/* nas classes vai{direção} basicamente mudamos a cor da opção selecionada
	anteriormente, alteramos o valor do índice ativo, e por fim
	alteramos a cor da nova opcão correspondente a essa novo índice	*/

	/****** textosMenuOpcoes é um vetor, de 0 a (sizeOpcoesPrincipais - 2) ele contém opções,
	de sizeOpcoesPrincipais até sizeOpcoesPrincipais.size() ele contém valores.

	o valor destacado atual é um composto de:
	sizeOpcoesPrincipais-1 ([0] dos valores) + numero de elementos dos niveis superiores + valoresAtivos[ativo]
	decompondo: sizeOpcoesPrincipais-1 equivale ao elemento [0], ao primeiro valor,
	numero de elementos dos niveis superiores é obtido através da soma dos sizes() dos níveis inferiores,
	e finalmente valoresAtivos[ativo] indica qual dos valores na "linha atual" estava destacado
	*******/
	int numeroElementosAnteriores = sizeOpcoesPrincipais - 1;	// instanciamos nosso contador, iniciado no "0" (sizeOpcoesPrincipais)
	for (int i = 0; i < ativo; i++) {	// nesse loop contabilizamos os elementos dos niveis anteriores
		numeroElementosAnteriores += opcoesOpcoes[i].size();	//	ou nenhum se o nível for 0
	}
	textosMenuOpcoes[(numeroElementosAnteriores + valoresAtivos[ativo])].setCor(0, 255, 0);
	valoresAtivos[ativo] = modulo((valoresAtivos[ativo] - 1), opcoesOpcoes[ativo].size());
	textosMenuOpcoes[(numeroElementosAnteriores + valoresAtivos[ativo])].setCor(255, 255, 0);
}
// aqui removemos o destaque da opção do índice (ativo), depois retornamos o índice para a primeira opção,
//	e finalmente destacamos o texto correspondente ao novo índice (0)
void MenuPrincipal::resetarMenuPrincipal()
{
	for (int i = 1; i < sizeOpcoesPrincipais; i++) {
		textosMenuPrincipal[i].setCor(0, 255, 0);	// retornamos as opções para a cor normal
	}
	ativo = jogar;			// em nome da usabilidade retornamos a opção para a primeira opção
	textosMenuPrincipal[ativo].setCor(255, 255, 0);	// agora alteramos a cor da primeira opção pra mostrar que ela está selecionada
}

/* alteramos o estadoInterno ou aplicacao.sair;
	executamos código necessário (se existir) antes da execução voltar pro loop desenhar
*/
void MenuPrincipal::vaiOpcao()
{
	switch (ativo) {
	case jogar:
		estadoInterno = jogar;
		//textosMenuPrincipal[Jogar].setCor(255, 0, 0);
		break;
	case opcoes:
		estadoInterno = opcoes;
		prepararTextoOpcoes();
		//textosMenuPrincipal[Opcoes].setCor(255, 0, 0);
		break;
	case creditos:
		estadoInterno = creditos;
		prepararTextoCreditos();
		//textosMenuPrincipal[Creditos].setCor(255, 0, 0);
		break;
	case ajuda:
		estadoInterno = ajuda;
		prepararTextoAjuda();
		//textosMenuPrincipal[Ajuda].setCor(255, 0, 0);
		break;
	case sair:
		aplicacao.sair = true; // libUnicornio fornece essa facilidade
		//textosMenuPrincipal[Sair].setCor(255, 0, 0);
		break;
	}
}

/* alteramos o estadoExterno
	interagimos com a classe jogo para enviar as variáveis corretas
	e suspender a execução do menu
*/
void MenuPrincipal::vaiOpcaoSecundario()
{
	switch (ativo) {
	case halterofilismoCampanha:
		obteveEscolha = true;
		break;
	case menuzando:
		vaiTopoSecundario(); // "resetarMenuSecundario()", para corrigir o destacamento das opcoes
		estadoInterno = esperando;
		break;
	}
}

// aqui configuramos o textoHandler para o menu de opções
void MenuPrincipal::prepararTextoOpcoes()
{
	textoHandler.setCor(150, 200, 50);
	textoHandler.setAlinhamento(TEXTO_CENTRALIZADO);
	textoHandler.setEspacamentoLinhas(2.0f);
	textoHandler.setWstring(textoCabecalhoOpcoes);
	textoHandler.setFonte("fonteNormal");
	// setar fonte nos textos de opções
	for (int i = 0; i < sizeOpcoesOpcoes; i++) {
		textosMenuOpcoes[i].setFonte("fonteNormal");
	}
	ativo = 0; // entramos nas opções direto na primeira opção
	textosMenuOpcoes[ativo].setCor(255, 255, 0);
}
// aqui configuramos o textoHandler para os créditos
void MenuPrincipal::prepararTextoCreditos()
{
	textoHandler.setCor(100, 20, 50);
	textoHandler.setAlinhamento(TEXTO_CENTRALIZADO);
	textoHandler.setEspacamentoLinhas(2.0f);
	textoHandler.setWstring(textoCreditos);
	textoHandler.setFonte("fonteNormal");
}
// aqui configuramos o textoHandler para o menu de ajuda
void MenuPrincipal::prepararTextoAjuda()
{
	textoHandler.setCor(100, 20, 50);
	textoHandler.setAlinhamento(TEXTO_CENTRALIZADO);
	textoHandler.setEspacamentoLinhas(2.0f);
	textoHandler.setWstring(textoAjuda[0]);
	textoHandler.setFonte("fonteNormal");
}

/* Aqui nós:
	1. desenhamos as opções e valores correspondentes com espaçamento adequado
	2. implementamos um sistema de seleção parecido com o do menu principal (com duplo realçamento)
		2.1 precisamos manter as seleções realçadas, e setar os valores correspondentes ao sair do menu
*/
void MenuPrincipal::gerenciarMenuOpcoes()
{
	// y = yBase + incrementoY
	// x = xValores + cElementoVetor * incrementoX
	// y = 90% - decrementoY
	int cNivelVetor = 0, cElementoVetor = 0;

	////////////////////////////////////////////////////////////////////////
	uniDepurar("Linha ativa", ativo);
	uniDepurar("Coluna ativa (nos valores)", valoresAtivos[ativo]);
	////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < sizeOpcoesOpcoes; i++) {	// primeiro precisamos posicionar cada elemento de acordo com sua função
												//	o que significa opções a esquerda, valores a direita
												//	e precisamos fazer isso em função de i ou do nível correspondente das variáveis
		if (i < sizeTextoOpcoes) { // estamos desenhando opções
			textosMenuOpcoes[i].desenhar(xOpcoes, yOpcoes + (i * espacamentoMenuOpcoes)); // x é fixo para as opcoes, y varia (por nível) igualmente para opcoes e valores
			if (mouseSobre(textosMenuOpcoes[i], textosMenuOpcoesX[i], textosMenuOpcoesY[i])) {	// se o mouse estiver sobre a opção atual
				vaiIndiceOpcoes(i);
			}
		} else {					// estamos desenhando valores, aqui o y deve variar apenas em função de cNivelVetor, nunca em função de i
								//	além disso, o x deve variar em função de cElementoVetor
			// como antes, aqui as coisas ficam um pouco mais complicadas, pois precisamos "transverssar"/atravessar ou iterar por mais de um nível no vetor
			//	dentro do vetor, para fazer isso sem usar iteradores, novamente vamos usar dois contadores, pois é o meio aceitável mais eficiente
			textosMenuOpcoes[i].desenhar(xValores + (cElementoVetor * espacamentoValoresOpcoes), yOpcoes + (cNivelVetor * espacamentoMenuOpcoes));
			if ((cElementoVetor + 1) >= opcoesOpcoes[cNivelVetor].size()) { // nível esgotado, ir para o próximo
				cNivelVetor++;		// próximo nível
				cElementoVetor = 0; // começar novamente pelo primeiro elemento
			}
			else { // tudo OK, apenas avançar elemento para próxima execução do loop
				cElementoVetor++;	// teoricamente, se o contadorTotalElementosTexto tiver sido mal implementado, isso aqui teria comportamento indefinido
			}
		}
	}
	// por fim desenhamos o cabeçalho
	textoHandler.desenhar(janela.getLargura()*.5, janela.getAltura()*.79);

	// aqui gerenciamos as seleções do usuário
	// a selação varia em dois eixos, em y (W S, ↑ ↓)  o jogador muda a opção, em x (A D, ← →) o jogador muda a variável;
	//	ambas precisam ter a cor destacada, no eixo x a mudança deve ser permanente
	if (teclado.soltou[TECLA_BAIXO] || teclado.soltou[TECLA_S]){
		vaiBaixoOpcoes();
	} else if (teclado.soltou[TECLA_CIMA] || teclado.soltou[TECLA_W]) {
		vaiCimaOpcoes();
	}
	// agora gerenciamos a seleção de valores, fazemos isso usando o vetor opcoesAtivas
	else if (teclado.soltou[TECLA_DIR] || teclado.soltou[TECLA_D]) {
		vaiDireitaOpcoes();
	} else if (teclado.soltou[TECLA_ESQ] || teclado.soltou[TECLA_A]) {
		vaiEsquerdaOpcoes();
	} else if (teclado.soltou[TECLA_HOME]) {
		vaiTopoOpcoes();
	} else if (teclado.soltou[TECLA_END]) {
		vaiBaseOpcoes();
	}
	// por fim, verificamos se devemos voltar ao menu principal
	else if (teclado.soltou[TECLA_ESPACO]) // antes de sair salvamos os estados
	{
		resetarMenuPrincipal();	// de graça essa função reseta o ativo para valores sãos
		estadoInterno = esperando;	// para efetivamente retornarmos a função desenhar() para o menu principal
	}
}

std::vector<int> MenuPrincipal::getOpcoes()
{
	return valoresAtivos;
}

/* MenuPrincipal nasceu com um propósito, para responder a grande questão de sua vida!!!
	O jogador escolheu?
*/
bool MenuPrincipal::escolheu()
{
	return obteveEscolha;
}

bool MenuPrincipal::mouseSobre(Texto objetoTexto, int x, int y)	// eu usaria referência pro const, mas quem explicaria tal coisa?
{
	if (mouse.y >= (y - 15) && mouse.y <= (y + objetoTexto.getAlturaLinha(0)) &&	// se o ponteiro está verticalmente próximo a esse objeto texto
		(mouse.x >= (x - 15) && (mouse.x <= (x + objetoTexto.getLargura())))) {	// também verificar se ele está horizontalmente próximo
		// caso positivo, o ponteiro provavelmente está sobre a opção atual (textosMenuPrincipal[i])
		return true;	//	então usamos a função vaiIndice com a opção atual (i) como argumento, para destacá-la
	}
	return false;
}