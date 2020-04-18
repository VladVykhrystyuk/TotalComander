#ifndef FILE_H
#define FILE_H

#include "Component.h"
#include <string>
#include <filesystem>
namespace fs = std::filesystem;
class File : public Component
{
public:

	  explicit File(const fs::path& p);
	  File(const File& d);
	  void set_parent(Component*);
	  virtual Component* get_parent();
	  void print();
	  void enter();
	  std::string get_path() { return path.string(); }

private:
	fs::path path;
	fs::file_time_type last_time;
	uintmax_t f_size;;
	Component* parent_;

};
#endif
