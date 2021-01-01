#pragma once
#include "Spawners.h"
#include "Marreta.h"

const int quantidadeDeSpawners = 18;

enum Cenarios {cenario1, cenario2, cenario3, cenario4, cenario5};

class Fases
{
public:

	void inicializar(Marreta *marreta, int cenarioAtual);
	void desenhar();
	int atualizar();
	void carregarSprites(Cenarios numeroCenario);
	int getCenarioAtual() { return cenarioAtual; }
	int getNumeroDeSpawners() { return numeroDeSpawners; }
	void gerenciadorDeSpawners(Cenarios numeroCenario);
	void finalizar();

protected:

	Texto texto;
	Uint64 tInicio;
	Marreta *marreta;
	Sprite background;
	Cenarios cenario;
	Spawner *spawner;
	int posicaoSorteadaX[quantidadeDeSpawners], posicaoSorteadaY[quantidadeDeSpawners], randomX, randomY, numeroDeSpawners = 0, tempo, cenarioAtual, spawnersMortos = 0;
	int resultado;
	bool temSpawner[9][5] = {}, spawnerNaoContou[15] = {};

};

