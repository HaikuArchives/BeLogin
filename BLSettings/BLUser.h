/*
 *
 * -=BLUser=-
 * The class that represents a user. The user has a Username and Password.
 * The user also has a boolean, which is set to true if it is an administrator.
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#ifndef BLUSER_H
#define BLUSER_H

#include "../BLShared/BLDefines.h"

class BLUser
{
public:
  BLUser(BString NewUsername, BString NewPassword);
  ~BLUser();
	
	inline BString& 	GetUsername()										{ return Username; };
	inline void    	SetUsername(BString NewUsername) 			{ this->Username = NewUsername; modified = true; };
	
	inline BString& 	GetPassword()                 				{ return Password; };
	inline void    	SetPassword(BString NewPassword) 			{ this->Password = NewPassword; modified = true; };
	
	inline bool    	IsAdministrator()             				{ return this->Username.Compare("Administrator") == 0; };
	inline bool 		HasBeenModified() 								{ return modified; };
	inline void			HasBeenModified(bool mod)						{ this->modified = mod; };
private:
	BString Username;
	BString Password;
	bool modified;
};

#endif