/*
 *
 * -=BLUser=-
 * The class that represents a user. The user has a Username and Password.
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#include "BLUser.h"

/*
 * BLUser(BString Username, BString Password, bool Administrator);
 *
 * Create a BLUser from the given parameters.
 */
BLUser::BLUser(BString NewUsername, BString NewPassword)
: Username(NewUsername), Password(NewPassword)
{}

/*
 * ~BLUser();
 *
 * Do whatever needs to be done in the destructor.
 * Nothing is done currently. 
 */
BLUser::~BLUser()
{ }