/*
 *
 * -=BLSettings=-
 * This class is the base settings class of BeLogin.
 * The key to the settings class is the BMessage's Flatten and Unflatten
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#ifndef BLSETTINGS_H
#define BLSETTINGS_H

#include <Message.h>
#include <Path.h>
#include <File.h>
#include <Beep.h>
#include <Entry.h>
#include "BLUsers.h"
#include "BLRunnable.h"
#include "BLBlocked.h"
#include "../BLShared/BLDefines.h"

//for MD5 algorithm
#include "../BLShared/md5.h"
#include <stdio.h>

class BLSettings : public BMessage
{
public:
	BLSettings(BPath path);
	~BLSettings();
  
	status_t Load();
	status_t Save();
	inline BLRunnable* 	GetRunnable() 	{ return this->Runnable; };
	inline BLBlocked* 	GetBlocked() 	{ return this->Blocked; };
	inline BLUsers* 		GetUsers() 		{ return this->Users; };
	inline BString&		GetLastUser()	{ return this->LastUser; };
	inline void				SetLastUser(BString& String) { this->LastUser = String; }; 
	bool HasBeenModified();
	
	char* MD5Hash(BString string);
	
private:
	const BString EnCrypt(BString&);
	const BString DeCrypt(BString&);
		
	BPath Path;
	BFile* File;
	BString LastUser;
	BLUsers* Users;
	BLRunnable* Runnable;
	BLBlocked* Blocked;
};
#endif