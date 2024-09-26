#ifndef PROTAGONIST_HPP
#define PROTAGONIST_HPP

#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include <random>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()


class Protagonist : public ObjetoDeJogo
{
public:
	Protagonist(const ObjetoDeJogo &obj, int life=100, int risk=0,int hunger=100,int energy=100,int fuel = 100,int distanceToEnd = 5000,int distanceToNextStation = 15, int distanceFromStorm = 250, int day = 0) : ObjetoDeJogo(obj), life(life), risk(risk), hunger(hunger), fuel(fuel), day(day), distanceToNextStation(distanceToNextStation), distancefromStorm(distanceFromStorm), distanceToEnd(distanceToEnd),canMove(true), canAct(true), HasMarket(true), HasPharmacy(true), HasBase(true), HasHouses(true), HasFuelDeposit(true) {}
	virtual ~Protagonist()	{}
	
	void Solver() { 
		canMove = false;
		int baseRisk = (100 - getDistanceFromStorm() - ((5000 - getDistanceToEnd()) * 0.01));
		if (baseRisk < 0) {
			baseRisk = 0;
		}
		risk = baseRisk;
		if (getFuel() >= getDistanceToNextStation()){
			canMove = true;
		} 
	}
	void nextTile(){
		setFuel(getFuel() - getDistanceToNextStation());
		setDistanceFromStorm(getDistanceFromStorm() + getDistanceToNextStation());
		setDistanceToEnd(getDistanceToEnd() - getDistanceToNextStation());
		setDistanceToNextStation(getRandomNumber (10 + (getDay() * 5), 50 + (getDay() * 5)));
		HasBase = randomChance(10);
		HasPharmacy = randomChance(15);
		HasFuelDeposit = randomChance(33);
		HasHouses = randomChance(75);
		HasMarket = randomChance(25);
		//provavelmente gastar um tempo

		Solver();
	}
	
	bool randomChance(int percentage) {
		srand(std::time(0));
    	return (rand() % 100) < percentage;
	}
	int getRandomNumber(int A, int B) {
		srand(std::time(0));
    	return A + rand() % (B - A + 1);
	}

	//bool isAlive() const { return life != 0; }
	int getLife() const { return life; }
	int getRisk() const { return risk; }
	int getHunger() const { return hunger; }
	int getFuel() const { return fuel; }
	void setFuel(int newFuel){ fuel = newFuel;}
	int getDay() const {return day;}
	int getDistanceToEnd() const { return distanceToEnd; }
	void setDistanceToEnd(int newDistance){ distanceToEnd = newDistance;} 
	int getDistanceToNextStation() const { return distanceToNextStation; }
	void setDistanceToNextStation(int newDistance){ distanceToNextStation = newDistance;}
	int getDistanceFromStorm() const { return distancefromStorm; }
	void setDistanceFromStorm(int newDistance){ distancefromStorm = newDistance;}
	bool getCanMove() const { return canMove; }
	bool getCanAct() const { return canAct; }

	bool getHasMarket() const { return HasMarket; }
	bool getHasBase() const { return HasBase; }
	bool getHasHouses() const { return HasHouses; }
	bool getHasPharmacy() const { return HasPharmacy; }
	bool getHasDeposit() const { return HasFuelDeposit; }
	
	
	//void sofrerAtaque(int ataque) { life = (life - ataque >= 0)?(life - ataque):0; }
	//int atacar() const { return 10; }
	
	//void pegarChave() { chave = true; }
	//bool possuiChave() const { return chave; } 
	
	//void salvarPrincesa() { princesa = true; }
	//bool salvouPrincesa() const { return princesa; }

private:
	int life;
	int risk;
	int hunger;
	int energy;
	int fuel;
	int distanceToEnd;
	int distanceToNextStation;
	int distancefromStorm;
	int day;
	bool isTurn;
	bool canMove;
	bool HasMarket;
	bool HasPharmacy;
	bool HasBase;
	bool HasHouses;
	bool HasFuelDeposit;
	bool canAct;
};

#endif // PROTAGONIST_HPP
