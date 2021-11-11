#ifndef TANK_HEADER
#define TANK_HEADER

class Tank
{
public:
	double capacity;
	double fuel_quantity;
	bool broken;
	bool valve;
	bool isConnected;
	int tank_id;
	Tank(int tank_id,double capacity);

	void fill_tank(double fuel_quantity);
};
#endif 
