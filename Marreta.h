#pragma once
#include "libUnicornio.h"

class Marreta
{

public:

	void inicializar(string nome, string caminho, int numAnimacao, int numFrames, string nomeAudio, string caminhoAudio);
	void atualizar();
	void desenhar();
	bool getDescendo() { return descendo; }
	bool getMatou() { return matou; }
	void setMatou() { matou = true; }
	float getAngulo() { return angulo; }
	Sprite getSprite() { return sprite; }
	void finalizar();

protected:

	string nome, nomeAudio;
	Sprite sprite;
	float angulo;
	bool pressionando, descendo, matou;
};

