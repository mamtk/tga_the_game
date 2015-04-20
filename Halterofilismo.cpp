#include "Halterofilismo.h"

Halterofilismo::Halterofilismo()
{
	
}


Halterofilismo::~Halterofilismo()
{
}

// não é possível fazer isso no construtor, pois a classe Halterofilismo é parte da classe Jogo
//	então o construtor dessa classe é executado antes da classe Jogo ter um tipo completo
void Halterofilismo::inicializar(int estado, vector<int> valoresOpcoesDeJogo)
{
	tipo = levantamentoNormal;
	estadoDoJogo = (EstadoDoJogo)estado;
	opcoesDeJogo = valoresOpcoesDeJogo;
	// começamos com a barra no centro da tela
	xBarra = xCentro = janela.getLargura() * .5;
	yBarra = yCentro = janela.getAltura() * .5;
	xyBarraProgresso = { xCentro - 450, yCentro - 100 };

	// inicializar sprites
	barra.setSpriteSheet("obj_HalterBarra");
	barra.setEscala(5, 5);
	fundo.setSpriteSheet("fundo_Halter01");
	protagonista.setSpriteSheet("per_Halter01");
	protagonista.setAnimacao(0);
	protagonista.setEscala(5, 5);
	// TODO: determinar dificuldades corretamente: velAnimBarra, taxaDificuldade, impacto das pragas (taxa ou vel ou ambos?)
	protagonista.setVelocidadeAnimacao(25);
	barraProgresso.setSpriteSheet("fx_HalterBarra");
	barraProgresso.setVelocidadeAnimacao(5);
	sizeBarraProgressoFrames = barraProgresso.getSpriteSheet()->getNumFramesDaAnimacao(0);
	progressoMaximo = sizeBarraProgressoFrames - 1;	// reduzimos 1, pois: indice ultimo elemento = total - 1
	xyLinhasObjetivo.resize(sizeBarraProgressoFrames);	// iniciar memória, antes de utilizá-la

	// inicializar valores xy da linha de progresso para cada frame da sprite
	int xBase = xyBarraProgresso[0] - barraProgresso.getLargura() * .5;	// como o desenho é centralizado, reduzimos apenas metade da largura
	int yBase = xyBarraProgresso[1] + 200;
	xyLinhasObjetivo[0] = { xBase, yBase + 6 };		// todos os valores de acordo com o GIMP
	xyLinhasObjetivo[1] = { xBase, yBase - 42 };
	xyLinhasObjetivo[2] = { xBase, yBase - 82 };
	xyLinhasObjetivo[3] = { xBase, yBase - 122 };
	xyLinhasObjetivo[4] = { xBase, yBase - 162 };
	xyLinhasObjetivo[5] = { xBase, yBase - 202 };
	xyLinhasObjetivo[6] = { xBase, yBase - 241 };
	xyLinhasObjetivo[7] = { xBase, yBase - 209 };
	xyLinhasObjetivo[8] = { xBase, yBase - 322 };
	xyLinhasObjetivo[9] = { xBase, yBase - 362 };
	xyLinhasObjetivo[10] = { xBase, yBase - 400 };

	// inicializar objetos texto
	// temporizador
	xTemporizador = xCentro;
	yTemporizador = yCentro * .15;
	textoTemporizador.setAlinhamento(TEXTO_CENTRALIZADO);
	textoTemporizador.setEspacamentoLinhas(1.5f);
	textoTemporizador.setCor(255, 255, 255); // começamos com branco
	textoTemporizador.setFonte("fonteGrande");
	// textoTemporizador2 a.k.a. sombra do texto (para que o texto nunca fique invisivel, mesmo em fundos brancos)
	temporizadorSombra.setAlinhamento(TEXTO_CENTRALIZADO);
	temporizadorSombra.setEspacamentoLinhas(1.5f);
	temporizadorSombra.setCor(0, 0, 0); // começamos e terminamos com preto
	temporizadorSombra.setFonte("fonteGrandeSombra");
	textoTemporizador.setWstring(L"2:35");
	temporizadorSombra.setWstring(L"2:35");

	// inicializar ponto no tempo para função dificultar
	temporizadorDificultar = clock();	// retorna o "tick" atual, pode-se dizer que vamos armazenar o "tempo" atual

	// a parte complicada de escolher o multiplicador da dificuldade é tornar a progressão gradual, por causa do sandbox (modo contínuo)
	switch (valoresOpcoesDeJogo[valorDificuldade]) {	// por isso aqui definimos valores com uma distância cada vez menor
	case 0:	// medio
		dificuldade = 1;	// 7
		chancePraga = 60;	// 1 chance em 60 (por segundo)
		break;
	case 1:	// difícil
		dificuldade = 12;	// 11
		chancePraga = 30;	// 1 chance em 30
		break;
	case 2:	// impossível
		dificuldade = 15;	// 15
		chancePraga = 15;	// 1 chance em 15
		break;
	case 3:	// impossível?
		dificuldade = 17;	// 17, e duvido!
		chancePraga = 7;	// 1 chance em 7
		break;
	}
	fatorDificuldade = 1000 / dificuldade;

	// inicializar menus
	// vitoria
	vector<wstring> vitoriaFatalityInativoStr = { L"Prosseguir", L"Repetir", L"Voltar ao menu", L"Sair do jogo" };
	vector<wstring> vitoriaFatalityAtivoStr = { L"Prosseguir", L"Tentar desafio", L"Repetir", L"Voltar ao menu", L"Sair do jogo" };
	vitoriaFatalityAtivo.inicializar(vitoriaFatalityInativoStr);
	vitoriaFatalityInativo.inicializar(vitoriaFatalityAtivoStr);
	// derrota
	vector<wstring> derrotaStr = { L"Repetir", L"Reiniciar", L"Voltar ao menu", L"Sair do jogo" };	// reiniciar volta para o preparar jogo
	vector<wstring> derrotaFatalityStr = { L"Continuar", L"Reiniciar", L"Voltar ao menu", L"Sair do jogo" };	// só aparece no modo campanha
	derrota.inicializar(derrotaStr);
	derrotaFatality.inicializar(derrotaFatalityStr);

	// iniciar temporizador
	temporizador.reset();
}

