#include "stdafx.h"
#include <map>
#include <fstream>

#include "TacticMap.h"


CTacticMap::CTacticMap()
{
}

BYTE CTacticMap::InitMap(LPCSTR map_file,IResourceManager* manager)
{
	std::ifstream file(map_file);
	char* buffer;
	UINT* int_buffer;
	if (!file.is_open())
	{
		return TMAP_ERROR_FILE;
	}
	file.seekg(0, file.end);
	int length = file.tellg();
	file.seekg(0, file.beg);
	buffer = new char[4];
	ZeroMemory(buffer, sizeof(char) * 4);
	file.read(buffer, 3);
	if (strcmp(buffer,TMAP_FILE_SIGNATURE))
	{
		return TMAP_ERROR_FILE;
	}
	delete[] buffer;
	buffer = new char[5];
	ZeroMemory(buffer, sizeof(char) * 5);
	file.read(buffer, 4);
	int_buffer = (UINT*)buffer;
	size_x = *int_buffer;
	ZeroMemory(buffer, sizeof(char) * 5);
	file.read(buffer, 4);
	int_buffer = (UINT*)buffer;
	size_y = *int_buffer;
	ZeroMemory(buffer, sizeof(char) * 5);
	file.read(buffer, 4);
	int_buffer = (UINT*)buffer;
	buffer = new char[*int_buffer + 1];
	ZeroMemory(buffer, sizeof(char) * (*int_buffer + 1));
	file.read(buffer, *int_buffer);
	delete[] int_buffer;
	char* str_chunk=NULL,*next_token=NULL;
	std::map<char, UINT> tiles;
	std::pair<char, UINT> pair;
	str_chunk = strtok_s(buffer, "|", &buffer);
	do{
		
		pair = CreateTile(str_chunk, manager);
		if (pair.second == NULL)
			return TMAP_ERROR_RESOURCE;
		tiles.insert(pair);
		str_chunk = strtok_s(buffer, "|", &buffer);
	} while (str_chunk!=NULL);
	
	buffer = new char;
	int i = 0, j = 0;
	this->tiles.push_back(std::vector<BYTE>());
	std::map<char, UINT>::iterator it;
	file.read(buffer, 1);
	while (!file.eof())
	{
		
		it = tiles.find(*buffer);
		if (it != tiles.end())
		{
			this->tiles[i].push_back(it->second);
			j++;
		}
		else {
			file.close();
			delete buffer;
 			return TMAP_ERROR_CORRUPTED;
		}
		if (j >= size_y && i<size_y-1)
		{
			this->tiles.push_back(std::vector<BYTE>());
			j = 0;
			i++;
		}
		file.read(buffer, 1);
	}
	file.close();
	if (i != size_x - 1 || j != size_y )
	{
		return TMAP_ERROR_CORRUPTED;
	}
	delete buffer;
	return TMAP_OK;
}

std::pair<char, UINT> CTacticMap::CreateTile(char* serialized_tile,IResourceManager* manager)
{
	char index;
	UINT res_index;
	if (serialized_tile == "")
		return std::pair<char,UINT>(NULL,NULL);
	index = serialized_tile[0];
	res_index=manager->addResource(RES_GDI_BITMAP, (LPCTSTR)(++serialized_tile));
	return std::pair<char, UINT>(index, res_index);
}
CTacticMap::~CTacticMap()
{
	for (auto i = tiles.begin(); i != tiles.end(); i++)
	{
		i->clear();
	}
	tiles.clear();
}

void CTacticMap::Render(IRenderer* renderer)
{
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			renderer->AddToQueue(i*TMAP_TILE_SIZE, j*TMAP_TILE_SIZE, tiles[i][j]);
		}
	}
}