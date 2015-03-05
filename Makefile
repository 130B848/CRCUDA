
all:
	cd src_c; make;
	cd src_d; make;

app:
	cd apps; make;

clean:
	cd src_c; make clean;
	cd src_d; make clean;

clean-app:
	cd apps; make clean;
