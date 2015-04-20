#pragma once
#include <ctime>
#include <string>

class Temporizador
{
	clock_t pontoZero;		// ponto inicial
	float tempoMaximoMS;	// milissegundos
	int tempoMaximoSegundos;	// segundos

	int horasMaximas, minutosMaximos, segundosMaximos;	// pra não calcular toda hora
	bool autoReset;

public:
	Temporizador();
	Temporizador(bool autoresetParam);
	~Temporizador();
	
	float getTempoMS();					// milissegundos
	int getTempo();						// segundos
	std::string getTempoFormatado();	// horas:minutos:segundos
	bool passouTempo(int segundos);		// automaticamente reseta o pontoZero se passou do limite
	bool passouTempoMS(int milissegundos);	// automaticamente reseta o pontoZero se passou do limite
	void setTempo(int segundos);		// segundos
	void setTempoMS(int milissegundos);	// milissegundos
	void reset();						// pontoZero = clock();
};

