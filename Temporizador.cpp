#include "Temporizador.h"


Temporizador::Temporizador()
{
	autoReset = false;
	pontoZero = clock();
}

Temporizador::Temporizador(bool autoreset)
{
	autoReset = autoreset;
	pontoZero = clock();
}

Temporizador::~Temporizador()
{
}

float Temporizador::getTempoMS()
{
	float tempoAtualMS = clock() - pontoZero;
	float tempoRestanteMS = tempoMaximoMS - tempoAtualMS;

	if (tempoRestanteMS < 0 && autoReset == true)
		reset();

	return tempoRestanteMS;
}

int Temporizador::getTempo()
{
	int tempoAtualSegundos = (clock() - pontoZero) / CLOCKS_PER_SEC; // CLOCKS_PER_SEC é definido no <time.h>
	int tempoRestante = tempoMaximoSegundos - tempoAtualSegundos;

	if (tempoRestante < 0 && autoReset == true)
		reset();

	return tempoRestante;
}


bool Temporizador::passouTempoMS(int milissegundos)
{
	float tempoAtualMS = clock() - pontoZero;
	float tempoRestanteMS = milissegundos - tempoAtualMS;

	if (tempoRestanteMS < 0) {
		reset();
		return true;
	}

	return false;
}

bool Temporizador::passouTempo(int segundos)
{
	int tempoAtualSegundos = (clock() - pontoZero) / CLOCKS_PER_SEC; // CLOCKS_PER_SEC é definido no <time.h>
	int tempoRestante = segundos - tempoAtualSegundos;

	if (tempoRestante < 0) {
		reset();
		return true;
	}

	return false;
}

std::string Temporizador::getTempoFormatado()
{
	std::string temporizadorFormatado;

	// clock() nos dá o "tick" atual, dele subtraimos o tick do inicioLevantamento, e para obter o tempo dividimos pela constante CLOCKS_PER_SEC
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
	tempoMaximoSegundos = segundos;
	tempoMaximoMS = segundos * 1000;
	horasMaximas = segundos * .00027777777777777778;
	minutosMaximos = (segundos - (horasMaximas * 3600)) * .01666666666666666667;
	segundosMaximos = segundos - (minutosMaximos * 60) - (horasMaximas * 3600);
}


void Temporizador::setTempoMS(int milissegundos)
{
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
