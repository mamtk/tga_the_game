﻿#include "Halterofilismo.h"
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
	queriaPalavrasLista = { "aulista", "bulista", "selista", "biblista", "coralista", "violista", "gaulista", "oculista", "simplista", "cafelista", "paulista", \
		"niilista", "noelista", "pugilista" };
	acabeiPalavrasEiro = { "aneiro", "boeiro", "bueiro", "geeiro", "nieiro", "oveiro", "rueiro", "useiro", "agosteiro", \
		"capeiro", "careiro", "coreiro", "dureiro", "fateiro", "fiteiro", "foreiro", "guieiro", "sineiro", "mineiro",
		"agoureiro", "assadeiro", "barulheiro", "benzedeiro", "faqueiro", "fogareiro", "letreiro", "milagreiro" };

	// iniciar temporizador
	temporizador.reset();

	// inicializar estado
	if (estadoDoJogo == jogoHalterofilismoCampanha)
		preparaCampanha();
	else	// só há uma possibilidade = sandbox()
		preparaSandbox();
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
		protagonista.setCor(50, 50, 50);
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
	desenhar();
}
// aqui oferecemos opções de jogo ao usuário: nome do personagem, sexo do protagonista, 
//	sprite do personagem (slider, incluindo opção pseudoaleatório),
//	tom de voz (slider, incluindo opção pseudoaleatório)
void Halterofilismo::preparaCampanha()
{
	// primeiro alocamos a historia
	vector<vector<wstring>> historia;
	historia.resize(6);	// nossa história terá 6 etapas
	// etapa 0 = inínio na fazenda
	historia[0] = { L"%NOME% nasceu em uma fazenda, sem energia elétrica, estradas de asfalto ou video-games para passar o tempo.", // "final" som de bebe chorando
		L"Desde a mais tenra idade, sempre gostou muito de exercer sua força e domínio sobre o mundo natural a sua volta.",
		L"Logo cresceu e se tornou uma pessoa conhecida pela capcidade física, já que conseguia quebrar bolas de bilhar usando as nádegas.", // "final" bolas bilhar
		L"Ano após ano, %NOME% aumentava sua força, com a ajuda de seus amigos mamíferos do reino animal, treinava todos os dias, até o esgotamento."
	};
	// etapa 1 = migração urbana
	historia[1] = { L"Após superar todos os seus amigos da fazena no cabo de guerra, incluindo o Sr. Cavalo Doido, era hora de migrar.", // "final" som de cavalo doido
		L"%NOME% decide que é hora de um êxodo rural, e prepara suas coisas para a longa viagem até a cidade grande.",	// "final" carro
		L"Enquanto relembra sua vida na fazenda, %NOME% aperta com força o amuleto de família que recebera dos pais antes da viagem.",
		L"Está na família há gerações, todo sabem que ele traz sorte. Pena que o amuleto é um pingente contendo um saquinho de esterco.", // "final" ovelhas
		L"Pra piorar as coisas, o único lugar com espaço para recém-chegados sem dinheiro treinarem levantamento de peso é o esgoto."
	};
	// etapa 2 = emprego em canil
	historia[2] = { L"Após longas horas de treinos e moscas, %NOME% finalmente percebe que sua sorte está mudando."
		L"Com um emprego em um canil, lugar para treinar não mais será um problema, do mesmo modo que treinar na fazenda não era.",
		L"%NOME% sempre se deu bem com animais, a única exceção era e ainda é os insetos.",	// "final" enxame
	};
	// etapa 3 = pequena academia nos suburbios
	historia[3] = { L"Infelizmente parece que um canil também é um lugar infestado por moscas.",
		L"%NOME% pede ao céu para que o seu destino não seja sobrecarregado com moscas.",	// "inicio" trovao
		L"Com o seu segundo salário, %NOME% finalmente pode pagar a mensalidade de uma academia de musculação."
		L"Isso sim deve livrá-%lo% das moscas, sempre as malditas moscas!"	// "inicio" trovao
	};
	// etapa 4 = academia no centro da cidade
	historia[4] = { L"%NOME% treinava duro para se livrar das moscas, nem que isso fosse a última coisa a fazer em vida!",
		L"Enquanto treinava na pequena academia, %NOME% percebeu que um senhor ia espirrar enquanto erguia toneladas de peso.",	// "final" espirro
		L"Por pura sorte, ele foi salvo %pelo nosso herói/pela nossa protagonista%, que conseguiu chutá-lo para longe da barra caindo.", // "final" ossos quebrando
		L"Feliz por ter quebrado apenas os dois braços, ele conta que é um olheiro da equipe Delta-Zeta-Simba-Rei-Leão, e convida %NOME% para a equipe.",
		L"Parece que tudo vai dar certo, finalmente! uma academia no centro da cidade! Finalmente as moscas vão embora."	// "inicio" trovao
	};
	// etapa 5 = levantamento nas olimpíadas no rio
	historia[5] = { L"%NOME% é %o próximo/a próxima% a ser chamada, finalmente o desafio final, as olímpiadas!",
		L"Infelizmente parece que o centro da cidade era rodeado por restaurantes, que atraem todo tipo de moscas!",
		L"Mas isso não era mais motivo de preocupação, afinal o nome %NOME% esta sendo chamado pelo anunciador oficial de levantadores olímpicos!",	// "nomeio" somfx_HalterVozNoRadio
		L"Esse é o nome que será chamado! Então o próximo desafio significa vencer as olimpíadas! Certamente um evento desse porte, com tanto dinheiro roubado via imposto...",
		L"É simplesmente impossível haver moscas atrapalhando por aqui!"	// "inicio" trovao
	};
	vector<string> sonsDeFundo = { "somfundo_HalterFazenda",
		"somfundo_HalterEsgoto",
		"somfundo_HalterCanil",
		"somfundo_HalterAcademiaSuburbio",
		"somfundo_HalterAcademiaCentro",
		"somfundo_HalterOlimpiadas"
	};
	etapaAtual = 0;
	historiaCampanha.inicializar(historia, "fundo_teste", sonsDeFundo);
}

