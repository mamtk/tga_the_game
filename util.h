#pragma once

// função módulo matemático
int modulo(int a, int b) {
	/***
	retorna o resto da divisão, porém, no caso de valores negativos,
		a adição de b neutraliza o sinal, e repete o resto da divisão
		com esse valor, para finalmente obter um resultado positivo
	***/
	return (a%b + b) % b;
}