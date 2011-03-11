DIRECTORY="/var/lib/park"

all: src/park.cpp
	g++ src/park.cpp -o park

install: all
	cp ./park /usr/local/sbin
	-test -d $(DIRECTORY) || mkdir $(DIRECTORY)
	-test -d $(DIRECTORY)/overrides || mkdir $(DIRECTORY)/overrides $(DIRECTORY)/overrides/prop/ $(DIRECTORY)/overrides/dep
	cp -r db $(DIRECTORY)

uninstall:
	rm /sbin/park
	rm -r $(DIRECTORY)

clean:
	rm -rf *o park
