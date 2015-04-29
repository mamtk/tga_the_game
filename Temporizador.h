#pragma once
#include <ctime>
#include <string>

class Temporizador
{
	clock_t pontoZero;			// ponto inicial "no tempo"
	clock_t tickAoPausar;		// ponto do pause "no tempo"
	float tempoMaximoMS;		// tempo máximo total em milissegundos
	int tempoMaximoSegundos;	// tempo máximo total em segundos

	int horasMaximas, minutosMaximos, segundosMaximos;	// pra não calcular toda hora
	bool autoReset, pausado = false;

public:
	Temporizador();
	Temporizador(bool autoresetParam);
	~Temporizador();
	
	float getTempoMS();					// milissegundos
	int getTempo();						// segundos
	float getTempoMaximoMS();			// milissegundos
	int getTempoMaximo();				// segundos
	float getTempoPassadoMS();			// milissegundos
	int getTempoPassado();				// segundos
	std::string getTempoFormatado();	// horas:minutos:segundos
	bool passouTempo(int segundos);		// automaticamente reseta o pontoZero se passou do limite
	bool passouTempoMS(int milissegundos);	// automaticamente reseta o pontoZero se passou do limite
	bool getPausado();
	void setTempo(int segundos);		// segundos
	void setTempoMS(int milissegundos);	// milissegundos
	void reset();						// pontoZero = clock();
	void pausar();						// pausar contagem
	void prosseguir();					// prosseguir contagem
};

