/*
 *
 * -=BLSettingsAddUserWindow=-
 * This is the window for the Add user view
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#include "BLSettingsAddUserWindow.h"

/*
 * BLSettingsAddUserWindow(BRect frame, BLSettings* bls);
 *
 * The constructor of the window adds the child to the view chain
 */
BLSettingsAddUserWindow::BLSettingsAddUserWindow(BRect frame, BLSettings* bls, BHandler* phandler)
: BWindow(frame, SETTINGS_TITLE_ADDUSERWINDOW, B_TITLED_WINDOW_LOOK, B_MODAL_APP_WINDOW_FEEL, B_NOT_RESIZABLE | B_NOT_ZOOMABLE | B_NOT_MINIMIZABLE | B_NOT_CLOSABLE), Settings(bls), ParentHandler(phandler)
{
	frame.OffsetTo(B_ORIGIN);
	Lock();
	View = new BLSettingsAddUserView(frame, Settings);
	AddChild(View);
	Unlock();
}

/*
 * ~BLSettingsAddUserWindow();
 *
 * Currently void
 */
BLSettingsAddUserWindow::~BLSettingsAddUserWindow()
{
}

/*
 * void MessageReceived(BMessage* Msg);
 *
 */
void BLSettingsAddUserWindow::MessageReceived(BMessage* Msg)
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