mkrom() {
	make clean
	make 
	/usr/games/mgba-qt "$1".gba
}
