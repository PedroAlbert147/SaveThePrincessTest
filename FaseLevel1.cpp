#include "FaseLevel1.hpp"

#include "Enemy.hpp"
#include "include/KeyBoard.hpp"
#include <iostream>
#include <sstream>  // Para std::ostringstream

void FaseLevel1::init()
{	
	//Objetos de jogo
	protagonist= new Protagonist(ObjetoDeJogo("Protagonist",SpriteAnimado("rsc/idle2.anm",1),18,38));
	objs.push_back(protagonist);

	frame = new ObjetoDeJogo("Frame",Sprite("rsc/frame.img"),25,120);
	objs.push_back(frame);
	
	//portao = new ObjetoDeJogo("frontDoor",Sprite("rsc/frontDoor.img"),49,102);
	//objs.push_back(portao);
													 //std::string(20,'#')
	objs.push_back(new ObjetoDeJogo("Life",TextSprite("####################"),20,20));
	SpriteBase *tmp = const_cast<SpriteBase*> (objs.back()->getSprite());
	life = dynamic_cast<TextSprite*> (tmp);

	objs.push_back(new ObjetoDeJogo("Indicator",TextSprite("####################"),20,110));
	tmp = const_cast<SpriteBase*> (objs.back()->getSprite());
	levelIndicators = dynamic_cast<TextSprite*> (tmp);

	objs.push_back(new ObjetoDeJogo("HouseIndicator",TextSprite("####################"),30,130));
	tmp = const_cast<SpriteBase*> (objs.back()->getSprite());
	structureIndicatorHouse = dynamic_cast<TextSprite*> (tmp);

	objs.push_back(new ObjetoDeJogo("MarketIndicator",TextSprite("####################"),33,142));
	tmp = const_cast<SpriteBase*> (objs.back()->getSprite());
	structureIndicatorMarket = dynamic_cast<TextSprite*> (tmp);

	objs.push_back(new ObjetoDeJogo("FuelIndicator",TextSprite("####################"),28,135));
	tmp = const_cast<SpriteBase*> (objs.back()->getSprite());
	structureIndicatorFuel = dynamic_cast<TextSprite*> (tmp);

	objs.push_back(new ObjetoDeJogo("FuelIndicator",TextSprite("####################"),40,164));
	tmp = const_cast<SpriteBase*> (objs.back()->getSprite());
	structureIndicatorBase = dynamic_cast<TextSprite*> (tmp);



	//blocos
	//objs.push_back(new ObjetoDeJogo("B1",Sprite("rsc/castleBlock1.img"),18,38));
	//colisoes.push_back(objs.back());
	
	
}

std::ostringstream oss;

