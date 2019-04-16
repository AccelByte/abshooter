#pragma once

/** profile achievement display information */
struct FAchievementEntry
{
	/** achievement id*/
	FString AchievementId;

	/** achievement name*/
	FString Name;

	/** achievement image URL*/
	FString ImageURL;

	/** achievement owned flag*/
	bool Achieved = false;

};
