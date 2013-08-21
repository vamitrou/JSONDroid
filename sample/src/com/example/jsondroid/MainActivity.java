/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.example.jsondroid;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.RandomAccessFile;
import java.net.URI;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

import com.vamitrou.jsondroid.JsonDatabase;

public class MainActivity extends Activity
{
	static String insertString = "";

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState)
	{

		super.onCreate(savedInstanceState);

		final int BATCH_COUNT = 5000;

		final String DB_NAME = "test";
		final String COL_NAME = "twitter";

		setContentView(R.layout.main);

		final EditText txtView = (EditText) findViewById(R.id.editText1);
		final EditText textNum = (EditText) findViewById(R.id.editText2);

		txtView.setText("time goes here");

		final Context ctx = this;

		Button btnGetRecord = (Button) findViewById(R.id.button9);
		btnGetRecord.setOnClickListener(new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				long start = System.currentTimeMillis();

				JsonDatabase.OpenDB(ctx, DB_NAME, COL_NAME);
				JsonDatabase.GetRecord("", "");
				JsonDatabase.CloseDB();

				long end = System.currentTimeMillis();

				Log.d("jsonDroid", String.valueOf(end - start));
				txtView.setText(String.valueOf(end - start) + "ms");
			}
		});

		Button btn = (Button) findViewById(R.id.button1); // new Button(this);
		btn.setOnClickListener(new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				long start = System.currentTimeMillis();

				JsonDatabase.OpenDB(ctx, DB_NAME, COL_NAME);
				String str = JsonDatabase.GetBatchRecords(BATCH_COUNT);
				JsonDatabase.CloseDB();

				long end = System.currentTimeMillis();

				Log.d("jsonDroid", String.valueOf(end - start));
				txtView.setText(String.valueOf(end - start) + "ms, "
						+ str.length() + " characters");

			}
		});

		Button btnInsert = (Button) findViewById(R.id.button2);
		btnInsert.setOnClickListener(new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				String str = "";
				if (insertString.length() == 0)
				{
					try
					{
						str = RequestTwitterRepos(Integer.valueOf(textNum
								.getText().toString()));

						insertString = str;
					}
					catch (Exception e)
					{
						e.printStackTrace();
					}
				}
				else
					str = insertString;

				long start = System.currentTimeMillis();
				JsonDatabase.OpenDB(ctx, DB_NAME, COL_NAME);
				JsonDatabase.InsertJSON(str);
				JsonDatabase.CloseDB();

				long end = System.currentTimeMillis();

				Log.d("jsonDroid", String.valueOf(end - start));
				txtView.setText(String.valueOf(end - start) + "ms");
			}
		});

		Button btnDelete = (Button) findViewById(R.id.button3); 
		btnDelete.setOnClickListener(new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				long start = System.currentTimeMillis();

				JsonDatabase.DeleteDB(ctx, DB_NAME);				

				long end = System.currentTimeMillis();

				Log.d("jsonDroid", String.valueOf(end - start));
				txtView.setText(String.valueOf(end - start) + "ms");
			}
		});

		Button btnWrite = (Button) findViewById(R.id.button4);
		btnWrite.setOnClickListener(new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				float usage = readUsage();
				Log.d("jsonDROID", "cpu usage: " + usage);
			}
		});

		Button btnSQLInsert = (Button) findViewById(R.id.button5);
		btnSQLInsert.setOnClickListener(new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{

				String str = "";

				if (insertString.length() == 0)
				{
					try
					{
						str = RequestTwitterRepos(Integer.valueOf(textNum
								.getText().toString()));
						insertString = str;
					}
					catch (Exception e)
					{
						e.printStackTrace();
					}
				}
				else
					str = insertString;

				long start = System.currentTimeMillis();

				DatabaseHandler handler = new DatabaseHandler(ctx);
				handler.addRecord(str);
				handler.close();

				long end = System.currentTimeMillis();

				Log.d("jsonDroid", String.valueOf(end - start));
				txtView.setText(String.valueOf(end - start) + "ms");
			}
		});

		Button btnSQLSelect = (Button) findViewById(R.id.button6);
		btnSQLSelect.setOnClickListener(new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				long start = System.currentTimeMillis();

				DatabaseHandler handler = new DatabaseHandler(ctx);
				String str = handler.getJSONArray();
				handler.close();

				long end = System.currentTimeMillis();

				Log.d("jsonDroid", String.valueOf(end - start));
				txtView.setText(String.valueOf(end - start) + "ms, "
						+ str.length() + " characters");
			}
		});

		Button btnSQLDelete = (Button) findViewById(R.id.button7);
		btnSQLDelete.setOnClickListener(new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				long start = System.currentTimeMillis();

				DatabaseHandler handler = new DatabaseHandler(ctx);
				handler.deleteRecords();
				handler.close();

				long end = System.currentTimeMillis();

				Log.d("jsonDroid", String.valueOf(end - start));
				txtView.setText(String.valueOf(end - start) + "ms");
			}
		});

		Button btnDownload = (Button) findViewById(R.id.button8);
		btnDownload.setOnClickListener(new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				try
				{

					insertString = RequestTwitterRepos(Integer.valueOf(textNum
							.getText().toString()));
				}
				catch (Exception e)
				{
					e.printStackTrace();
				}
			}
		});

		Button btn_parse_insert = (Button) findViewById(R.id.button99);
		btn_parse_insert.setOnClickListener(new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				String str = "";

				if (insertString.length() == 0)
				{
					try
					{
						str = RequestTwitterRepos(Integer.valueOf(textNum
								.getText().toString()));
						insertString = str;
					}
					catch (Exception e)
					{
						e.printStackTrace();
					}
				}
				else
					str = insertString;

				long start = System.currentTimeMillis();

				JSONParser.ParseJSON(ctx, str);

				long end = System.currentTimeMillis();

				txtView.setText(String.valueOf(end - start) + "ms");
			}
		});

		Button btn_parse_delete = (Button) findViewById(R.id.button999);
		btn_parse_delete.setOnClickListener(new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				RelationalHandler handler = new RelationalHandler(ctx);
				handler.deleteRecords();
				handler.close();
			}
		});
	}

	public static String RequestTwitterRepos(int count) throws Exception
	{

		BufferedReader in = null;
		String page = null;

		try
		{

			HttpClient client = new DefaultHttpClient();
			HttpGet request = new HttpGet();

			if (count == 200)
				request.setURI(new URI(
						"https://dl.dropboxusercontent.com/s/s0h13r9e3sadq2d/200.json?token_hash=AAFgmny9F_7t5dA3QX_Ta6l5zN2KfAFFoeEEpUKPw5ZupQ&dl=1"));
			else if (count == 500)
				request.setURI(new URI(
						"https://dl.dropboxusercontent.com/s/xgyhpjjiuge6nfr/500.json?token_hash=AAFjiB0LglXZdlw4nByAoQJIVM7R6j4ueoEoGZsBCGWa0g&dl=1"));
			else if (count == 1000)
				request.setURI(new URI(
						"https://dl.dropboxusercontent.com/s/4m25djm32bq2vrd/1000.json?token_hash=AAG6w0-46mbOYANo6GYNTeYv-AbnbVVdZ4dwTnqLiMZNgg&dl=1"));
			else
				request.setURI(new URI(
						"https://api.github.com/orgs/twitter/repos?page=1&per_page="
								+ count
				));

			HttpResponse response = client.execute(request);

			in = new BufferedReader(new InputStreamReader(response.getEntity()
					.getContent()));

			StringBuffer sb = new StringBuffer("");
			String line = "";
			String NL = System.getProperty("line.separator");

			while ((line = in.readLine()) != null)
			{
				sb.append(line + NL);
			}

			in.close();
			page = sb.toString();
		}
		finally
		{
			if (in != null)
			{
				try
				{
					in.close();
					return page;
				}
				catch (IOException e)
				{
					return "";
				}
			}
		}
		return "";
	}

	private float readUsage()
	{
		try
		{
			RandomAccessFile reader = new RandomAccessFile("/proc/stat", "r");
			String load = reader.readLine();

			String[] toks = load.split(" ");

			long idle1 = Long.parseLong(toks[5]);
			long cpu1 = Long.parseLong(toks[2]) + Long.parseLong(toks[3])
					+ Long.parseLong(toks[4]) + Long.parseLong(toks[6])
					+ Long.parseLong(toks[7]) + Long.parseLong(toks[8]);

			try
			{
				Thread.sleep(360);
			}
			catch (Exception e)
			{
			}

			reader.seek(0);
			load = reader.readLine();
			reader.close();

			toks = load.split(" ");

			long idle2 = Long.parseLong(toks[5]);
			long cpu2 = Long.parseLong(toks[2]) + Long.parseLong(toks[3])
					+ Long.parseLong(toks[4]) + Long.parseLong(toks[6])
					+ Long.parseLong(toks[7]) + Long.parseLong(toks[8]);

			return (float) (cpu2 - cpu1) / ((cpu2 + idle2) - (cpu1 + idle1));

		}
		catch (IOException ex)
		{
			ex.printStackTrace();
		}

		return 0;
	}
}