// loop principal
void Halterofilismo::desenhar()
{
	// switch case estado do jogo

	// case sandbox
	// preparar
	
	// iniciar jogo
	if (barraProgresso.getFrameAtual() >= progressoMaximo) {
		textoTemporizador.setWstring(L"Parabéns, você ganhou!");
		textoTemporizador.desenhar(xCentro, yCentro);
		// fadeout de ~5s, depois menu de vitória baseado no tipo de jogo
	}
	else {
		fundo.desenhar(xCentro, yCentro);
		protagonista.desenhar(xCentro, yCentro);

		/****/
		// isso aqui será definido em outra função ou num dos preparar ou em sandbox ou em campanha
		progressoMaximo = sizeBarraProgressoFrames - 1;	// reduzimos 1, pois: indice ultimo elemento = total - 1
		if (!inicioLevantamento) // equivale a if( == 0), então o levantamento começou agora
			inicioLevantamento = clock();	// clock nos dá o "tick" atual, equivale a dizer que armazenamos o tempo atual
		if (passouTempoDificultar(fatorDificuldade)) {
			dificultar();
		}
		if (passouTempo(10000))
			pragaAlada();
		temporizador.setTempo(60);	// 60 segundos
		/****/

		// primeiro gerenciamos o progresso (pois se terminou queremos exibir menu, etc antes de desenhar algo)
		//gerenciarProgresso();
		// desenhamos a barra antes apenas das pragas e do hud
		barra.desenhar(xBarra, yBarra);
		// desenhamos o hud antes apenas das pragas
		desenharHUD();
		gerenciarPragas();
		gerenciarLevantamento();	// temporizador, progresso, eventos
	}
}
// aqui desenhamos na tela os elementos necessários pela mecânica do jogo
void Halterofilismo::desenharHUD()
{
	// desenhamos a barra de progresso
	barraProgresso.desenhar(xyBarraProgresso[0], xyBarraProgresso[1]);
	// desenhamos a linha de objetivo
	uniDesenharRetangulo(xyLinhasObjetivo[progressoMaximo][0], xyLinhasObjetivo[progressoMaximo][1], 0, 100, 1, 0, 0, 255, 0, 0);
	// desenhamos o temporizador
	textoTemporizador.setString(temporizador.getTempoFormatado());
	temporizadorSombra.setString(temporizador.getTempoFormatado());

	// para sugerir urgência, dependendo do tempo restante, mudamos as cores para amarelo (10-), e vermelho (5-)
	if (temporizador.getTempo() <= 5) {
		textoTemporizador.setCor(255, 0, 0);
		temporizadorSombra.setCor(127, 0, 0);
		textoTemporizador.setEscala(2, 2);
		temporizadorSombra.setEscala(2, 2);
	}
	else if (temporizador.getTempo() <= 9) {
		textoTemporizador.setCor(255, 255, 0);
		temporizadorSombra.setCor(127, 127, 0);
		textoTemporizador.setEscala(1.5, 1.5);
		temporizadorSombra.setEscala(1.5, 1.5);
	}

	// primeiro desenhamos a sombra
	temporizadorSombra.desenhar(xTemporizador, yTemporizador);
	textoTemporizador.desenhar(xTemporizador, yTemporizador);
}

