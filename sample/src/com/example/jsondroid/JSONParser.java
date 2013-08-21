package com.example.jsondroid;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.util.Log;

public class JSONParser
{
	static JSONArray repos = null;

	public static void ParseJSON(Context ctx, String str)
	{
		JSONArray repos = null;
		try
		{
			repos = new JSONArray(str);
		}
		catch (JSONException e)
		{
			Log.e("JSON Parser", "Error parsing data " + e.toString());
		}

		RelationalHandler handler = new RelationalHandler(ctx);
		SQLiteDatabase db = handler._open();
		db.beginTransaction();
		
		try
		{
			// looping through All repos
			for (int i = 0; i < repos.length(); i++)
			{
				JSONObject repo = repos.getJSONObject(i);

				// Storing each json item in variable
				int repo_id = repo.getInt(RelationalHandler.REPO_ID);
				String repo_name = repo.getString(RelationalHandler.REPO_NAME);
				String repo_full_name = repo.getString(RelationalHandler.REPO_FULL_NAME);
				boolean repo_private = repo.getBoolean(RelationalHandler.REPO_PRIVATE);
				String repo_html_url = repo.getString(RelationalHandler.REPO_HTML_URL);
				String repo_description = repo.getString(RelationalHandler.REPO_DESCRIPTION);
				boolean repo_fork = repo.getBoolean(RelationalHandler.REPO_FORK);
				String repo_url = repo.getString(RelationalHandler.REPO_URL);
				String repo_forks_url = repo.getString(RelationalHandler.REPO_FORKS_URL);
				String repo_keys_url = repo.getString(RelationalHandler.REPO_KEYS_URL);
				String repo_collaborators_url = repo.getString(RelationalHandler.REPO_COLLABORATORS_URL);
				String repo_teams_url = repo.getString(RelationalHandler.REPO_TEAMS_URL);
				String repo_hooks_url = repo.getString(RelationalHandler.REPO_HOOKS_URL);
				String repo_issue_events_url = repo.getString(RelationalHandler.REPO_ISSUE_EVENTS_URL);
				String repo_events_url = repo.getString(RelationalHandler.REPO_EVENTS_URL);
				String repo_assignees_url = repo.getString(RelationalHandler.REPO_ASSIGNEES_URL);
				String repo_branches_url = repo.getString(RelationalHandler.REPO_BRANCHES_URL);
				String repo_tags_url = repo.getString(RelationalHandler.REPO_TAGS_URL);
				String repo_blobs_url = repo.getString(RelationalHandler.REPO_BLOBS_URL);
				String repo_git_tags_url = repo.getString(RelationalHandler.REPO_GIT_TAGS_URL);
				String repo_git_refs_url = repo.getString(RelationalHandler.REPO_GIT_REFS_URL);
				String repo_trees_url = repo.getString(RelationalHandler.REPO_TREES_URL);
				String repo_statuses_url = repo.getString(RelationalHandler.REPO_STATUSES_URL);
				String repo_languages_url = repo.getString(RelationalHandler.REPO_LANGUAGES_URL);
				String repo_stargazers_url = repo.getString(RelationalHandler.REPO_STARGAZERS_URL);
				String repo_contributors_url = repo.getString(RelationalHandler.REPO_CONTRIBUTORS_URL);
				String repo_subscribers_url = repo.getString(RelationalHandler.REPO_SUBSCRIBERS_URL);
				String repo_subscription_url = repo.getString(RelationalHandler.REPO_SUBSCRIPTION_URL);
				String repo_commits_url = repo.getString(RelationalHandler.REPO_COMMITS_URL);
				String repo_git_commits_url = repo.getString(RelationalHandler.REPO_GIT_COMMITS_URL);
				String repo_comments_url = repo.getString(RelationalHandler.REPO_COMMENTS_URL);
				String repo_issue_comment_url = repo.getString(RelationalHandler.REPO_ISSUE_COMMENT_URL);
				String repo_contents_url = repo.getString(RelationalHandler.REPO_CONTENTS_URL);
				String repo_compare_url = repo.getString(RelationalHandler.REPO_COMPARE_URL);
				String repo_merges_url = repo.getString(RelationalHandler.REPO_MERGES_URL);
				String repo_archive_url = repo.getString(RelationalHandler.REPO_ARCHIVE_URL);
				String repo_downloads_url = repo.getString(RelationalHandler.REPO_DOWNLOADS_URL);
				String repo_issues_url = repo.getString(RelationalHandler.REPO_ISSUES_URL);
				String repo_pulls_url = repo.getString(RelationalHandler.REPO_PULLS_URL);
				String repo_milestones_url = repo.getString(RelationalHandler.REPO_MILESTONES_URL);
				String repo_notifications_url = repo.getString(RelationalHandler.REPO_NOTIFICATIONS_URL);
				String repo_labels_url = repo.getString(RelationalHandler.REPO_LABELS_URL);
				String repo_created_at = repo.getString(RelationalHandler.REPO_CREATED_AT);
				String repo_updated_at = repo.getString(RelationalHandler.REPO_UPDATED_AT);
				String repo_pushed_at = repo.getString(RelationalHandler.REPO_PUSHED_AT);
				String repo_git_url = repo.getString(RelationalHandler.REPO_GIT_URL);
				String repo_ssh_url = repo.getString(RelationalHandler.REPO_SSH_URL);
				String repo_clone_url = repo.getString(RelationalHandler.REPO_CLONE_URL);
				String repo_svn_url = repo.getString(RelationalHandler.REPO_SVN_URL);
				String repo_homepage = repo.getString(RelationalHandler.REPO_HOMEPAGE);
				int repo_size = repo.getInt(RelationalHandler.REPO_SIZE);
				int repo_watchers_count = repo.getInt(RelationalHandler.REPO_WATCHERS_COUNT);
				String repo_language = repo.getString(RelationalHandler.REPO_LANGUAGE);
				boolean repo_has_issues = repo.getBoolean(RelationalHandler.REPO_HAS_ISSUES);
				boolean repo_has_downloads = repo.getBoolean(RelationalHandler.REPO_HAS_DOWNLOADS);
				boolean repo_has_wiki = repo.getBoolean(RelationalHandler.REPO_HAS_WIKI);
				int repo_forks_count = repo.getInt(RelationalHandler.REPO_FORKS_COUNT);
				String repo_mirror_url = repo.getString(RelationalHandler.REPO_MIRROR_URL);
				int repo_open_issues_count = repo.getInt(RelationalHandler.REPO_OPEN_ISSUES_COUNT);
				int repo_forks = repo.getInt(RelationalHandler.REPO_FORKS);
				int repo_open_issues = repo.getInt(RelationalHandler.REPO_OPEN_ISSUES);
				int repo_watchers = repo.getInt(RelationalHandler.REPO_WATCHERS);
				String repo_master_branch = repo.getString(RelationalHandler.REPO_MASTER_BRANCH);
				String repo_default_branch = repo.getString(RelationalHandler.REPO_DEFAULT_BRANCH);
								
				
				// Permissions
				JSONObject permissions = repo.getJSONObject(RelationalHandler.REPO_PERMISSIONS);
				boolean permissions_admin = permissions.getBoolean(RelationalHandler.PERMISSIONS_ADMIN);
				boolean permissions_push = permissions.getBoolean(RelationalHandler.PERMISSIONS_PUSH);
				boolean permissions_pull = permissions.getBoolean(RelationalHandler.PERMISSIONS_PULL);
				
				
				// Owner
				JSONObject owner = repo.getJSONObject(RelationalHandler.REPO_OWNER);
				String owner_login = owner.getString(RelationalHandler.OWNER_LOGIN);
				int owner_id = owner.getInt(RelationalHandler.OWNER_ID);
				String owner_avatar_url = owner.getString(RelationalHandler.OWNER_AVATAR_URL);
				String owner_gravatar_id = owner.getString(RelationalHandler.OWNER_GRAVATAR_ID);
				String owner_url = owner.getString(RelationalHandler.OWNER_URL);
				String owner_html_url = owner.getString(RelationalHandler.OWNER_HTML_URL);
				String owner_followers_url = owner.getString(RelationalHandler.OWNER_FOLLOWERS_URL);
				String owner_following_url = owner.getString(RelationalHandler.OWNER_FOLLOWING_URL);
				String owner_gists_url = owner.getString(RelationalHandler.OWNER_GISTS_URL);
				String owner_starred_url = owner.getString(RelationalHandler.OWNER_STARRED_URL);
				String owner_subscriptions_url = owner.getString(RelationalHandler.OWNER_SUBSCRIPTIONS_URL);
				String owner_organizations_url = owner.getString(RelationalHandler.OWNER_ORGANIZATIONS_URL);
				String owner_repos_url = owner.getString(RelationalHandler.OWNER_REPOS_URL);
				String owner_events_url = owner.getString(RelationalHandler.OWNER_EVENTS_URL);
				String owner_received_events_url = owner.getString(RelationalHandler.OWNER_RECEIVED_EVENTS_URL);
				String owner_type = owner.getString(RelationalHandler.OWNER_TYPE);
	
				
				handler.addRecord(db, repo_id, repo_name, repo_full_name, repo_private, repo_html_url, repo_description, repo_fork, repo_url, repo_forks_url, repo_keys_url, repo_collaborators_url, repo_teams_url, repo_hooks_url, repo_issue_events_url, repo_events_url, repo_assignees_url, repo_branches_url, repo_tags_url, repo_blobs_url, repo_git_tags_url, repo_git_refs_url, repo_trees_url, repo_statuses_url, repo_languages_url, repo_stargazers_url, repo_contributors_url, repo_subscribers_url, repo_subscription_url, repo_commits_url, repo_git_commits_url, repo_comments_url, repo_issue_comment_url, repo_contents_url, repo_compare_url, repo_merges_url, repo_archive_url, repo_downloads_url, repo_issues_url, repo_pulls_url, repo_milestones_url, repo_labels_url, repo_notifications_url, repo_created_at, repo_updated_at, repo_pushed_at, repo_git_url, repo_ssh_url, repo_clone_url, repo_svn_url, repo_homepage, repo_size, repo_watchers_count, repo_language, repo_has_issues, repo_has_downloads, repo_has_wiki, repo_forks_count, repo_mirror_url, repo_open_issues_count, repo_forks, repo_open_issues, repo_watchers, repo_master_branch, repo_default_branch, owner_login, owner_id, owner_avatar_url, owner_gravatar_id, owner_url, owner_html_url, owner_followers_url, owner_following_url, owner_gists_url, owner_starred_url, owner_subscriptions_url, owner_organizations_url, owner_repos_url, owner_events_url, owner_received_events_url, owner_type, permissions_admin, permissions_push, permissions_pull);
			}
		}
		catch (JSONException e)
		{
			e.printStackTrace();
		}
		
		db.endTransaction();
		handler._close(db);
		
		handler.close();
	}
}
