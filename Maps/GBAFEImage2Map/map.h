
//{{BLOCK(map)

//======================================================================
//
//	map, 240x160@4, 
//	Transparent color : FF,00,00
//	+ palette 16 entries, not compressed
//	+ 601 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 30x20 
//	Total size: 32 + 19232 + 1200 = 20464
//
//	Time-stamp: 2018-02-25, 01:02:29
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MAP_H
#define GRIT_MAP_H

#define mapTilesLen 19232
extern const unsigned int mapTiles[4808];

#define mapMapLen 1200
extern const unsigned short mapMap[600];

#define mapPalLen 32
extern const unsigned short mapPal[16];

#endif // GRIT_MAP_H

//}}BLOCK(map)
