#include "Marreta.h"

void Marreta::inicializar(string nome, string caminho, int numAnimacao, int numFrames, string nomeAudio, string caminhoAudio)
{
	this->nome = nome;
	this->nomeAudio = nomeAudio;
	angulo = 360;
	pressionando = descendo = matou = false;
	

	if (!gRecursos.carregouSpriteSheet(this->nome))
		gRecursos.carregarSpriteSheet(this->nome, caminho, numAnimacao, numFrames);

	if (!gRecursos.carregouAudio(this->nomeAudio))
		gRecursos.carregarAudio(this->nomeAudio, caminhoAudio);

	sprite.setSpriteSheet(this->nome);
}

void Marreta::atualizar()
{
	if(gMouse.pressionou[BOTAO_MOUSE_ESQ])
		gAudios.tocar(nomeAudio, 100);

	if (gMouse.segurando[BOTAO_MOUSE_ESQ])
	{
		pressionando = true;
		if (angulo > 270)
		{
			angulo -= 10;
			descendo = true;
		}
		else
			descendo = false;
	}
	else
	{
		angulo = 360;
		pressionando = descendo = matou = false;
	}
}

void Marreta::desenhar()
{
	sprite.desenhar(gMouse.x, gMouse.y, angulo);
}

void Marreta::finalizar()
{
	gRecursos.descarregarAudio(nomeAudio);
	gRecursos.descarregarSpriteSheet(nome);
}
