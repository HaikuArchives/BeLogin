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

#include "BLSettings.h"

/*
 * BLSettings(BPath path);
 *
 * Create a BLSettings object with the given path
 */
BLSettings::BLSettings(BPath path)
: LastUser(NULL), Users(NULL), Runnable(NULL), Blocked(NULL)
{
	File = new BFile();
	Path = path;
	Users = new BLUsers();
	Runnable = new BLRunnable();
	Blocked = new BLBlocked();
	
	add_system_beep_event(VALID_SYSTEM_BEEP);
	add_system_beep_event(INVALID_SYSTEM_BEEP);
}

/*
 * ~BLSettings();
 *  
 * When the BLSettings is deleted, all it's arrays needs to be deleted.
 * There is no need to empty them, since they clean themselves.
 */
BLSettings::~BLSettings()
{
	if(File != NULL)
		delete File;

	if(Users != NULL)
		delete Users;

	if(Runnable != NULL)
		delete Runnable;

	if(Blocked != NULL)
		delete Blocked;
}

/*
 * bool Load();
 *
 * Load the settings from the file.
 */
status_t BLSettings::Load()
{
	/*
	 * Load settings:
	 * 1. Version 	(String)
	 * 2. Users		(Array)
	 * 3. Runnable	(Array)
	 * 4. Blocked	(Array)
	 */

	/* Open the file */
	BEntry entry(Path.Path());
	
	File->SetTo(&entry, B_READ_ONLY);
	
	if(File->InitCheck() != B_OK)
		return BL_LOAD_ERROR;
	
	/* Unflatten from the file */
	if(Unflatten(File) != B_OK)
		return BL_LOAD_ERROR;
	
	/* Check the version */
	BString Version;
	if(FindString("Version", &Version) != B_OK)
		return BL_LOAD_ERROR;

	/* Needed for GetInfo */
	type_code typecode;
	int32 count = 0;

	/* Read the users */
	/* Get number of users */
	if(GetInfo("Username", &typecode, &count) == B_OK)
	{ 
		/* load each user */
		for(int ui=0;ui<count;ui++)
		{
			BString Username;
			BString Password;

			if(FindString("Username", ui, &Username) != B_OK)
				return BL_LOAD_ERROR;

			if(FindString("Password", ui, &Password) != B_OK)
				return BL_LOAD_ERROR;

			BLUser* user = new BLUser(DeCrypt(Username), DeCrypt(Password));
			Users->AddItem(user);
		}
	}

	/* Read Runnable */
	count = 0;
	
	/* Get number of runnables */
	if(GetInfo("Runnable", &typecode, &count) == B_OK)
	{ 
		/* load each runnable */
		for(int ri=0;ri<count;ri++)
		{
			BString runnable;

			if(FindString("Runnable", ri, &runnable) != B_OK)
				return BL_LOAD_ERROR;
			Runnable->AddItem(new BString(DeCrypt(runnable)));
		}
	}

	/* Read Blocked */
	count = 0;
	
	/* Get number of Blocked */
	if(GetInfo("Blocked", &typecode, &count) == B_OK)
	{ 
		/* load each blocked */
		for(int bi=0;bi<count;bi++)
		{
			BString blocked;

			if(FindString("Blocked", bi, &blocked) != B_OK)
				return BL_LOAD_ERROR;
			Blocked->AddItem(new BString(DeCrypt(blocked)));
		}
	}
		
	/* Read the last user */
	if(FindString("LastUser", &LastUser) != B_OK)
		return BL_LOAD_ERROR;

	LastUser = DeCrypt(LastUser);

	File->Unset();

	return B_OK;
}

/*
 * bool Save();
 *
 * Save the settings to the file.
 */
status_t BLSettings::Save()
{
	MakeEmpty();
	/* Open the file */
	BEntry entry(Path.Path());
	File->SetTo(&entry, B_WRITE_ONLY | B_CREATE_FILE | B_ERASE_FILE);

	if(File->InitCheck() != B_OK)
		return BL_SAVE_ERROR;

	/*
	 * Save settings:
	 * 1. Version 	(String)
	 * 2. Users		(Array)
	 * 3. Runnable	(Array)
	 * 4. Blocked	(Array)
	 */
	
	/* Add the version*/	
	AddString("Version", VERSION);
	
	/* Add each User */
	for(int ui=0;ui<Users->CountItems();ui++)
	{	
		BLUser* User = Users->ItemAt(ui);
		AddString("Username", EnCrypt(User->GetUsername()));
		AddString("Password", EnCrypt(User->GetPassword()));
	}
	
	/* Add each Runnable */
	for(int ri=0;ri<Runnable->CountItems();ri++)
	{
		AddString("Runnable", EnCrypt(*((BString*)Runnable->ItemAt(ri))));
	} 	

	/* Add each Blocked */
	for(int bi=0;bi<Blocked->CountItems();bi++)
	{
		AddString("Blocked", EnCrypt(*((BString*)Blocked->ItemAt(bi))));
	}
	
	AddString("LastUser", EnCrypt(LastUser));
	
	/* Flatten me (BMessage)*/
	if(Flatten(File) != B_OK)
		return BL_SAVE_ERROR;

	File->Unset();
	
	return B_OK;
}

/*
 * const BString& EnCrypt(BString& String);
 *
 * Encrypt a string - this is just a simple encryption.
 * Need better encryption that also allows regeneration...
 */
const BString BLSettings::EnCrypt(BString& String)
{
	BString Key = "#%)&%.-q2 ½";
	BString Temp;
	int x, ch;
	int y = 0;

    for (x=0;x<String.Length();x++) 
	{
		if (y<(Key.Length()-1))
			y++;
		else
			y=0;
		
		ch = String[x]; //aquire character
		ch = ch^Key[y]; //XOR with key
		ch = ~ch;		 //NOT 
	   
		Temp += ch;		 //add to string
	}
	return Temp;
}

/*
 * char* MD5Hash(BString string);
 *
 * MD5 encryption rutine, taken from Nathan Whitehorns
 * multiuser implementation, slighty modified. Only used to
 * store the password.
 */
char* BLSettings::MD5Hash(BString string) {
	//acquire char buffer from string
	char* password = string.LockBuffer(string.Length());
    string.UnlockBuffer();

	//prepare for MD5 Hashing	
	MD5Context context;
	unsigned char digest[16];
	static char hex_digest[33];

	//do hashing
	MD5Init(&context);		
	MD5Update(&context, (uint8*) password, strlen(password));
	MD5Final(digest, &context);
	
	//copy to buffer
	for (int index = 0; index < 16; index++) {
        sprintf(&(hex_digest[index*2]), "%02X", digest[index] & 255);
    }

	return hex_digest;
}

/*
 * const BString& DeCrypt(BString& String);
 *
 * Decrypt a string, doesn't do much yet...
 */
const BString BLSettings::DeCrypt(BString& String)
{
	return EnCrypt(String);
}

/*
 * bool HasBeenModified();
 *
 * 
 */
bool BLSettings::HasBeenModified()
{
	if(Users->HasBeenModified() == true)
		return true;
	
	if(Runnable->HasBeenModified() == true)
		return true;

	if(Blocked->HasBeenModified() == true)
		return true;
	
	return false;
}