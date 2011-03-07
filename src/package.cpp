#include "package.h"

package::package(string packname) {
	this.name = packname;
	this.properties = PackageProperties(packname);
	this.find_dependencies()
}

int package::find_dependencies() {
	
}
