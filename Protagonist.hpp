#ifndef PROTAGONIST_HPP
#define PROTAGONIST_HPP

#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include <random>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()


class Protagonist : public ObjetoDeJogo
{
public:
	Protagonist(const ObjetoDeJogo &obj, int life=100, int risk=0,int hunger=100,int energy=100,int fuel = 100,int distanceToEnd = 5000,int distanceToNextStation = 15, int distanceFromStorm = 250, int day = 0) : ObjetoDeJogo(obj), life(life), risk(risk), hunger(hunger), fuel(fuel), day(day), distanceToNextStation(distanceToNextStation), distancefromStorm(distanceFromStorm), distanceToEnd(distanceToEnd),canMove(true), canAct(true), HasMarket(true), HasPharmacy(true), HasBase(true), HasHouses(true), HasFuelDeposit(true), canLoot(true) {}
	virtual ~Protagonist()	{}
	
	void Solver() { 
		canMove = false;
		canLoot = false;
		int baseRisk = (100 - getDistanceFromStorm() - ((5000 - getDistanceToEnd()) * 0.01));
		if (baseRisk < 0) {
			baseRisk = 0;
		}
		if (baseRisk > 100){
			baseRisk = 100;
		}
		risk = baseRisk;

		if (getDistanceFromStorm() <= 0){
			setLife(getLife() - 5);
		}

		//can move attributer
		if (getFuel() >= getDistanceToNextStation()){
			canMove = true;
		} 
		//can loot attributer
		if(getHasBase() == true || getHasDeposit() == true || getHasHouses() == true || getHasMarket() == true || getHasPharmacy() == true){
			canLoot = true;
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
		setDay(getDay()+1);
		//provavelmente gastar um tempo
		

		Solver();
	}
	
	void loot(int target){

		setDay(getDay()+1);


		int dice = getRandomNumber(50,150) - risk;
		if (dice < 0){
			dice = 0;
		}

		switch(target){
		
		case 1:// house
			if (dice >= 25){
				addToInv(getRandomNumber(1,3));
			}
			break;
		case 2:// market
			if (dice >= 33){
				addToInv(1);
			}
			break;
		case 3:// fuel
			if (dice >= 40) {
				setFuel(getFuel()+25);
			}
			break;
		case 4:// pharmacy
			if (dice >=50) {
				addToInv(3);
			}
			break;
		}

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
	void setLife(int newLife){ 
		if (newLife < 0){
			life = 0;
		}
		if (newLife > 100){
			life = 100;
		}
		life = newLife;}
	int getRisk() const { return risk; }
	int getHunger() const { return hunger; }
	int getFuel() const { return fuel; }
	void setFuel(int newFuel){ 
		if (newFuel < 0){
			fuel = 0;
		}
		if (newFuel > 100){
			fuel = 100;
		}
		fuel = newFuel;}
	int getDay() const {return day;}
	void setDay(int newDay){ 
		day = newDay;
		setDistanceFromStorm(getDistanceFromStorm() - 20);
	}
	int getDistanceToEnd() const { return distanceToEnd; }
	void setDistanceToEnd(int newDistance){ distanceToEnd = newDistance;} 
	int getDistanceToNextStation() const { return distanceToNextStation; }
	void setDistanceToNextStation(int newDistance){ distanceToNextStation = newDistance;}
	int getDistanceFromStorm() const { return distancefromStorm; }
	void setDistanceFromStorm(int newDistance){ distancefromStorm = newDistance;}
	bool getCanMove() const { return canMove; }
	bool getCanAct() const { return canAct; }
	bool getCanLoot() const { return canLoot; }

	void addToInv(int target){
		for(int i = 0;i <= 9;i++){
			if (Inventory[i] == 0) {
				Inventory[i] = target;
				return;
			}
		}
		//mensagem de inventario lotado
	}

	void delFromInv(int target){
		for(int i = 0;i <= 9;i++){
			if (Inventory[i] == target) {
				Inventory[i] = 0;
				return;
			}
		}
	}

	bool hasInInv(int target){
		for(int i = 0;i <= 9;i++){
			if (Inventory[i] == target) {
				return true;
			}
		}
		return false;
	}


	bool getHasMarket() const { return HasMarket; }
	bool getHasBase() const { return HasBase; }
	bool getHasHouses() const { return HasHouses; }
	bool getHasPharmacy() const { return HasPharmacy; }
	bool getHasDeposit() const { return HasFuelDeposit; }

	int Inventory[9] = {0,0,0,0,0,0,0,0,0};

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
	bool canLoot;


};

#endif // PROTAGONIST_HPP
