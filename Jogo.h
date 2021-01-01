#pragma once
#include "Fases.h";

enum Telas { tJogo, tCreditos, tInstrucoes, tSaida, tInicial, tPassouFase, tGameOver };
enum Botoes { bJogar, bCreditos, bInstrucoes, bSair, bOk, bVoltar, bProxima };

class Jogo
{
public:
	Jogo();
	~Jogo();

	void inicializar();
	void executar();
	void finalizar();

protected:

	Telas telaAtual;
	Fases fase;
	Marreta marreta;
	BotaoSprite botoes[7];
	Sprite background;
	int statusResultado;

	void telaInicial();
	void telaJogo();
	void telaCreditos();
	void telaInstrucoes();
	void telaPassouFase();
	void telaGameOver();

	
};

