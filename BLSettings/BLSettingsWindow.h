/*
*
* -=BLSettingsWindow=-
* This is the main window, which is shown upon a login
*
* Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
* This software and its sourcecode is covered by the "Gnu General Public License". 
*
*/

#ifndef BLSETTINGSWINDOW_H
#define BLSETTINGSWINDOW_H

#include <Box.h>
#include <TabView.h>
#include <Alert.h>
#include <Button.h>
#include <Application.h>
#include <Screen.h>
#include "../BLShared/BLDefines.h"
#include "BLSettings.h"
#include "BLSettingsAboutWindow.h"
#include "BLSettingsUserView.h"
#include "BLSettingsBlockedView.h"
#include "BLSettingsRunnableView.h"

class BLSettingsWindow : public BWindow
{
public:
	BLSettingsWindow(BRect frame, BLSettings* bls);
	~BLSettingsWindow();
	bool QuitRequested();
	void MessageReceived(BMessage* Msg);

private:
	BLSettings* Settings;
	BLSettingsAboutWindow* AboutWindow;
	BBox *Box;	
	BTabView* TabView;
	BLSettingsUserView* UserView;
	BLSettingsBlockedView* BlockedView;
	BLSettingsRunnableView* RunnableView;
};

#endif
