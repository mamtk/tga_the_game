#include "Historia.h"

Historia::Historia()
{
}

Historia::~Historia()
{
}


void Historia::inicializar(vector<vector<wstring>> historia, vector<string> fundos, vector<string> sonsDeFundo, vector<vector<vector<string>>> sonsDaHistoria, \
	vector<vector<Sprite>> sprites, vector<vector<int>> spritesXY)
{
	if (fundos.size() >= historia.size())
		stringsFundos = fundos;
	if (sprites.size() > 0 && spritesXY.size() > 0) {	// isso aqui não vai ser implementado, mas poderia...
		sprElementos = sprites;
		elementosXY = spritesXY;
	}
	if (sonsDeFundo.size() > 0) {
		int sizeSonsDeFundo = sonsDeFundo.size();
		historiaSonsDeFundo.resize(sizeSonsDeFundo);
		for (int somDeFundo = 0; somDeFundo < sizeSonsDeFundo; somDeFundo++) { // para cada som de fundo
			historiaSonsDeFundo[somDeFundo].setAudio(sonsDeFundo[somDeFundo]);	// carregamos o som correto
		}
	}
	// isso aqui é horrível de feio, mas quem ia explicar um contâiner diferente?
	if (sonsDaHistoria.size() > 0) {
		int sizeSons = sonsDaHistoria.size();
		historiaSons.resize(sizeSons);	// alocamos a memória a ser utilizada
		historiaSonsDefinidos.resize(sizeSons);	// alocamos a memória a ser utilizada
		for (int etapa = 0; etapa < sizeSons; etapa++) {	// para cada etapa
			int sizeSonsDaEtapa = sonsDaHistoria[etapa].size();
			historiaSons[etapa].resize(sizeSonsDaEtapa);	// alocamos a memória a ser utilizada
			historiaSonsDefinidos[etapa].resize(sizeSonsDaEtapa);	// alocamos a memória a ser utilizada

			for (int linha = 0; linha < sizeSonsDaEtapa; linha++) {	// para cada linha
				//int sizeSonsDaLinha = sonsDaHistoria[etapa][linha].size();	// sempre = 3, pois quando varia de [0,2]
				historiaSons[etapa][linha].resize(3);	// alocamos a memória a ser utilizada
				historiaSonsDefinidos[etapa][linha].resize(3);	// alocamos a memória a ser utilizada

				for (int quando = 0; quando < 3; quando++) { // para cada "quando" da linha
					if (sonsDaHistoria[etapa][linha].size() > quando && !sonsDaHistoria[etapa][linha][quando].empty()) {	// se há som definido (tamanho da string > 1)
						historiaSons[etapa][linha][quando].setAudio(sonsDaHistoria[etapa][linha][quando]);	// carregamos o áudio correto
						historiaSonsDefinidos[etapa][linha][quando] = true;
					}
				}
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
		if (!stringsFundos.empty())	// se houver fundos definidos
			sprFundo.setSpriteSheet(stringsFundos[etapa]);	// setar a sprite
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
			textoLinhas[linha].setAlinhamento(TEXTO_ALINHADO_A_ESQUERDA);
			textoLinhas[linha].setFonte("fonteNormalSombra");
			textoLinhas[linha].setCor(255, 255, 255);
			textoLinhas[linha].ajustarStringParaLargura(970);	// 95% de 1024 = ~970
			yTotal += textoLinhas[linha].getAltura() + 71;	// um espaço maior facilita a leitura
			yLinhas.push_back(yTotal);	// adicionar a posição da linha atual no y das linhas
		}
		if (historiaSonsDeFundo.size() > etapaAtual) {	// se o som de fundo atual, ou posterior estiver definido
			// parar todos os outros sons
			int sizeSonsDeFundo = historiaSonsDeFundo.size();
			for (int som = 0; som < sizeSonsDeFundo; som++)
				historiaSonsDeFundo[som].parar();

			// na verdade esse teste não adianta, já que a classe som retorna endereços inválidos caso não exista som carregado...
			//	isso significa que eu devia fazer um vetor com os sons definidos, mas eu vou definir som para todos os fundos, então
			//	não pretendo fazer isso, pelo menos até meu caso de uso mudar
			// if (historiaSonsDeFundo[etapaAtual].getAudio()->estaCarregado())	// se tocar() nulo, aparece mensagem de erro, então testamos
				historiaSonsDeFundo[etapaAtual].tocar();
		}
		// verificamos se há som para tocar no início da primeira linha
		if (historiaSonsDefinidos.size() > etapa && historiaSonsDefinidos[etapa].size() > linhaAtual && historiaSonsDefinidos[etapa][linhaAtual][tocarComecoDaLinha])
			historiaSons[etapaAtual][linhaAtual][tocarComecoDaLinha].tocar();
	}
	// primeiro de tudo desenhar o fundo, se existir
	if (stringsFundos.size() > 0)
		sprFundo.desenhar(xCentro, yCentro);
	// depois a sobrecamada
	sprSobreCamada.desenhar(xCentro, yCentro);
	// finalmente desenhamos o texto passado, começando em x = 5%, e y% = 15%
	for (int linha = 0; linha < linhaAtual; linha++) {	// para cada linha até a linha anterior a atual
		textoLinhas[linha].desenhar(xLinhas, yLinhas[linha]);	// desenhamos a linha inteira
	}
	// atualizamos o contador da letra atual
	// se a história não foi pausada _E_ a letraAtual é menos que o total da linhaAtual _E_ se passou tantos milissegundos, avançamos uma letra
	if (!pausado && letraAtual < sizeLinhas[linhaAtual] && tempoPrint.passouTempoMS(10)) {
		letraAtual++;
		// verificamos se há som para tocar na letra atual
		if (letraAtual == (int)(sizeLinhas[linhaAtual] * .5)) {
			if (historiaSonsDefinidos.size() > etapa && historiaSonsDefinidos[etapa].size() > linhaAtual && historiaSonsDefinidos[etapa][linhaAtual][tocarComecoDaLinha])
				historiaSons[etapa][linhaAtual][tocarMeioDaLinha].tocar();
		}
		else if (letraAtual == sizeLinhas[linhaAtual] ) {
			if (historiaSonsDefinidos.size() > etapa && historiaSonsDefinidos[etapa].size() > linhaAtual && historiaSonsDefinidos[etapa][linhaAtual][tocarComecoDaLinha])
				historiaSons[etapa][linhaAtual][tocarFinalDaLinha].tocar();
		}

		// setamos a string do objeto texto da linha atual, levando em consideração a letra atual
		//	substr retorna uma substring da atual, pedimos uma da posição 0 até letraAtual
		textoLinhas[linhaAtual].setWstring(historiaLinhas[etapaAtual][linhaAtual].substr(0, letraAtual));
		// também ajustamos a linha para que não exceda a largura da tela
		textoLinhas[linhaAtual].ajustarStringParaLargura(975);	// 95% de 1024 = ~970
	}
	// por fim desenhamos a linha atual
	textoLinhas[linhaAtual].desenhar(xLinhas, yLinhas[linhaAtual]);

	// por fim, se a classe não está pausada,
	//	gerenciamos as entradas do jogador; esperamos um tempo antes de aceitar o mouse, para evitar os cliques do menu anterior
	if (!pausado && (teclado.soltou[TECLA_A] || teclado.soltou[TECLA_S] || teclado.soltou[TECLA_D] || teclado.soltou[TECLA_W] || \
		teclado.soltou[TECLA_DIR] || teclado.soltou[TECLA_ESQ] || teclado.soltou[TECLA_CIMA] || teclado.soltou[TECLA_BAIXO] || \
		teclado.soltou[TECLA_ENTER] || teclado.soltou[TECLA_ESPACO] || (mouse.soltou[BOTAO_ESQ] && tempoClique.passouTempoMS(300)))) {
		if (linhaAtual < totalLinhasEtapaAtual - 1) {	// se linha atual menor que o tamanho - 1 (última posição)
			if (letraAtual < sizeLinhas[linhaAtual]) {	// se ainda não terminamos de desenhar a linha
				textoLinhas[linhaAtual].setWstring(historiaLinhas[etapaAtual][linhaAtual]);	// corrigir a wstring do objeto texto, do contrário a linha ficará incompleta
				// também ajustar para a largura da tela
				textoLinhas[linhaAtual].ajustarStringParaLargura(975);	// 95% de 1024 = ~970
			}
			// aumentar a linha atual, resetar letraAtual
			linhaAtual++;
			letraAtual = 0;
			// verificar se há som para tocar no começo da linha
			if (historiaSonsDefinidos.size() > etapa && historiaSonsDefinidos[etapa].size() > linhaAtual && historiaSonsDefinidos[etapa][linhaAtual][tocarComecoDaLinha])
				historiaSons[etapa][linhaAtual][tocarComecoDaLinha].tocar();
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
	if (linhaAtual == totalLinhasEtapaAtual - 1 && letraAtual == sizeLinhas[linhaAtual])
		return true;

	return false;
}

void Historia::prosseguir()
{
	if (pausado)
		pausado = false;
}

void Historia::pausar()
{
	if (!pausado)
		pausado = true;
}
