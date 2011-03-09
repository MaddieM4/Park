#ifndef PACKAGE_SCHEDULE
#define PACKAGE_SCHEDULE

#include <string>
using std::string

class PackageSchedule {
	string text;

	PackageSchedule::PackageSchedule(string text);
	PackageSchedule::next();
	int PackageSchedule::make(string command);
	int PackageSchedule::kill();
	PackageSchedule::operator=(PackageSchedule* newschedule);
}

#endif // PACKAGE_SCHEDULE
