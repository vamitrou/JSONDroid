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

#include "Database.h"

#include <string.h>
#include <map>
#include <vector>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>   /* For open(), creat() */

#include "Utilities.cpp"
#include "Namespace.h"
#include "Record.h"
#include "Extent.h"

using namespace std;

Database::Database(string folder, string dbName) {
	newCollectionPos = 0;
	lastExtentPointer = DiskLoc(-1, -1);
	name = dbName;
	db_folder = folder;

	openNamespaceFile();

	// read existing collections and put their indexes in a map
	for (int i(0); i < MAX_DB_COLLECTIONS; i++)
	{
		if ((unsigned) strlen(nsFile[i].name) == 0)
		{
			// no more collections
			break;
		}

		nsFile[i].db = this; 				// setting the correct parent
		collectionIndexes[nsFile[i].name] = i;
		newCollectionPos++;

		if (nsFile[i].lastExtentLoc > lastExtentPointer)
		{
			lastExtentPointer = nsFile[i].lastExtentLoc;
		}
	}

	loadDataFiles(lastExtentPointer.fileNum);
}

void Database::deleteDB(string folder, string dbName) {
	deleteDBFiles(dbName, folder);
}

void Database::closeDB() {
	unmapFiles();

	if (_DEBUG)
		LOGI("-----");
}

void Database::msyncFiles() {
	if (msync(nsFile, NS_FILESIZE, MS_ASYNC) == -1) {
		LOGE("Error msyncing .ns file");
		// Decide here whether to close(fd) and exit() or not. Depends...
	}

	data_map::iterator iter;
	for (iter = data.begin(); iter != data.end(); ++iter) {
		if (msync(data[iter->first], DATAFILE_SIZE, MS_ASYNC) == -1) {
			LOGE("can not msync");
		}
	}
}

void Database::unmapFiles() {
	// un-map Namespace
	// free the mmapped memory
	if (munmap(nsFile, NS_FILESIZE) == -1) {
		LOGE("Error un-mmapping .ns file");
		// Decide here whether to close(fd) and exit() or not. Depends...
	}

	// un-map data
	data_map::iterator iter;
	for (iter = data.begin(); iter != data.end(); ++iter) {
		/*if (msync(data[iter->first], DATAFILE_SIZE, MS_ASYNC) == -1)
		 {
		 LOGE("can not msync");
		 }*/

		if (munmap(data[iter->first], DATAFILE_SIZE) == -1) {
			LOGE("Error un-mapping data file");
		} else {
			if (_DEBUG)
				LOGI("data file unmapped successfully");
		}
	}

	close(fd);
	for (int i(0); i < dataFileHandlers.size(); i++) {
		LOG_INT("closing file ", close(dataFileHandlers[i]));
	}
}

DiskLoc Database::increaseLastExtentLocation(DiskLoc extent,
		bool forceOpenFile) {
	//if (extent == NULL) extent = lastExtentPointer;
	if (lastExtentPointer.fileNum >= 0
			&& extent.offset + EXTENT_SIZE < DATAFILE_SIZE - 1)
	{
		// at least to have space for one extent

		lastExtentPointer.offset = extent.offset + EXTENT_SIZE;
	}
	else
	{
		lastExtentPointer.fileNum += 1;
		lastExtentPointer.offset = 0;

		if (forceOpenFile)
		{
			// create new file
			getDataFile(lastExtentPointer.fileNum);
		}
	}

	return lastExtentPointer;
}

void Database::openNamespaceFile() {
	string flname = db_folder;
	mkdir(flname.c_str(), (mode_t) 0600);
	flname.append(name);
	flname.append(".ns");

	bool fexists = fileExists(flname.c_str());
	if (fexists) {
		openFile(flname, fd);
	} else {
		createFile(flname, NS_FILESIZE, fd);
	}

	// MMAP IT!
	nsFile = (Namespace*) mmap(0, NS_FILESIZE, PROT_READ | PROT_WRITE,
			MAP_SHARED, fd, 0);
	if (nsFile == MAP_FAILED) {
		close(fd);
		LOGE("Error mmapping the file");
		exit(1);
	}
}

