/*
 *
 * -=BLLoginWindow=-
 * This is the Main window. It contains the Login view too.
 * The main window adds a menubar to the top. All BMessages go through
 * this window.
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#ifndef BLLOGINWINDOW_H
#define BLLOGINWINDOW_H

#include <MenuBar.h>
#include <Menu.h>
#include <MenuItem.h>
#include <Roster.h>
#include <unistd.h>
#include <MessageRunner.h>

#include "../BLShared/BLDefines.h"
#include "../BLSettings/BLSettings.h"
#include "BLLoginView.h"
#include "BLAboutWindow.h"

class BLLoginWindow : public BWindow
{
public:
	BLLoginWindow(BRect frame, BLSettings* bls);
	~BLLoginWindow();
	bool QuitRequested();
	void MessageReceived(BMessage* Msg);
	void ApplicationLaunch(BMessage* Msg);
	void TerminateApplications();

private:
	BLSettings* Settings;
	BLLoginView* View;
	BMenuBar* MenuBar;
	BLAboutWindow* AboutWindow;
	BMessageRunner * Runner;
	bool Exiting;
	int Attempts;
};

#endif
