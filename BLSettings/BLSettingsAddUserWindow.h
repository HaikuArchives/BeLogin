/*
*
* -=BLSettingsAddUserWindow=-
* This is the window for the Add user view
*
* Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
* This software and its sourcecode is covered by the "Gnu General Public License". 
*
*/

#ifndef BLSETTINGSADDUSERWINDOW_H
#define BLSETTINGSADDUSERWINDOW_H

#include "../BLShared/BLDefines.h"
#include "BLSettingsAddUserView.h"

class BLSettingsAddUserWindow : public BWindow
{
public:
	BLSettingsAddUserWindow(BRect, BLSettings* bls, BHandler* phandler);
	~BLSettingsAddUserWindow();
	void MessageReceived(BMessage* Msg);
private:
	BLSettingsAddUserView*	View;
	BLSettings* Settings;
	BHandler* ParentHandler;
};

#endif