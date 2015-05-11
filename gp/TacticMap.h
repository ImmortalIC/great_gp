#pragma once
#define TMAP_OK 0
#define TMAP_ERROR_FILE 1
#define TMAP_ERROR_RESOURCE 2
#define TMAP_FILE_SIGNATURE "Imp"
#define TMAP_TILE_SIZE 100

class CTacticMap
{
public:
	CTacticMap();
	~CTacticMap();
	void Render();
	BYTE InitMap(LPCSTR map_file);
private:
	BYTE** tiles;
	UINT size_x, size_y;
	std::pair<char,UINT> CreateTile(std::string serialized_tile);

};

