#include "Tank.h"

Tank::Tank(int tank_id,double capacity)
{
	valve = false;
	this->capacity = capacity;
	broken = false;
	fuel_quantity = 0;
	isConnected = false;
	this->tank_id = tank_id;
}

void Tank::fill_tank(double fuel_quantity)
{
	if (fuel_quantity <= 0) return;
	if (this->fuel_quantity + fuel_quantity >= capacity)
	{
		this->fuel_quantity = capacity;
	}
	else
	{
		this->fuel_quantity += fuel_quantity;
	}
}
