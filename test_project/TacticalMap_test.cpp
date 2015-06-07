#pragma once
#include <gtest/gtest.h>
#include <TacticMap.h>
#include <fstream>
#include "RenderMock.h"
#include "ResourceManagerMock.h"



class TacticMapTest : public testing::Test
{
protected:
	virtual void SetUp()
	{
		
		//correct map file
		char file2[169] = { 'I', 'm', 'p', 10, 0, 0, 0, 10, 0, 0, 0, 3, 15, 0, 0, 0, 'A', 't', 'e', 's', 't', '_', 't', 'i', 'l', 'e', '1', '.', 'b', 'm', 'p', 15, 0, 0, 0, 'B', 't', 'e', 's', 't', '_', 't', 'i', 'l', 'e', '2', '.', 'b', 'm', 'p', 15, 0, 0, 0, 'C', 't', 'e', 's', 't', '_', 't', 'i', 'l', 'e', '3', '.', 'b', 'm', 'p', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', };
		//wrong signature
		char file1[152] = { 'S', 10, 0, 0, 0, 10, 0, 0, 0, 3, 10, 0, 0, 0,  'A','t', 'i', 'l', 'e', '1', '.', 'b', 'm', 'p', 10,0,0,0,'B',  't', 'i', 'l', 'e', '2', '.', 'b', 'm', 'p', 10,0,0,0, 'C', 't', 'i', 'l', 'e', '3', '.', 'b', 'm', 'p', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'C', 'C', };
		//non-existing tile-file
		char file3[154] = { 'I', 'm', 'p', 10, 0, 0, 0, 10, 0, 0, 0, 3,10, 0, 0, 0, 'A', 't', 'i', 'l', 'e', '1', '.', 'b', 'm', 'p', 10,0,0,0, 'B', 't', 'i', 'l', 'e', '2', '.', 'b', 'm', 'p',10,0,0,0 , 'C', 'e', 'm', 'p', 't', 'y', '.', 'b', 'm', 'p', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'C', 'C', };
		//wrong tiles definition
		char file4[154] = { 'I', 'm', 'p', 10, 0, 0, 0, 10, 0, 0, 0, 3,10, 0, 0, 0, 'A', 't', 'i', 'l', 'e', '1', '.', 'b', 'm', 'p', 10,0,0,0, 'B', 't', 'i', 'l', 'e', '2', '.', 'b', 'm', 'p', 10,0,0,0, 'C', 't', 'i', 'l', 'e', '3', '.', 'b', 'm', 'p', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'F', 'B', 'A', 'B', 'E', 'B', 'A', 'D', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'C', 'C', };
		std::ofstream file("tm_test1.map");
	
		
		file.write(file1, 154);
		file.close();
		file.open("tm_test2.map", std::ofstream::out);
	
		file.write(file2, 169);
		file.close();
		file.open("tm_test3.map", std::ofstream::out);
		file.write(file3, 154);
		file.close();
		file.open("tm_test4.map", std::ofstream::out);
		file.write(file4, 154);
		file.close();
	}

	virtual void TearDown()
	{
		remove("tm_test1.map");
		remove("tm_test2.map");
		remove("tm_test3.map");
		remove("tm_test4.map");
	}
};

TEST_F(TacticMapTest, NonExistingFile)
{
	CTacticMap map;
	CResourceManagerMock mock;
	EXPECT_EQ(TMAP_ERROR_FILE, map.InitMap("no_such_file.map", &mock));
}

TEST_F(TacticMapTest, CorruptedFile)
{
	CTacticMap map;
	CResourceManagerMock mock;

	EXPECT_CALL(mock, addResource(RES_GDI_BITMAP, testing::StrCaseEq("tile3.bmp"))).WillOnce(testing::Return(3));
	EXPECT_CALL(mock, addResource(RES_GDI_BITMAP, testing::StrCaseEq("tile2.bmp"))).WillOnce(testing::Return(2));
	EXPECT_CALL(mock, addResource(RES_GDI_BITMAP, testing::StrCaseEq("tile1.bmp"))).WillOnce(testing::Return(1));
	EXPECT_EQ(TMAP_ERROR_CORRUPTED, map.InitMap("tm_test4.map", &mock));
}

TEST_F(TacticMapTest, WrongSignature)
{
	CTacticMap map;
	CResourceManagerMock mock;
	EXPECT_EQ(TMAP_ERROR_FILE, map.InitMap("tm_test1.map",&mock));
}

TEST_F(TacticMapTest, NonExistingTiles)
{
	CTacticMap map;
	CResourceManagerMock mock;
	EXPECT_CALL(mock, addResource(testing::_, testing::_)).WillOnce(testing::Return(NULL));
	EXPECT_CALL(mock, addResource(RES_GDI_BITMAP, testing::StrCaseEq("tile2.bmp"))).WillOnce(testing::Return(2));
	EXPECT_CALL(mock, addResource(RES_GDI_BITMAP, testing::StrCaseEq("tile1.bmp"))).WillOnce(testing::Return(1));
	EXPECT_EQ(TMAP_ERROR_RESOURCE, map.InitMap("tm_test3.map",&mock));
}

TEST_F(TacticMapTest, CorrectMap)
{
	CTacticMap map;
	CResourceManagerMock mock;
	
	EXPECT_CALL(mock, addResource(RES_GDI_BITMAP, testing::StrCaseEq("test_tile3.bmp"))).WillOnce(testing::Return(3));
	EXPECT_CALL(mock, addResource(RES_GDI_BITMAP, testing::StrCaseEq("test_tile2.bmp"))).WillOnce(testing::Return(2));
	EXPECT_CALL(mock, addResource(RES_GDI_BITMAP, testing::StrCaseEq("test_tile1.bmp"))).WillOnce(testing::Return(1));
	EXPECT_EQ(TMAP_OK, map.InitMap("tm_test2.map", &mock));
}

TEST_F(TacticMapTest, RenderTest)
{
	CTacticMap map;
	CResourceManagerMock mock;
	CRendererMock render;
	
	EXPECT_CALL(mock, addResource(RES_GDI_BITMAP, testing::StrCaseEq("test_tile3.bmp"))).WillOnce(testing::Return(3));
	EXPECT_CALL(mock, addResource(RES_GDI_BITMAP, testing::StrCaseEq("test_tile2.bmp"))).WillOnce(testing::Return(2));
	EXPECT_CALL(mock, addResource(RES_GDI_BITMAP, testing::StrCaseEq("test_tile1.bmp"))).WillOnce(testing::Return(1));
	char calls[100] = { 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 'A' };
	
	for (int i = 99; i >= 0; i--)
	{
		switch (calls[i])
		{
		case 'A':
			EXPECT_CALL(render, AddToQueue(floor(i / 10)*TMAP_TILE_SIZE, (i % 10)*TMAP_TILE_SIZE, 1)).Times(1);
			break;
		case 'B':
			EXPECT_CALL(render, AddToQueue(floor(i / 10)*TMAP_TILE_SIZE, (i % 10)*TMAP_TILE_SIZE, 2)).Times(1);
			break;
		case 'C':
			EXPECT_CALL(render, AddToQueue(floor(i / 10)*TMAP_TILE_SIZE, (i % 10)*TMAP_TILE_SIZE, 3)).Times(1);
			break;
			
		}
	}
	ASSERT_EQ(TMAP_OK,map.InitMap("tm_test2.map", &mock));
	map.Render(&render);

}
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}