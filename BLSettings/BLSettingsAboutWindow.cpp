/*
 *
 * -=BLSettingsAboutWindow=-
 * This is the About window
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#include "BLSettingsAboutWindow.h"

/*
 * BLAboutWindow(BRect);
 *
 * The constructor just adds the Aboutview
 */
BLSettingsAboutWindow::BLSettingsAboutWindow(BRect frame)
: BWindow(frame, SETTINGS_TITLE_ABOUTWINDOW, B_TITLED_WINDOW_LOOK, B_MODAL_APP_WINDOW_FEEL, B_NOT_RESIZABLE | B_NOT_ZOOMABLE | B_NOT_MINIMIZABLE)
{
	frame.OffsetTo(B_ORIGIN);
	View = new BLSettingsAboutView(frame);
	Lock();
	AddChild(View);
	Unlock();
}

/* 
 * void MessageReceived(BMessage Msg*);
 *
 * Message handling... Quit if a B_QUIT_REQUESTED is received
 */
void BLSettingsAboutWindow::MessageReceived(BMessage* Msg)
{
	switch(Msg->what)
	{
		case B_QUIT_REQUESTED:
		{
			Quit();
			break;
		}
		default:
		{
			BWindow::MessageReceived(Msg);
		}
	}
}