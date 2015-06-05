#pragma once
#include <vector>
#include "base_interfaces.h"
#include "stdafx.h"

#define TMAP_OK 0
#define TMAP_ERROR_FILE 1
#define TMAP_ERROR_RESOURCE 2
#define TMAP_ERROR_CORRUPTED 3
#define TMAP_FILE_SIGNATURE "Imp"
#define TMAP_TILE_SIZE 100

class CTacticMap
{
public:
	CTacticMap();
	~CTacticMap();
	void Render(IRenderer* renderer);
	BYTE InitMap(LPCSTR map_file,IResourceManager* manager);
private:
	std::vector<std::vector<BYTE>> tiles;
	UINT size_x, size_y;
	std::pair<char,UINT> CreateTile(char* serialized_tile,IResourceManager* manager);

};

