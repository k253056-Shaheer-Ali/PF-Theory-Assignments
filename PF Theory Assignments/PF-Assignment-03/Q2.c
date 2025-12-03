#include<stdio.h>

float calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets){
	
	if (fuel <= 0) { //base case
		printf("Planet %d: Fuel Remaining = 0\n", planet);
        printf("\nMission Failed! Spacecraft ran out of fuel.\n");
		return 0;
	}
	if (planet > totalPlanets) {  //base case
        printf("\nMission Successful! Spacecraft completed the journey.\n");
        return 1;
    }
	
    fuel = fuel - consumption;
    fuel = fuel + recharge;
    //Solar recharge every 4th planet
    if(planet%4 == 0){
        fuel = fuel + solarBonus;
    }

    printf("Planet %d: Fuel Remaining = %d\n", planet, fuel);

    return calculateFuel(fuel, consumption, recharge, solarBonus, planet+1, totalPlanets);
}

int main(){ //i did all values hardcoded
	int initialFuel = 500;      // starting fuel
    int consumption  = 70;      // fuel used per planet
    int recharge     = 20;      // gravitational assist fuel
    int solarBonus   = 100;     // solar recharge after every 4th planet
    int totalPlanets = 10; 

    calculateFuel(initialFuel, consumption, recharge, solarBonus, 1, totalPlanets);
	return 0;
}