// jogo com história (se ativa), e progresso linear baseado na dificuldade até um final
void Halterofilismo::campanha()
{
	historiaCampanha.desenhar(etapaAtual);
	if (historiaCampanha.terminouEtapa())
		etapaAtual++;
}

// aqui: avançamos animações (barras, personagem), gerenciamos eventos (pragaAlada), encerramos o levantamento
void Halterofilismo::gerenciarLevantamento()
{
	// TODO: se progresso = 0 e diminuir = morte()
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
	// se totalChegouPraga > 0
	assoviarPalavras();
}

// aqui gerenciamos o estado das letras, e desenhamos elas
void Halterofilismo::assoviarPalavras()
{
	// se não há frase definida, inicializamos tudo
	if (fraseAssovio.empty())
		inicializarPalavrasDoPoder();

	// gerenciar teclas pressionadas
	// for loop a partir da primeira não ativa, se pressionou letra diferente (função dedicada, teclouErrado()), zera ativas, reseta sprites

	// primeiro descobrimos qual a primeira letra das inativas
	int sizeLetrasAtivadas = letrasAtivadas.size();
	int primeiroInativo = -1;
	for (int i = 0; i < sizeLetrasAtivadas; i++) {	// aqui descobrimos a posição da primeira letra não ativa
		if (letrasAtivadas[i] == false) {
			primeiroInativo = i;
			break;
		}
	}
	// se todas as letras ativas, limpar frase
	if (primeiroInativo == -1) {
		ativarEspantarMoscas();	// ativa o evento que faz as moscas irem embora (e impede que venham novas durante isso)
		limparFrase();
		return;	// mais nada para se fazer nessa função
	}

	// segundo verificamos se o jogador pressionou uma letra incorreta
	if (pressionouErrado(fraseAssovio[primeiroInativo])) {	// se o jogador pressionou uma letra incorreta
		for (int i = 0; i < sizeLetrasAtivadas; i++) {	// desativar tudo
			desativarLetra(i);	// a função gerencia automaticamente o que for ou não espaço
		}
		primeiroInativo = 0;	// 0 é o novo primeiro inativo
	}
	// se soltou a letra inativa atual, mudar pra ativa, alterar sprite
	if (pressionouCerto(fraseAssovio[primeiroInativo])) {	// se o jogador pressionou a letra correta atual
		char letra = fraseAssovio[primeiroInativo];
		ativarLetra(primeiroInativo);	// ativamos a letra
	}
	// por fim, desenhamos a frase do poder
	desenharPalavrasDoPoder();
}

