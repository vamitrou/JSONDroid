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

#include "Record.h"
#include "Utilities.cpp"
#include <iostream>
#include <sys/mman.h>

Record::Record(DiskLoc extLoc, DiskLoc pRec)
{

}

void Record::init(int prev, bson *&b)
{
	prevRecLoc = prev;
	nextRecLoc = -1;

	length = bson_size(b); // + sizeof(bson);

	char *rawData = &data[0];
	memcpy ( rawData, b->data, length);


	if (_DEBUG) LOG_INT("bson size: ", length);
}

bool Record::isNull()
{
	return false;
}
