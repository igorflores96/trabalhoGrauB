#pragma once
#include "Inimigos.h"


const int quantidadeInimigos = 10;


class Spawner
{

public:

	void inicializar(int posicaoSorteadaX, int posicaoSorteadaY);
	void definirPosicoes();
	void carregarSprites();
	void desenhar();
	int atualizar(Vetor2D posicao, Sprite spriteMarreta, bool descendo, float anguloMarreta, bool matou);
	Vetor2D getPosicao() { return posicao; }
	bool getVivo() { return vivo; }
	void finalizar();

protected:

	Uint64 tInicioRespawn;
	Inimigo inimigo;
	Sprite sprite;
	Vetor2D posicoes[9][5], posicao;
	bool vivo;
	int inimigosRespawnados = 0, tempo, resultado;

};

