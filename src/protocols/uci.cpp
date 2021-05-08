
#include <string>
#include <sstream>
#include <iostream>
#include <functional>
#include <map>

#include "uci.h"
#include "chess.h"
#include "textutils.h"

using namespace std;


// Implementation

class Uci
{
// Hookup

private:
	map<string, function<void(stringstream&&)>> commands {};
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
	Position position;
public:
	void uci(stringstream&&);
	void isready(stringstream&&);
	void quit(stringstream&&);
	void ucinewgame(stringstream&&);
	void read_position(stringstream&&);
	void printboard(stringstream&&);
};

// Commands

void Uci::uci(stringstream&&)
{
	print("id name Hyla");
	print("author Sewbacca");
	print("uciok");
}

void Uci::isready(stringstream&&)
{
	print("readyok");
}

void Uci::quit(stringstream&&)
{
	running = false;
}

void Uci::ucinewgame(stringstream&&)
{
	read_position(stringstream("startpos"));
}

void Uci::read_position(stringstream&& args)
{
	string type;

	args >> type;

	if(type == "startpos")
		position = read_fen(STARTPOS);
	else if(type == "fen")
		position = read_fen(args);
	else
		log("Invalid type");
	
	string token;
	args >> token;
	if(token != "moves") return;
	
	while(true)
	{
		Move move = read_move(args, position);
		if(!args) break;
		position.play(move);
	}
}

void Uci::printboard(stringstream&&)
{
	cout << position << endl;
}

// Hookup

Uci::Uci()
{
	// Registering commands

	#define REGISTER_AS(name, uci_name) commands[uci_name] = std::bind(&Uci::name, this, std::placeholders::_1)
	#define REGISTER(name) REGISTER_AS(name, #name)
	
	REGISTER(uci);
	REGISTER(quit);
	REGISTER(isready);
	REGISTER(printboard);
	REGISTER_AS(printboard, "d");
	REGISTER(ucinewgame);
	REGISTER_AS(read_position, "position");

	#undef REGISTER
	#undef REGISTER_AS
}

void Uci::main()
{
	while(running)
	{
		string line;
		getline(cin, line);
		stringstream stream(line);

		string cmd;

		stream >> cmd;

		if(cmd == "")
			continue;
		
		if(commands.find(cmd) == commands.end())
		{
			log("Command '" + cmd + "'not found!");
			continue;
		}

		commands[cmd](std::move(stream));
	}
}

// API

void uci_main()
{
	// Just load the manager and let it do its magic
	Uci manager;
	manager.main();
}