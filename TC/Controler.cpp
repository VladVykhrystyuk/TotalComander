#include "Controler.h"
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <string>
#include <list>
#include <cstddef>

Controler::Controler(const std::string& path):index(0) {
	this->dir = new Directory(path);
	this->current = this->dir;
	this->dir->enter();
	this->dir->print_content();
}

void Controler::enter_dir(int i) {
	system("cls");
	current = dir->get_element(i);
	current->set_parent(dir);
	dir = dir->get_element(i);
	current->enter();
	index = 0;
	dir->print_color(index);
}

void Controler::back_dir() {
	system("cls");
	dir->erase_vector();
	dir = static_cast<Directory*>(dir->get_parent());
	current = dir;
	index = 0;
	dir->print_content();
}

void Controler::run() {
	for (;;) {
		if (_kbhit()) {
			int k = _getch();
			if (k == 224) {
				switch (_getch())
				{
				case 72: {
					up();
					dir->print_color(index);
					break;
				}
				case 80: {
					down();
					dir->print_color(index);
					break;
				}
				default:
					break;
				}
			}
			else { ////// enter bakcspace
				switch (k)
				{
				case 13: {
					if (fs::is_directory(dir->get_element_file(index)->get_path())) {
						enter_dir(index);
					}
					else {
						showFile();
					}
					break;
				}
				case 8: {
					back_dir();
					break;
				}
				default:
					break;
				}
			}
		}
	}
}

void Controler::up() {
	if (index > 0) {
		index--;
	}
}
void Controler::down() {
	if (index < dir->get_elements_count() - 1) {
		index++;
	}
}

void Controler::showFile() {
	std::string txt = dir->get_element_file(index)->get_path();
	std::ifstream fin;
	fin.open(txt, std::fstream::in);
	bool is_open_read = fin.is_open();
	std::list<std::string> text;
	std::string temp;
	if (!is_open_read) {
		std::cout << "Eror: file is not open!" << std::endl;
	}
	else {
		std::cout << "File is open" << std::endl;
		while (!fin.eof()) {
			getline(fin, temp);
			if (temp.empty()) {
				break;
			}
			text.push_back(temp);
		}
		for (auto i = text.begin(); i != text.end(); i++) {
			std::cout << *i << std::endl;
		}
		text.clear();
	}
}

std::list<std::string>& Controler::get_text() {
	return text;
}
