/*
*
* -=BLUsers=-
* This class is simply a collection of all the users.
*
* Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
* This software and its sourcecode is covered by the "Gnu General Public License". 
*
*/

#ifndef BLUSERS_H
#define BLUSERS_H

#include <List.h>
#include "BLUser.h"
#include "../BLShared/BLDefines.h"

class BLUsers : public BList
{
public:
	~BLUsers();
	void AddItem(BLUser* User);
	BLUser* ItemAt(int index);
	bool IsValid(BString& Username, BString& Password);
	bool IsAdministrator(BString& Username, BString& Password);
	bool RemoveUser(BString username);
	bool UserExists(BString username, bool casesensitive = false);
	BLUser* GetUser(BString username);
	bool HasBeenModified();
private:
	bool modified;
};
#endif