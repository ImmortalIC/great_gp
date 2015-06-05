#pragma once
#include <gtest/gtest.h>
#include <TacticBoard.h>
#include "RenderMock.h"
#include "ResourceManagerMock.h"


using testing::StrCaseEq;
using testing::Return;
TEST(TacticBoardTest, TestEnviroment1Iteration)
{
	CRendererMock render;
	CResourceManagerMock manager;
	CTacticBoard board = CTacticBoard(&render, &manager);
	{
		testing::InSequence dummy;
		EXPECT_CALL(manager, addResource(RES_GDI_BITMAP, StrCaseEq("test_tile1.bmp"))).WillOnce(Return(1));
		EXPECT_CALL(manager, addResource(RES_GDI_BITMAP, StrCaseEq("test_tile2.bmp"))).WillOnce(Return(2));
		EXPECT_CALL(manager, addResource(RES_GDI_BITMAP, StrCaseEq("test_tile3.bmp"))).WillOnce(Return(3));
		EXPECT_CALL(manager, addResource(RES_GDI_BITMAP, StrCaseEq("test_unit1.bmp"))).WillOnce(Return(4));
		EXPECT_CALL(manager, addResource(RES_GDI_BITMAP, StrCaseEq("test_unit2.bmp"))).WillOnce(Return(5));
	}
	ASSERT_EQ(true, board.InitTestEnv());
	for (int i = 0; i < 100; i++)
	{
		EXPECT_CALL(render, AddToQueue(floor(i / 10)*TMAP_TILE_SIZE, (i % 10)*TMAP_TILE_SIZE, i % 3 + 1));
	}
	EXPECT_CALL(render, AddToQueue(100, 100, 4));
	EXPECT_CALL(render, AddToQueue(600, 200, 5));
	EXPECT_CALL(render, AddToQueue(600, 800, 4));
	board.CalcIteration();
}