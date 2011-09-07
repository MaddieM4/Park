#include <yaml.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum {
	deb,
	slack,
	rpm
} PackageType;

typedef struct {
	char *name;
} config;

// define some functions
config* defaultyaml();
mergeyaml(config*, config*);

int main(int argc, char *argv[]){
	PackageType ptype;

	if (argc < 3) {
		if (argc == 2) {
			if (!strcmp(argv[1],"--help")) superusage();
		}
		usage("Not enough arguments");
	}
	if (!strcmp(argv[1],"D")) {
		ptype = deb;
	} else if (!strcmp(argv[1],"S")) {
		ptype = slack;
	} else if (!strcmp(argv[1],"R")) {
		ptype = rpm;
	} else {
		usage("Bad package type argument");
	}

	char* dir = argv[argc-1];
	printf(dir);

	//char* pfname, sfname;

	config *primary, *secondary;
	primary = defaultyaml();
	secondary = defaultyaml();

	mergeyaml(primary, secondary);

	return 0;
}

config *defaultyaml() {
	config* dyaml = malloc(sizeof(config));
	dyaml->name = "hellodolly";
	return dyaml;
}

mergeyaml(config* primary, config* secondary) {
	if (secondary->name != NULL) primary->name = secondary->name;
}

printyaml(config* tbp) {
	yaml_emitter_t emitter;
	yaml_event_t event;

	//yaml_emitter_initialize(&emitter);

	//yaml_emitter_set_output_file(&emitter, stdout);

	int write_handler() {
		return 0;
	}
	//yaml_set_output(&emitter, write_handler
}

//config *readyaml(char* filename) {
//	FILE *fp;
//	fp = fopen(filename, "rb");
//	if (fp == null) {
//		return defaultyaml();
//	}
//}

usage(char* specific) {
	fprintf(stderr, "park-meta: %s\nSyntax: park-meta {D | S | R } [-e] dir\n", specific);
	exit(1);
}

superusage(){
	printf("\
park-meta TYPE [-e] DIR\n\
\n\
Generates the metadata for park-build to make a package of type TYPE\n\
If the -e flag is present, export results to environment variables\n\
If not, print merged YAML to stdout\n\
DIR is the root dir of the package, of which there must be a .park-meta\n\
folder, or else this program will have to make assumptions\n\
\n\
Type-specific config properties override package defaults.\n");
	exit(0);
}
