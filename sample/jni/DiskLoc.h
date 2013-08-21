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

#include <string.h>
#include <iostream>

using namespace std;

#ifndef DISKLOC_H
#define DISKLOC_H

class DiskLoc
{
public:
	int fileNum;
	int offset;

	DiskLoc();

	DiskLoc(int num, int ofs);

	void init();

	void init(int num, int ofs);

	void init(DiskLoc loc);

	string toString(string descr);

	int Compare(const DiskLoc &rhs) const;

	bool operator == (const DiskLoc &rhs) const;

	bool operator < (const DiskLoc &rhs) const;

	bool operator > (const DiskLoc &rhs) const;

	bool isNull();
};

#endif