// aqui oferecemos opções de jogo ao usuário: incluem cenário (slider, incluindo opção pseudoaleatório),
//	dificuldade inicial (slider + personalizada), sexo do protagonista, tipo do levantamento, 
void Halterofilismo::preparaSandbox()
{

}

// jogo sem fim, mas com opção de sair a cada rodada; dificuldade aumenta a cada rodada vencida
//	mantemos um contador de vitórias (fatality conta como derrota, mas pode ser pulado)
void Halterofilismo::sandbox()
{

}
// aqui oferecemos opções de jogo ao usuário: nome do personagem, sexo do protagonista, 
//	sprite do personagem (slider, incluindo opção pseudoaleatório),
//	tom de voz (slider, incluindo opção pseudoaleatório)
void Halterofilismo::preparaCampanha()
{
}

// jogo com história (se ativa), e progresso linear baseado na dificuldade até um final
void Halterofilismo::campanha()
{

}

// aqui: avançamos animações (barras, personagem), gerenciamos eventos (pragaAlada), encerramos o levantamento
void Halterofilismo::gerenciarLevantamento()
{
	// SE a barra de progresso ainda não atingiu o objetivo, verificamos o intervalo das teclas
	if (barraProgresso.getFrameAtual() < progressoMaximo) {
		// TODO && barraProgresso.getFrameAtual() >= progressoMaximo
		// aqui gerenciamos a alteração no progresso pelas teclas de ação
		if (teclado.soltou[TECLA_W] || teclado.soltou[TECLA_CIMA]) {
			barraProgresso.avancarAnimacao();
			protagonista.avancarAnimacao();
			moverBarra();
		}
		if (teclado.soltou[TECLA_S] || teclado.soltou[TECLA_BAIXO]) {
			barraProgresso.avancarAnimacao();
			protagonista.avancarAnimacao();
			moverBarra();
		}
	}
	// verificamos se ao final de tudo atingimos o objetivo final
	// TODO || barraProgresso.getFrameAtual() >= progressoMaximo
	if (barraProgresso.getFrameAtual() >= progressoMaximo) {	// atingimos o objetivo, fim do levantamento
		
	}
}

void Halterofilismo::moverBarra()
{
	// movimento ainda rudimentar
	// TODO: cara sprite precisa de um trajeto com coordenadas para cada frame da animação (simples vetor<vetor<int>> por sprite)
	//	[1][2], 1 é o frame da animação, [2] são as coordenadas x,y, talvez a rotação também
	if (barraSobe) {
		barraSobe = false;
		yBarra += 10;
	}
	else {
		barraSobe = true;
		yBarra -= 10;
	}
}

void Halterofilismo::setarTemporizador(int milissegundos)
{
	tempoMaximo = milissegundos;
	minutosMaximos = milissegundos * 0.01666666666666666667;	// dividimos por 60 pra obter os minutos
	segundosMaximos = tempoMaximo - (minutosMaximos * 60);		// subtraimos os minutos dos segundos totais
}

bool Halterofilismo::passouTempoDificultar(int milissegundos)
{
	if ((clock() - pontoTempoDificuldade) >= milissegundos) {
		pontoTempoDificuldade = clock();
		return true;
	}
	return false;
}

// TODO: passar isso para temporizador genérico (criar overloaded type, que ao passar do ponto reseta sozinho)
bool Halterofilismo::passouTempo(int milissegundos)
{
	if ((clock() - pontoTempo) >= milissegundos) {
		pontoTempo = clock();
		return true;
	}
	return false;
}

