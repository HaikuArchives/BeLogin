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

#include "BLBlocked.h"

/*
* ~BLBlocked();
*
* When the list is deleted, we need to empty the BList of BStrings.
*/
BLBlocked::~BLBlocked()
{
	for(int i=0;i<CountItems();i++)
		delete (BString*)ItemAt(i);
}

/*
* void AddItem(BString* string);
*
* Add the BString to the BList. Since the BList AddItem is a void
* pointer list, the BString has to be converted into such.
* This function is merely a convinience function since the type
* casting could be done at a higher level.
*/
void BLBlocked::AddItem(BString* string)
{
	BList::AddItem((void*)string); 
}

/*
* BString* ItemAt(int index);
*
* Get the BString from the list and cast the void pointer
* into a BString before returning it.
*/
BString* BLBlocked::ItemAt(int index)
{ 
	return (BString*) BList::ItemAt(index); 
}

/*
* bool IsAllowedToRun(const char* signature);
*
* Check each entry in the list for the given signature.
* If there is a mach return true
*/
bool BLBlocked::IsAllowedToRun(const char* signature)
{
	for(int i=0;i<CountItems();i++)
	{
		/* Use Case insensitive search */
		if(ItemAt(i)->ICompare(signature) == 0)
			return true;
	}
	return false;
}

/*
* bool Exists(BString& blocked);
*
* Check each entry in the list for the given string.
* If there is a match return true
*/
bool BLBlocked::Exists(BString& blocked)
{
	for(int i=0;i<CountItems();i++)
	{
		/* Use Case insensitive search */
		if(ItemAt(i)->ICompare(blocked) == 0)
		{	
			return true;
		}
	}
	return false;
}

/*
* bool RemoveBlocked(BString& blocked);
*
* Check each entry in the list for the given string.
* If there is a match delete it.
*/
bool BLBlocked::RemoveBlocked(BString& blocked)
{
	for(int i=0;i<CountItems();i++)
	{
		/* Use Case insensitive search */
		if(ItemAt(i)->ICompare(blocked) == 0)
		{	
			delete (BString*) RemoveItem(i);
			modified = true;
			return true;
		}
	}
	return false;
}

bool BLBlocked::HasBeenModified(bool hmod)
{
 if(hmod == true) 
 	modified = true;
 
 return modified;
}