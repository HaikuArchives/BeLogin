/*
 *
 * -=BLUsers=-
 * This class is simply a collection of all the users.
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#include "BLUsers.h"

/*
 * ~BLUsers();
 *
 * When the list is deleted, we need to empty the BList of users.
 */
BLUsers::~BLUsers()
{
	for(int i=0;i<CountItems();i++)
		delete ItemAt(i);
}

/*
 * void AddItem(BLUser* User);
 *
 * Add the BLUser to the BList. Since the BList AddItem is a void
 * pointer list, the BLUser has to be converted into such.
 * This function is merely a convinience function since the type
 * casting could be done at a higher level.
 */
void BLUsers::AddItem(BLUser* User)
{
	BList::AddItem((void*)User); 
}

/*
 * BLUser* ItemAt(int index);
 *
 * Get the BLUser from the list and cast the void pointer
 * into a BLUser before returning it.
 */
BLUser* BLUsers::ItemAt(int index)
{
	return (BLUser*)BList::ItemAt(index); 
}

/*
 * bool IsValid(BString* Username, BString* Password);
 *
 * Check the list for an user with the given username/password
 */
bool BLUsers::IsValid(BString& Username, BString& Password)
{
	for(int i=0;i<CountItems();i++)
	{
		BLUser* user = ItemAt(i);
		if(user->GetUsername().Compare(Username) == 0 && user->GetPassword().Compare(Password) == 0)
			return true;
	}
	return false;	
}

/*
 * bool IsAdministrator(BString* Username, BString* Password);
 *
 * Check the list for an administrator with the given username/password
 */
bool BLUsers::IsAdministrator(BString& Username, BString& Password)
{
	for(int i=0;i<CountItems();i++)
	{
		BLUser* user = ItemAt(i);
		if(user->IsAdministrator() == true && user->GetPassword().Compare(Password) == 0 && user->GetUsername().Compare(Username) == 0)
			return true;
	}
	return false;	
}

/*
 * bool RemoveUser(BString username);
 *
 * Remove the user with given username
 */
bool BLUsers::RemoveUser(BString username)
{
	for(int i=0;i<CountItems();i++)
	{
		BLUser* user = ItemAt(i);
		if(user->GetUsername().Compare(username) == 0)
		{
			delete (BLUser*) RemoveItem(i);
			modified = true;
			return true;
		}
	}
	return false;	
}

/*
 * bool UserExists(BString username);
 *
 * Find the user with given username
 */
bool BLUsers::UserExists(BString username, bool casesensitive)
{
	for(int i=0;i<CountItems();i++)
	{
		BLUser* user = ItemAt(i);
		if(casesensitive)
		{
			if(user->GetUsername().ICompare(username) == 0)
			{
				return true;
			}
		}
		else
		{
			if(user->GetUsername().Compare(username) == 0)
			{
				return true;
			}
		}
	}
	return false;	
}

/*
 * bool GetUser(BString username);
 *
 * Retreive the user with given username
 */
BLUser* BLUsers::GetUser(BString username)
{
	for(int i=0;i<CountItems();i++)
	{
		BLUser* user = ItemAt(i);
		if(user->GetUsername().Compare(username) == 0)
		{
			return user;
		}
	}
	return NULL;	
}

/*
 * bool HasBeenModified(bool hmod);
 *
 * Retrieve a bool indicating whether or not modifications has occurred
 * or set modified if supplied with a true argument
 */
bool BLUsers::HasBeenModified()
{
	if(modified == true)
		return true;

	for(int i=0;i<CountItems();i++)
	{
		BLUser* user = ItemAt(i);
		if(user->HasBeenModified() == true)
		{
			return true;
		}
	}
	return false;
}