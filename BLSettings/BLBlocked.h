/*
*
* -=BLBlocked=-
* This class is a collection of all the programs which should be blocked
* from running. The programs are represented as BStrings and can be either
* app signatures of paths.
*
* Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
* This software and its sourcecode is covered by the "Gnu General Public License". 
*
*/

#ifndef BLBLOCKED_H
#define BLBLOCKED_H

#include "../BLShared/BLDefines.h"
#include <List.h>

class BLBlocked : public BList
{
public:
	~BLBlocked();
	void AddItem(BString* string);
	BString* ItemAt(int index);
	bool IsAllowedToRun(const char* signature);
	bool Exists(BString& blocked);
	bool RemoveBlocked(BString& blocked);
	bool HasBeenModified(bool hmod = false);
private:
	bool modified;
};
#endif