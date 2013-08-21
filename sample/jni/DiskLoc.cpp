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
#include "Utilities.cpp"

DiskLoc::DiskLoc()
{
	init();
}

DiskLoc::DiskLoc(int num, int ofs)
{
	init(num, ofs);
}

void DiskLoc::init()
{
	fileNum = -1;
	offset = -1;
}

void DiskLoc::init(int num, int ofs)
{
	fileNum = num;
	offset = ofs;
}

void DiskLoc::init(DiskLoc loc)
{
	fileNum = loc.fileNum;
	offset = loc.offset;
}

string DiskLoc::toString(string descr)
{
	char buf[100];
	sprintf(buf, "%s, Location: %d,%d\0", descr.c_str(), fileNum, offset);
	string str = buf;
	return str;
}

int DiskLoc::Compare(const DiskLoc &rhs) const
{
	int a = TCompare(fileNum, rhs.fileNum);
	if (a == 0) a = TCompare(offset, rhs.offset);
	return a;
}

bool DiskLoc::operator == (const DiskLoc &rhs) const
{
	return !Compare(rhs);
}

bool DiskLoc::operator < (const DiskLoc &rhs) const
{
	return Compare(rhs)<0;
}

bool DiskLoc::operator > (const DiskLoc &rhs) const
{
	return Compare(rhs)>0;
}

bool DiskLoc::isNull()
{
	return fileNum == -1 || offset == -1;
}
