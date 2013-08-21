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

#include "Namespace.h"

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <iostream>

#include "Extent.h"
#include "Record.h"
#include "Database.h"

#include "Utilities.cpp"

#include "json/jsmn.c"
#include "bson/bson.c"

Namespace::Namespace(Database* database, string collectionName,
		DiskLoc extentLoc)
{
	db = database;

	string str2 = collectionName.substr(0,
			min(NAME_SIZE, (int) collectionName.length()));
	sprintf(name, "%s", str2.c_str());
	firstExtentLoc = extentLoc; //DiskLoc(0,0);
	lastExtentLoc = extentLoc; //DiskLoc(0,0);
	recordCount = 0;
}

Namespace::Namespace(Database* database, string collectionName)
{
	init(database, collectionName);
}

void Namespace::init(Database* database, string collectionName)
{
	db = database;

	string str2 = collectionName.substr(0,
			min(NAME_SIZE, (int) collectionName.length()));
	sprintf(name, "%s", str2.c_str());
	recordCount = 0;

	extentCursor = DiskLoc();
	recordCursor = -1;
}

Extent* Namespace::getFirstExtent()
{
	return db->getExtent(firstExtentLoc);
}

Extent* Namespace::getLastExtent()
{
	return db->getExtent(lastExtentLoc);
}

Record* Namespace::getFirstRecord()
{
	return getFirstExtent()->getFirstRecord();
}

Record* Namespace::getLastRecord()
{

	return getLastExtent()->getLastRecord();
}

// returns NULL if no more records in collection
Record* Namespace::getNextRecord(Record *cursor)
{

	return NULL;
}

void Namespace::deleteCollection()
{

	memcpy(name, "\0", 1);
	firstExtentLoc.init(-1, -1);
	lastExtentLoc.init(-1, -1);
}

void Namespace::insert(const char* str)
{

	int count = 0;

	bson** bs = json_to_bson(str, count);

	Extent* lastExtent = getLastExtent();
	int success = 0;
	for (int i(0); i < count; i++)
	{
		success = lastExtent->addRecord(bs[i]);

		while (success != 0)
		{
			db->attachExtent(this);

			lastExtent = getLastExtent();
			success = lastExtent->addRecord(bs[i]);
		}

		free(bs[i]);
	}
	free(bs);
}

void Namespace::printData()
{
	DiskLoc nextExtentLoc = firstExtentLoc;
	while (!nextExtentLoc.isNull())
	{
		Extent* extent = db->getExtent(nextExtentLoc);
		int nextRecordOffset = extent->firstRecord;
		while (nextRecordOffset != -1)
		{
			LOG_INT("print record num: ", nextRecordOffset);
			Record* record = extent->getRecord(nextRecordOffset);
			int jsonSize = 0;
//			bson_to_json(((bson*)record->data)->data, 0, true, 0, jsonSize);
			nextRecordOffset = record->nextRecLoc;
		}

		nextExtentLoc = extent->nextExtent;
	}
}

string Namespace::getData()
{
	string data = "{\"docs\":[";
	DiskLoc nextExtentLoc = firstExtentLoc;
	while (!nextExtentLoc.isNull())
	{
		Extent* extent = db->getExtent(nextExtentLoc);
		int nextRecordOffset = extent->firstRecord;
		while (nextRecordOffset != -1)
		{
			Record* record = extent->getRecord(nextRecordOffset);
			//LOGI(record->data);
			data.append(record->data);

			nextRecordOffset = record->nextRecLoc;

			if (nextRecordOffset != -1)
				data.append(",");
		}

		nextExtentLoc = extent->nextExtent;
	}
	data.append("]}");
	return data;
}

Record* Namespace::getNextRecord()
{
	Record *rec;
	if (extentCursor.isNull()) // the first time after connection the extent cursor will be null
	{
		extentCursor = firstExtentLoc; // so, get the first extent of the colection
		if (_DEBUG)
			LOGI("getting first extent");
	}

	if (extentCursor.isNull()) // if first extent is null, then no extents exist
		return NULL;  // no extents

	Extent* extent = db->getExtent(extentCursor);

	if (recordCursor == -1)	// the first time the record cursor will be null as well
	{
		recordCursor = extent->firstRecord;	// get the first record of the extent

		if (recordCursor == -1)	// if first record is null, then no records exist
			return NULL;  // no records

		rec = extent->getRecord(recordCursor);
	}
	else // else, the cursor shows the previous record, should take the next one and return its data
	{
		rec = extent->getRecord(recordCursor);

		if (rec->nextRecLoc == -1) // if its next record is null, then go to next extent
		{
			if (extent->nextExtent.isNull()) // if the next extent is null, then no more extents
			{
				return NULL;  // no more records
			}
			else							// proceed with the next extent
			{
				extentCursor = extent->nextExtent;
				recordCursor = -1;
				return getNextRecord();
			}
		}
		else
		{
			recordCursor = rec->nextRecLoc;	// next record exists, so put the cursor on it
			if (_DEBUG)
				LOGI("getting next record");
			rec = extent->getRecord(recordCursor);
		}
	}
	return rec;
}

