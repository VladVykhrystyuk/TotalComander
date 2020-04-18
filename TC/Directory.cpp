#include "Directory.h"
#include "File.h"
#include <cstddef>
#include <windows.h>
#include <iomanip>

Directory::Directory(const fs::path& p) : path(p), last_time(fs::last_write_time(p)) {}
Directory::Directory(const Directory& d) {
	if (this != &d) {
		this->path = d.path;
		this->last_time = d.last_time;
		this->elements = d.elements;
		this->parent_ = d.parent_;
	}
}

void Directory::print() {
	using namespace std::chrono;
	size_t found = get_path().find_last_of("/\\");
	std::time_t cftime = system_clock::to_time_t(time_point_cast<system_clock::duration>(last_time - 
		fs::file_time_type::clock::now() + system_clock::now()));
	std::cout << get_path().substr(found + 1) << std::setw(50) << " time: " << asctime(localtime(&cftime)); //<< std::endl;
	/*for (auto it = elements.begin(); it != elements.end(); it++) {
		(*it)->print();
	}*/
}

void Directory::print_content() {
	for (auto it = elements.begin(); it != elements.end(); it++) {
		(*it)->print();
	}
}


void Directory::erase_vector() {
	elements.clear();
}

void Directory::enter() {
	for (const auto& entry : fs::directory_iterator(path)) {
		if (entry.is_directory()) {
			Component* dir = new Directory(entry.path());
			elements.push_back(dir);
		}
		else {
			Component* file = new File(entry.path());
			elements.push_back(file);
		}
	}
}

Component* Directory::get_parent() {
	return parent_;
}

void Directory::set_parent(Component* parent) {
	this->parent_ = parent;
}

Directory* Directory::get_element(unsigned int i) {
	return static_cast<Directory*>(elements.at(i));
}

File* Directory::get_element_file(unsigned int i) {
	return static_cast<File*>(elements.at(i));
}

int Directory::get_elements_count() {
	return elements.size();
}

void Directory::print_color(int c) {
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (auto i = 0; i < elements.size(); i++) {
		if (i == c) {
			SetConsoleTextAttribute(hConsole, 12);
		}
		elements.at(i)->print();
		SetConsoleTextAttribute(hConsole, 15);
	}
}