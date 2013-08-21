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

#ifndef __JSONUTIL__
#define __JSONUTIL__


//#include "json/jsmn.c"

//#include "bson/bson.c"

#include <string.h>
#include <stdio.h>
#include <iostream>

#include "Utilities.cpp"

using namespace std;

#define MAXTOKENS 1024
	/*inline int** json_to_bson(string json, int &count)
	{
		//bson *b, **bs;

		int r;
		jsmn_parser p;
		jsmntok_t tok[MAXTOKENS];

		jsmn_init(&p);
		r = jsmn_parse(&p, json.c_str(), tok, MAXTOKENS);

		if (r != JSMN_SUCCESS)
		{
			LOGE("Parse error");
			exit(1);
			return NULL;
		}

		LOG_INT("token 0 size: ", tok[0].size);

		if (tok[0].type == JSMN_ARRAY)
		{
			// many objects
			count = 0;
		}
		else
		{
			// one object
			count = 1;
			//b = (bson*)malloc(sizeof(bson));
			//bson_init(b);

		}




	}

	inline void parseToken(int &parent, string json, jsmntok_t *tokens, int cursor)
	{
		/*for (int i(0); i<MAXTOKENS; i++)
		{
			switch(tok[i].type)
			{
				case JSMN_OBJECT:
					//bson bs = parseJSONobject(tok[i].)
					//bson_append_bson()
					break;
				default:
					break;
			}
		}
	}

	inline void parseJSONobject(int &parent, string json, jsmntok_t *tokens, int cursor)
	{

	}

	inline void parseJSONarray(string json, int &b)
	{

	}

	inline void parseJSONprimitive(string json, int &b)
	{

	}

	inline void parseJSONstring(string json, int &b)
	{

	}*/

#endif