char* Namespace::getNextRecordData(int &recordSize)
{
	Record *rec;

	if (extentCursor.isNull()) // the first time after connection the extent cursor will be null
	{
		extentCursor = firstExtentLoc; // so, get the first extent of the colection
		if (_DEBUG)
			LOGI("getting first extent");
	}

	if (extentCursor.isNull()) // if first extent is null, then no extents exist
		return NULL;  // no extents

	Extent* extent = db->getExtent(extentCursor);

	if (recordCursor == -1)	// the first time the record cursor will be null as well
	{
		recordCursor = extent->firstRecord;	// get the first record of the extent

		if (recordCursor == -1)	// if first record is null, then no records exist
			return NULL;  // no records

		rec = extent->getRecord(recordCursor);
	}
	else // else, the cursor shows the previous record, should take the next one and return its data
	{
		rec = extent->getRecord(recordCursor);

		if (rec->nextRecLoc == -1) // if its next record is null, then go to next extent
		{
			if (extent->nextExtent.isNull()) // if the next extent is null, then no more extents
			{
				return NULL;  // no more records
			}
			else							// proceed with the next extent
			{
				extentCursor = extent->nextExtent;
				recordCursor = -1;
				return getNextRecordData(recordSize);
			}
		}
		else
		{
			recordCursor = rec->nextRecLoc;	// next record exists, so put the cursor on it
			if (_DEBUG)
				LOGI("getting next record");
			rec = extent->getRecord(recordCursor);
		}
	}

	int bsonSize = 0;
	bson_little_endian32( &bsonSize, rec->data);
	char *val = (char*) malloc((bsonSize + 128) * sizeof(char));
	int cur = 0;
	return bson_to_json(val, rec->data, 0, true, 0, recordSize, cur);
}

Record* Namespace::getRecord(const char* key, const char* value)
{
	Record *rec;
	do
	{
		rec = getNextRecord();
		//LOGI("found record");
	} while (rec != NULL);

	return NULL;
}

/*char* Namespace::getNextBatch(int &count) {
 if (_DEBUG)
 LOGI("get next batch");

 int batchSize = 0;
 int sizes[count];
 char *records[count]; //= (char**)malloc(count*sizeof(char*));
 for (int i(0); i < count; i++) {
 int recordSize = 0;
 char* rec = getNextRecordData(recordSize);

 //(rec.length() == 0) // || iteratorFinished)
 if (recordSize == 0) {
 count = i;
 return serializeJSON(records, batchSize, i, sizes);
 }

 records[i] = rec;
 batchSize += recordSize;
 sizes[i] = recordSize;
 }

 return serializeJSON(records, batchSize, count, sizes);
 } */

char* Namespace::getNextBatch(int &count)
{
	if (_DEBUG)
		LOGI("get next batch");

	int batchSize = 0;
	int sizes[count];
	int jsonSize = 0;
	char *records[count]; //= (char**)malloc(count*sizeof(char*));

	int lastRetrievedRecord = -1, recordSize, skip = 0;

	int i = 0;
	Extent *extent = getFirstExtent();
	while (extent != NULL)
	{
		lastRetrievedRecord = -1;
		Record *record = extent->getFirstRecord();
		while (record != NULL && i < count)
		{
			recordSize = 0;

			int bsonSize = 0;
			bson_little_endian32( &bsonSize, record->data);
			//FORCE_LOG_INT("bsonSize: ", bsonSize);
			char *val = (char*) malloc((bsonSize + 100) * sizeof(char));
			int cur = 0;
			val = bson_to_json(val, record->data, 0, true, bsonSize, recordSize,
					cur);

			records[i] = val;
			batchSize += recordSize;
			sizes[i] = recordSize;
			jsonSize += recordSize;

			record = extent->getRecord(record->nextRecLoc);

			i++;
		}

		extent = db->getExtent(extent->nextExtent);
	}

	count = i;
	FORCE_LOG_INT("count: ", i);

	return serializeJSON(records, jsonSize, count, sizes);
}

char* Namespace::serializeJSON(char** records, int recordsSize,
		int recordsCount, int sizes[])
{

	if (recordsCount == 0)
		return NULL;

	recordsSize += recordsCount + 20; // for commas, and 1 for null-terminator
	FORCE_LOG_INT("json size: ", recordsSize);
	char *json = (char*) malloc(recordsSize * sizeof(char));
	int cursor = 1;

	memcpy(&json[0], "[", 1);

	for (int i = 0; i < recordsCount; i++)
	{
		memcpy(&json[cursor], records[i], sizes[i]);
		cursor += sizes[i];

		if (i < recordsCount - 1)
		{
			memcpy(&json[cursor], ",", 1);
			cursor += 1;
		}
		free(records[i]);
	}

	memcpy(&json[cursor], "]", 1);
	cursor++;

	return json;
}

