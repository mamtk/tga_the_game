#pragma once
#include "libUnicornio.h"

// função módulo matemático (≠ resto da divisão)
int modulo(int a, int b)
{
	/***
	retorna o resto da divisão, porém, no caso de valores negativos,
		a adição de b neutraliza o sinal, e repete o resto da divisão
		com esse valor, para finalmente obter um resultado positivo
	***/
	return (a%b + b) % b;
}

/*
Isso aqui deu errado de uma forma tal que é difícil até de imaginar.
Parece que a função desenhar é responsável por atualizar a animação, o que
	significa que quando eu desenho uma cópia do objeto, a animação no objeto
	original não é atualizada. Resumindo, vou ter que fazer isso na mão em cada
	classe, contexto, etc. PS: quem ia explicar a referência?

// função para desenhar um painel de história
void desenharHistoria(Sprite &fundo)	// fundo é uma cópia, quem ia explicar a referência?
{
	fundo.setEscala(10, 10);
	fundo.desenhar(499, 499);
}
*/