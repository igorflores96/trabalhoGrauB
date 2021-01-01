#include "Spawners.h"

void Spawner::inicializar(int posicaoSorteadaX, int posicaoSorteadaY)
{
	carregarSprites();
	definirPosicoes();
	posicao = posicoes[posicaoSorteadaX][posicaoSorteadaY];
	vivo = true;
	tInicioRespawn = gTempo.getTicks();
	tempo = 5;
	inimigo.inicializar(posicoes[posicaoSorteadaX][posicaoSorteadaY], rand() % 5);

}

void Spawner::definirPosicoes()
{
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			if (x == 0 && y == 0)
			{
				posicoes[x][y].x = 384;
				posicoes[x][y].y = 134;
			}
			else
			{
				posicoes[x][y].x = 384 + (64 * (x + 1));
				posicoes[x][y].y = 134 * (y + 1);
			}
		}
	}
}

void Spawner::carregarSprites()
{
	if (!gRecursos.carregouSpriteSheet("spawner1"))
		gRecursos.carregarSpriteSheet("spawner1", "assets/imagens/spawner1.png", 1, 3);

	sprite.setSpriteSheet("spawner1");
}

void Spawner::desenhar()
{
	vivo = inimigo.getVivo();

	if (vivo)
		sprite.desenhar(posicao.x, posicao.y);

}


int Spawner::atualizar(Vetor2D posicao, Sprite spriteMarreta, bool descendo, float anguloMarreta, bool matou)
{
	sprite.avancarAnimacao();

	if (!inimigo.getNoRespawn())
	{
		resultado = inimigo.atualizar(posicao, spriteMarreta, descendo, anguloMarreta, inimigosRespawnados, matou);

		if (resultado == CHEGOU_NO_FINAL)
			return CHEGOU_NO_FINAL;
		else if (resultado)
			return 1;
	}

	if (!inimigo.getNoRespawn())
		inimigo.desenhar();

	if (inimigo.getNoRespawn())
	{
		if (gTempo.getTempoAteTickAtual(tInicioRespawn) > tempo)
		{
			inimigo.resetar(this->posicao);
			tInicioRespawn = gTempo.getTicks();
			inimigosRespawnados += 1;
		}
	}


	return 0;
}



void Spawner::finalizar()
{
	inimigo.finalizar();
	gRecursos.descarregarSpriteSheet("spawner1");
}
