#include "stdafx.h"
#include <map>
#include <fstream>
#include "App.h"
#include "TacticMap.h"


CTacticMap::CTacticMap()
{
}

BYTE CTacticMap::InitMap(LPCSTR map_file)
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
	file.get(buffer, 3);
	if (buffer != TMAP_FILE_SIGNATURE)
	{
		return TMAP_ERROR_FILE;
	}
	delete[] buffer;
	buffer = new char[3];
	ZeroMemory(buffer, sizeof(char) * 3);
	file.get(buffer, 2);
	int_buffer = (UINT*)buffer;
	size_x = *int_buffer;
	ZeroMemory(buffer, sizeof(char) * 3);
	file.get(buffer, 2);
	int_buffer = (UINT*)buffer;
	size_y = *int_buffer;
	ZeroMemory(buffer, sizeof(char) * 3);
	file.get(buffer, 2);
	int_buffer = (UINT*)buffer;
	buffer = new char[*int_buffer + 1];
	ZeroMemory(buffer, sizeof(char) * (*int_buffer + 1));
	file.get(buffer, *int_buffer);
	delete[] int_buffer;
	char* str_chunk;
	std::map<char, UINT> tiles;
	do{
		str_chunk = strtok(buffer, "|");

		tiles.insert(CreateTile(str_chunk));
	} while (str_chunk!=NULL);
	delete[] buffer;
	buffer = new char;
	int i = 0, j = 0;
	const UINT temp = this->size_y;
	this->tiles = new BYTE*[size_x];
	this->tiles[0] = new BYTE[size_y];
		
	while (!file.eof())
	{
		file.get(buffer, 1);
		this->tiles[i][j++] = *buffer;
		if (j >= size_y)
		{
			this->tiles[++i] = new BYTE[size_y];
			j = 0;
		}
	}
	file.close();
	delete buffer;
	return TMAP_OK;
}

std::pair<char, UINT> CTacticMap::CreateTile(std::string serialized_tile)
{
	char index;
	UINT res_index;
	if (serialized_tile == "")
		return std::pair<char,UINT>(NULL,NULL);
	index = serialized_tile[0];
	res_index=CApp::getApp()->main_r_manager.addResource(RES_GDI_BITMAP, (LPCTSTR)serialized_tile.substr(1).c_str());
	return std::pair<char, UINT>(index, res_index);
}
CTacticMap::~CTacticMap()
{
	if (tiles != nullptr)
	{
		for (int i = 0; i < size_x; i++)
			delete[] tiles[i];
		delete[] tiles;
	}
}

void CTacticMap::Render()
{
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			CApp::getApp()->main_renderer.AddToQueue(i*TMAP_TILE_SIZE, j*TMAP_TILE_SIZE, tiles[i][j]);
		}
	}
}