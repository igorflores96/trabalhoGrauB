#include "Inimigos.h"


void Inimigo::inicializar(Vetor2D posicaoSpawner, int tipoSorteado)
{
	posicao = posicaoSpawner;
	tipo = (TipoInimigo)(tipoSorteado);
	vivo = true;
	noRespawn = false;

	carregarSprites();

	if (tipo == inimigo1)
	{
		sprite.setSpriteSheet("medusa");
		vida = 3;
		velocidade = 0.6;
	}
	if (tipo == inimigo2)
	{
		sprite.setSpriteSheet("minidragon");
		velocidade = 1;
		vida = 1;
		posicao.y += 50; // pra nascer mais embaixo.
	}
	if (tipo == inimigo3)
	{
		sprite.setSpriteSheet("dragon");
		velocidade = 0.2;
		vida = 4;
	}
	if (tipo == inimigo4)
	{
		sprite.setSpriteSheet("demon");
		velocidade = 0.5;
		vida = 5;
	}
	if (tipo == inimigo5)
	{
		sprite.setSpriteSheet("lagarto");
		velocidade = 0.9;
		vida = 2;
		posicao.y += 25; // pra nascer mais embaixo.
	}

	tInicioFase = gTempo.getTicks();

}

int Inimigo::atualizar(Vetor2D posicaoSpawner, Sprite spriteMarreta, bool descendo, float anguloMarreta, int contadorRespawn, bool matou)
{
	sprite.avancarAnimacao();

	if (this->tipo == inimigo1)
		sprite.setVelocidadeAnimacao(3);
	else if (this->tipo == inimigo2)
		sprite.setVelocidadeAnimacao(3);
	else if (this->tipo == inimigo3)
		sprite.setVelocidadeAnimacao(1);
	else if (this->tipo == inimigo4)
		sprite.setVelocidadeAnimacao(4);
	else if (this->tipo == inimigo5)
		sprite.setVelocidadeAnimacao(4);


	if (tempoDoInicio > 1 && !noRespawn)
	{
		if (this->posicao.x < sprite.getLargura() / 2 && vivo)
		{
			return CHEGOU_NO_FINAL;
		}
		else if (uniTestarColisao(spriteMarreta, gMouse.x, gMouse.y, anguloMarreta, sprite, posicao.x, posicao.y, 0) && gMouse.pressionou[BOTAO_MOUSE_ESQ] && vivo && descendo && !matou)
		{
			
			vida -= 1;

			if (vida == 0 && contadorRespawn == 8)
			{
				gAudios.tocar("hitmonstro", 10);
				vivo = false;
			}
			else if (vida == 0)
			{
				gAudios.tocar("hitmonstro", 10);
				noRespawn = true;
				return 1;
			}
		}
		else
		{
			this->posicao.x -= velocidade;
		}
	}


	return 0;
}

void Inimigo::desenhar()
{
	tempoDoInicio = gTempo.getTempoAteTickAtual(tInicioFase);


	if (vivo && tempoDoInicio > 1 && !noRespawn)
		sprite.desenhar(posicao.x, posicao.y);
}

void Inimigo::resetar(Vetor2D posicaoSpawner)
{
	tipo = (TipoInimigo)(rand() % 5);
	if (tipo == inimigo1)
	{
		sprite.setSpriteSheet("medusa");
		velocidade = 0.3;
		vida = 2;
	}
	if (tipo == inimigo2)
	{
		sprite.setSpriteSheet("minidragon");
		velocidade = 0.8;
		vida = 1;
	}
	if (tipo == inimigo3)
	{
		sprite.setSpriteSheet("dragon");
		velocidade = 0.2;
		vida = 4;
	}
	if (tipo == inimigo4)
	{
		sprite.setSpriteSheet("demon");
		velocidade = 0.5;
		vida = 5;
	}
	if (tipo == inimigo5)
	{
		sprite.setSpriteSheet("lagarto");
		velocidade = 0.9;
		vida = 2;
	}

	noRespawn = false;
	posicao = posicaoSpawner;

}


void Inimigo::carregarSprites()
{
	if (!gRecursos.carregouSpriteSheet("medusa"))
		gRecursos.carregarSpriteSheet("medusa", "assets/imagens/medusateste1.png", 1, 4);
	if (!gRecursos.carregouSpriteSheet("minidragon"))
		gRecursos.carregarSpriteSheet("minidragon", "assets/imagens/minidragon.png", 1, 4);
	if (!gRecursos.carregouSpriteSheet("dragon"))
		gRecursos.carregarSpriteSheet("dragon", "assets/imagens/dragon.png", 1, 5);
	if (!gRecursos.carregouSpriteSheet("demon"))
		gRecursos.carregarSpriteSheet("demon", "assets/imagens/demon.png", 1, 4);
	if (!gRecursos.carregouSpriteSheet("lagarto"))
		gRecursos.carregarSpriteSheet("lagarto", "assets/imagens/lagarto.png", 1, 4);

	if(!gRecursos.carregouAudio("hitmonstro"))
		gRecursos.carregarAudio("hitmonstro", "assets/sons/hitmonstro.mp3");

}


void Inimigo::finalizar()
{
	gRecursos.descarregarSpriteSheet("medusa");
	gRecursos.descarregarSpriteSheet("minidragon");
	gRecursos.descarregarSpriteSheet("dragon");
	gRecursos.descarregarSpriteSheet("demon");
	gRecursos.descarregarSpriteSheet("lagarto");
}
