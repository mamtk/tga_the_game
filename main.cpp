#include "Jogo.h"

using namespace std;

int main(int argc, char* argv[])
{
	vector<int> a;
	Jogo jogo;
	jogo.inicializar();
	jogo.executar();
	jogo.finalizar();

	return 0;
}