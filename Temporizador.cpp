#include "Temporizador.h"


Temporizador::Temporizador()
{
	autoReset = false;
	pontoZero = clock();
}

Temporizador::Temporizador(bool autoreset)
{
	// autoReset significa que cada vez que o tempo retornado ultrapassar o tempo máximo
	//	o pontoZero muda automaticamente para o ponto em que a função foi chamada
	autoReset = autoreset;
	pontoZero = clock();
}

Temporizador::~Temporizador()
{
}

float Temporizador::getTempoMS()
{
	if (pausado) {	// se pausado, primeiro anular diferença desde o pause
		pontoZero += (clock() - tickAoPausar);
		tickAoPausar = clock();	// em seguida atualizar tickAoPausar para que os mesmos ticks não sejam adicionados duas vezes
	}

	// clock() nos dá o "tick" atual, dele subtraimos o tick do pontoZero, e obtemos o tempo transcorrido em ms
	float tempoAtualMS = clock() - pontoZero;
	float tempoRestanteMS = tempoMaximoMS - tempoAtualMS;

	if (tempoRestanteMS < 0 && autoReset == true && !pausado)
		reset();

	return tempoRestanteMS;
}

int Temporizador::getTempo()
{
	if (pausado) {	// se pausado, primeiro anular diferença desde o pause
		pontoZero += (clock() - tickAoPausar);
		tickAoPausar = clock();	// em seguida atualizar tickAoPausar para que os mesmos ticks não sejam adicionados duas vezes
	}

	// clock() nos dá o "tick" atual, dele subtraimos o tick do pontoZero, e para obter o tempo transcorrido em segundos dividimos pela constante CLOCKS_PER_SEC
	int tempoAtualSegundos = (clock() - pontoZero) / CLOCKS_PER_SEC; // CLOCKS_PER_SEC é definido no <time.h>
	int tempoRestante = tempoMaximoSegundos - tempoAtualSegundos;

	if (tempoRestante < 0 && autoReset == true && !pausado)
		reset();

	return tempoRestante;
}


bool Temporizador::passouTempoMS(int milissegundos)
{
	if (pausado) {	// se pausado, primeiro anular diferença desde o pause
		pontoZero += (clock() - tickAoPausar);
		tickAoPausar = clock();	// em seguida atualizar tickAoPausar para que os mesmos ticks não sejam adicionados duas vezes
	}

	// clock() nos dá o "tick" atual, dele subtraimos o tick do pontoZero, e obtemos o tempo transcorrido em ms
	float tempoAtualMS = clock() - pontoZero;
	// apenas estamos interessados se passaram x milissegundos, caso positivo, resetamos o pontoZero
	float tempoRestanteMS = milissegundos - tempoAtualMS;

	if (tempoRestanteMS < 0 && !pausado) {
		reset();
		return true;
	}

	return false;
}

bool Temporizador::passouTempo(int segundos)
{
	if (pausado) {	// se pausado, primeiro anular diferença desde o pause
		pontoZero += (clock() - tickAoPausar);
		tickAoPausar = clock();	// em seguida atualizar tickAoPausar para que os mesmos ticks não sejam adicionados duas vezes
	}
	// clock() nos dá o "tick" atual, dele subtraimos o tick do pontoZero, e para obter o tempo transcorrido em segundos dividimos pela constante CLOCKS_PER_SEC
	int tempoAtualSegundos = (clock() - pontoZero) / CLOCKS_PER_SEC; // CLOCKS_PER_SEC é definido no <time.h>
	// apenas estamos interessados se passaram x segundos, caso positivo, resetamos o pontoZero
	int tempoRestante = segundos - tempoAtualSegundos;

	if (tempoRestante < 0 && !pausado) {
		reset();
		return true;
	}

	return false;
}

