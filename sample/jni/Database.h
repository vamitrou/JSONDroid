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

#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <vector>

#include "DiskLoc.h"

class Namespace;
class Record;
class Extent;

using namespace std;

#define NS_FILESIZE (MAX_DB_COLLECTIONS * sizeof(Namespace))

typedef map<string, int> ns_map; // collection name -> mmapped array index
typedef map<int, char*> data_map; // data file index -> mapped data

class Database
{
private:

	int fd; // .ns file handle
	vector<int> dataFileHandlers; // data file handlers

	int newCollectionPos;
	DiskLoc lastExtentPointer;

	string db_folder;
	string name;
	ns_map collectionIndexes;

	Namespace* nsFile; 		// Namespace file data
	data_map data;			// data file mmapped contents

public:
	int main();
	Database() { }

	Database(string folder, string dbName);

	void closeDB();

	void deleteDB(string folder, string dbName);

	void unmapFiles();

	void msyncFiles();

	DiskLoc increaseLastExtentLocation(DiskLoc extent, bool forceOpenFile);

	void openNamespaceFile();

	void getDataFile(int index);

	void openFile(string flname, int& handle);

	void createFile(string flname, unsigned size, int& handle);

	void loadDataFiles(int untilIndex);

	Extent* getExtent(DiskLoc diskLoc);

	Record* getRecord(DiskLoc diskLoc);

	Namespace* getCollection(string collection);

	Extent* attachExtent(Namespace *ns);

};

#endif
