#ifndef CONTROLER_H
#define CONTROLER_H
#include "Component.h"
#include "File.h"
#include "Directory.h"

class Controler
{
public:
	explicit Controler(const std::string&);
	void enter_dir(int);
	void back_dir();
	void run();
	std::list<std::string>& get_text();
private:
	Component* current;
	Directory* dir;
	File* file;
	unsigned int index;
	void up();
	void down();
	void showFile();
	std::list<std::string> text;
};

#endif 
