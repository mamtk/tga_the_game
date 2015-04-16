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

	//	O resto da inicializa鈬o vem aqui!
	//	...
	//	1)	Carregar as fontes (passando o tamanho da fonte como parametro)
	/* tentaremos uma nomenclatura padronizada --- edit 01
		fonte*		-	para fontes, ex. fonteNormal
		fundo_\1\2	-	para fundos, \1 é o jogo, \2 QUALQUER identificador; ex. fundo_Halter01, fundo_HalterCenaLago, ...
		per_\1\2	-	para personagens (tudo que age/tem vontade), ex. per_HalterMosca1, per_TiroPato, ...
		obj_\1\2	-	para objetos (mesmo com animação), ex. obj_HalterRochaDoLago, obj_JudoAnelDeFogo, ...
		fx_\1\2		-	para imateriais/efeitos, ex. fx_TiroFumaca, fx_ArcoSangue, ...
	*/
	recursos.carregarFonte("fonteNormal", "UbuntuMono-R.ttf", 17);
	// halterofilismo
	recursos.carregarSpriteSheet("fundo_Halter01", "img/fundos/halter_01.png");
	recursos.carregarSpriteSheet("per_Halter01", "img/per/lucas1.png", 3, 9);
	recursos.carregarSpriteSheet("fx_HalterBarra", "img/fx/fx_HalterBar.png", 1, 11);
	// especificar numeros de frames diferentes do maior
	recursos.getSpriteSheet("per_Halter01")->setNumFramesDaAnimacao(0, 3);
	recursos.getSpriteSheet("per_Halter01")->setNumFramesDaAnimacao(1, 8);
}

void Jogo::finalizar()
{
	//	O resto da finaliza鈬o vem aqui (provavelmente, em ordem inversa a inicializa鈬o)!
	//	...
	recursos.descarregarTodasFontes();

	uniFinalizar();
}

void Jogo::executar()
{
	menu.inicializar();	// algumas funções não podem ser executadas no construtor daquela classe (pois jogo ainda possui tipo incompleto)
	while(!teclado.soltou[TECLA_ESC] && !aplicacao.sair)
	{
		uniIniciarFrame();

		//	Seu cigo vem aqui!
		//	...
		gerenciarEstado();

		uniTerminarFrame();
	}
}

void Jogo::gerenciarEstado()
{
	switch (estado) {
		case menuPrincipal:
			menu.desenhar();	// desenhar o menu? a verdade é que o menu se desenha sozinho! haha, piada idiota.
			if (menu.escolheu()) {	// verificar se o jogador já fez a sua escolha
				opcoesDeJogo = menu.getOpcoes();	// em caso positivo, recuperamos as opções de jogo
				estado = halterofilismo;	// e alteramos nosso estado para o jogo em si
				halterofilia.inicializar();
			}
			break;
		case halterofilismo:
			halterofilia.desenhar();
			break;
	}
}