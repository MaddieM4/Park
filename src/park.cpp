#include <stdio.h>
#include <string.h>
#include <string>

using std::string;

int autoremove_later(int argc, char** argv) {
	string last = argv[argc-1];
	if (last == "-" && argc>2) {
		return 1;
	} else {
		return 0;
	}
}

string* arguments(int argc, char** argv) {
	// get all real arguments
	int dist = argc-2;
	if (autoremove_later(argc, argv)) {
		dist = argc-3;
	}
	string* result;
	result = new string[dist+1];
	int j = 2;
	for (int i=0;i<dist;i++) {
		result[i] = argv[j];
		j++;
		if (j < argc-1) {
			string next = argv[j];
			if (next == "--as" or next == "--to") {
				result[i] += " ";
				result[i] += argv[j];
				result[i] += " ";
				result[i] += argv[j+1];
				j += 2;
				dist-=2;
			}
		}
	}
	// terminate with blank string ("")
	result[dist]="";
	return result;
}

int auto_r() {
	// create list of all explicit + dependency packages
	// create list of all installed packages
	// remove "keepers" from master list
	// remove all packages left on the list
	return 1;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		fprintf(stderr, "park: not enough arguments\n");
		return 1;
	}

	string command = argv[1];
	string* args = arguments(argc, argv);
	int numargs = 0;
	string would = "";
	while (args[numargs] != "") {
		would += "\n\t"+ args[numargs];
		numargs++;
	}
	int autoremove = autoremove_later(argc, argv);

	if (command == "+") {
		if (numargs > 0) {
			// Installation command
			printf("Install a repo\n\n");
			printf("Would install:%s\n", would.c_str());
		} else {
			// List all explicitly installed packages
			// ...in other words, cat ./db/explicit
			FILE* explic = fopen("/var/lib/park/db/explicit", "r");
			if (explic!=NULL) {
				char *c;
				while (fscanf(explic,"%s",c) == 1) {
					printf("%s %d\n",c, strlen(c));
				}
			}
		}
	} else if (command == "-") {
		if (numargs>0) {
			printf("Uninstall a package\n\n");
			printf("Would uninstall:%s\n", would.c_str());
		} else {
			printf("Autoremove packages not in the explicit tree\n");
		}
	} else if (command == "x") {
		if (numargs>0) {
			printf("Update a package\n\n");
			printf("Would update:%s\n", would.c_str());
		} else {
			printf("Update all packages (freakishly slow)\n");
		}
	} else if (command == "/") {
		if (numargs>0) {
			printf("Get information about a package\n\n");
			printf("Would list for:%s\n", would.c_str());
		} else {
			printf("Print the dependency tree\n");
		}
	} else if (command == ".") {
		if (numargs>0) {
			printf("Do repo-y stuff to a package\n\n");
			printf("Would give access to:%s\n", would.c_str());
		} else {
			printf("Repo statistics of all packages\n");
		}
	} else {
		fprintf(stderr, "park: bad subcommand (%s)\n", command.c_str());
	}
	if (autoremove) {
		printf("\n--\n");
		if (auto_r()) {
			printf("Autoremove complete!\n");
		} else {
			fprintf(stderr, "park: failed to complete autoremove\n");
		}
	}
	//printf("Autoremove: %d\n", autoremove);
}
