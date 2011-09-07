#include <yaml.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum {
	deb,
	slack,
	rpm
} PackageType;

int main(int argc, char *argv[]){
	PackageType ptype;

	if (argc < 3) {
		usage("Not enough arguments");
	}
	if (!strcmp(argv[1],"D")) {
		ptype = deb;
	} else if (argv[1]=="S") {
		ptype = slack;
	} else if (argv[1]=="R") {
		ptype = rpm;
	} else if (argv[1]=="--help") {
		superusage();
	} else {
		usage("Bad package type argument");
	}

	char* dir = argv[argc-1];
	printf(dir);

	yaml_parser_t parser;
	yaml_event_t event;

	//yaml_parser_set_input_file(&parser, 
	return 0;
}

usage(char* specific) {
	fprintf(stderr, "park-meta: %s\nSyntax: park-meta {D | S | R } [-e] dir\n", specific);
	exit(1);
}

superusage(){
	printf("");
	exit(0);
}
