
all:
	cd src_c; make;
	cd src_s; make;

app:
	cd apps; make;

clean:
	cd src_c; make clean;
	cd src_s; make clean;

clean-app:
	cd apps; make clean;