void Database::getDataFile(int index) {
	string flname = db_folder;
	mkdir(flname.c_str(), (mode_t) 0600);
	flname.append(name);
	flname.append(".");
	char buf[100];
	sprintf(buf, "%d", index);
	flname.append(buf);

	int handle;

	bool fexists = fileExists(flname.c_str());
	if (fexists) {
		LOG_INT("opening data file: ", index);
		openFile(flname, handle);
	} else {
		if (_DEBUG)
			LOGI("creating data file");
		createFile(flname, DATAFILE_SIZE, handle);
	}

	// MMAP FILE 				//  | O_TRUNC
	data[index] = (char*) mmap(0, DATAFILE_SIZE, PROT_READ | PROT_WRITE,
			MAP_SHARED, handle, 0);
	if (data[index] == MAP_FAILED) {
		close(handle);
		LOGE("Error mmapping data file");
		exit(1);
	}
	else
	{
		LOGI("file mapped");
	}

	dataFileHandlers.push_back(handle);
}

void Database::openFile(string flname, int& handle) {
	handle = open(flname.c_str(), O_RDWR | O_CREAT, (mode_t) 0600);
	if (handle == -1) {
		string msg = "error opening/creating file ";
		msg.append(flname);
		LOGE(msg.c_str());
		exit(1);
	}
}

void Database::createFile(string flname, unsigned size, int& handle) {
	openFile(flname, handle);

	if (_DEBUG)
		LOGI("stretching file");

	// Stretch the file size to the size of the (mmapped) array of Namespaces
	int result = lseek(handle, size - 1, SEEK_SET);
	if (result == -1) {
		close(handle);
		LOGE("Error calling lseek() to 'stretch' the file");
		exit(1);
	}

	// write a zero-byte (\0) to the end of the file to keep its size
	result = write(handle, "", 1);
	if (result != 1) {
		close(handle);
		LOGE("Error writing last byte of the file");
		exit(1);
	}
}

void Database::loadDataFiles(int untilIndex) {
	for (int i(0); i <= untilIndex; i++)
	{
		getDataFile(i);
	}
}

Extent* Database::getExtent(DiskLoc diskLoc)
{
	if (diskLoc.fileNum == -1 || diskLoc.offset == -1)
		return NULL;

	return (Extent*) &data[diskLoc.fileNum][diskLoc.offset];
}

Record* Database::getRecord(DiskLoc diskLoc) {
	return (Record*) &data[diskLoc.fileNum][diskLoc.offset];
}

Namespace* Database::getCollection(string collection)
{
	ns_map::const_iterator i = collectionIndexes.find(collection);
	if (i != collectionIndexes.end())
	{
		// Namespace exists
		if (_DEBUG)
			LOGI("collection exists");
		return &nsFile[collectionIndexes[collection]];
	}
	else
	{
		if (_DEBUG)
			LOGI("collection does not exist, creating now");

		Namespace nspace = nsFile[collectionIndexes.size()];
		nspace.init(this, collection);
		attachExtent(&nspace);

		collectionIndexes[collection] = newCollectionPos;
		newCollectionPos++;

		nsFile[collectionIndexes[collection]] = nspace;
		return &nsFile[collectionIndexes[collection]];
	}
}

Extent* Database::attachExtent(Namespace *ns)
{
	DiskLoc loc = increaseLastExtentLocation(lastExtentPointer, true);

	Extent *newExtent = (Extent*) &data[loc.fileNum][loc.offset];

	Extent *firstExtent = getExtent(ns->firstExtentLoc);
	if (firstExtent->isNull())
	{
		ns->firstExtentLoc.init(loc); // = loc;
		ns->lastExtentLoc = ns->firstExtentLoc;

		newExtent->init(loc);

		return (Extent*) &data[loc.fileNum][loc.offset];
	}

	Extent *lastExtent = getExtent(ns->lastExtentLoc);
	if (lastExtent->isNull())
	{
		newExtent->init(loc);
		LOGE("should NEVER be in here");
	}
	else
	{
		newExtent->init(ns->lastExtentLoc, loc);
		lastExtent->nextExtent = loc;
	}
	ns->lastExtentLoc = loc;

	return (Extent*) &data[loc.fileNum][loc.offset];
}
