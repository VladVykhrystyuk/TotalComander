#include "File.h"
#include <iostream>
#include <chrono>
#include <iomanip>

File::File(const fs::path& p) : path(p),
last_time(fs::last_write_time(p)), 
f_size(fs::file_size(p)) {}


File::File(const File& f) {
	if (this != &f) {
		this->path = f.path;
	}
}


void File::enter() {

}

void File::print() {
	using namespace std::chrono;
	std::time_t cftime = system_clock::to_time_t(time_point_cast<system_clock::duration>(last_time - fs::file_time_type::clock::now() + system_clock::now()));
	size_t found = path.string().find_last_of("/\\");
	std::cout << path.string().substr(found + 1) << std::setw(10) <<
		f_size << " b" << std::setw(35) << 
		" time: " << asctime(localtime(&cftime)); //<< std::endl;
}

Component* File::get_parent() {
	return parent_;
}

void File::set_parent(Component* parent) {
	this->parent_ = parent;
}
