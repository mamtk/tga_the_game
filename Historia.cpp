#include "Historia.h"

Historia::Historia()
{
}

Historia::~Historia()
{
}


void Historia::inicializar(vector<vector<wstring>> historia, string fundo, vector<string> sonsDeFundo, vector<vector<string>> sonsDaHistoria,\
	vector<vector<Sprite>> sprites, vector<vector<int>> spritesXY)
{
	if (fundo.size() > 0)
		sprFundo.setSpriteSheet(fundo);
	if (sprites.size() > 0 && spritesXY.size() > 0) {
		sprElementos = sprites;
		elementosXY = spritesXY;
	}
	if (sonsDeFundo.size() > 0) {
		int sizeSonsDeFundo = sonsDeFundo.size();
		historiaSonsDeFundo.resize(sizeSonsDeFundo);
		for (int somDeFundo; somDeFundo < sizeSonsDeFundo; somDeFundo++) { // para cada som de fundo
			historiaSonsDeFundo[somDeFundo].setAudio(sonsDeFundo[somDeFundo]);	// carregamos o som correto
		}
	}
	if (sonsDaHistoria.size() > 0) {
		int sizeSons = sonsDaHistoria.size();
		historiaSons.resize(sizeSons);	// alocamos a memória a ser utilizada
		for (int etapa = 0; etapa < sizeSons; etapa++) {	// para cada etapa
			int sizeSonsDaEtapa = sonsDaHistoria[etapa].size();
			historiaSons.resize(sizeSonsDaEtapa);	// alocamos a memória a ser utilizada
			for (int som = 0; som < sizeSonsDaEtapa; som++) { // para cada som da etapa
				historiaSons[etapa][som].setAudio(sonsDaHistoria[etapa][som]);	// carregamos o áudio correto
			}
		}
	}
	historiaLinhas = historia;
	totalEtapas = historia.size() - 1;	// total = tamanho - 1 = índice do elemento final
	xCentro = janela.getLargura() * .5;
	yCentro = janela.getAltura() * .5;
	xLinhas = xCentro;	// infelizmente o texto é centralizado, então o X é sempre relativo...

	sprSobreCamada.setSpriteSheet("fx_Dot");	// permite ler letras brancas em qualquer fundo
	sprSobreCamada.setCor(0, 0, 0, 125);
	sprSobreCamada.setEscala(xCentro * 1.9, yCentro * 1.9);		// para cobrir 95% da tela

	// variáveis de estado
	linhaAtual = letraAtual = 0;
	// o motivo de setarmos a etapa atual para -1 é para detectarmos a primeira chamada da função desenhar
	//	como uma etapa nova (etapa != etapaAtual), e assim inicializar corretamente suas variáveis
	etapaAtual = -1;
}

