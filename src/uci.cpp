
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::cin;
using std::cerr;
#include <tuple>
using std::tuple;
#include <functional>
using std::function;
using std::bind;
#include <map>
using std::map;

// Implementation

class Uci
{
// Hookup

private:
	map<string, function<void(string)>> commands {};
public:
	Uci();
	void main();

// Command api

private: 
	static void log(string message) { cerr << "info string " << message << std::endl; };
	static void print(string message) { cout << message << std::endl; };

// Commands

private:
	bool running = true;
public:
	void uci(string);
	void isready(string);
	void quit(string);

};

// Commands

void Uci::uci(string args)
{
	print("id name Hyla");
	print("author Sewbacca");
	print("uciok");
}

void Uci::isready(string)
{
	print("readyok");
}

void Uci::quit(string)
{
	running = false;
}

// Hookup

tuple<string, string> tokenize_commandline(string line)
{
	string command = "";
	string args = "";

	bool firstWord = true;
	for(char c : line)
	{
		if(c == ' ')
			firstWord = false;
		else if(firstWord)
			command += c;
		else
			args += c;
	}

	return { command, args };
}


Uci::Uci()
{
	// Registering commands

	using namespace std::placeholders;
	#define REGISTER(name) commands[#name] = std::bind(&Uci::name, this, _1)
	
	REGISTER(uci);
	REGISTER(quit);
	REGISTER(isready);

	#undef FUNCTION
}

void Uci::main()
{
	while(running)
	{
		string line;
		getline(cin, line);
		auto [ cmd, args ] = tokenize_commandline(line);
		if(commands.find(cmd) == commands.end())
		{
			log("Command '" + cmd + "'not found!");
			continue;
		}

		commands[cmd](args);
	}
}

// API

void uci_main()
{
	// Just load the manager and let it do its magic
	Uci manager;
	manager.main();
}