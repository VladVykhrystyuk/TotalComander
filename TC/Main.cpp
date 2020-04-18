#include "Directory.h"
#include "Controler.h"
#include <string>
int main() {
	
	std::string p("C:/");
	Controler* c = new Controler(p);

	c->run();
	delete c;
	
	return 0;
}