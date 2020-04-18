#ifndef DIRECTORY_H
#define DIRECTORY_H
#include "Component.h"
#include "File.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class Directory : public Component
{
public:

	explicit Directory(const fs::path& p);
	Directory(const Directory& d);
	void set_parent(Component*);	
	virtual Component* get_parent();
	void print() override;
	void print_content();
	void print_color(int);
	void enter() override;
	Directory* get_element(unsigned int);
	File* get_element_file(unsigned int);
	std::string get_path() { return path.string(); }
	int get_elements_count();
	void erase_vector();

private:
	fs::path path;
	fs::file_time_type last_time;
	Component* parent_;
	std::vector <Component*> elements;
};

#endif // !DIRECTORY_H