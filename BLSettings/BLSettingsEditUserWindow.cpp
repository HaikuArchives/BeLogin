/*
 *
 * -=BLSettingsEditUserWindow=-
 * This is the window for the Edit user view
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#include "BLSettingsEditUserWindow.h"

/*
 * BLSettingsEditUserWindow(BRect frame, BLSettings* bls, BHandler* phandler, BString* user);
 *
 * The constructor of the window adds the child to the view chain
 */
BLSettingsEditUserWindow::BLSettingsEditUserWindow(BRect frame, BLSettings* bls, BHandler* phandler, BString* user)
: BWindow(frame, SETTINGS_TITLE_EDITUSERWINDOW, B_TITLED_WINDOW_LOOK, B_MODAL_APP_WINDOW_FEEL, B_NOT_RESIZABLE | B_NOT_ZOOMABLE | B_NOT_MINIMIZABLE | B_NOT_CLOSABLE), Settings(bls), ParentHandler(phandler)
{
	Username = *user;
	frame.OffsetTo(B_ORIGIN);
	Lock();
	View = new BLSettingsEditUserView(frame, Settings, &Username);
	AddChild(View);
	Unlock();
}

/*
 * ~BLSettingsEditUserWindow();
 *
 * Currently void
 */
BLSettingsEditUserWindow::~BLSettingsEditUserWindow()
{
}

/*
 * void MessageReceived(BMessage* Msg);
 *
 */
void BLSettingsEditUserWindow::MessageReceived(BMessage* Msg)
{
	switch(Msg->what)
	{
		case BL_USER_UPDATE:
		{
			BMessenger messenger(ParentHandler);
			messenger.SendMessage(BL_USER_UPDATE);
		}
		default:
		{
			/* If we're not going to use the message, send it along to the base class */
			BWindow::MessageReceived(Msg);
		}
	}
}