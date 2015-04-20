#pragma once
#include <ctime>
#include <string>

class Temporizador
{
	clock_t pontoZero;		// ponto inicial
	float tempoMaximoMS;	// milissegundos
	int tempoMaximoSegundos;	// segundos

	int horasMaximas, minutosMaximos, segundosMaximos;	// pra não calcular toda hora

public:
	Temporizador();
	~Temporizador();
	
	float getTempoMS();					// milissegundos
	int getTempo();						// segundos
	std::string getTempoFormatado();	// horas:minutos:segundos
	void setTempo(int segundos);		// segundos
	void setTempoMS(int milissegundos);	// milissegundos
	void reset();						// pontoZero = clock();
};

