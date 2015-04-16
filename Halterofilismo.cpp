#include "Halterofilismo.h"


Halterofilismo::Halterofilismo()
{
	
}


Halterofilismo::~Halterofilismo()
{
}

// loop principal
void Halterofilismo::desenhar()
{
	fundo.desenhar(xCentro, yCentro);
	personagem.desenhar(xCentro, yCentro);
	barraProgresso.desenhar(xCentro - 450, yCentro - 100);
	if (teclado.soltou[TECLA_W] || teclado.soltou[TECLA_CIMA]) {
		personagem.avancarAnimacao();
		barraProgresso.avancarAnimacao();
	}
}
// não é possível fazer isso no construtor, pois a classe Halterofilismo é parte da classe Jogo
//	então o construtor dessa classe é executado antes da classe Jogo ter um tipo completo
void Halterofilismo::inicializar()
{
	xCentro = janela.getLargura() * .5;
	yCentro = janela.getAltura() * .5;
	fundo.setSpriteSheet("fundo_Halter01");
	personagem.setSpriteSheet("per_Halter01");
	personagem.setAnimacao(0);
	personagem.setEscala(5, 5);
	personagem.setVelocidadeAnimacao(25);
	barraProgresso.setSpriteSheet("fx_HalterBarra");
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