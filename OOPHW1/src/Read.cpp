#include "Read.h"

//Initialize pointer to zero so that it can be initialized in first call to getInstance
Read* Read::instance = 0;

Read::Read()
{
	cout << "Enter the Input File Name : (Default File Name is input.txt)" << endl;
	cin >> inputFile;
}

Read* Read::getInstance()
{
	//Singleton Pattern
	if (!instance)
	{
		instance = new Read();
	}

	return instance;
}

vector<commands> Read::getData()
{
	return data;
}

void Read::readFile()
{
	commands input;
	fstream myfile;
	string eof;
	myfile.open(inputFile, ios::in);

	if (myfile.is_open())
	{
		while (myfile >> input.command)
		{
			input.command.erase(remove(input.command.begin(), input.command.end(), ';'), input.command.end());
			if (input.command == "start_engine" || input.command == "stop_engine" || input.command == "list_connected_tanks" ||
				input.command == "print_total_fuel_quantity" || input.command == "print_total_consumed_fuel_quantity" ||
				input.command == "stop_simulation" || input.command == "print_fuel_tank_count" || input.command == "list_fuel_tanks")
			{
				input.command.erase(remove(input.command.begin(), input.command.end(), ';'), input.command.end());
				data.push_back(input);
			}
			else if (input.command == "fill_tank")
			{
				input.command.erase(remove(input.command.begin(), input.command.end(), ';'), input.command.end());
				myfile >> input.idCapacity >> input.quantity;
				data.push_back(input);
			}
			else if(input.command == "add_fuel_tank" || input.command == "remove_fuel_tank" || input.command == "connect_fuel_tank_to_engine"
					|| input.command =="disconnect_fuel_tank_from_engine"|| input.command == "print_tank_info"|| input.command == "open_valve"
					|| input.command == "close_valve"|| input.command == "break_fuel_tank" || input.command == "repair_fuel_tank" || input.command == "wait")
			{
				input.command.erase(remove(input.command.begin(), input.command.end(), ';'), input.command.end());
				myfile >> input.idCapacity;
				data.push_back(input);
			}

		}
	}
	else
	{
		cout << "Error Opening Input File" << endl;
	}
	myfile.close();
}

