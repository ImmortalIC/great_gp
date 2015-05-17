#include <gtest/gtest.h>
#include <gmock\gmock.h>
#include <TacticMap.h>
#include <fstream>

class CRendererMock : public IRenderer
{
public:

	MOCK_METHOD0(Render, bool());
	MOCK_METHOD3(AddToQueue, void(UINT x, UINT y, ULONG resource));
	MOCK_METHOD3(InitRenderer, bool(HWND handle, UINT window_width, UINT window_height));

};

class CResourceManagerMock : public IResourceManager
{
public:
	MOCK_METHOD2(addResource, UINT(UINT type,const LPCTSTR path));
	virtual IResource_ptr operator[](UINT index) { return nullptr; };
	~CResourceManagerMock(){};
	virtual void CleanOld() {};
};

class TacticMapTest : public testing::Test
{
protected:
	virtual void SetUp()
	{
		//correct map file
		char file2[141] = { 'I', 'm', 'p', (char)0, (char)10, (char)0, (char)10, (char)0, (char)32, 'A', 't', 'i', 'l', 'e', '1', '.', 'b', 'm', 'p', '|', 'B', 't', 'i', 'l', 'e', '2', '.', 'b', 'm', 'p', '|', 'C', 't', 'i', 'l', 'e', '3', '.', 'b', 'm', 'p', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'C', 'C', };
		//wrong signature
		char file1[139] = {'S', 0, 10, 0, 10, 0, 32, 'A', 't', 'i', 'l', 'e', '1', '.', 'b', 'm', 'p', '|', 'B', 't', 'i', 'l', 'e', '2', '.', 'b', 'm', 'p', '|', 'C', 't', 'i', 'l', 'e', '3', '.', 'b', 'm', 'p', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'C', 'C', };
		//non-existing tile-file
		char file3[141] = { 'I', 'm', 'p', 0, 10, 0, 10, 0, 32, 'A', 't', 'i', 'l', 'e', '1', '.', 'b', 'm', 'p', '|', 'B', 't', 'i', 'l', 'e', '2', '.', 'b', 'm', 'p', '|', 'C', 'e', 'm', 'p', 't', 'y', '.', 'b', 'm', 'p', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'C', 'C', };
		//wrong tiles definition
		char file4[141] = { 'I', 'm', 'p', 0, 10, 0, 10, 0, 32, 'A', 't', 'i', 'l', 'e', '1', '.', 'b', 'm', 'p', '|', 'B', 't', 'i', 'l', 'e', '2', '.', 'b', 'm', 'p', '|', 'C', 'e', 'm', 'p', 't', 'y', '.', 'b', 'm', 'p', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'F', 'B', 'A', 'B', 'E', 'B', 'A', 'D', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'C', 'C', };
		std::ofstream file("tm_test1.map");
	
		
		file.write(file1, 140);
		file.close();
		file.open("tm_test2.map", std::ofstream::out);
	
		file.write(file2, 138);
		file.close();
		file.open("tm_test3.map", std::ofstream::out);
		file.write(file3, 139);
		file.close();
		file.open("tm_test4.map", std::ofstream::out);
		file.write(file4, 139);
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
	EXPECT_CALL(mock, addResource(RES_GDI_BITMAP,"empty.bmp")).WillOnce(testing::Return(NULL));
	EXPECT_CALL(mock, addResource(RES_GDI_BITMAP, "tile2.bmp")).WillOnce(testing::Return(2));
	EXPECT_CALL(mock, addResource(RES_GDI_BITMAP, "tile1.bmp")).WillOnce(testing::Return(1));
	EXPECT_EQ(TMAP_ERROR_RESOURCE, map.InitMap("tm_test3.map",&mock));
}

TEST_F(TacticMapTest, CorrectMap)
{
	CTacticMap map;
	CResourceManagerMock mock;
	EXPECT_CALL(mock, addResource(RES_GDI_BITMAP, "tile3.bmp")).WillOnce(testing::Return(3));
	EXPECT_CALL(mock, addResource(RES_GDI_BITMAP, "tile2.bmp")).WillOnce(testing::Return(2));
	EXPECT_CALL(mock, addResource(RES_GDI_BITMAP, "tile1.bmp")).WillOnce(testing::Return(1));
	EXPECT_EQ(TMAP_OK, map.InitMap("tm_test3.map", &mock));
}

TEST_F(TacticMapTest, RenderTest)
{
	CTacticMap map;
	CResourceManagerMock mock;
	CRendererMock render;
	EXPECT_CALL(mock, addResource(RES_GDI_BITMAP, "tile3.bmp")).WillOnce(testing::Return(3));
	EXPECT_CALL(mock, addResource(RES_GDI_BITMAP, "tile2.bmp")).WillOnce(testing::Return(2));
	EXPECT_CALL(mock, addResource(RES_GDI_BITMAP, "tile1.bmp")).WillOnce(testing::Return(1));
	char calls[100] = { 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'C', 'C' };
	for (int i = 99; i > 0; i--)
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
	map.InitMap("tm_test3.map", &mock);
	map.Render(&render);

}
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}