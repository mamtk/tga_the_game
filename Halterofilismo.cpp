#include "Halterofilismo.h"
#include "Temporizador.h"

Halterofilismo::Halterofilismo()
{
	
}


Halterofilismo::~Halterofilismo()
{
}

// não é possível fazer isso no construtor, pois a classe Halterofilismo é parte da classe Jogo
//	então o construtor dessa classe é executado antes da classe Jogo ter um tipo completo.
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
	// sprites texto (códix assoviaris)
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
	textoTemporizador.setCor(255, 255, 255); // branco
	textoTemporizador.setFonte("fonteGrande");
	// textoTemporizador2 a.k.a. sombra do texto (para que o texto nunca fique invisivel, mesmo em fundos brancos)
	textoTemporizadorSombra.setAlinhamento(TEXTO_CENTRALIZADO);
	textoTemporizadorSombra.setEspacamentoLinhas(1.5f);
	textoTemporizadorSombra.setCor(0, 0, 0); // preto
	textoTemporizadorSombra.setFonte("fonteGrandeSombra");
	//textoTemporizador.setWstring(L"2:35"); // depuração
	//textoTemporizadorSombra.setWstring(L"2:35"); // depuração
	textoMensagem.setAlinhamento(TEXTO_CENTRALIZADO);
	textoMensagem.setEspacamentoLinhas(1.5f);
	textoMensagem.setCor(255, 255, 255); // branco
	textoMensagem.setFonte("fonteGrande");
	textoAvisoPragas.setAlinhamento(TEXTO_CENTRALIZADO);
	textoAvisoPragas.setEspacamentoLinhas(1.5f);
	textoAvisoPragas.setCor(255, 255, 255); // branco
	textoAvisoPragas.setFonte("fonteGrande");
	textoAvisoPragas.setWstring(L"Moscas vão me sobrecarregar!\nPreciso assoviar a saga da minha vida!\nDigite as palavras do poder!");
	textoAvisoPragasSombra.setAlinhamento(TEXTO_CENTRALIZADO);
	textoAvisoPragasSombra.setEspacamentoLinhas(1.5f);
	textoAvisoPragasSombra.setCor(0, 0, 0); // preto
	textoAvisoPragasSombra.setFonte("fonteGrande");
	textoAvisoPragasSombra.setWstring(L"Moscas vão me sobrecarregar!\nPreciso assoviar a saga da minha vida!\nDigite as palavras do poder!");

	// inicializar ponto no tempo para função dificultar
	pontoTempoDificuldade = clock();	// retorna o "tick" atual, pode-se dizer que vamos armazenar o "tempo" atual

	// a parte complicada de escolher o multiplicador da dificuldade é tornar a progressão gradual, por causa do sandbox (modo contínuo)
	switch (valoresOpcoesDeJogo[valorDificuldade]) {	// por isso aqui definimos valores com uma distância cada vez menor
	case 0:	// medio
		dificuldade = 7;	// 7
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

	// inicializar palavras do poder de espantar pragas
	queriaPalavrasLista = { "biblista", "carlista", "fabulista", "fossilista", "gaullista", "oculista", "simplista", "mobilista", "paulista", \
		"niilista", "psicanalista", "pugilista" };
	acabeiPalavrasEiro = { "agosteiro", "agoureiro", "aguaceiro", "assadeiro", "banheiro", "barulheiro", "benzedeiro", "careiro", "chiqueiro", \
		"coqueiro", "dinheiro", "dianteiro", "esterqueiro", "faqueiro", "fogareiro", "inteiro", "isqueiro", "letreiro", "milagreiro" };

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
		/****/
		// isso aqui será definido em outra função ou num dos preparar ou em sandbox ou em campanha
		progressoMaximo = sizeBarraProgressoFrames - 1;	// reduzimos 1, pois: indice ultimo elemento = total - 1
		if (!inicioLevantamento) // equivale a if( == 0), então o levantamento começou agora
			inicioLevantamento = clock();	// clock nos dá o "tick" atual, equivale a dizer que armazenamos o tempo atual

		if (tempoDificultar.passouTempoMS(fatorDificuldade)) {
			dificultar();
		}
		if (tempoPragas.passouTempoMS(5000))
			pragaAlada();
		temporizador.setTempo(60);	// 60 segundos
		/****/

		// primeiro gerenciamos o progresso (pois se terminou queremos exibir menu, etc antes de desenhar algo)
		//gerenciarProgresso();
		fundo.desenhar(xCentro, yCentro);
		protagonista.setCor(100, 255, 9);
		protagonista.desenhar(xCentro, yCentro);
		// desenhamos a barra antes apenas das pragas e do hud
		barra.desenhar(xBarra, yBarra);
		// desenhamos o hud antes apenas das pragas
		desenharHUD();
		gerenciarPragas();
		gerenciarLevantamento();	// temporizador, progresso, eventos
		if (avisoPrimeiraPraga) { // se temos que avisar, temos que avisar!
			if (tempoAvisoPragas.passouTempo(segundosAvisoPragas))
				avisoPrimeiraPraga = false;

			textoAvisoPragasSombra.desenhar(xCentro, yCentro);
			textoAvisoPragas.desenhar(xCentro, yCentro);
		}
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
	textoTemporizadorSombra.setString(temporizador.getTempoFormatado());

	// para sugerir urgência, dependendo do tempo restante, mudamos as cores para amarelo (10-), e vermelho (5-)
	if (temporizador.getTempo() <= 5) {
		textoTemporizador.setCor(255, 0, 0);
		textoTemporizadorSombra.setCor(127, 0, 0);
		textoTemporizador.setEscala(2, 2);
		textoTemporizadorSombra.setEscala(2, 2);
	}
	else if (temporizador.getTempo() <= 9) {
		textoTemporizador.setCor(255, 255, 0);
		textoTemporizadorSombra.setCor(127, 127, 0);
		textoTemporizador.setEscala(1.5, 1.5);
		textoTemporizadorSombra.setEscala(1.5, 1.5);
	}

	// primeiro desenhamos a sombra
	textoTemporizadorSombra.desenhar(xTemporizador, yTemporizador);
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
		if (chegouPraga[i]) {	// contabilizar apenas pragas efetivas (pousadas)
			if (barraProgresso.getFrameAtual() > 0)	// deu subscript error, esse uso certamente não faz parte do projeto xP
				barraProgresso.avancarAnimacao(-deltaTempo);	// como queremos um retrocederAnimacao, precisamos fazer na mão
			if (protagonista.getFrameAtual() > 0)	// aprendi a lição com a barraProgresso
				protagonista.avancarAnimacao(-deltaTempo);	// como queremos um retrocederAnimacao, precisamos fazer na mão
		}
	}

}