std::string Temporizador::getTempoFormatado()
{
	if (pausado) {	// se pausado, primeiro anular diferença desde o pause
		pontoZero += (clock() - tickAoPausar);
		tickAoPausar = clock();	// em seguida atualizar tickAoPausar para que os mesmos ticks não sejam adicionados duas vezes
	}

	// o formato é hh:mm:ss
	std::string temporizadorFormatado;

	// clock() nos dá o "tick" atual, dele subtraimos o tick do pontoZero, e para obter o tempo transcorrido em segundos dividimos pela constante CLOCKS_PER_SEC
	int tempoAtualSegundos = (clock() - pontoZero) / CLOCKS_PER_SEC; // CLOCKS_PER_SEC é definido no <time.h>
	int horasRestantes = 0;
	if (horasMaximas > 0) {	// só calcular as horas se o limite exigir
		horasRestantes = horasMaximas - (tempoAtualSegundos * .00027777777777777778);	// para segundos em horas, dividimos por 3600

		temporizadorFormatado = std::to_string(horasRestantes);		// usamos o facilitador to_string que converte objetos para o tipo string
		temporizadorFormatado += ":";								// e vamos adicionando tudo por etapas, pra facilitar a explicação
	}
	int minutosRestantes = minutosMaximos - (tempoAtualSegundos * .01666666666666666667);	// para segundos em minutos, dividimos por 60
	// para obter o resto, subtraimos minutos * 60 e horas * 3600 dos segundos totais
	int segundosRestantes = tempoMaximoSegundos - tempoAtualSegundos - (minutosRestantes * 60) - (horasRestantes * 3600);

	temporizadorFormatado = std::to_string(minutosRestantes);	// usamos o facilitador to_string que converte objetos para o tipo string
	temporizadorFormatado += ":";								// e vamos adicionando tudo por etapas, pra facilitar a explicação
	temporizadorFormatado += std::to_string(segundosRestantes);		// novamente foi preciso converter um int em string
	return temporizadorFormatado;
}


void Temporizador::setTempo(int segundos)
{
	// setamos o tempo limite em segundos
	tempoMaximoSegundos = segundos;
	tempoMaximoMS = segundos * 1000;
	horasMaximas = segundos * .00027777777777777778;
	minutosMaximos = (segundos - (horasMaximas * 3600)) * .01666666666666666667;
	segundosMaximos = segundos - (minutosMaximos * 60) - (horasMaximas * 3600);
}


void Temporizador::setTempoMS(int milissegundos)
{
	// setamos o tempo limite em milissegundos
	tempoMaximoMS = milissegundos;
	tempoMaximoSegundos = milissegundos * 0.001;
	tempoMaximoMS = tempoMaximoSegundos * 1000;
	horasMaximas = tempoMaximoSegundos * .00027777777777777778;
	minutosMaximos = (tempoMaximoSegundos - (horasMaximas * 3600)) * .01666666666666666667;
	segundosMaximos = tempoMaximoSegundos - (minutosMaximos * 60) - (horasMaximas * 3600);

}

// aqui nós alteramos o pontoZero para o ponto atual "no tempo"
void Temporizador::reset()
{
	pontoZero = clock();
}

// aqui nós pausamos o temporizador (usamos para o menu instantâneo)
void Temporizador::pausar()
{
	if (!pausado) {	// só armazenar o tickAoPausar atual se a classe não estava pausada
		// pausar significa congelar o "tick", como isso não é possível,
		//	queremos adicionar a diferença: pontoZero += tickAoDespausar - tickAoPausar
		tickAoPausar = clock();
		pausado = true;
	}
}

// aqui nós "despausamos" o temporizador (usamos ao fechar o menu instantâneo)
void Temporizador::prosseguir()
{
	if (pausado) {	// só devemos atualizar o pontoZero se a classe estava pausada
		pontoZero += (clock() - tickAoPausar);
		pausado = false;
	}
}

bool Temporizador::getPausado()
{
	return pausado;
}

// milissegundos
float Temporizador::getTempoMaximoMS()
{
	return tempoMaximoMS;
}
// segundos
int Temporizador::getTempoMaximo()
{
	return tempoMaximoSegundos;
}