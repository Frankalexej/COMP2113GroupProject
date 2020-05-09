#pragma once
#define BLOCK	"█"
#define CURSOR	"↑"

// use these three if you would like to reduce Chinese characters in map

//#define LAND	"\x1B[37m█\x1B[0m"	// white block
//#define HILL	"\x1B[32m█\x1B[0m"	// green block
//#define SEA		"\x1B[36m█\x1B[0m"	// blue block

// LAND, HILL and SEA: please use these three when page cannot load normally
// this is because on some OS █ is displayed in single width, whereas all our game settings are based on double-width

#define LAND	"\x1B[37m地\x1B[0m"	// white block
#define HILL	"\x1B[32m山\x1B[0m"	// green block
#define SEA		"\x1B[36m海\x1B[0m"	// blue block

#define CAP		"都"	// capital
#define SOL		"兵"	// soldier
#define ENG		"工"	// engineer
#define LAV		"車"	// lav
#define TANK	"炮"	// tank
#define FBRK	"厰"	// factory


#define RST		"\x1B[0m"	// required part for escape sequences
#define KRED	"\x1B[91m"	// bright red, for player A
#define KYEL	"\x1B[93m"	// bright yellow, for player B
#define KGRN	"\x1B[92m"	// bright green, for move-to cursor
#define KBLB	"\x1B[100m"	// bright black background, used to denote available movement region at cursor
// red 红色
#define FRED(x) KRED x RST
// yellow 黄色
#define FYEL(x) KYEL x RST

#define FGRN(x) KGRN x RST

#define FBLB(x) KBLB x RST