void Halterofilismo::pragaAlada()
{
	if (primeiraPraga) { // se for a primeira praga
		primeiraPraga = false;		// não mais
		avisoPrimeiraPraga = true;	// agora vamos mostrar um aviso!
		tempoAvisoPragas.reset();	// iniciar temporizador
	}

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
		if (chegouPraga[i] != true && (xyPragas[i][0] != xCentro || xyPragas[i][1] != yCentro)) {	// ainda não chegamos lá

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
	assoviarPalavras();
}

// aqui oferecemos a opção do jogador 
void Halterofilismo::assoviarPalavras()
{
	if (fraseAssovio.empty()) {	// se não está definida, inicializamos tudo
		fraseAssovio = "queria ser ";
		fraseAssovio += queriaPalavrasLista[rand() % queriaPalavrasLista.size()];
		fraseAssovio += ", mas acabei ";
		fraseAssovio += acabeiPalavrasEiro[rand() % acabeiPalavrasEiro.size()];
		letrasAladas.resize(fraseAssovio.size()); // 5 sprites = espaços = não desenhadas
		letrasXYOriginal.resize(letrasAladas.size());
		letrasXYAtual.resize(letrasAladas.size());
		letrasAtivadas.resize(letrasAladas.size());
		
		for (int i = 0; i < letrasAladas.size(); i++) {	// definimos os valores padrão
			letrasAtivadas[i] = false;
			if (fraseAssovio[i] == ' '/*espaço*/) {
				letrasXYOriginal[i].resize(2);	// alocamos a memória que vamos utilizar
				// iniciar coordenadas âncora em 0
				letrasXYOriginal[i][0] = 0;	// 0 significará não desenhar
				letrasXYOriginal[i][1] = 0;	// 0 significará não desenhar
			}
			else {
				letrasXYOriginal[i].resize(2);	// alocamos a memória que vamos utilizar
				// iniciar coordenadas âncora para desenho das letras
				letrasXYOriginal[i][1] = yCentro * 0.5;	// y original de cada letra (10%)
				letrasXYOriginal[i][0] = .3 * xCentro + (27 * i);	// x original de cada letra: 5% + 276 * i

				// inicializar sprite
				letrasAladas[i].setSpriteSheet("fx_Letras");
				letrasAladas[i].setEscala(.7, .7);
				// decidir frame
				switch (fraseAssovio[i]) {
				case 'a':
					letrasAladas[i].setFrame(letraA);
					break;
				case 'b':
					letrasAladas[i].setFrame(letraB);
					break;
				case 'c':
					letrasAladas[i].setFrame(letraC);
					break;
				case 'd':
					letrasAladas[i].setFrame(letraD);
					break;
				case 'e':
					letrasAladas[i].setFrame(letraE);
					break;
				case 'f':
					letrasAladas[i].setFrame(letraF);
					break;
				case 'g':
					letrasAladas[i].setFrame(letraG);
					break;
				case 'h':
					letrasAladas[i].setFrame(letraH);
					break;
				case 'i':
					letrasAladas[i].setFrame(letraI);
					break;
				case 'j':
					letrasAladas[i].setFrame(letraJ);
					break;
				case 'l':
					letrasAladas[i].setFrame(letraL);
					break;
				case 'm':
					letrasAladas[i].setFrame(letraM);
					break;
				case 'n':
					letrasAladas[i].setFrame(letraN);
					break;
				case 'o':
					letrasAladas[i].setFrame(letraO);
					break;
				case 'p':
					letrasAladas[i].setFrame(letraP);
					break;
				case 'q':
					letrasAladas[i].setFrame(letraQ);
					break;
				case 'r':
					letrasAladas[i].setFrame(letraR);
					break;
				case 's':
					letrasAladas[i].setFrame(letraS);
					break;
				case 't':
					letrasAladas[i].setFrame(letraT);
					break;
				case 'u':
					letrasAladas[i].setFrame(letraU);
					break;
				case 'v':
					letrasAladas[i].setFrame(letraV);
					break;
				case 'x':
					letrasAladas[i].setFrame(letraX);
					break;
				case 'z':
					letrasAladas[i].setFrame(letraZ);
					break;
				case ',':
					letrasAladas[i].setFrame(letraVirgulina);
					break;
				}
			}
		}
	}
	// TODO: desenhar só até a primeira virgula, depois que teclar tudo, desenhar a segunda parte
	int primeiroAposVirgula;
	for (int i = 0; i < letrasAladas.size(); i++) {
		if (i > 0 && letrasAladas[i - 1].getFrameAtual() == letraVirgulina) {	// se o anterior foi uma vírgula, saltar fora
			primeiroAposVirgula = i;
			break;
		}
		letrasAladas[i].desenhar(letrasXYOriginal[i][0], letrasXYOriginal[i][1]);
	}
	for (int i = primeiroAposVirgula; i < letrasAladas.size(); i++) {
		letrasAladas[i].desenhar(letrasXYOriginal[i][0] - (primeiroAposVirgula * 27), letrasXYOriginal[i][1]+100);
	}
}