// aqui inicializamos a frase do poder
void Halterofilismo::inicializarPalavrasDoPoder()
{
	fraseAssovio = "queria ser ";
	fraseAssovio += queriaPalavrasLista[rand() % queriaPalavrasLista.size()];	// tudo bem usar size, pois o módulo nunca chega no número
	fraseAssovio += ", mas acabei ";
	fraseAssovio += acabeiPalavrasEiro[rand() % acabeiPalavrasEiro.size()];		// tudo bem usar size, pois o módulo nunca chega no número
	letrasAladas.resize(fraseAssovio.size()); // 5 sprites = espaços = não desenhadas
	int sizeLetrasAladas = letrasAladas.size();
	letrasXYOriginal.resize(sizeLetrasAladas);
	letrasXYAtual.resize(sizeLetrasAladas);
	letrasAtivadas.resize(sizeLetrasAladas);

	for (int i = 0; i < sizeLetrasAladas; i++) {	// definimos os valores padrão
		if (fraseAssovio[i] == ' '/*espaço*/) {
			letrasAtivadas[i] = true;	// espaços não precisam ser pressionados
			letrasXYOriginal[i].resize(2);	// alocamos a memória que vamos utilizar
			// iniciar coordenadas âncora em 0
			letrasXYOriginal[i][0] = 0;	// 0 significará não desenhar
			letrasXYOriginal[i][1] = 0;	// 0 significará não desenhar
		}
		else {
			letrasAtivadas[i] = false;
			letrasXYOriginal[i].resize(2);	// alocamos a memória que vamos utilizar
			// iniciar coordenadas âncora para desenho das letras
			letrasXYOriginal[i][1] = yCentro * 0.5;	// y original de cada letra (10%)
			letrasXYOriginal[i][0] = .3 * xCentro + (27 * i);	// x original de cada letra: 5% + 276 * i

			// inicializar sprite
			letrasAladas[i].setSpriteSheet("fx_Letras");
			letrasAladas[i].setEscala(.7, .7);
			// decidir frame
			letrasAladas[i].setFrame(traduzLetraFrame(fraseAssovio[i]));
		}
	}
}

// aqui desenhamos as letras da frase de poder
void Halterofilismo::desenharPalavrasDoPoder()
{
	// TODO: desenhar só até a primeira virgula, depois que teclar tudo, desenhar a segunda parte
	int primeiroAposVirgula = 0, noise = 0;
	int sizeLetrasAladas = letrasAladas.size();
	// desenhar apenas até a primeira virgula nas coordenadas originais
	for (int i = 0; i < sizeLetrasAladas; i++) {
		if (i > 0 && fraseAssovio[i - 1] == ',') {	// se o anterior foi uma vírgula, saltar fora
			primeiroAposVirgula = i;
			break;
		}
		if (!(rand() % 31)) {	// horrível de feio, mas funciona sem criar classes que usem ponteiros que quem ia explicar!
			noise = rand() % 7;
			letrasAladas[i].desenhar(letrasXYOriginal[i][0], letrasXYOriginal[i][1] + noise);
		}
		else {
			letrasAladas[i].desenhar(letrasXYOriginal[i][0], letrasXYOriginal[i][1]);
		}
	}
	for (int i = primeiroAposVirgula; i < sizeLetrasAladas; i++) {
		if (!(rand() % 31)) {	// horrível de feio, mas funciona sem criar classes que usem ponteiros que quem ia explicar!
			noise = rand() % 7;
			letrasAladas[i].desenhar(letrasXYOriginal[i][0] - (primeiroAposVirgula * 27), letrasXYOriginal[i][1] + 100 + noise);
		}
		else {
			letrasAladas[i].desenhar(letrasXYOriginal[i][0] - (primeiroAposVirgula * 27), letrasXYOriginal[i][1] + 100);
		}
	}
}

