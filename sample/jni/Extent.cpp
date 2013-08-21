/*
JSONDroid - A document-store database developed for smartphones
Copyright (C) 2013 Vasileios Mitrousis

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#include "Extent.h"
#include "Record.h"

#include "Utilities.cpp"

Extent::Extent()
{
	prevExtent = DiskLoc(-1,-1);
	nextExtent = DiskLoc(-1,-1);
	firstRecord = -1;
	lastRecord = -1;
}

Extent::Extent(DiskLoc current)
{
	init(current);
}

Extent::Extent(DiskLoc previous, DiskLoc current)
{
	init(previous, current);
}

void Extent::init(DiskLoc current)
{
	isValid = true;
	prevExtent = DiskLoc(-1,-1);
	nextExtent = DiskLoc(-1,-1);

	firstRecord = -1;
	lastRecord = -1;
}

void Extent::init(DiskLoc previous, DiskLoc current)
{
	isValid = true;
	prevExtent = previous;
	nextExtent = DiskLoc(-1,-1);

	firstRecord = -1;
	lastRecord = -1;
}

bool Extent::isNull()
{
	return !isValid;
}

Record* Extent::getFirstRecord()
{
	LOG_INT("first record:", firstRecord);
	if (firstRecord == -1)
	{
		return NULL;
	}

	return (Record*)&data[firstRecord];
}

Record* Extent::getLastRecord()
{
	if (lastRecord == -1)
	{
		if (_DEBUG) LOGI("lastRecord == -1");
		return NULL;
	}

	return (Record*)&data[lastRecord];
}

Record* Extent::getRecord(int offset)
{
	if (offset == -1)
	{
		return NULL;
	}
//FORCE_LOG_INT("getRecord, offset: ", offset);

	return (Record*)&data[offset];
}

int Extent::addRecord(bson *b)
{
	int lastLoc = lastRecord;
	Record *lastRecordObj = getLastRecord();
	if (lastRecordObj == NULL)
	{
		// no records in extent

		firstRecord = 0;
		lastRecord = 0;
	}
	else
	{
		int bsonSize = 0;
		bson_little_endian32(&bsonSize, b->data);

		int newLoc = lastRecord + lastRecordObj->getLength();
		if (newLoc + sizeof(Record) + bsonSize > EXTENT_SIZE-EXTENT_HEADER_SIZE-1)
		{
			// needs new extent
			return -1;
		}

		lastRecordObj->nextRecLoc = newLoc;

		lastRecord = newLoc;
	}

	lastRecordObj = getLastRecord();
	lastRecordObj->init(lastLoc, b);

	return 0;
}

