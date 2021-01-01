#include "Jogo.h"

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
	srand(time(0));

	uniInicializar(1024, 768, false, "Monsters Invaders");

	//Backgrounds
	if (!gRecursos.carregouSpriteSheet("tCreditos"))
		gRecursos.carregarSpriteSheet("tCreditos", "assets/imagens/tCreditos.png", 1, 1);
	if (!gRecursos.carregouSpriteSheet("tInstrucoes"))
		gRecursos.carregarSpriteSheet("tInstrucoes", "assets/imagens/tInstrucoes.png", 1, 1);
	if (!gRecursos.carregouSpriteSheet("tMenu"))
		gRecursos.carregarSpriteSheet("tMenu", "assets/imagens/tMenu.png", 1, 1);
	if (!gRecursos.carregouSpriteSheet("tProximaFase"))
		gRecursos.carregarSpriteSheet("tProximaFase", "assets/imagens/tProximaFase.png", 1, 1);
	if (!gRecursos.carregouSpriteSheet("gameover"))
		gRecursos.carregarSpriteSheet("gameover", "assets/imagens/tGameOver.png", 1, 1);

	//Botoes
	gRecursos.carregarSpriteSheet("bJogar", "assets/botoes/jogar.png", 3);
	botoes[bJogar].setSpriteSheet("bJogar");
	botoes[bJogar].setPos(gJanela.getLargura() / 2, 500);

	gRecursos.carregarSpriteSheet("bCreditos", "assets/botoes/creditos.png", 3);
	botoes[bCreditos].setSpriteSheet("bCreditos");
	botoes[bCreditos].setPos(gJanela.getLargura() / 2, 550);

	gRecursos.carregarSpriteSheet("bInstrucoes", "assets/botoes/instrucoes.png", 3);
	botoes[bInstrucoes].setSpriteSheet("bInstrucoes");
	botoes[bInstrucoes].setPos(gJanela.getLargura() / 2, 600);

	gRecursos.carregarSpriteSheet("bSair", "assets/botoes/sair.png", 3);
	botoes[bSair].setSpriteSheet("bSair");
	botoes[bSair].setPos(gJanela.getLargura() / 2, 650);

	gRecursos.carregarSpriteSheet("bOk", "assets/botoes/ok.png", 3);
	botoes[bOk].setSpriteSheet("bOk");
	botoes[bOk].setPos(890, 720);

	gRecursos.carregarSpriteSheet("bVoltar", "assets/botoes/voltar.png", 3);
	botoes[bVoltar].setSpriteSheet("bVoltar");
	botoes[bVoltar].setPos(890, 720);

	gRecursos.carregarSpriteSheet("bProxima", "assets/botoes/proxima.png", 3);
	botoes[bProxima].setSpriteSheet("bProxima");
	botoes[bProxima].setPos(890, 720);

	//Músicas
	if (!gRecursos.carregouMusica("musicamenu"))
		gRecursos.carregarMusica("musicamenu", "assets/sons/musicamenu.mp3", 40);
	if (!gRecursos.carregouMusica("musicabatalha"))
		gRecursos.carregarMusica("musicabatalha", "assets/sons/musicabatalha.mp3", 50);
	if (!gRecursos.carregouMusica("musicavitoria"))
		gRecursos.carregarMusica("musicavitoria", "assets/sons/vitoria.mp3", 50);

	telaAtual = tInicial;

}



void Jogo::executar()
{
	while (telaAtual != tSaida && !gEventos.sair)
	{
		uniIniciarFrame();

		switch (telaAtual)
		{
		case tInicial: telaInicial();
			break;

		case tJogo: telaJogo();
			break;

		case tCreditos: telaCreditos();
			break;

		case tInstrucoes: telaInstrucoes();
			break;

		case tPassouFase: telaPassouFase();
			break;

		case tGameOver: telaGameOver();
			break;
		}

		uniTerminarFrame();
	}
}

void Jogo::finalizar()
{
	fase.finalizar();
	gRecursos.descarregarTudo();

	uniFinalizar();
}

void Jogo::telaInicial()
{
	if (!gMusica.estaTocando())
		gMusica.tocar("musicamenu", true);

	background.setSpriteSheet("tMenu");
	background.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	botoes[bJogar].atualizar();
	botoes[bJogar].desenhar();
	if (botoes[bJogar].estaClicado())
	{
		gMusica.parar();
		telaAtual = tJogo;
		fase.inicializar(&marreta, 0);
	}

	botoes[bCreditos].atualizar();
	botoes[bCreditos].desenhar();
	if (botoes[bCreditos].estaClicado())
	{
		telaAtual = tCreditos;
	}

	botoes[bInstrucoes].atualizar();
	botoes[bInstrucoes].desenhar();
	if (botoes[bInstrucoes].estaClicado())
	{
		telaAtual = tInstrucoes;
	}

	botoes[bSair].atualizar();
	botoes[bSair].desenhar();
	if (botoes[bSair].estaClicado())
	{
		telaAtual = tSaida;
	}
}

void Jogo::telaJogo()
{
	gMouse.esconderCursor();

	if(!gMusica.estaTocando())
		gMusica.tocar("musicabatalha", true);

	fase.desenhar();
	statusResultado = fase.atualizar();
	if (statusResultado == 0)
	{
		gMusica.parar();
		telaAtual = tPassouFase;
	}
	else if (statusResultado == CHEGOU_NO_FINAL)
	{
		gMusica.parar();
		telaAtual = tGameOver;
	}
}

void Jogo::telaCreditos()
{
	background.setSpriteSheet("tCreditos");
	background.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	botoes[bOk].atualizar();
	botoes[bOk].desenhar();
	if (botoes[bOk].estaClicado())
	{
		telaAtual = tInicial;
	}
}

void Jogo::telaInstrucoes()
{
	background.setSpriteSheet("tInstrucoes");
	background.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	botoes[bVoltar].atualizar();
	botoes[bVoltar].desenhar();
	if (botoes[bVoltar].estaClicado())
	{
		telaAtual = tInicial;
	}
}

void Jogo::telaPassouFase()
{
	gMouse.mostrarCursor();

	if (!gMusica.estaTocando())
		gMusica.tocar("musicavitoria", true);
	
	background.setSpriteSheet("tProximaFase");
	background.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	botoes[bProxima].atualizar();
	botoes[bProxima].desenhar();
	if (botoes[bProxima].estaClicado())
	{

		gMusica.parar();
		if ((fase.getCenarioAtual() + 1) <= 4)
		{
			telaAtual = tJogo;
			fase.inicializar(&marreta, fase.getCenarioAtual() + 1);
		}
		else
			telaAtual = tInicial;
	}
}

void Jogo::telaGameOver()
{
	gMouse.mostrarCursor();

	background.setSpriteSheet("gameover");
	background.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	botoes[bVoltar].atualizar();
	botoes[bVoltar].desenhar();
	if (botoes[bVoltar].estaClicado())
	{
		telaAtual = tInicial;
	}
}