unsigned FaseLevel1::run(SpriteBuffer &screen)
{
	//std::string ent;
	
	//padrão
	draw(screen);
	system("clear");
	show(screen);

	char input;
	bool running = true;
	
	KeyBoard::setNonBlocking(true);

	int gameState = 0; //0 = esperando jogador //1 = processando entrada
	int action = 0; //0 not assigned//1 move

	while (running)
	{
		//lendo entrada

		//getline(std::cin,ent);
		if (gameState == 0){
			if (KeyBoard::readInput(input)){
				// Processa a entrada do teclado
				switch (input)
				{
				case 'q':
					running = false; // Sai do loop se 'q' for pressionado
					break;
				case '1':
					if (protagonist->getCanMove()){
						std::cout << "Movendo para cima" << std::endl;
						gameState = 1;
						break;
					}
				case 's':
					std::cout << "Movendo para baixo" << std::endl;
					break;
				case 'a':
					std::cout << "Movendo para a esquerda" << std::endl;
					break;
				case 'd':
					std::cout << "Movendo para a direita" << std::endl;
					break;
				default:
					std::cout << "Tecla pressionada: " << input << std::endl;
					break;
				}
			}
		}

		oss << " "
		<<"  Saúde: " << protagonist->getLife()
		<< "  Risco: " << protagonist->getRisk()
		<< "  Fome: " << protagonist->getHunger()
		<< "  Combustível: " << protagonist->getFuel()
		;

		life->setText(oss.str());
		oss.str(" ");

		oss << "  Distancia ate a próxima estação: " << protagonist->getDistanceToNextStation() 
		<< "  Distancia ate a fronteira: " << protagonist->getDistanceToEnd()
		<< "  Distancia da tempestade: " << protagonist->getDistanceFromStorm();


		levelIndicators->setText(oss.str());
		oss.str(" ");


		if (protagonist->getHasHouses() == true){
			oss << "Há prédios abandonados aqui.";
			structureIndicatorHouse->setText(oss.str());
			oss.str(" ");
		}else{
			oss.str(" ");
			structureIndicatorHouse->setText(oss.str());
		}

		if (protagonist->getHasDeposit() == true){
			oss << "Há uma estação de combustível aqui.";
			structureIndicatorFuel->setText(oss.str());
			oss.str(" ");
		}else{
			oss.str(" ");
			structureIndicatorFuel->setText(oss.str());
		}

		if (protagonist->getHasMarket() == true){
			oss << "Há um mercado aqui.";
			structureIndicatorMarket->setText(oss.str());
			oss.str(" ");
		}else{
			oss.str(" ");
			structureIndicatorMarket->setText(oss.str());
		}
		
		if (protagonist->getHasBase() == true){
			oss << "Há uma base aqui.";
			structureIndicatorBase->setText(oss.str());
			oss.str(" ");
		}else{
			oss.str(" ");
			structureIndicatorBase->setText(oss.str());
		}


		//processando entradas

		if (gameState==1){
			switch (action){
			case 0:
				gameState = 0;
			case 1:
				protagonist->nextTile();
				gameState = 0;
			}
		}
		/*int posL = hero->getPosL(), posC = hero->getPosC();
		
		if (ent == "w" && hero->getPosL() > 10)
			hero->moveUp(3);
		else if (ent == "s" && hero->getPosL() < screen.getAltura() - 15)
			hero->moveDown(3);
		else if (ent == "a" && hero->getPosC() > 12)
			hero->moveLeft(3);
		else if (ent == "d" && hero->getPosC() < screen.getLargura() - hero->getSprite()->getLargura() - 13)
			hero->moveRight(3);
		else if (ent == "x") {
			for (int g = 0 ; g < 2 ; g++)
				if (hero->colideCom(*guardas[g])) {
					guardas[g]->sofrerAtaque(hero->atacar());
					if (!guardas[g]->isAlive())
						guardas[g]->desativarObj();
				}
		}
		else if (ent == "q")
			return Fase::END_GAME;
			

		if (colideComBloco()) 
			hero->moveTo(posL,posC);
		
		*/
		//processando eventos

		


		/*


		for (int g = 0 ; g < 2 ; g++)
				if (hero->colideCom(*guardas[g])) {
					hero->sofrerAtaque(guardas[g]->atacar());
					
					if (!hero->isAlive())
						return Fase::GAME_OVER;
					
					life->setText(std::string(hero->getLife()/5,'#'));
				}
		
		if (hero->colideCom(*chave))
		{
			chave->desativarObj();
			miniChave->ativarObj();
			hero->pegarChave();
		}
		else if (hero->colideCom(*tapetePorta) && hero->possuiChave())
		{
			porta->openTheDoor();
		}
		else if (hero->colideCom(*princesa))
		{
			princesa->desativarObj();
			hero->salvarPrincesa();
		}
		else if (hero->colideCom(*portao) && hero->salvouPrincesa())
		{
			return Fase::LEVEL_COMPLETE;
		}
		*/
		
		//padrão
		update();
		draw(screen);
		system("clear");
		show(screen);
		usleep(200000);
		
	}
	return Fase::END_GAME; // não necessário
}

/*bool FaseLevel1::colideComBloco() const
{
	for (auto it = colisoes.begin() ; it != colisoes.end() ; ++it)
		if (hero->colideCom(**it)) {
			return true;
		}
	
	if (hero->colideCom(*porta) && !porta->isOpen() )
		return true;
	
	return false;
}
*/