void Historia::desenhar(int etapa)
{
	if (etapaAtual != etapa && etapa <= totalEtapas) {	// passamos para uma nova etapa!
		tempoClique.reset();
		etapaAtual = etapa;
		linhaAtual = letraAtual = 0;

		totalLinhasEtapaAtual = historiaLinhas[etapa].size();
		// aqui alocamos a memória correta, e setamos os valores todos para false novamente
		linhasDesenhadas.resize(totalLinhasEtapaAtual, false);
		textoLinhas.resize(totalLinhasEtapaAtual);
		sizeLinhas.resize(totalLinhasEtapaAtual);
		yLinhas.resize(0);	// limpamos os valores, pois usamos push_back, que adiciona após o último elemento
		int yTotal = yCentro * .3; // começamos em y = 15%, e vamos aumentando conforme descemos
		yLinhas.push_back(yTotal);	// adicionamos a posição '0' no y das linhas
		for (int linha = 0; linha < totalLinhasEtapaAtual; linha++) {
			sizeLinhas[linha] = historiaLinhas[etapaAtual][linha].size();
			textoLinhas[linha].setWstring(historiaLinhas[etapaAtual][linha]);
			textoLinhas[linha].setFonte("fonteNormalSombra");
			textoLinhas[linha].setCor(255, 255, 255);
			textoLinhas[linha].ajustarStringParaLargura(970);	// 95% de 1024 = ~970
			yTotal += textoLinhas[linha].getAltura() * 2;	// um espaço maior facilita a leitura
			yLinhas.push_back(yTotal);	// adicionar a posição da linha atual no y das linhas
		}
	}
	// primeiro de tudo desenhar o fundo
	sprFundo.desenhar(xCentro, yCentro);
	/* SE o setCorAlpha realmente mudasse algo, eu usaria isso aqui
		mas como parece não ser o caso, editei os fundos na mão mesmo...
	// depois a sobrecamada
	sprSobreCamada.desenhar(xCentro, yCentro);
	*/
	// finalmente desenhamos o texto passado, começando em x = 5%, e y% = 15%
	for (int linha = 0; linha < linhaAtual; linha++) {	// para cada linha até a linha anterior a atual
		textoLinhas[linha].desenhar(xLinhas, yLinhas[linha]);	// desenhamos a linha inteira
	}
	// atualizamos o contador da letra atual
	// se a letraAtual é menos que o total da linhaAtual _E_ se passou tantos milissegundos, avançamos uma letra
	if (letraAtual < sizeLinhas[linhaAtual] && tempoPrint.passouTempoMS(10)) {
		letraAtual++;
		// setamos a string do objeto texto da linha atual, levando em consideração a letra atual
		//	substr retorna uma substring da atual, pedimos uma da posição 0 até letraAtual
		textoLinhas[linhaAtual].setWstring(historiaLinhas[etapaAtual][linhaAtual].substr(0, letraAtual));
		// também ajustamos a linha para que não exceda a largura da tela
		textoLinhas[linhaAtual].ajustarStringParaLargura(975);	// 95% de 1024 = ~970
	}
	// por fim desenhamos a linha atual
	textoLinhas[linhaAtual].desenhar(xLinhas, yLinhas[linhaAtual]);

	// por fim gerenciamos as entradas do jogador; esperamos um tempo antes de aceitar o mouse, para evitar os cliques do menu anterior
	if (teclado.soltou[TECLA_A] || teclado.soltou[TECLA_S] || teclado.soltou[TECLA_D] || teclado.soltou[TECLA_W] || \
		teclado.soltou[TECLA_DIR] || teclado.soltou[TECLA_ESQ] || teclado.soltou[TECLA_CIMA] || teclado.soltou[TECLA_BAIXO] || \
		teclado.soltou[TECLA_ENTER] || teclado.soltou[TECLA_ESPACO] || (mouse.soltou[BOTAO_ESQ] && tempoClique.passouTempoMS(300))) {
		if (linhaAtual < totalLinhasEtapaAtual - 1) {	// se linha atual menor que o tamanho - 1 (última posição)
			if (letraAtual < sizeLinhas[linhaAtual]) {	// se ainda não terminamos de desenhar a linha
				textoLinhas[linhaAtual].setWstring(historiaLinhas[etapaAtual][linhaAtual]);	// corrigir a wstring do objeto texto, do contrário a linha ficará incompleta
				// também ajustar para a largura da tela
				textoLinhas[linhaAtual].ajustarStringParaLargura(975);	// 95% de 1024 = ~970
			}
			// aumentar a linha atual, resetar letraAtual
			linhaAtual++;
			letraAtual = 0;
		}
		else if (letraAtual != sizeLinhas[linhaAtual]) {	// jogador tem pressa
			letraAtual = sizeLinhas[linhaAtual];
			textoLinhas[linhaAtual].setWstring(historiaLinhas[etapaAtual][linhaAtual]);	// corrigir a wstring do objeto texto, do contrário a linha ficará incompleta
			// também ajustar para a largura da tela
			textoLinhas[linhaAtual].ajustarStringParaLargura(975);	// 95% de 1024 = ~970
		}
	}
}

bool Historia::terminouEtapa()
{
	if (linhaAtual == totalLinhasEtapaAtual -1 && letraAtual == sizeLinhas[linhaAtual])
		return true;

	return false;
}