void Halterofilismo::dificultar()
{
	// deltaTempo é definido pela libUnicornio, ela que avança a animação
	if (barraProgresso.getFrameAtual() > 0)	// deu subscript error, esse uso certamente não faz parte do projeto xP
		barraProgresso.avancarAnimacao(-deltaTempo);	// como queremos um retrocederAnimacao, precisamos fazer na mão
	if (protagonista.getFrameAtual() > 0)	// aprendi a lição com a barraProgresso
		protagonista.avancarAnimacao(-deltaTempo);	// como queremos um retrocederAnimacao, precisamos fazer na mão
	// para cada mosca, repetimos o "regredirAnimação", mas só se ela já chegou ao objetivo
	int sizePragas = pragasAladas.size();
	for (int i = 0; i < sizePragas; i++) {
		if (barraProgresso.getFrameAtual() > 0)	// deu subscript error, esse uso certamente não faz parte do projeto xP
			barraProgresso.avancarAnimacao(-deltaTempo);	// como queremos um retrocederAnimacao, precisamos fazer na mão
		if (protagonista.getFrameAtual() > 0)	// aprendi a lição com a barraProgresso
			protagonista.avancarAnimacao(-deltaTempo);	// como queremos um retrocederAnimacao, precisamos fazer na mão
	}

}

void Halterofilismo::pragaAlada()
{
	Sprite praga;
	// sem texto, apenas a cue de numa nova praga
	if (tipo == levantamentoNormal)
		praga.setSpriteSheet("per_HalterMosca");
	else
		praga.setSpriteSheet("per_HalterPombo");
	//praga.setEscala(5, 5);

	pragasAladas.push_back(praga);	// adicionar Sprite recém criada no final (back) do vetor

	int sizePragas = pragasAladas.size();
	if (xyPragas.size() < sizePragas) // queremos nos certificar de que a memória foi reservada
		xyPragas.resize(pragasAladas.size());
	if (chegouPraga.size() < sizePragas)
		chegouPraga.resize(sizePragas);	// queremos nos certificar de que a memória foi reservada

	int elementoAtual = sizePragas - 1;	// lembrar que size = id do último elemento + 1
	xyPragas[elementoAtual].resize(2);	// precisamos de 2 elementos
	chegouPraga[elementoAtual] = false;
	// a praga deve surgir de uma das quadro bordas da tela, vamos usar 0,1,2,3, começando pela direita sentido horário
	switch (rand() % 4) {
	case 0:	// it's me, direita!
	default:
		xyPragas[elementoAtual][0] = xCentro * 2;
		xyPragas[elementoAtual][1] = rand() % (yCentro * 2);
		break;
	case 1:	// it's baixo
		xyPragas[elementoAtual][0] = rand() % (xCentro * 2);
		xyPragas[elementoAtual][1] = yCentro * 2;
		break;
	case 2:	// esquerda
		xyPragas[elementoAtual][0] = 0;
		xyPragas[elementoAtual][1] = rand() % (yCentro * 2);
		break;
	case 3:	// cima
		xyPragas[elementoAtual][0] = rand() % (xCentro * 2);
		xyPragas[elementoAtual][1] = 0;
		break;
	}
}

void Halterofilismo::gerenciarPragas()
{
	int sizePragas = pragasAladas.size();
	// aqui fazemos a praga se aproximar do local escolhido em sua criação de modo não-linear (pseudoaleatório)
	for (int i = 0; i < sizePragas; i++) {
		if (xyPragas[i][0] != xCentro || xyPragas[i][1] != yCentro) {	// ainda não chegamos lá

			// atuamos no eixo (x)
			if (rand() % 3) {	// módulo 3, nos dá 66% de chance de não ser 0 (false)
				// vamos adicionar um pouco de ruído
				if (rand() % 2)
					xyPragas[i][0] -= rand() % 4;
				else
					xyPragas[i][0] += rand() % 4;
			}
			else {	// vamos seguir um trajeto linear
				if (xyPragas[i][0] > xCentro)
					xyPragas[i][0] -= 1;
				else if (xyPragas[i][0] < xCentro)
					xyPragas[i][0] += 1;
			}

			// atuamos no eixo (y)
			if (rand() % 3) {	// módulo 3, nos dá 66% de chance de não ser 0 (false)
				// vamos adicionar um pouco de ruído
				if (rand() % 2)
					xyPragas[i][1] -= rand() % 7;
				else
					xyPragas[i][1] += rand() % 7;
			}
			else {	// vamos seguir um trajeto linear
				if (xyPragas[i][1] > yCentro)
					xyPragas[i][1] -= 1;
				else if (xyPragas[i][1] < yCentro)
					xyPragas[i][1] += 1;
			}
			if (xyPragas[i][0] == xCentro && xyPragas[i][1] == yCentro)
				chegouPraga[i] = true;
		}
		pragasAladas[i].desenhar(xyPragas[i][0], xyPragas[i][1]);
	}
}
