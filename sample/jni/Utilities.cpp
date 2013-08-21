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

#ifndef _UTIL_
#define _UTIL_

#include <android/log.h>
#include <fstream>
#include <string.h>
#include <dirent.h>

#include "Constants.h"

#define _DEBUG 0


#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__))

using namespace std;

//namespace Utilities
//{

inline void LOG_INT(string descr, int a)
	{
		if (_DEBUG == 0)
			return;

		char buf[100];
		sprintf(buf, "%s%d", descr.c_str(), a);

		LOGI(buf);
	}

	inline void FORCE_LOG_INT(string descr, int a)
	{
		char buf[100];
		sprintf(buf, "%s%d", descr.c_str(), a);

		LOGI(buf);
	}

	inline void my_printf()
	{

	}

	inline bool fileExists(const char *filename)
	{
		ifstream ifile(filename);
		return ifile;
	}

	template<typename T>
	int TCompare(T a, T b)
	{
		if (a < b) return -1;
		if (b < a) return 1;
		return 0;
	}

	inline void deleteFile(const char* flName)
	{
		if( remove( flName ) != 0 )
			LOGE( "Error deleting file" );
		else
			LOGI( "File successfully deleted" );
	}

	inline void deleteDBFiles(string dbName, string folder)
	{
		DIR *dpdf;
		struct dirent *epdf;

		dpdf = opendir(folder.c_str());
		if (dpdf != NULL)
		{
		   while (epdf = readdir(dpdf))
		   {
			   string fileName(epdf->d_name);
			   if (fileName.find(dbName) != string::npos)
			   {
				   // delete file
				   string flname = folder;
				   flname.append(epdf->d_name);
				   deleteFile(flname.c_str());
			   }
		   }
		}
	}

//}


#endif
