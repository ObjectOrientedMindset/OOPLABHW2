#ifndef ENGINE_HEADER
#define ENGINE_HEADER


#include"Read.h"
#include"Tank.h"
class Engine
{
private:
	struct internalTank {
		double capacity;
		double fuel;
	};
	internalTank internal_tank;
	const double fuel_per_second = 5.5;
	bool status;
	int runIterator;
	int tank_id;
	double total_consumed_fuel;
	double total_fuel;
	Read* read;
	vector<commands> command;
	vector<Tank> tanks;
	fstream myfile;
	string outputFile;
public:
	Engine();
	~Engine();
	void run();
	void add_fuel_tank(double capacity);
	void remove_fuel_tank(int tank_id);
	void connect_fuel_tank_to_engine(int tank_id);
	void disconnect_fuel_tank_from_engine(int tank_id);
	void fill_tank(int tank_id, double quantity);
	void start_engine();
	void stop_engine();
	void absorb_fuel();
	void consume_fuel();
	void wait(int seconds);
	void open_valve(int tank_id);
	void close_valve(int tank_id);
	void break_fuel_tank(int tank_id);
	void repair_fuel_tank(int tank_id);
};
#endif
