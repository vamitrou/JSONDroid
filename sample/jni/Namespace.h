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

#ifndef NAMESPACE_H
#define NAMESPACE_H

#include <stdio.h>
#include <algorithm>
#include <iostream>

#include "Extent.h"

#include "json/jsmn.h"

class Record;
class Database;

#include "bson/bson.h"

using namespace std;

#define NAME_SIZE 40

class Namespace
{
	friend class Database;

private:
	DiskLoc firstExtentLoc;
	DiskLoc lastExtentLoc;

	DiskLoc extentCursor;
	int recordCursor;

private:
	bson** json_to_bson(const char* json, int &count);
	char* bson_to_json(char *val, const char *data , int depth, bool isObject, int bsonSize, int &jsonSize, int &cursor);
	void parseJSON(bson* &p, const char* json, jsmntok_t *tokens, int &tokenCursor, bool createNew, int elementCount);

	Record* getNextRecord();

protected:
	Database* db;

public:
	char name[NAME_SIZE];
	int recordCount;

	Namespace(Database* database, string collectionName, DiskLoc extentLoc);
	Namespace(Database* database, string collectionName);

	void init(Database* database, string collectionName);

	Extent* getFirstExtent();

	Extent* getLastExtent();

	Record* getFirstRecord();

	Record* getLastRecord();

	Record* getNextRecord(Record *cursor);

	void insert(const char* str);

	void printData();

	char* getNextRecordData(int &recordSize);

	char* getNextBatch(int &count);

	char* serializeJSON(char** records, int recordsSize, int recordsCount, int sizes[]);

	string getData();

	void resetCursors();

	void deleteCollection();

	Record* getRecord(const char* key, const char* value);

};

#endif