void Namespace::resetCursors()
{
	extentCursor = DiskLoc();
	recordCursor = -1;
}

// json functions

#define MAXTOKENS 102400
bson** Namespace::json_to_bson(const char* json, int &count)
{
	bson *b, **bs;

	int r;
	jsmn_parser p;
	jsmntok_t tok[MAXTOKENS];

	jsmn_init(&p);
	r = jsmn_parse(&p, json, tok, MAXTOKENS);

	if (r != JSMN_SUCCESS)
	{
		LOGE("Parse error");
		//LOGI(json);
		LOG_INT("parser error code: ", r);
		exit(1);
	}

	if (tok[0].type != JSMN_OBJECT && tok[0].type != JSMN_ARRAY)
	{
		LOGE("not valid json");
		exit(1);
	}

	int cursor = 0;

	if (tok[0].type == JSMN_ARRAY)
	{
		bs = (bson **) malloc(sizeof(bson *) * tok[0].size);
		count = tok[0].size;

		cursor++;

		for (int i = 0; i < tok[0].size; i++)
		{
			b = (bson *) malloc(sizeof(bson));
			bson_init(b);

			parseJSON(b, json, tok, cursor, true, 1);

			bson_finish(b);
			bs[i] = b;
		}

		//bs = parseJSONarray(json, tok, cursor);

	}
	else if (tok[0].type == JSMN_OBJECT)
	{
		count = 1;
		bs = (bson **) malloc(sizeof(bson *) * 1);

		b = (bson*) malloc(sizeof(bson));
		bson_init(b);

		parseJSON(b, json, tok, cursor, true, 1);

		/*bson_append_string(b, "key1", "value1");
		 bson_append_string(b, "key2", "value2");
		 bson_append_start_object(b, "testobj");
		 bson_append_string(b, "color", "red");
		 bson_append_finish_object(b);
		 bson_append_start_array(b, "testarray");
		 bson_append_start_object(b, "");
		 bson_append_string(b, "color2", "green");
		 bson_append_finish_object(b);
		 bson_append_start_object(b, "");
		 bson_append_string(b, "color3", "blue");
		 bson_append_finish_object(b);
		 bson_append_finish_array(b);
		 bson_append_start_array(b, "testarray2");
		 bson_append_string(b, "", "color2");
		 bson_append_string(b, "", "color3");
		 bson_append_finish_array(b);*/

		bson_finish(b);

		bs[0] = b;

		//bson_to_json(b->data, 0, true);
	}
	else
	{
		LOGE("invalid json, should be object or array");
	}

	return bs;
}

void Namespace::parseJSON(bson* &p, const char* json, jsmntok_t *tokens,
		int &tokenCursor, bool createNew, int elementCount)
{
	if (_DEBUG)
		LOGI("parse");

	char buf[100];
	int autoKey = 0;
	char firstChar;
	int count = 0;

	char keyBuf[255];
	char valueBuf[1024];
	bool tokenIsKey = false;

	for (int i(0); i < elementCount; i++)
	{
		jsmntok_t token = tokens[tokenCursor];

		tokenIsKey = false;

		// check if the token contains a key (look for ':' within 5 chars after its end
		for (int k(0); k < 5; k++)
		{
			{
				if (json[token.end + k] == ':')
				{

					memcpy(keyBuf, &json[token.start], token.end - token.start);
					keyBuf[token.end - token.start] = '\0';

					tokenIsKey = true;
					break;
				}
			}
		}

		if (tokenIsKey)
		{
			tokenCursor++;
			continue;	// that token was key, continue with the rest
		}

		switch (token.type)
		{
		case JSMN_ARRAY:
			count = token.size;
			bson_append_start_array(p, keyBuf);
			tokenCursor++;
			parseJSON(p, json, tokens, tokenCursor, false, token.size);
			bson_append_finish_array(p);
			break;
		case JSMN_OBJECT:
			if (createNew)
			{
				createNew = false;
				tokenCursor++;
				parseJSON(p, json, tokens, tokenCursor, false, token.size);
			}
			else
			{
				bson_append_start_object(p, keyBuf);
				tokenCursor++;
				parseJSON(p, json, tokens, tokenCursor, false, token.size);
				bson_append_finish_object(p);
			}
			break;
		case JSMN_STRING:
			memcpy(valueBuf, &json[token.start], token.end - token.start);
			valueBuf[token.end - token.start] = '\0';
			bson_append_string(p, keyBuf, valueBuf);
			tokenCursor++;
			break;
		case JSMN_PRIMITIVE:
			firstChar = json[token.start];
			if (firstChar == 't' || firstChar == 'f')
			{
				// todo: wrong boolean parameter
				memcpy(valueBuf, &json[token.start], token.end - token.start);
				valueBuf[token.end - token.start] = '\0';
				bson_append_bool(p, keyBuf, atoi(valueBuf));
			}
			else if (firstChar == 'n')
			{
				bson_append_null(p, keyBuf);
			}
			else
			{
				memcpy(valueBuf, &json[token.start], token.end - token.start);
				valueBuf[token.end - token.start] = '\0';
				double v = atof(valueBuf);

				if (fmod(v, 1) == 0)
				{
					/* variable is an integer */
					bson_append_int(p, keyBuf, (int) v);
				}
				else
				{
					bson_append_double(p, keyBuf, v);
				}
			}
			tokenCursor++;
			break;
		default:
			break;
		}
	}
}

