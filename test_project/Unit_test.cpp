#pragma once
#include <gtest/gtest.h>
#include "RenderMock.h"
#include <UnitFactory.h>
#include <Unit.h>

TEST(UnitTest, GettingPosition)
{
	CUnitFactory fact;
	std::shared_ptr<ITacticObject> unit = std::shared_ptr<ITacticObject>(fact.CreateUnit(1, 100, 100));
	POINT example,result;
	example.x = 100;
	example.y = 100;
	result = unit->getPosition();
	EXPECT_EQ(example.x, result.x);
	EXPECT_EQ(example.y, result.y);
}

TEST(UnitTest, Rendering)
{
	CUnitFactory fact;
	std::shared_ptr<ITacticObject> unit = std::shared_ptr<ITacticObject>(fact.CreateUnit(1, 100, 100));
	CRendererMock renderer;
	EXPECT_CALL(renderer, AddToQueue(100, 100, 1));
	unit->Render(&renderer);
}