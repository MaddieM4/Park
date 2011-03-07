#include <stdio.h>
#include <string.h>
#include <string>

using std::string;

void printargs(int argc, char** argv) {
	for(int i=0; i<argc; i++) {
		fprintf(stdout, "Arg #%d = '%s'\n", i, argv[i]);
	}
}

int main(int argc, char** argv) {
	// Do stuff
	//printargs(argc, argv);
	// test loading
	if (argc < 2) {
		fprintf(stderr, "park: not enough arguments\n");
		return 1;
	}

	std::string command = argv[1];

	//fprintf(stdout, "Subcommand length:%d\n", command.length());
	//fprintf(stdout, "True = %d\n", (command=="+") );
	if (command == "+") {
		if (argc > 2) {
			// Installation command
			fprintf(stdout, "Install a repo");
		} else {
			// List all explicitly installed packages
			// ...in other words, cat ./db/explicit
			FILE* explic = fopen("./db/explicit", "r");
			while (1) {
				char c = getc(explic);
				if (c==EOF) {
					return 0;
				} else {
					fprintf(stdout, "%c", c);
				}
			}
		}
	} else if (command == "-") {
		fprintf(stdout, "Uninstall a repo");
	} else if (command == "x") {
		fprintf(stdout, "Update a repo");
	} else if (command == "/") {
		fprintf(stdout, "Get information about a repo");
	} else if (command == ".") {
		fprintf(stdout, "Set the channel of a repo");
	} else {
		fprintf(stderr, "park: bad subcommand (%s)\n", command.c_str());
		return 1;
	}
	fprintf(stdout, "\n");
}