// aqui testamos exaustivamente por teclas pressionadas erroneamente
bool Halterofilismo::pressionouErrado(char letra)
{
	if (teclado.soltou[TECLA_A] && letra != 'a')
		return true;
	if (teclado.soltou[TECLA_B] && letra != 'b')
		return true;
	if (teclado.soltou[TECLA_C] && letra != 'c')
		return true;
	if (teclado.soltou[TECLA_D] && letra != 'd')
		return true;
	if (teclado.soltou[TECLA_E] && letra != 'e')
		return true;
	if (teclado.soltou[TECLA_F] && letra != 'f')
		return true;
	if (teclado.soltou[TECLA_G] && letra != 'g')
		return true;
	if (teclado.soltou[TECLA_H] && letra != 'h')
		return true;
	if (teclado.soltou[TECLA_I] && letra != 'i')
		return true;
	if (teclado.soltou[TECLA_J] && letra != 'j')
		return true;
	if (teclado.soltou[TECLA_K] && letra != 'k')
		return true;
	if (teclado.soltou[TECLA_L] && letra != 'l')
		return true;
	if (teclado.soltou[TECLA_M] && letra != 'm')
		return true;
	if (teclado.soltou[TECLA_N] && letra != 'n')
		return true;
	if (teclado.soltou[TECLA_O] && letra != 'o')
		return true;
	if (teclado.soltou[TECLA_P] && letra != 'p')
		return true;
	if (teclado.soltou[TECLA_Q] && letra != 'q')
		return true;
	if (teclado.soltou[TECLA_R] && letra != 'r')
		return true;
	if (teclado.soltou[TECLA_T] && letra != 't')
		return true;
	if (teclado.soltou[TECLA_U] && letra != 'u')
		return true;
	if (teclado.soltou[TECLA_V] && letra != 'v')
		return true;
	if (teclado.soltou[TECLA_X] && letra != 'x')
		return true;
	if (teclado.soltou[TECLA_Y] && letra != 'y')
		return true;
	if (teclado.soltou[TECLA_Z] && letra != 'z')
		return true;
	if (teclado.soltou[TECLA_VIRGULA] && letra != ',')
		return true;
	return false;
}
// aqui testamos pela tecla correta
bool Halterofilismo::pressionouCerto(char letra)
{
	switch (letra) {
	case 'a':
		if (teclado.soltou[TECLA_A])
			return true;
		break;
	case 'b':
		if (teclado.soltou[TECLA_B])
			return true;
		break;
	case 'c':
		if (teclado.soltou[TECLA_C])
			return true;
		break;
	case 'd':
		if (teclado.soltou[TECLA_D])
			return true;
		break;
	case 'e':
		if (teclado.soltou[TECLA_E])
			return true;
		break;
	case 'f':
		if (teclado.soltou[TECLA_F])
			return true;
		break;
	case 'g':
		if (teclado.soltou[TECLA_G])
			return true;
		break;
	case 'h':
		if (teclado.soltou[TECLA_H])
			return true;
		break;
	case 'i':
		if (teclado.soltou[TECLA_I])
			return true;
		break;
	case 'j':
		if (teclado.soltou[TECLA_J])
			return true;
		break;
	case 'l':
		if (teclado.soltou[TECLA_L])
			return true;
		break;
	case 'm':
		if (teclado.soltou[TECLA_M])
			return true;
		break;
	case 'n':
		if (teclado.soltou[TECLA_N])
			return true;
		break;
	case 'o':
		if (teclado.soltou[TECLA_O])
			return true;
		break;
	case 'p':
		if (teclado.soltou[TECLA_P])
			return true;
		break;
	case 'q':
		if (teclado.soltou[TECLA_Q])
			return true;
		break;
	case 'r':
		if (teclado.soltou[TECLA_R])
			return true;
		break;
	case 's':
		if (teclado.soltou[TECLA_S])
			return true;
		break;
	case 't':
		if (teclado.soltou[TECLA_T])
			return true;
		break;
	case 'u':
		if (teclado.soltou[TECLA_U])
			return true;
		break;
	case 'v':
		if (teclado.soltou[TECLA_V])
			return true;
		break;
	case 'x':
		if (teclado.soltou[TECLA_X])
			return true;
		break;
	case 'z':
		if (teclado.soltou[TECLA_Z])
			return true;
		break;
	case ',':
		if (teclado.soltou[TECLA_VIRGULA])
			return true;
		break;
	}
	return false;
}
void Halterofilismo::desativarLetra(int indice)
{
	if (fraseAssovio[indice] == ' ')	// se for um espaço, nada fazer
		return;
	// setar sprite
	letrasAladas[indice].setSpriteSheet("fx_Letras");
	letrasAladas[indice].setEscala(.7, .7);
	// decidir frame
	letrasAladas[indice].setFrame(traduzLetraFrame(fraseAssovio[indice]));
	// marcar como inativa
	letrasAtivadas[indice] = false;
}
void Halterofilismo::ativarLetra(int indice)
{
	// setar sprite
	letrasAladas[indice].setSpriteSheet("fx_LetrasIluminadas");
	letrasAladas[indice].setEscala(.7, .7);
	// decidir frame
	letrasAladas[indice].setFrame(traduzLetraFrame(fraseAssovio[indice]));
	// marcar como ativa
	letrasAtivadas[indice] = true;
}

