/*
 *
 * -=BLSettingsEditUserWindow=-
 * This is the window for the Edit user view
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#ifndef BLSETTINGSEDITUSERWINDOW_H
#define BLSETTINGSEDITUSERWINDOW_H

#include "../BLShared/BLDefines.h"
#include "BLSettings.h"

#include "BLSettingsEditUserView.h"

class BLSettingsEditUserWindow : public BWindow
{
public:
	BLSettingsEditUserWindow(BRect, BLSettings* bls, BHandler* phandler, BString* user);
	~BLSettingsEditUserWindow();
	void MessageReceived(BMessage* Msg);
private:
	BLSettingsEditUserView*	View;
	BLSettings* Settings;
	BHandler* ParentHandler;
	BString Username;
};

#endif