/*
*
* -=BLSettingsAboutWindow=-
* This is the Settings About window
*
* Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
* This software and its sourcecode is covered by the "Gnu General Public License". 
*
*/

#ifndef BLSETTINGSABOUTWINDOW_H
#define BLSETTINGSABOUTWINDOW_H

#include <Window.h>
#include <Message.h>
#include "../BLShared/BLDefines.h"
#include "BLSettingsAboutView.h"

class BLSettingsAboutWindow : public BWindow
{
public:
	BLSettingsAboutWindow(BRect);
	void MessageReceived(BMessage* Msg);
private:
	BLSettingsAboutView*	View;
};

#endif