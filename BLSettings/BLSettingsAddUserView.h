/*
 *
 * -=BLSettingsAddUserView=-
 * This is the Add user View
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#ifndef BLSETTINGSADDUSERVIEW_H
#define BLSETTINGSADDUSERVIEW_H

#include <View.h>
#include <Window.h>
#include <ListView.h>
#include <Rect.h>
#include <ScrollView.h>
#include <Button.h>
#include <Screen.h>
#include <Alert.h>
#include <TextControl.h>
#include "../BLShared/BLDefines.h"
#include "BLSettings.h"

class BLSettingsAddUserView : public BView
{
public:
	BLSettingsAddUserView(BRect canvas, BLSettings* bls);
	~BLSettingsAddUserView();	
	void MessageReceived(BMessage* Msg);
	void AttachedToWindow();
private:
	BLSettings* Settings;
	BButton* btnCancel;
	BButton* btnOk;
	BTextControl* txtUsername;
	BTextControl* txtPassword;
	BTextControl* txtConfirmedPassword;
};

#endif	