#ifndef FASELEVEL1_HPP
#define FASELEVEL1_HPP

#include "ASCII_Engine/Fase.hpp"
#include <string>
#include <list>

#include "Enemy.hpp"
#include "Door.hpp"
#include "Hero.hpp"
#include "Protagonist.hpp"

class FaseLevel1 : public Fase
{
public:
	FaseLevel1(std::string name, const Sprite &bkg) : Fase(name,bkg) {}
	FaseLevel1(std::string name, const SpriteAnimado &bkg) : Fase(name,bkg) {}
	virtual ~FaseLevel1() {}
	
	
	virtual void init();
	virtual unsigned run(SpriteBuffer &screen);
	
	bool colideComBloco() const;
	
private:

	Enemy *guardas[2];
	Protagonist *protagonist;
	Hero *hero;
	Door *porta;
	ObjetoDeJogo *tapetePorta;
	ObjetoDeJogo *portao;
	ObjetoDeJogo *chave;
	ObjetoDeJogo *miniChave;
	ObjetoDeJogo *princesa;
	ObjetoDeJogo *frame;
	ObjetoDeJogo *train;
	
	TextSprite *life;
	TextSprite *levelIndicators;
	TextSprite *structureIndicatorHouse;
	TextSprite *structureIndicatorFuel;
	TextSprite *structureIndicatorMarket;
	TextSprite *structureIndicatorPharmacy;
	TextSprite *structureIndicatorBase;
	TextSprite *InventoryIndicator;
	
	std::list<ObjetoDeJogo*> colisoes;
};

#endif // FASELEVEL1_HPP
