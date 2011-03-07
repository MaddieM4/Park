#include <stdio.h>
#include <string.h>
#include <string>

using std::string;

void printargs(int argc, char** argv) {
	for(int i=0; i<argc; i++) {
		fprintf(stdout, "Arg #%d = '%s'\n", i, argv[i]);
	}
}

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
	for (int i=0;i<dist;i++) {
		result[i] = argv[i+2];
	}
	// terminate with blank string ("")
	result[dist]="";
	return result;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		fprintf(stderr, "park: not enough arguments\n");
		return 1;
	}

	string command = argv[1];
	string* args = arguments(argc, argv);
	int numargs = 0;
	while (args[numargs] != "") {
		numargs++;
	}
	int autoremove = autoremove_later(argc, argv);

	if (command == "+") {
		if (numargs > 0) {
			// Installation command
			fprintf(stdout, "Install a repo\n\n");
			string cat = "";
			for (int i=0; i<numargs; i++) {
				cat += " "+ args[i];
				i++;
			}
			fprintf(stdout, "Would install:%s\n", cat.c_str());
		} else {
			// List all explicitly installed packages
			// ...in other words, cat ./db/explicit
			FILE* explic = fopen("./db/explicit", "r");
			while (1) {
				char c = getc(explic);
				if (c==EOF) {
					break;
				} else {
					fprintf(stdout, "%c", c);
				}
			}
		}
	} else if (command == "-") {
		if (numargs>0) {
			fprintf(stdout, "Uninstall a package\n");
		} else {
			fprintf(stdout, "Autoremove packages not in the explicit tree\n");
		}
	} else if (command == "x") {
		if (numargs>0) {
			fprintf(stdout, "Update a package\n");
		} else {
			fprintf(stdout, "Update all packages (freakishly slow)\n");
		}
	} else if (command == "/") {
		if (numargs>0) {
			fprintf(stdout, "Get information about a package\n");
		} else {
			fprintf(stdout, "Print the dependency tree\n");
		}
	} else if (command == ".") {
		if (numargs>0) {
			fprintf(stdout, "Do repo-y stuff to a package\n");
		} else {
			fprintf(stdout, "Repo statistics of all packages\n");
		}
	} else {
		fprintf(stderr, "park: bad subcommand (%s)\n", command.c_str());
		return 1;
	}
	//fprintf(stdout, "Autoremove: %d\n", autoremove);
}
