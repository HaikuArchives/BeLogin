/*
 *
 * -=BLSettingsLoginWindow=-
 * This is the Login window.
 * It is needed to validate an user.
 * 
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#ifndef BLSETTINGSLOGINWINDOW_H
#define BLSETTINGSLOGINWINDOW_H

#include <Screen.h>
#include <Application.h>
#include <Beep.h>
#include "../BLShared/BLDefines.h"
#include "BLSettings.h"
#include "BLSettingsLoginView.h"
#include "BLSettingsAboutWindow.h"

class BLSettingsLoginWindow : public BWindow
{
public:
	BLSettingsLoginWindow(BRect frame, BLSettings* bls);
	~BLSettingsLoginWindow();
	bool QuitRequested();
	void MessageReceived(BMessage* Msg);

private:
	BLSettings* Settings;
	BLSettingsAboutWindow* AboutWindow;
	BLSettingsLoginView* View;
};

#endif