char* Namespace::bson_to_json(char* val, const char *data, int depth,
		bool isObject, int bsonSize, int &jsonSize, int &cursor)
{

	char *object;

	int bufSize;

	char keybuf[512];
	char buf[512];
	int c = 0;

	bson_iterator i;
	const char *key;
	int temp;
	bson_timestamp_t ts;
	char oidhex[25];
	bson scope;
	bson_iterator_from_buffer(&i, data);
	//bson_iterator_init(&i, data);

	if (isObject)
	{
		memcpy(&val[cursor], "{", 1);
		cursor += 1;
	}
	else
	{
		memcpy(&val[cursor], "[", 1);
		cursor += 1;
	}

	while (bson_iterator_next(&i) && i.progress < bsonSize)
	{
		if (c > 0)
		{
			memcpy(&val[cursor], ",", 1);
			cursor += 1;
		}
		c++;

		bson_type t = bson_iterator_type(&i);
		if (t == 0)
		{
			break;
		}
		key = bson_iterator_key(&i);

		if (key[0] != '\0')
		{
			sprintf(keybuf, "\"%s\":", key);
			key = &keybuf[0];
		}

		switch (t)
		{
		case BSON_DOUBLE:
			sprintf(buf, "%s%f", key, bson_iterator_double(&i));
			bufSize = strlen(buf);
			memcpy(&val[cursor], buf, bufSize);
			cursor += bufSize;
			break;
		case BSON_STRING:
			sprintf(buf, "%s\"%s\"", key, bson_iterator_string(&i));
			bufSize = strlen(buf);
			memcpy(&val[cursor], buf, bufSize);
			cursor += bufSize;
			break;
		case BSON_OID:
			bson_oid_to_string(bson_iterator_oid(&i), oidhex);
			sprintf(buf, "%s\"%s\"", key, oidhex);
			bufSize = strlen(buf);
			memcpy(&val[cursor], buf, bufSize);
			cursor += bufSize;
			break;
		case BSON_BOOL:
			sprintf(buf, "%s%s", key,
					bson_iterator_bool(&i) ? "true" : "false");
			bufSize = strlen(buf);
			memcpy(&val[cursor], buf, bufSize);
			cursor += bufSize;
			break;
		case BSON_NULL:
			sprintf(buf, "%snull", key);
			bufSize = strlen(buf);
			memcpy(&val[cursor], buf, bufSize);
			cursor += bufSize;
			break;
		case BSON_INT:
			sprintf(buf, "%s%d", key, bson_iterator_int(&i));
			bufSize = strlen(buf);
			memcpy(&val[cursor], buf, bufSize);
			cursor += bufSize;
			break;
		case BSON_OBJECT:
			sprintf(buf, "%s\0", key);
			memcpy(&val[cursor], buf, strlen(buf));
			cursor += strlen(buf);

			object = bson_to_json(val, bson_iterator_value(&i), depth + 1, true,
					bsonSize - cursor, jsonSize, cursor);

			break;
		case BSON_ARRAY:
			sprintf(buf, "%s", key);
			bufSize = strlen(buf);
			memcpy(&val[cursor], buf, bufSize);
			cursor += bufSize;

			object = bson_to_json(val, bson_iterator_value(&i), depth + 1,
					false, bsonSize - cursor, jsonSize, cursor);

			break;
		default:
			LOGE("can't print type");
			FORCE_LOG_INT("type: ", t);

			memcpy(&val[cursor], "}", 1);
			cursor += 1;
			jsonSize = cursor;
			return val;
		}
	}

	if (isObject)
	{
		memcpy(&val[cursor], "}", 1);
		cursor += 1;
		memcpy(&val[cursor], "\0", 1);

	}
	else
	{
		memcpy(&val[cursor], "]", 1);
		cursor += 1;
	}

	jsonSize = cursor;
	return val;
}
