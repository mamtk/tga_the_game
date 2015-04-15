#include "MenuPrincipal.h"
#include "util.h"


MenuPrincipal::MenuPrincipal()
{
	opcoesPrincipais = { L"Iniciar Jogo", L"Opções", L"Ajuda", L"Créditos", L"Sair" };
	textosMenuPrincipal.resize(opcoesPrincipais.size());	// iniciamos a memória, pois já sabemos o que vamos utilizar 
	sizeOpcoesPrincipais = textosMenuPrincipal.size();	// assim não precisamos ficar chamando size(), e nem usar iteradores...

	// inicializar objetos Texto para cada uma das opções do menu principal
	for (int i = 0; i < sizeOpcoesPrincipais; i++) {
		textosMenuPrincipal[i].setCor(0, 255, 0);
		textosMenuPrincipal[i].setAlinhamento(TEXTO_CENTRALIZADO);
		textosMenuPrincipal[i].setEspacamentoLinhas(1.5f);
		textosMenuPrincipal[i].setWstring(opcoesPrincipais[i]);
		textosMenuPrincipal[i].setFonte("fonteNormal");
	}
	textosMenuPrincipal[0].setCor(255, 255, 0);

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
	sizetextoOpcoes = textoOpcoes.size();	// assim não precisamos ficar chamando size(), e nem usar iteradores...
	opcoesOpcoes.resize(opcoesPrincipais.size());	// iniciamos a memória, pois já sabemos o que vamos utilizar

	int contadorTotalElementosTexto = sizetextoOpcoes;	// vamos contar também os elementos texto de variáveis, para inicializar corretamente textosMenuOpcoes
	// inicializar os "valores" possiveis para cada texto de opção
	for (int i = 0; i < sizetextoOpcoes; i++) {
		switch (i) { // talvez fique mais fácil de entender se eu usar um loop for (embora fique mais lento, só roda uma vez)
		case 0: // variáveis possíveis para a opção [0] do textoOpcoes
			opcoesOpcoes[i] = { L"Normal", L"Difícil", L"Impossível", L"Impossível?" }; // opções para [0] (dificuldade)
			contadorTotalElementosTexto += opcoesOpcoes[i].size(); // fazer a contabilidade corretamente
			break;
		case 1: // variáveis possíveis para a opção [1] do textoOpcoes
			opcoesOpcoes[i] = { L"Não", L"Sim" }; // opções para [2] (desativar eventos pseudoaleatórios)
			contadorTotalElementosTexto += opcoesOpcoes[i].size(); // fazer a contabilidade corretamente
			break;
		case 2: // variáveis possíveis para a opção [2] do textoOpcoes
			opcoesOpcoes[i] = { L"Não", L"Sim" }; // opções para [3] (desativar fatality)
			contadorTotalElementosTexto += opcoesOpcoes[i].size(); // fazer a contabilidade corretamente
			break;
		case 3: // variáveis possíveis para a opção [2] do textoOpcoes
			opcoesOpcoes[i] = { L"Não", L"Sim" }; // opções para [4] (desativar som)
			contadorTotalElementosTexto += opcoesOpcoes[i].size(); // fazer a contabilidade corretamente
			break;
		}
	}
	// agora que temos opcoes+valores, sabemos o tamanho do vetor de textos necessario
	textosMenuOpcoes.resize(contadorTotalElementosTexto);	// os primeiros n = sizetextoOpcoes são as opções, os elementos seguintes são variáveis
															//	não precisamos de índice, pois o textosMenuOpcoes nos fornece um de graça
	int cNivelVetor = 0, cElementoVetor = 0;						// contadores necessários para adicionar em ordem as opcoesOpcoes
	for (int i = 0; i < contadorTotalElementosTexto; i++) { // inicializamos de forma análoga aos itens do menu principal
		textosMenuOpcoes[i].setCor(0, 255, 0);
		textosMenuOpcoes[i].setAlinhamento(TEXTO_CENTRALIZADO);
		textosMenuOpcoes[i].setEspacamentoLinhas(1.5f);
		textosMenuOpcoes[i].setFonte("fonteNormal");

		if (i < sizetextoOpcoes) // estamos inicializando opções
			textosMenuOpcoes[i].setWstring(textoOpcoes[i]);
		else {					// estamos inicializando valores
			// aqui as coisas ficam um pouco mais complicadas, pois precisamos "transverssar"/atravessar ou iterar por mais de um nível
			//	dentro do vetor, para fazer isso sem usar iteradores, podemos usar dois contadores, para saber o nível e o elemento em que estamos
			textosMenuOpcoes[i].setWstring(opcoesOpcoes[cNivelVetor][cElementoVetor]);
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


MenuPrincipal::~MenuPrincipal()
{
}

void MenuPrincipal::desenhar()
{
	// o menu é desenhado no meio da tela
	int xMenu = janela.getLargura() * .5;
	int yBase = janela.getAltura() * .5;

	switch (estadoInterno) {
	default:
	case Esperando:	// Aqui simplesmente desenhamos e esperamos por eventos no menu principal
		for (int i = 0; i < sizeOpcoesPrincipais; i++) {
			textosMenuPrincipal[i].setFonte("fonteNormal");
			textosMenuPrincipal[i].desenhar(xMenu, yBase + (i * 27));
			int tamanhoTexto = textosMenuPrincipal[i].getWstring().size();
			if (mouse.y >= (yBase + (27 * i) - 15) && mouse.y <= (yBase + (27 * i)) && \
				(mouse.x >= (xMenu - tamanhoTexto * 5) && (mouse.x <= (xMenu + tamanhoTexto * 5)))) {
				// mouse provavelmente sobre a opção atual
				vaiIndice(i);
			}
		}

		if (teclado.soltou[TECLA_CIMA] || teclado.soltou[TECLA_W]) {
			vaiCima();
		} else if (teclado.soltou[TECLA_BAIXO] || teclado.soltou[TECLA_S]) {
			vaiBaixo();
		} else if (teclado.soltou[TECLA_END]) {
			vaiBase();
		} else if (teclado.soltou[TECLA_HOME]) {
			vaiTopo();
		} else if (teclado.soltou[TECLA_ENTER] || teclado.soltou[TECLA_ESPACO] || mouse.pressionou[0]) {	// [0] = primeiro botao do mouse
			vaiOpcao();
		}
		break;
	case Opcoes:
			// prefiro fazer a classe mudar de estado (valores) em uma função específica
			gerenciarMenuOpcoes();
		break;
	case Creditos:
		textoHandler.desenhar(janela.getLargura()*.5, janela.getAltura()*.5);
		if (teclado.soltou[TECLA_ENTER] || teclado.soltou[TECLA_ESPACO] || mouse.pressionou[0]) {	// [0] = primeiro botao do mouse
			resetarMenuPrincipal(); // usabilidade: antes de retornar para o menu principal queremos voltar para a primeira opção
			estadoInterno = Esperando;
		}
		break;
	case Ajuda:
		// não esquecer de só colocar 'blablabla', como naquele trabalho que o professor gostou tanto,
		//	que chegou a mostrar pra nós
		textoHandler.desenhar(janela.getLargura()*.5, janela.getAltura()*.5);
		if (teclado.soltou[TECLA_ENTER] || teclado.soltou[TECLA_ESPACO] || mouse.pressionou[0]) {	// [0] = primeiro botao do mouse
			resetarMenuPrincipal(); // usabilidade: antes de retornar para o menu principal queremos voltar para a primeira opção
			estadoInterno = Esperando;
		}
		break;
	case Sair:
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
// e essas gerenciam os movimentos de seleção do menu de opções
void MenuPrincipal::vaiBaixoOpcoes()
{
	textosMenuOpcoes[ativo].setCor(0, 255, 0);
	ativo = modulo((ativo + 1), sizetextoOpcoes);
	textosMenuOpcoes[ativo].setCor(255, 255, 0);
}
void MenuPrincipal::vaiCimaOpcoes()
{
	textosMenuOpcoes[ativo].setCor(0, 255, 0);
	ativo = modulo((ativo - 1), sizetextoOpcoes);
	textosMenuOpcoes[ativo].setCor(255, 255, 0);
}
void MenuPrincipal::vaiTopoOpcoes()
{
	textosMenuOpcoes[ativo].setCor(0, 255, 0);
	ativo = 0; // 0 = primeiro elemento
	textosMenuOpcoes[ativo].setCor(255, 255, 0);
}
void MenuPrincipal::vaiBaseOpcoes()
{
	textosMenuOpcoes[ativo].setCor(0, 255, 0);
	ativo = sizetextoOpcoes - 1; // sizetextoOpcoes = tamanho, como começa em zero reduzimos 1
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
	int a = valoresAtivos[ativo];
	textosMenuOpcoes[(sizeOpcoesPrincipais + ativo + valoresAtivos[ativo])].setCor(0, 255, 0);
	valoresAtivos[ativo] = modulo((valoresAtivos[ativo] + 1), opcoesOpcoes[ativo].capacity()-1);
	textosMenuOpcoes[(sizeOpcoesPrincipais + ativo + valoresAtivos[ativo])].setCor(255, 255, 0);
}
void MenuPrincipal::vaiEsquerdaOpcoes()
{

	textosMenuOpcoes[(sizeOpcoesPrincipais + ativo + valoresAtivos[ativo])].setCor(0, 255, 0);
	valoresAtivos[ativo] = modulo((valoresAtivos[ativo] - 1), opcoesOpcoes[ativo].size());
	textosMenuOpcoes[(sizeOpcoesPrincipais + ativo + valoresAtivos[ativo])].setCor(255, 255, 0);
}
void MenuPrincipal::resetarMenuPrincipal()
{
	textosMenuPrincipal[ativo].setCor(0, 255, 0);	// primeiro retornamos créditos para a cor normal
	ativo = Jogar;						// em nome da usabilidade retornamos a opção para a primeira opção
	textosMenuPrincipal[ativo].setCor(255, 255, 0);	// agora alteramos a cor da primeira opção pra mostrar que ela está selecionada
}

/* alteramos o estadoInterno ou querSair;
	executamos código necessário (se existir) antes da execução voltar pro loop desenhar
*/
void MenuPrincipal::vaiOpcao()
{
	switch (ativo) {
	case Jogar:
		estadoInterno = Jogar;
		//textosMenuPrincipal[Jogar].setCor(255, 0, 0);
		break;
	case Opcoes:
		estadoInterno = Opcoes;
		prepararTextoOpcoes();
		//textosMenuPrincipal[Opcoes].setCor(255, 0, 0);
		break;
	case Creditos:
		estadoInterno = Creditos;
		prepararTextoCreditos();
		//textosMenuPrincipal[Creditos].setCor(255, 0, 0);
		break;
	case Ajuda:
		estadoInterno = Ajuda;
		prepararTextoAjuda();
		//textosMenuPrincipal[Ajuda].setCor(255, 0, 0);
		break;
	case Sair:
		aplicacao.sair = true; // libUnicornio fornece essa facilidade
		//textosMenuPrincipal[Sair].setCor(255, 0, 0);
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
	int totalElementos = textosMenuOpcoes.size(); // contador de elementos texto (para não ficar chamando size() desnecessariamente)
	for (int i = 0; i < totalElementos; i++) {
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
	int totalElementos = textosMenuOpcoes.size();
	int xOpcoes = janela.getLargura()*0.15; // x = 5%
	int xValores = janela.getLargura()*0.39; // x = 35%
	int incrementoY = 71; // y = yBase + incrementoY
	int incrementoX = 150; // x = xValores + cElementoVetor * incrementoX
	int yBase = janela.getAltura()*0.1; // y = 90% - decrementoY
	int cNivelVetor = 0, cElementoVetor = 0;
	for (int i = 0; i < totalElementos; i++) {	// primeiro precisamos posicionar cada elemento de acordo com sua função
												//	o que significa opções a esquerda, valores a direita
												//	e precisamos fazer isso em função de i ou do nível correspondente das variáveis
		if (i < sizetextoOpcoes) // estamos desenhando opções
			textosMenuOpcoes[i].desenhar(xOpcoes, yBase + (i * incrementoY)); // x é fixo para as opcoes, y varia (por nível) igualmente para opcoes e valores
		else {					// estamos desenhando valores, aqui o y deve variar apenas em função de cNivelVetor, nunca em função de i
								//	além disso, o x deve variar em função de cElementoVetor
			// como antes, aqui as coisas ficam um pouco mais complicadas, pois precisamos "transverssar"/atravessar ou iterar por mais de um nível no vetor
			//	dentro do vetor, para fazer isso sem usar iteradores, novamente vamos usar dois contadores, pois é o meio aceitável mais eficiente
			textosMenuOpcoes[i].desenhar(xValores + (cElementoVetor * incrementoX), yBase + (cNivelVetor * incrementoY));
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
	if (teclado.soltou[TECLA_DIR] || teclado.soltou[TECLA_D]) {
		vaiDireitaOpcoes();
	}
	// por fim, verificamos se devemos voltar ao menu principal
	else if (teclado.soltou[TECLA_ESPACO]) // antes de sair salvamos os estados
	{
		resetarMenuPrincipal();	// de graça essa função reseta o ativo para valores sãos
		estadoInterno = Esperando;	// para efetivamente retornarmos a função desenhar() para o menu principal
	}
}