

case "$1" in
	all)
	echo "----------------------------release all-----------------------------"
	source ./setenv.sh camconfig;make clean;make;make;make install
	source ./setenv.sh iptv;make clean;make;make;make install
	source ./setenv.sh mcas_demo;make clean;make;make;make install
	source ./setenv.sh tuner_demo;make clean;make;make;make install		
	;;
	*)
	source ./setenv.sh $1;make clean;make;make;make install
	;;
esac






