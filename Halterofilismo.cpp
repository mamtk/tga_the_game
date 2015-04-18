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
	xCentro = janela.getLargura() * .5;
	yCentro = janela.getAltura() * .5;
	xyBarraProgresso = { xCentro - 450, yCentro - 100 };

	// inicializar sprites
	barra.setSpriteSheet("obj_HalterBarra");
	fundo.setSpriteSheet("fundo_Halter01");
	protagonista.setSpriteSheet("per_Halter01");
	protagonista.setAnimacao(0);
	protagonista.setEscala(5, 5);
	protagonista.setVelocidadeAnimacao(25);
	barraProgresso.setSpriteSheet("fx_HalterBarra");
	barraProgresso.setVelocidadeAnimacao(5);
	sizeBarraProgressoFrames = barraProgresso.getSpriteSheet()->getNumFramesDaAnimacao(0);
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
	temporizador.setAlinhamento(TEXTO_CENTRALIZADO);
	temporizador.setEspacamentoLinhas(1.5f);
	temporizador.setCor(255, 255, 255); // começamos com branco
	temporizador.setFonte("fonteGrande");
	// temporizador2 a.k.a. sombra do texto (para que o texto nunca fique invisivel, mesmo em fundos brancos)
	temporizadorSombra.setAlinhamento(TEXTO_CENTRALIZADO);
	temporizadorSombra.setEspacamentoLinhas(1.5f);
	temporizadorSombra.setCor(0, 0, 0); // começamos e terminamos com preto
	temporizadorSombra.setFonte("fonteGrandeSombra");
	temporizador.setWstring(L"2:35");
	temporizadorSombra.setWstring(L"2:35");

	// inicializar ponto no tempo para função dificultar
	pontoTempoDificuldade = clock();	// retorna o "tick" atual, pode-se dizer que vamos armazenar o "tempo" atual

	// a parte complicada de escolher o multiplicador da dificuldade é tornar a progressão gradual, por causa do sandbox (modo contínuo)
	switch (valoresOpcoesDeJogo[valorDificuldade]) {	// por isso aqui definimos valores com uma distância cada vez menor
	case 0:	// medio
		dificuldade = 7;	// 7
		break;
	case 1:	// difícil
		dificuldade = 12;	// 11
		break;
	case 2:	// impossível
		dificuldade = 15;	// 15
		break;
	case 3:	// impossível?
		dificuldade = 17;	// 17, e duvido!
		break;
	}
	fatorDificuldade = 1000 / dificuldade;
}

// loop principal
void Halterofilismo::desenhar()
{
	// switch case estado do jogo

	// case sandbox
	// preparar
	
	// iniciar jogo
	fundo.desenhar(xCentro, yCentro);
	protagonista.desenhar(xCentro, yCentro);
	barra.desenhar(xCentro, yCentro);
	barra.setEscala(5, 5);
	progressoMaximo = sizeBarraProgressoFrames - 1;	// reduzimos 1, pois: indice ultimo elemento = total - 1
	if (!inicioLevantamento) // equivale a if( == 0), então o levantamento começou agora
		inicioLevantamento = clock();	// clock nos dá o "tick" atual, equivale a dizer que armazenamos o tempo atual
	if (passouTempo(fatorDificuldade))
		dificultar();
	setarTemporizador(60);	// 60 segundos
	desenharHUD();
	uniDepurar("inicioLevantamento", inicioLevantamento);
	gerenciarPragas();
	gerenciarLevantamento();	// temporizador, progresso, eventos
}
// aqui desenhamos na tela os elementos necessários pela mecânica do jogo
void Halterofilismo::desenharHUD()
{
	// desenhamos a barra de progresso
	barraProgresso.desenhar(xyBarraProgresso[0], xyBarraProgresso[1]);
	// desenhamos a linha de objetivo
	uniDesenharRetangulo(xyLinhasObjetivo[progressoMaximo][0], xyLinhasObjetivo[progressoMaximo][1], 0, 100, 1, 0, 0, 255, 0, 0);
	// atualizamos e desenhamos o temporizador
	// clock() nos dá o "tick" atual, dele subtraimos o tick do inicioLevantamento, e para obter o tempo dividimos pela constante CLOCKS_PER_SEC
	float tempoAtualSegundos = (clock() - inicioLevantamento) / CLOCKS_PER_SEC; // CLOCKS_PER_SEC é definido no <time.h>
	int minutosRestantes = minutosMaximos - (tempoAtualSegundos * 0.01666666666666666667);	// para segundos em minutos, dividimos por 60
	int segundosRestantes = tempoMaximo - tempoAtualSegundos - (minutosRestantes * 60);	// para obter o resto, subtraimos minutos * 60 dos segundos totais
	// queremos atualizar a string do temporizador com os resultados minutosRestantes:segundosRestantes
	string temporizadorFormatado = to_string(minutosRestantes);	// usamos o facilitador to_string que converte objetos para o tipo string
	temporizadorFormatado += ":";								// e vamos adicionando tudo por etapas, pra facilitar a explicação
	temporizadorFormatado += to_string(segundosRestantes);		// novamente foi preciso converter um int em string
	// agora podemos atualizar a string do temporizador
	temporizador.setString(temporizadorFormatado);
	temporizadorSombra.setString(temporizadorFormatado);
	// para sugerir urgência, dependendo do tempo restante, mudamos as cores para amarelo (10-), e vermelho (5-)
	if ((tempoMaximo - tempoAtualSegundos) <= 5) {
		temporizador.setCor(255, 0, 0);
		temporizadorSombra.setCor(127, 0, 0);
		temporizador.setEscala(2, 2);
		temporizadorSombra.setEscala(2, 2);
	}
	else if ((tempoMaximo - tempoAtualSegundos) <= 9) {
		temporizador.setCor(255, 255, 0);
		temporizadorSombra.setCor(127, 127, 0);
		temporizador.setEscala(1.5, 1.5);
		temporizadorSombra.setEscala(1.5, 1.5);
	}

	// primeiro desenhamos a sombra
	temporizadorSombra.desenhar(xTemporizador, yTemporizador);
	temporizador.desenhar(xTemporizador, yTemporizador);
}

// aqui oferecemos opções de jogo ao usuário: incluem cenário (slider, incluindo opção pseudoaleatório),
//	dificuldade inicial (slider + personalizada), sexo do protagonista, 
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

}

void Halterofilismo::setarTemporizador(int milissegundos)
{
	tempoMaximo = milissegundos;
	minutosMaximos = milissegundos * 0.01666666666666666667;	// dividimos por 60 pra obter os minutos
	segundosMaximos = tempoMaximo - (minutosMaximos * 60);		// subtraimos os minutos dos segundos totais
}

bool Halterofilismo::passouTempo(int milissegundos)
{
	if ((clock() - pontoTempoDificuldade) >= milissegundos) {
		pontoTempoDificuldade = clock();
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
}

void Halterofilismo::pragaAlada()
{
	Sprite praga;
	// sem texto, apenas a cue
	if (tipo == levantamentoNormal)
		praga.setSpriteSheet("per_HalterMosca");
	else
		praga.setSpriteSheet("per_HalterPombo");
	pragasAlada.push_back(praga);	// adicionar Sprite recém criada no final (back) do vetor
}

void Halterofilismo::gerenciarPragas()
{

}
