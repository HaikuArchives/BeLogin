/*
*
* -=BLSettingsUserView=-
* This is the user view.  
*
* Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
* This software and its sourcecode is covered by the "Gnu General Public License". 
*
*/

#ifndef BLSETTINGSUSERVIEW_H
#define BLSETTINGSUSERVIEW_H

#include "../BLShared/BLDefines.h"
#include "BLSettings.h"
#include "BLSettingsAddUserWindow.h"
#include "BLSettingsEditUserWindow.h"

class BLSettingsUserView : public BView
{
public:
	BLSettingsUserView(BRect canvas, BLSettings* bls);
	~BLSettingsUserView();
	void AttachedToWindow();
	void MessageReceived(BMessage* Msg);
private:
	BLSettings* Settings;
	BListView* ListView;
	BButton* btnAdd;
	BButton* btnEdit;
	BButton* btnDelete;
	BLSettingsAddUserWindow* AddUserWindow;
	BLSettingsEditUserWindow* EditUserWindow;
};

#endif