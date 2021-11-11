#include "Engine.h"

Engine::Engine()
{
	cout << "Enter the Output File Name : (Default File Name is output.txt)" << endl;
	cin >> outputFile;
	status = false;
	runIterator = 0;
	read = read->getInstance();
	read->readFile();
	command = read->getData();
	internal_tank.capacity = 55;
	internal_tank.fuel = 0;
	tank_id = 1;
	total_consumed_fuel = 0;
	total_fuel = 0;
	srand(time(0));
	myfile.open(outputFile, ios::out);
}

Engine::~Engine()
{
	delete read;
}

void Engine::run()
{
	while (command[runIterator].command != "stop_simulation" && runIterator < command.size())
	{
		if (internal_tank.fuel < 20 && status)
		{
			absorb_fuel();
		}

		if (command[runIterator].command == "start_engine")
		{
			start_engine();
		}
		else if (command[runIterator].command == "stop_engine")
		{
			stop_engine();
		}
		else if (command[runIterator].command == "add_fuel_tank")
		{
			add_fuel_tank(command[runIterator].idCapacity);
			consume_fuel();
		}
		else if (command[runIterator].command == "remove_fuel_tank")
		{
			remove_fuel_tank(command[runIterator].idCapacity);
			consume_fuel();
		}
		else if (command[runIterator].command == "connect_fuel_tank_to_engine")
		{
			connect_fuel_tank_to_engine(command[runIterator].idCapacity);
			consume_fuel();
		}
		else if (command[runIterator].command == "disconnect_fuel_tank_from_engine")
		{
			disconnect_fuel_tank_from_engine(command[runIterator].idCapacity);
			consume_fuel();
		}
		else if (command[runIterator].command == "fill_tank")
		{
			fill_tank(command[runIterator].idCapacity, command[runIterator].quantity);
			consume_fuel();
		}
		else if (command[runIterator].command == "open_valve")
		{
			open_valve(command[runIterator].idCapacity);
			consume_fuel();
		}
		else if (command[runIterator].command == "close_valve")
		{
			close_valve(command[runIterator].idCapacity);
			consume_fuel();
		}
		else if (command[runIterator].command == "break_fuel_tank")
		{
			break_fuel_tank(command[runIterator].idCapacity);
			consume_fuel();
		}
		else if (command[runIterator].command == "repair_fuel_tank")
		{
			repair_fuel_tank(command[runIterator].idCapacity);
			consume_fuel();
		}
		else if (command[runIterator].command == "wait")
		{
			wait(command[runIterator].idCapacity);
		}
		else if (command[runIterator].command == "list_fuel_tanks")
		{
			if (myfile.is_open())
			{
				myfile << "Fuel Tanks Id List" << endl;
				for (size_t i = 0; i < tanks.size(); i++)
				{
					myfile << tanks[i].tank_id << endl;
				}
				myfile << "---------------------------------------------------" << endl;
			}
			else
			{
				cout << "Error Opening Output File" << endl;
			}
		}
		else if (command[runIterator].command == "print_fuel_tank_count")
		{
			if (myfile.is_open())
			{
				myfile << "Fuel Tank Count" << endl;
				myfile << tanks.size() << endl;
				myfile << "---------------------------------------------------" << endl;
			}
			else
			{
				cout << "Error Opening Output File" << endl;
			}
		}
		else if (command[runIterator].command == "list_connected_tanks")
		{
			if (myfile.is_open())
			{
				myfile << "Connected Tank List" << endl;
				for (size_t i = 0; i < tanks.size(); i++)
				{
					if (tanks[i].isConnected)
					{
						myfile << tanks[i].tank_id << endl;
					}
				}
				myfile << "---------------------------------------------------" << endl;
			}
			else
			{
				cout << "Error Opening Output File" << endl;
			}
		}
		else if (command[runIterator].command == "print_total_fuel_quantity")
		{
			if (myfile.is_open())
			{
				myfile << "Total Fuel Quantity" << endl;
				for (size_t i = 0; i < tanks.size(); i++)
				{
					total_fuel += tanks[i].fuel_quantity;
				}
				total_fuel += internal_tank.fuel;
				myfile << total_fuel << endl;
				myfile << "---------------------------------------------------" << endl;
			}
			else
			{
				cout << "Error Opening Output File" << endl;
			}
		}
		else if (command[runIterator].command == "print_total_consumed_fuel_quantity")
		{
			if (myfile.is_open())
			{
				myfile << "Total Consumed Fuel" << endl;
				myfile << total_consumed_fuel << endl;
				myfile << "---------------------------------------------------" << endl;
			}
			else
			{
				cout << "Error Opening Output File" << endl;
			}
		}
		else if (command[runIterator].command == "print_tank_info")
		{
			if (myfile.is_open())
			{
				myfile << "Tank Info" << endl;
				myfile << "Broken : " << tanks[command[runIterator].idCapacity].broken << endl;
				myfile << "Capacity : " << tanks[command[runIterator].idCapacity].capacity << endl;
				myfile << "Fuel Quantity : " << tanks[command[runIterator].idCapacity].fuel_quantity << endl;
				myfile << "Connected : " << tanks[command[runIterator].idCapacity].isConnected << endl;
				myfile << "Tank ID : " << tanks[command[runIterator].idCapacity].tank_id << endl;
				myfile << "Valve : " << tanks[command[runIterator].idCapacity].valve << endl;
				myfile << "---------------------------------------------------" << endl;
			}
			else
			{
				cout << "Error Opening Output File" << endl;
			}
		}
		++runIterator;
	}
}

