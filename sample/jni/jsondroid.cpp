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
#include <jni.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>

using namespace std;

#include "Utilities.cpp"
#include "Database.h"
#include "Namespace.h"
#include "Record.h"

#include <time.h>


extern "C" {

	Database *db;
	Namespace *col;

	char *result;

	void
	Java_com_vamitrou_jsondroid_JsonDatabase_openDB( JNIEnv* env, jobject thiz, jstring folder, jstring dbName, jstring colName )
	{
		const char *db_name = env->GetStringUTFChars(dbName, 0);
		const char *col_name = env->GetStringUTFChars(colName, 0);
		const char *db_folder = env->GetStringUTFChars(folder, 0);

		db = new Database(db_folder, db_name);
		col = db->getCollection(col_name);

		col->resetCursors();

		env->ReleaseStringUTFChars(dbName, db_name);
		env->ReleaseStringUTFChars(colName, col_name);
		env->ReleaseStringUTFChars(folder, db_folder);
	}

	void
	Java_com_vamitrou_jsondroid_JsonDatabase_closeDB( JNIEnv* env, jobject thiz )
	{
		db->closeDB();
		delete db;
	}

	void
	Java_com_vamitrou_jsondroid_JsonDatabase_deleteDB( JNIEnv* env,
                                                  jobject thiz, jstring folder, jstring dbName )
	{
		const char *db_name = env->GetStringUTFChars(dbName, 0);
		const char *db_folder = env->GetStringUTFChars(folder, 0);

		deleteDBFiles(db_name, db_folder);
		//col->deleteCollection();

		env->ReleaseStringUTFChars(dbName, db_name);
		env->ReleaseStringUTFChars(folder, db_folder);
	}

	void
	Java_com_vamitrou_jsondroid_JsonDatabase_insertToDB( JNIEnv* env,
                                                  jobject thiz, jstring str )
	{
		const char *data = env->GetStringUTFChars(str, 0);

		col->insert(data);

		env->ReleaseStringUTFChars(str, data);
	}

	jstring
	Java_com_vamitrou_jsondroid_JsonDatabase_selectFromDB( JNIEnv* env,
                                                  jobject thiz )
	{
		clock_t t;

		if (_DEBUG) LOGI("-starting");

		string data(col->getData());

		LOG_INT("data size:", data.size());

		jstring str = env->NewStringUTF(data.c_str());

		return str;
	}

	jstring Java_com_vamitrou_jsondroid_JsonDatabase_selectRecord(JNIEnv* env, jobject thiz,
													jstring jkey, jstring jvalue, jobject count)
	{
		const char *key = env->GetStringUTFChars(jkey, 0);
		const char *value = env->GetStringUTFChars(jvalue, 0);

		Record* record = col->getRecord(key, value);

		env->ReleaseStringUTFChars(jkey, key);
		env->ReleaseStringUTFChars(jvalue, value);

		jstring str = env->NewStringUTF("");
		return str;
	}

	jstring Java_com_vamitrou_jsondroid_JsonDatabase_getNextRecord(JNIEnv* env, jobject thiz)
	{
		int recSize;
		jstring resultString = env->NewStringUTF(result);

		return resultString;
	}

	jstring Java_com_vamitrou_jsondroid_JsonDatabase_getBatchRecords(JNIEnv* env, jobject thiz, jobject count)
	{
		jclass intWrapperClass = env->GetObjectClass(count);
		jmethodID getContent = env->GetMethodID(intWrapperClass, "getContent", "()I");
		int content = env->CallIntMethod(count, getContent);

		result = col->getNextBatch(content);
		jstring resultString;
		if (result != NULL)
		{
			resultString = env->NewStringUTF(result);
			free(result);
		}
		else
		{
			content = 0;
			resultString = env->NewStringUTF("");
		}

		content = 0;
		jmethodID setContent = env->GetMethodID(intWrapperClass, "setContent", "(I)V");
		env->CallVoidMethod(count, setContent, content);

		return resultString;
	}
}
