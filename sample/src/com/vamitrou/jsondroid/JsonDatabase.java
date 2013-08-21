package com.vamitrou.jsondroid;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Environment;

public class JsonDatabase {

	private static JsonDatabase instance;

	private boolean is_open = false;
	private boolean is_inserting = false;

	private static JsonDatabase getInstance() {
		if (instance == null)
			instance = new JsonDatabase();

		return instance;
	}

	public static void OpenDB(Context ctx, String dbName, String colName) {
		JsonDatabase db = getInstance();
		if (!db.is_open)
		{			
			PackageManager m = ctx.getPackageManager();
			String s = ctx.getPackageName();
			PackageInfo p;
			try
			{
				p = m.getPackageInfo(s, 0);
				s = p.applicationInfo.dataDir + "/";
			}
			catch (NameNotFoundException e)
			{
				s = Environment.getExternalStorageDirectory().getPath() + "/";
			}		
			
			db.openDB(s, dbName, colName);
		}
		
		db.is_open = true;
	}

	public static void CloseDB() {
		JsonDatabase db = getInstance();
		db.closeDB();

		db.is_open = false;
	}

	public static String GetBatchRecords(int count) {
		JsonDatabase db = getInstance();

		if (!db.is_open)
			return "";

		IntWrapper intWrapper = new IntWrapper(count);
		String str = db.getBatchRecords(intWrapper);
		
		return str;
	}
	
	public static String GetRecord(String key, String value) {
		JsonDatabase db = getInstance();

		if (!db.is_open)
			return "";
		
		return db.selectRecord(key, value);
	}

	public static int InsertJSON(String json) {
		JsonDatabase db = getInstance();

		if (!db.is_open)
			return -1;

		while (db.is_inserting) {
			// wait to finish previous insertion
		}

		db.is_inserting = true;

		db.insertToDB(json);

		db.is_inserting = false;

		return 0;
	}

	public static int DeleteDB(Context ctx, String dbName) {
		JsonDatabase db = getInstance();

		if (db.is_open)
			return -1;

		PackageManager m = ctx.getPackageManager();
		String s = ctx.getPackageName();
		PackageInfo p;
		try
		{
			p = m.getPackageInfo(s, 0);
			s = p.applicationInfo.dataDir + "/";
		}
		catch (NameNotFoundException e)
		{
			s = Environment.getExternalStorageDirectory().getPath() + "/";
		}		
		
		
		db.deleteDB(s, dbName);
		

		return 0;
	}

	private native void openDB(String folder, String dbName, String colName);

	private native void closeDB();

	private native String selectFromDB();

	private native String getNextRecord();

	private native String getBatchRecords(IntWrapper count);

	private native void insertToDB(String data);

	private native void deleteDB(String folder, String dbName);

	private native void writeData();

	private native void readData();
	
	private native String selectRecord(String key, String value);

	private native String unimplementedStringFromJNI();

	static {
		System.loadLibrary("jsondroid");
	}
}
