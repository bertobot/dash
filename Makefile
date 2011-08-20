all:
	make -C core
	make -C server
	make -C tests

clean:
	make -C core clean
	make -C server clean
	make -C tests clean

mrproper:
	make -C core mrproper
	make -C server mrproper
	make -C tests mrproper

