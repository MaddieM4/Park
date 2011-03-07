#ifndef PACKAGE
#define PACKAGE

#include "PackageProperties.h"

#include <string>
using std::string

class package {
	string name;
	PackageProperties properties;
	string* dependencies;

	package::package(string packname);
	int package::install();
	int package::uninstall();
	int package::download();
	int package::set_up(string link);
	int package::set_down(string link);
	int package::set_channel(string channel);
	int package::set_schedule(string schedule);
	int package::set_auto(int auto);
	int package::find_dependencies();
}

#endif // PACKAGE
