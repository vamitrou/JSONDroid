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
#include "bson/bson.h"

#ifndef RECORD_H
#define RECORD_H

#define RECORD_HEADER_HEIGHT (3*sizeof(int) + sizeof(DiskLoc))

class Record
{
public:
	int length;
	DiskLoc extentLoc;
	int nextRecLoc;
	int prevRecLoc;
	char data[1];

	bool isNull();

	Record(DiskLoc extLoc, DiskLoc pRec);
	void init(int prev, bson *&b);
	int getLength() { return RECORD_HEADER_HEIGHT + length; }
};

#endif
