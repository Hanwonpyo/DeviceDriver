#pragma once
#include <iostream>
#include <exception>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../Project22/DeviceDriver.cpp"

using namespace testing;

class MockFlash : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long), (override));
	MOCK_METHOD(void, write, (long, unsigned char), (override));
};

class DeviceDriverTestFixture : public Test
{
public:
	void SetUp() override
	{
		lba = 0x10000;
		WRITTEN_DATA = 0xAA;
		ERASED_DATA = 0XFF;
	}

	MockFlash fd;
	DeviceDriver dd{ &fd }; // SUT
	int lba;
	int WRITTEN_DATA;
	int ERASED_DATA;
};

TEST_F(DeviceDriverTestFixture, Read5Times)
{
	EXPECT_CALL(fd, read(lba)).Times(5);
	dd.read(lba);
}
TEST_F(DeviceDriverTestFixture, WriteAtErasedArea)
{
	EXPECT_CALL(fd, read(lba)).WillOnce(Return(ERASED_DATA));
	EXPECT_CALL(fd, write(lba, WRITTEN_DATA)).Times(1);
	dd.write(lba, WRITTEN_DATA);
}
TEST_F(DeviceDriverTestFixture, WriteAtWrittenArea)
{
	EXPECT_CALL(fd, read(lba)).WillOnce(Return(WRITTEN_DATA));
	EXPECT_THROW({
		dd.write(lba,WRITTEN_DATA);
		}, std::exception);
}
TEST_F(DeviceDriverTestFixture, WhenDiffrentDataFromRead)
{
	EXPECT_CALL(fd, read(lba)).WillOnce(Return(0xAB)).WillRepeatedly(Return(0xAA));
	EXPECT_THROW({
		dd.read(lba);
		}, std::exception);
}