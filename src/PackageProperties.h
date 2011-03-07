#ifndef PACKAGE_PROPERTIES
#define PACKAGE_PROPERTIES

#include "PackageSchedule.h"

#include <string>
using std::string

class PackageProperties {
	string repo_up, repo_down, channel, version;
	int auto;
	PackageSchedule schedule;

	PackageProperties::PackageProperties(string packname);
}

#endif // PACKAGE_PROPERTIES
