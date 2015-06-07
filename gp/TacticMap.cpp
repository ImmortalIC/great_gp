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
	delete[] buffer;
	buffer = new char;
	ZeroMemory(buffer, sizeof(char));
	file.read(buffer, 1);
	BYTE num_tiles = buffer[0];
	delete[] buffer;

	int_buffer = new UINT;
	std::map<char, UINT> tiles;
	std::pair<char, UINT> pair;

	//tiles.insert(std::pair<char, UINT>('F', 4));

	int i = 0, j = 0;
	for( i = 0; i < num_tiles; i++)
	{
		ZeroMemory(int_buffer, sizeof(UINT));
		file.read((char*)int_buffer, sizeof(UINT));
		buffer = new char[*int_buffer+sizeof(wchar_t)];
		ZeroMemory(buffer, sizeof(char)*(*int_buffer + sizeof(wchar_t)));
		
		file.read(buffer, *int_buffer);
		buffer[*int_buffer] = 0;
		pair = CreateTile(buffer, manager);
	
		if (pair.second == NULL)
			return TMAP_ERROR_RESOURCE;
		tiles.insert(pair);
		delete[] buffer;
	}

	buffer = new char;
	i = 0;
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