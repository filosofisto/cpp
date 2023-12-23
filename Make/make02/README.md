# make01

It shows variable into a makefile.

## Run

	make

	make BUILD_DEBUG=no

	export BUILD_DEBUG=no
	make


The export does not works, only if BUILD_DEBUG is not defined inside the makefile.
Add the make hammer -e which makes the environment take precedence

