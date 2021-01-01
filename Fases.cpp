#include "Fases.h"

void Fases::inicializar(Marreta* marreta, int cenarioAtual)
{
	this->marreta = marreta;
	tInicio = gTempo.getTicks();
	cenario = (Cenarios)(cenarioAtual);
	this->cenarioAtual = cenarioAtual;
	gerenciadorDeSpawners(cenario);

	spawnersMortos = numeroDeSpawners;
	spawner = new Spawner[numeroDeSpawners];
	

	for (int snc = 0; snc < 15; snc++)
		spawnerNaoContou[snc] = false;

	for (int s = 0; s < numeroDeSpawners; s++)
	{
		do
		{
			randomX = rand() % 9;
			randomY = rand() % 5;

		} while (temSpawner[randomX][randomY]);

		temSpawner[randomX][randomY] = true;

		posicaoSorteadaX[s] = randomX;
		posicaoSorteadaY[s] = randomY;

		spawner[s].inicializar(posicaoSorteadaX[s], posicaoSorteadaY[s]);
	}

	this->marreta->inicializar("marreta", "assets/imagens/marreta.png", 1, 1, "somMarreta", "assets/sons/marreta.mp3");

	carregarSprites(cenario);
}

void Fases::desenhar()
{
	background.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
}

int Fases::atualizar()
{
	tempo = gTempo.getTempoAteTickAtual(tInicio);

	marreta->atualizar();

	for (int s = 0; s < numeroDeSpawners; s++)
		spawner[s].desenhar();

	for (int s = 0; s < numeroDeSpawners; s++)
	{
		resultado = spawner[s].atualizar(spawner[s].getPosicao(), marreta->getSprite(), marreta->getDescendo(), marreta->getAngulo(), marreta->getMatou());
		
		if (resultado == CHEGOU_NO_FINAL)
			return CHEGOU_NO_FINAL;
		else if (resultado)
			marreta->setMatou();

	}

	for (int s = 0; s < numeroDeSpawners; s++)
	{
		if (!spawner[s].getVivo() && !spawnerNaoContou[s])
		{
			gAudios.tocar("cristal", 60);
			temSpawner[posicaoSorteadaX[s]][posicaoSorteadaY[s]] = false;
			spawnersMortos -= 1;
			spawnerNaoContou[s] = true;
		}
	}
	
	marreta->desenhar();

	return spawnersMortos;
}

void Fases::carregarSprites(Cenarios numeroCenario)
{
	cenario = numeroCenario;

	if (!gRecursos.carregouSpriteSheet("montefuji"))
		gRecursos.carregarSpriteSheet("montefuji", "assets/imagens/montefuji.png", 1, 1);
	if (!gRecursos.carregouSpriteSheet("cristo"))
		gRecursos.carregarSpriteSheet("cristo", "assets/imagens/cristo.png", 1, 1);
	if (!gRecursos.carregouSpriteSheet("tajmahal"))
		gRecursos.carregarSpriteSheet("tajmahal", "assets/imagens/tajmahal.png", 1, 1);
	if (!gRecursos.carregouSpriteSheet("maia"))
		gRecursos.carregarSpriteSheet("maia", "assets/imagens/maia.png", 1, 1);
	if (!gRecursos.carregouSpriteSheet("egito"))
		gRecursos.carregarSpriteSheet("egito", "assets/imagens/egito.png", 1, 1);
	if (!gRecursos.carregouAudio("cristal"))
		gRecursos.carregarAudio("cristal", "assets/sons/cristal.mp3");


	if (cenario == cenario1)
		background.setSpriteSheet("montefuji");
	else if (cenario == cenario2)
		background.setSpriteSheet("cristo");
	else if (cenario == cenario3)
		background.setSpriteSheet("tajmahal");
	else if (cenario == cenario4)
		background.setSpriteSheet("maia");
	else if (cenario == cenario5)
		background.setSpriteSheet("egito");
}


void Fases::gerenciadorDeSpawners(Cenarios numeroCenario)
{
	cenario = numeroCenario;

	if (cenario == cenario1)
		numeroDeSpawners = 7;
	else if (cenario == cenario2)
		numeroDeSpawners = 10;
	else if (cenario == cenario3)
		numeroDeSpawners = 13;
	else if (cenario == cenario4)
		numeroDeSpawners = 14;
	else if (cenario == cenario5)
		numeroDeSpawners = 15;
}

void Fases::finalizar()
{
	for (int s = 0; s < quantidadeDeSpawners; s++)
		spawner[s].finalizar();
	gRecursos.descarregarSpriteSheet("montefuji");
	gRecursos.descarregarSpriteSheet("cristo");
	gRecursos.descarregarSpriteSheet("tajmahal");
	gRecursos.descarregarSpriteSheet("maia");
	gRecursos.descarregarSpriteSheet("egito");
	gRecursos.descarregarAudio("cristal");
	marreta->finalizar();
}