void Halterofilismo::ativarEspantarMoscas()
{

}
void Halterofilismo::limparFrase()
{
	fraseAssovio = "";
	letrasAladas.resize(0);
	letrasXYOriginal.resize(0);
	letrasXYAtual.resize(0);
	letrasAtivadas.resize(0);

}

int Halterofilismo::traduzLetraFrame(char letra)	// se não for função, vai ficar cheio de linha sem significância
{
	switch (letra) {
	case 'a':
		return letraA;
		break;
	case 'b':
		return letraB;
		break;
	case 'c':
		return letraC;
		break;
	case 'd':
		return letraD;
		break;
	case 'e':
		return letraE;
		break;
	case 'f':
		return letraF;
		break;
	case 'g':
		return letraG;
		break;
	case 'h':
		return letraH;
		break;
	case 'i':
		return letraI;
		break;
	case 'j':
		return letraJ;
		break;
	case 'l':
		return letraL;
		break;
	case 'm':
		return letraM;
		break;
	case 'n':
		return letraN;
		break;
	case 'o':
		return letraO;
		break;
	case 'p':
		return letraP;
		break;
	case 'q':
		return letraQ;
		break;
	case 'r':
		return letraR;
		break;
	case 's':
		return letraS;
		break;
	case 't':
		return letraT;
		break;
	case 'u':
		return letraU;
		break;
	case 'v':
		return letraV;
		break;
	case 'x':
		return letraX;
		break;
	case 'z':
		return letraZ;
		break;
	case ',':
		return letraVirgulina;
		break;
	default:
		return 0;
	}
	return 0;
}