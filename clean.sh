

case "$1" in
	all)
	echo "----------------------------release all-----------------------------"
	source ./setenv.sh mcas_demo;make clean
	source ./setenv.sh camconfig;make clean
	source ./setenv.sh tuner_demo;make clean
	source ./setenv.sh iptv;make clean
	;;
	*)
	source ./setenv.sh $1;make clean
	;;
esac






