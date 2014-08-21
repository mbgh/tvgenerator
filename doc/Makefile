DESIGN = TVGenerator

all: doc view

doc:
	~/software/doxygen/doxygen-1.8.6/bin/doxygen $(DESIGN).doxyfile

view:
	firefox ./html/index.html

clean:
	rm -rf ./html