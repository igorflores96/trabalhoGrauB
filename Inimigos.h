#pragma once
#include "libUnicornio.h"
#include <ctime>

#define CHEGOU_NO_FINAL -10

enum TipoInimigo { inimigo1, inimigo2, inimigo3, inimigo4, inimigo5 };

class Inimigo
{
public:

	void inicializar(Vetor2D posicaoSpawner, int tipoSorteado);
	int atualizar(Vetor2D posicaoSpawner, Sprite spriteMarreta, bool descendo, float anguloMarreta, int contadorRespawn, bool matou);
	void desenhar();
	void resetar(Vetor2D posicaoSpawner);
	void carregarSprites();
	bool getVivo() { return vivo; }
	bool getNoRespawn() { return noRespawn; }
	void finalizar();

protected:

	Uint64 tInicioFase;
	Sprite sprite;
	Vetor2D posicao;
	bool vivo, noRespawn, chegouNoFim;
	int vida, tempoDoInicio;
	TipoInimigo tipo;
	float velocidade;

};