void Engine::add_fuel_tank(double capacity)
{
	Tank tank(tank_id, capacity);
	tanks.push_back(tank);
	++tank_id;
}

void Engine::remove_fuel_tank(int tank_id)
{
	for (size_t i = 0; i < tanks.size(); i++)
	{
		if (tanks[i].tank_id == tank_id)
		{
			if (!tanks[i].valve)
			{
				tanks.erase(tanks.begin() + i);
			}
		}
	}
}
void Engine::connect_fuel_tank_to_engine(int tank_id)
{
	for (size_t i = 0; i < tanks.size(); i++)
	{
		if (tanks[i].tank_id == tank_id)
		{
			tanks[i].isConnected = true;
		}
	}
}

void Engine::disconnect_fuel_tank_from_engine(int tank_id)
{
	for (size_t i = 0; i < tanks.size(); i++)
	{
		if (tanks[i].tank_id == tank_id)
		{
			if (!tanks[i].valve)
			{
				tanks[i].isConnected = false;
			}
		}
	}
}

void Engine::fill_tank(int tank_id, double quantity)
{
	for (size_t i = 0; i < tanks.size(); i++)
	{
		if (tanks[i].tank_id == tank_id)
		{
			tanks[i].fill_tank(quantity);
		}
	}
}


void Engine::start_engine()
{
	for (size_t i = 0; i < tanks.size(); i++)
	{
		if (tanks[i].isConnected)
		{
			status = true;
			break;
		}
	}
}

void Engine::stop_engine()
{
	status = false;
}

void Engine::absorb_fuel()
{
	int a = internal_tank.capacity - internal_tank.fuel;
	for (size_t i = 0; i < tanks.size(); i++)
	{
		if (tanks[i].isConnected)
		{
			if (tanks[i].fuel_quantity > 0)
			{
				if (tanks[i].fuel_quantity >= a)
				{
					internal_tank.fuel += a;
					tanks[i].fuel_quantity -= a;
					return;
				}
				else
				{
					internal_tank.fuel += tanks[i].fuel_quantity;
					tanks[i].fuel_quantity -= tanks[i].fuel_quantity;
					return;
				}
			}
		}
	}

}
void Engine::consume_fuel()
{
	if (status)
	{
		if (internal_tank.fuel > fuel_per_second)
		{
			internal_tank.fuel -= fuel_per_second;
			total_consumed_fuel += fuel_per_second;
		}
		else
		{
			total_consumed_fuel += internal_tank.fuel;
			internal_tank.fuel = 0;
		}
	}
}
void Engine::open_valve(int tank_id)
{
	for (size_t i = 0; i < tanks.size(); i++)
	{
		if (tanks[i].tank_id == tank_id)
		{
			tanks[i].valve = true;
		}
	}
}

void Engine::wait(int seconds)
{
	if (internal_tank.fuel - (fuel_per_second * seconds) > 0)
	{
		internal_tank.fuel -= fuel_per_second * seconds;
		total_consumed_fuel += fuel_per_second * seconds;
	}
	else
	{
		total_consumed_fuel += internal_tank.fuel;
		internal_tank.fuel = 0;
	}
}

void Engine::close_valve(int tank_id)
{
	for (size_t i = 0; i < tanks.size(); i++)
	{
		if (tanks[i].tank_id == tank_id)
		{
			tanks[i].valve = false;
		}
	}
}

void Engine::break_fuel_tank(int tank_id)
{
	for (size_t i = 0; i < tanks.size(); i++)
	{
		if (tanks[i].tank_id == tank_id)
		{
			tanks[i].broken = true;
		}
	}
}

void Engine::repair_fuel_tank(int tank_id)
{

	for (size_t i = 0; i < tanks.size(); i++)
	{
		if (tanks[i].tank_id == tank_id)
		{
			tanks[i].broken = false;
		}
	}
}








