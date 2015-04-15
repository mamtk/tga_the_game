#include "Jogo.h"

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
	uniInicializar(1024, 768, false, "TGA - The Game");

	//	O resto da inicializa��o vem aqui!
	//	...
	//	1)	Carregar as fontes (passando o tamanho da fonte como parametro)
	recursos.carregarFonte("fonteNormal", "./UbuntuMono-R.ttf", 17);
}

void Jogo::finalizar()
{
	//	O resto da finaliza��o vem aqui (provavelmente, em ordem inversa a inicializa��o)!
	//	...
	recursos.descarregarTodasFontes();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!teclado.soltou[TECLA_ESC] && !aplicacao.sair)
	{
		uniIniciarFrame();

		//	Seu c�digo vem aqui!
		//	...
		gerenciarEstado();

		uniTerminarFrame();
	}
}

void Jogo::gerenciarEstado()
{
	switch (estado) {
		case menuPrincipal:
			menu.desenhar();
			break;
		case halterofilismo:
			break;
	}
}