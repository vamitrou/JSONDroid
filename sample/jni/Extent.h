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

#include "DiskLoc.h"
#include "Constants.h"
#include "Record.h"
#include "bson/bson.h"

#define EXTENT_HEADER_SIZE (2*sizeof(DiskLoc) + 2*sizeof(int) + sizeof(bool))
#define EXTENT_DATA_SIZE (EXTENT_SIZE - EXTENT_HEADER_SIZE)

#ifndef EXTENT_H
#define EXTENT_H

class Extent
{
	friend class Database;

protected:
	bool isValid;

public:
	//int length;
	DiskLoc nextExtent;
	DiskLoc prevExtent;
	int firstRecord;
	int lastRecord;
	char data[EXTENT_DATA_SIZE];

	Extent();
	Extent(DiskLoc current);
	Extent(DiskLoc previous, DiskLoc current);

	bool isNull();

	void init(DiskLoc current);
	void init(DiskLoc previous, DiskLoc current);

	Record* getFirstRecord();
	Record* getLastRecord();

	Record* getRecord(int offset);

	int addRecord(bson *b);
};

#endif
