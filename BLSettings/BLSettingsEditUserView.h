/*
*
* -=BLSettingsAddUserView=-
* This is the Edit user View
*
* Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
* This software and its sourcecode is covered by the "Gnu General Public License". 
*
*/

#ifndef BLSETTINGSEDITUSERVIEW_H
#define BLSETTINGSEDITUSERVIEW_H

#include <View.h>
#include <Window.h>
#include <Messenger.h>
#include <Alert.h>
#include <Button.h>
#include <TextControl.h>

#include "../BLShared/BLDefines.h"
#include "BLSettings.h"

class BLSettingsEditUserView : public BView
{
public:
	BLSettingsEditUserView(BRect canvas, BLSettings* bls, BString* user);
	~BLSettingsEditUserView();	
	void MessageReceived(BMessage* Msg);
	void AttachedToWindow();
private:
	BLSettings* Settings;
	BButton* btnCancel;
	BButton* btnOk;
	BTextControl* txtUsername;
	BTextControl* txtOldPassword;
	BTextControl* txtPassword;
	BTextControl* txtConfirmedPassword;
	BString* Username;
};

#endif	