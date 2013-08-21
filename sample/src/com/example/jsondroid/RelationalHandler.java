package com.example.jsondroid;

import android.content.ContentValues;
import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class RelationalHandler extends SQLiteOpenHelper
{

	// All Static variables
	// Database Version
	private static final int DATABASE_VERSION = 1;

	// Database Name
	private static final String DATABASE_NAME = "github";

	// Contacts table name
	public static final String TABLE_REPOS = "repos";
	public static final String TABLE_OWNERS = "owners";
	public static final String TABLE_PERMISSIONS = "permissions";

	// Contacts Table Columns names
	public static final String REPO_ID = "id";
	public static final String REPO_NAME = "name";
	public static final String REPO_FULL_NAME = "full_name";
	public static final String REPO_OWNER = "owner";
	public static final String REPO_PRIVATE = "private";
	public static final String REPO_HTML_URL = "html_url";
	public static final String REPO_DESCRIPTION = "description";
	public static final String REPO_FORK = "fork";
	public static final String REPO_URL = "url";
	public static final String REPO_FORKS_URL = "forks_url";
	public static final String REPO_KEYS_URL = "keys_url";
	public static final String REPO_COLLABORATORS_URL = "collaborators_url";
	public static final String REPO_TEAMS_URL = "teams_url";
	public static final String REPO_HOOKS_URL = "hooks_url";
	public static final String REPO_ISSUE_EVENTS_URL = "issue_events_url";
	public static final String REPO_EVENTS_URL = "events_url";
	public static final String REPO_ASSIGNEES_URL = "assignees_url";
	public static final String REPO_BRANCHES_URL = "branches_url";
	public static final String REPO_TAGS_URL = "tags_url";
	public static final String REPO_BLOBS_URL = "blobs_url";
	public static final String REPO_GIT_TAGS_URL = "git_tags_url";
	public static final String REPO_GIT_REFS_URL = "git_refs_url";
	public static final String REPO_TREES_URL = "trees_url";
	public static final String REPO_STATUSES_URL = "statuses_url";
	public static final String REPO_LANGUAGES_URL = "languages_url";
	public static final String REPO_STARGAZERS_URL = "stargazers_url";
	public static final String REPO_CONTRIBUTORS_URL = "contributors_url";
	public static final String REPO_SUBSCRIBERS_URL = "subscribers_url";
	public static final String REPO_SUBSCRIPTION_URL = "subscription_url";
	public static final String REPO_COMMITS_URL = "commits_url";
	public static final String REPO_GIT_COMMITS_URL = "git_commits_url";
	public static final String REPO_COMMENTS_URL = "comments_url";
	public static final String REPO_ISSUE_COMMENT_URL = "issue_comment_url";
	public static final String REPO_CONTENTS_URL = "contents_url";
	public static final String REPO_COMPARE_URL = "compare_url";
	public static final String REPO_MERGES_URL = "merges_url";
	public static final String REPO_ARCHIVE_URL = "archive_url";
	public static final String REPO_DOWNLOADS_URL = "downloads_url";
	public static final String REPO_ISSUES_URL = "issues_url";
	public static final String REPO_PULLS_URL = "pulls_url";
	public static final String REPO_MILESTONES_URL = "milestones_url";
	public static final String REPO_NOTIFICATIONS_URL = "notifications_url";
	public static final String REPO_LABELS_URL = "labels_url";
	public static final String REPO_CREATED_AT = "created_at";
	public static final String REPO_UPDATED_AT = "updated_at";
	public static final String REPO_PUSHED_AT = "pushed_at";
	public static final String REPO_GIT_URL = "git_url";
	public static final String REPO_SSH_URL = "ssh_url";
	public static final String REPO_CLONE_URL = "clone_url";
	public static final String REPO_SVN_URL = "svn_url";
	public static final String REPO_HOMEPAGE = "homepage";
	public static final String REPO_SIZE = "size";
	public static final String REPO_WATCHERS_COUNT = "watchers_count";
	public static final String REPO_LANGUAGE = "language";
	public static final String REPO_HAS_ISSUES = "has_issues";
	public static final String REPO_HAS_DOWNLOADS = "has_downloads";
	public static final String REPO_HAS_WIKI = "has_wiki";
	public static final String REPO_FORKS_COUNT = "forks_count";
	public static final String REPO_MIRROR_URL = "mirror_url";
	public static final String REPO_OPEN_ISSUES_COUNT = "open_issues_count";
	public static final String REPO_FORKS = "forks";
	public static final String REPO_OPEN_ISSUES = "open_issues";
	public static final String REPO_WATCHERS = "watchers";
	public static final String REPO_MASTER_BRANCH = "master_branch";
	public static final String REPO_DEFAULT_BRANCH = "default_branch";
	public static final String REPO_PERMISSIONS = "permissions";

	public static final String OWNER_LOGIN = "login";
	public static final String OWNER_ID = "id";
	public static final String OWNER_AVATAR_URL = "avatar_url";
	public static final String OWNER_GRAVATAR_ID = "gravatar_id";
	public static final String OWNER_URL = "url";
	public static final String OWNER_HTML_URL = "html_url";
	public static final String OWNER_FOLLOWERS_URL = "followers_url";
	public static final String OWNER_FOLLOWING_URL = "following_url";
	public static final String OWNER_GISTS_URL = "gists_url";
	public static final String OWNER_STARRED_URL = "starred_url";
	public static final String OWNER_SUBSCRIPTIONS_URL = "subscriptions_url";
	public static final String OWNER_ORGANIZATIONS_URL = "organizations_url";
	public static final String OWNER_REPOS_URL = "repos_url";
	public static final String OWNER_EVENTS_URL = "events_url";
	public static final String OWNER_RECEIVED_EVENTS_URL = "received_events_url";
	public static final String OWNER_TYPE = "type";

	public static final String PERMISSIONS_ADMIN = "admin";
	public static final String PERMISSIONS_PUSH = "push";
	public static final String PERMISSIONS_PULL = "pull";

	public RelationalHandler(Context context)
	{
		super(context, DATABASE_NAME, null, DATABASE_VERSION);
	}

	// Creating Tables
	@Override
	public void onCreate(SQLiteDatabase db)
	{
		String CREATE_REPOS_TABLE = "CREATE TABLE " + TABLE_REPOS + "("
				+ REPO_ID + " INTEGER," + REPO_NAME + " TEXT,"
				+ REPO_FULL_NAME + " TEXT," + REPO_OWNER + " INTEGER,"
				+ REPO_PRIVATE + " TEXT," + REPO_HTML_URL + " TEXT,"
				+ REPO_DESCRIPTION + " TEXT," + REPO_FORK + " TEXT," + REPO_URL
				+ " TEXT," + REPO_FORKS_URL + " TEXT," + REPO_KEYS_URL
				+ " TEXT," + REPO_COLLABORATORS_URL + " TEXT," + REPO_TEAMS_URL
				+ " TEXT," + REPO_HOOKS_URL + " TEXT," + REPO_ISSUE_EVENTS_URL
				+ " TEXT," + REPO_EVENTS_URL + " TEXT," + REPO_ASSIGNEES_URL
				+ " TEXT," + REPO_BRANCHES_URL + " TEXT," + REPO_TAGS_URL
				+ " TEXT," + REPO_BLOBS_URL + " TEXT," + REPO_GIT_TAGS_URL
				+ " TEXT," + REPO_GIT_REFS_URL + " TEXT," + REPO_TREES_URL
				+ " TEXT," + REPO_STATUSES_URL + " TEXT," + REPO_LANGUAGES_URL
				+ " TEXT," + REPO_STARGAZERS_URL + " TEXT,"
				+ REPO_CONTRIBUTORS_URL + " TEXT," + REPO_SUBSCRIBERS_URL
				+ " TEXT," + REPO_SUBSCRIPTION_URL + " TEXT,"
				+ REPO_COMMITS_URL + " TEXT," + REPO_GIT_COMMITS_URL + " TEXT,"
				+ REPO_COMMENTS_URL + " TEXT," + REPO_ISSUE_COMMENT_URL
				+ " TEXT," + REPO_CONTENTS_URL + " TEXT," + REPO_COMPARE_URL
				+ " TEXT," + REPO_MERGES_URL + " TEXT," + REPO_ARCHIVE_URL
				+ " TEXT," + REPO_DOWNLOADS_URL + " TEXT," + REPO_ISSUES_URL
				+ " TEXT," + REPO_PULLS_URL + " TEXT," + REPO_MILESTONES_URL
				+ " TEXT," + REPO_NOTIFICATIONS_URL + " TEXT,"
				+ REPO_LABELS_URL + " TEXT," + REPO_CREATED_AT + " TEXT,"
				+ REPO_UPDATED_AT + " TEXT," + REPO_PUSHED_AT + " TEXT,"
				+ REPO_GIT_URL + " TEXT," + REPO_SSH_URL + " TEXT,"
				+ REPO_CLONE_URL + " TEXT," + REPO_SVN_URL + " TEXT,"
				+ REPO_HOMEPAGE + " TEXT," + REPO_SIZE + " INTEGER,"
				+ REPO_WATCHERS_COUNT + " INTEGER," + REPO_LANGUAGE + " TEXT,"
				+ REPO_HAS_ISSUES + " TEXT," + REPO_HAS_DOWNLOADS + " TEXT,"
				+ REPO_HAS_WIKI + " TEXT," + REPO_FORKS_COUNT + " INTEGER,"
				+ REPO_MIRROR_URL + " TEXT," + REPO_OPEN_ISSUES_COUNT
				+ " INTEGER," + REPO_FORKS + " INTEGER," + REPO_OPEN_ISSUES
				+ " INTEGER," + REPO_WATCHERS + " INTEGER,"
				+ REPO_MASTER_BRANCH + " TEXT," + REPO_DEFAULT_BRANCH
				+ " TEXT," + REPO_PERMISSIONS + " INTEGER" + ")";

		String CREATE_OWNER_TABLE = "CREATE TABLE " + TABLE_OWNERS + "("
				+ OWNER_ID + " INTEGER," + OWNER_LOGIN + " TEXT,"
				+ OWNER_AVATAR_URL + " TEXT," + OWNER_GRAVATAR_ID + " TEXT,"
				+ OWNER_URL + " TEXT," + OWNER_HTML_URL + " TEXT,"
				+ OWNER_FOLLOWERS_URL + " TEXT," + OWNER_FOLLOWING_URL
				+ " TEXT," + OWNER_GISTS_URL + " TEXT," + OWNER_STARRED_URL
				+ " TEXT," + OWNER_SUBSCRIPTIONS_URL + " TEXT,"
				+ OWNER_ORGANIZATIONS_URL + " TEXT," + OWNER_REPOS_URL
				+ " TEXT," + OWNER_EVENTS_URL + " TEXT,"
				+ OWNER_RECEIVED_EVENTS_URL + " TEXT," + OWNER_TYPE + " TEXT"
				+ ")";

		String CREATE_PERMISSIONS_TABLE = "CREATE TABLE " + TABLE_PERMISSIONS + "(" 
				+ REPO_ID + " INTEGER,"+ PERMISSIONS_ADMIN + " TEXT," + PERMISSIONS_PUSH
				+ " TEXT," + PERMISSIONS_PULL + " TEXT" + ")";

		db.execSQL(CREATE_REPOS_TABLE);
		db.execSQL(CREATE_OWNER_TABLE);
		db.execSQL(CREATE_PERMISSIONS_TABLE);
	}

	// Upgrading database
	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion)
	{
		// Drop older table if existed
		db.execSQL("DROP TABLE IF EXISTS " + TABLE_REPOS);
		db.execSQL("DROP TABLE IF EXISTS " + TABLE_OWNERS);
		db.execSQL("DROP TABLE IF EXISTS " + TABLE_PERMISSIONS);

		// Create tables again
		onCreate(db);
	}
	
	public SQLiteDatabase _open()
	{
		return this.getWritableDatabase();
	}
	
	public void _close(SQLiteDatabase db)
	{
		db.close();
	}
	
	public void addRecord(SQLiteDatabase db, int repo_id, String repo_name, String repo_full_name, boolean repo_private, String repo_html_url, String repo_description, boolean repo_fork, String repo_url, String repo_forks_url, String repo_keys_url, String repo_collaborators_url, String repo_teams_url, String repo_hooks_url, String repo_issue_events_url, String repo_events_url, String repo_assignees_url, String repo_branches_url, String repo_tags_url, String repo_blobs_url, String repo_git_tags_url, String repo_git_refs_url, String repo_trees_url, String repo_statuses_url, String repo_languages_url, String repo_stargazers_url, String repo_contributors_url, String repo_subscribers_url, String repo_subscription_url, String repo_commits_url, String repo_git_commits_url, String repo_comments_url, String repo_issue_comment_url, String repo_contents_url, String repo_compare_url, String repo_merges_url, String repo_archive_url, String repo_downloads_url, String repo_issues_url, String repo_pulls_url, String repo_milestones_url, String repo_labels_url, String repo_notifications_url, String repo_created_at, String repo_updated_at, String repo_pushed_at, String repo_git_url, String repo_ssh_url, String repo_clone_url, String repo_svn_url, String repo_homepage, int repo_size, int repo_watchers_count, String repo_language, boolean repo_has_issues, boolean repo_has_downloads, boolean repo_has_wiki, int repo_forks_count, String repo_mirror_url, int repo_open_issues_count, int repo_forks, int repo_open_issues, int repo_watchers, String repo_master_branch, String repo_default_branch,
			String owner_login, int owner_id, String owner_avatar_url, String owner_gravatar_id, String owner_url, String owner_html_url, String owner_followers_url, String owner_following_url, String owner_gists_url, String owner_starred_url, String owner_subscriptions_url, String owner_organizations_url, String owner_repos_url, String owner_events_url, String owner_received_events_url, String owner_type,
			boolean permissions_admin, boolean permissions_push, boolean permissions_pull)
	{
		//SQLiteDatabase db = this.getWritableDatabase();

		ContentValues repo = new ContentValues();
		repo.put(REPO_ID, repo_id); 
		repo.put(REPO_NAME, repo_name);
		repo.put(REPO_FULL_NAME, repo_full_name);
		repo.put(REPO_OWNER, owner_id);
		repo.put(REPO_PRIVATE, repo_private ? "true" : "false");
		repo.put(REPO_HTML_URL, repo_html_url);
		repo.put(REPO_DESCRIPTION, repo_description);
		repo.put(REPO_FORK, repo_fork ? "true" : "false");
		repo.put(REPO_URL, repo_url);
		repo.put(REPO_FORKS_URL, repo_forks_url);
		repo.put(REPO_KEYS_URL, repo_keys_url);
		repo.put(REPO_COLLABORATORS_URL, repo_collaborators_url);
		repo.put(REPO_TEAMS_URL, repo_teams_url);
		repo.put(REPO_HOOKS_URL, repo_hooks_url);
		repo.put(REPO_ISSUE_EVENTS_URL, repo_issue_events_url);
		repo.put(REPO_EVENTS_URL, repo_events_url);
		repo.put(REPO_ASSIGNEES_URL, repo_assignees_url);
		repo.put(REPO_BRANCHES_URL, repo_branches_url);
		repo.put(REPO_TAGS_URL, repo_tags_url);
		repo.put(REPO_BLOBS_URL, repo_blobs_url);
		repo.put(REPO_GIT_TAGS_URL, repo_git_tags_url);
		repo.put(REPO_GIT_REFS_URL, repo_git_refs_url);
		repo.put(REPO_TREES_URL, repo_trees_url);
		repo.put(REPO_STATUSES_URL, repo_statuses_url);
		repo.put(REPO_LANGUAGES_URL, repo_languages_url);
		repo.put(REPO_STARGAZERS_URL, repo_stargazers_url);
		repo.put(REPO_CONTRIBUTORS_URL, repo_contributors_url);
		repo.put(REPO_SUBSCRIBERS_URL, repo_subscribers_url);
		repo.put(REPO_SUBSCRIPTION_URL, repo_subscription_url);
		repo.put(REPO_COMMITS_URL, repo_commits_url);
		repo.put(REPO_GIT_COMMITS_URL, repo_git_commits_url);
		repo.put(REPO_COMMENTS_URL, repo_comments_url);
		repo.put(REPO_ISSUE_COMMENT_URL, repo_issue_comment_url);
		repo.put(REPO_CONTENTS_URL, repo_contents_url);
		repo.put(REPO_COMPARE_URL, repo_compare_url);
		repo.put(REPO_MERGES_URL, repo_merges_url);
		repo.put(REPO_ARCHIVE_URL, repo_archive_url);
		repo.put(REPO_DOWNLOADS_URL, repo_downloads_url);
		repo.put(REPO_ISSUES_URL, repo_issues_url);
		repo.put(REPO_PULLS_URL, repo_pulls_url);
		repo.put(REPO_MILESTONES_URL, repo_milestones_url);
		repo.put(REPO_NOTIFICATIONS_URL, repo_notifications_url);
		repo.put(REPO_LABELS_URL, repo_labels_url);
		repo.put(REPO_CREATED_AT, repo_created_at);
		repo.put(REPO_UPDATED_AT, repo_updated_at);
		repo.put(REPO_PUSHED_AT, repo_pushed_at);
		repo.put(REPO_GIT_URL, repo_git_url);
		repo.put(REPO_SSH_URL, repo_ssh_url);
		repo.put(REPO_CLONE_URL, repo_clone_url);
		repo.put(REPO_SVN_URL, repo_svn_url);
		repo.put(REPO_HOMEPAGE, repo_homepage);
		repo.put(REPO_SIZE, repo_size);
		repo.put(REPO_WATCHERS_COUNT, repo_watchers_count);
		repo.put(REPO_LANGUAGE, repo_language);
		repo.put(REPO_HAS_ISSUES, repo_has_issues);
		repo.put(REPO_HAS_DOWNLOADS, repo_has_downloads);
		repo.put(REPO_HAS_WIKI, repo_has_wiki);
		repo.put(REPO_FORKS_COUNT, repo_forks_count);
		repo.put(REPO_MIRROR_URL, repo_mirror_url);
		repo.put(REPO_OPEN_ISSUES_COUNT, repo_open_issues_count);
		repo.put(REPO_FORKS, repo_forks);
		repo.put(REPO_OPEN_ISSUES, repo_open_issues);
		repo.put(REPO_WATCHERS, repo_watchers);
		repo.put(REPO_MASTER_BRANCH, repo_master_branch);
		repo.put(REPO_DEFAULT_BRANCH, repo_default_branch);
		
		
		ContentValues owner = new ContentValues();
		owner.put(OWNER_ID, owner_id);
		owner.put(OWNER_LOGIN, owner_login);
		owner.put(OWNER_AVATAR_URL, owner_avatar_url);
		owner.put(OWNER_GRAVATAR_ID, owner_gravatar_id);
		owner.put(OWNER_URL, owner_url);
		owner.put(OWNER_HTML_URL, owner_html_url);
		owner.put(OWNER_FOLLOWERS_URL, owner_followers_url);
		owner.put(OWNER_FOLLOWING_URL, owner_following_url);
		owner.put(OWNER_GISTS_URL, owner_gists_url);
		owner.put(OWNER_STARRED_URL, owner_starred_url);
		owner.put(OWNER_SUBSCRIPTIONS_URL, owner_subscriptions_url);
		owner.put(OWNER_ORGANIZATIONS_URL, owner_organizations_url);
		owner.put(OWNER_REPOS_URL, owner_repos_url);
		owner.put(OWNER_EVENTS_URL, owner_events_url);
		owner.put(OWNER_RECEIVED_EVENTS_URL, owner_received_events_url);
		owner.put(OWNER_TYPE, owner_type);
		
		
		ContentValues permissions = new ContentValues();
		permissions.put(PERMISSIONS_ADMIN, permissions_admin);
		permissions.put(PERMISSIONS_PUSH, permissions_push);
		permissions.put(PERMISSIONS_PULL, permissions_pull);
		permissions.put(REPO_ID, repo_id);
		
		
		
		// Inserting Rows
		db.insert(TABLE_REPOS, null, repo);
		db.insert(TABLE_OWNERS, null, owner);
		db.insert(TABLE_PERMISSIONS, null, permissions);
		
		//db.close(); // Closing database connection
	}
	
	public void deleteRecords() 
	{
        SQLiteDatabase db = this.getWritableDatabase();
        
        String deleteQuery1 = "DELETE FROM " + TABLE_REPOS + " WHERE 1";
        String deleteQuery2 = "DELETE FROM " + TABLE_OWNERS + " WHERE 1";
        String deleteQuery3 = "DELETE FROM " + TABLE_PERMISSIONS + " WHERE 1";
        
        db.execSQL(deleteQuery1);
        db.execSQL(deleteQuery2);
        db.execSQL(deleteQuery3);
        
        db.close();
    }

}
