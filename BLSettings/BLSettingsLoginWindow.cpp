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

#include "BLSettingsLoginWindow.h"

/*
 * BLSettingsLoginWindow(BRect frame);
 *
 * The constructor of the window adds the child to the view chain
 */
BLSettingsLoginWindow::BLSettingsLoginWindow(BRect frame, BLSettings* bls)
: BWindow(frame, SETTINGS_TITLE_LOGIN_WINDOW, B_TITLED_WINDOW_LOOK, B_MODAL_APP_WINDOW_FEEL, B_NOT_RESIZABLE | B_NOT_ZOOMABLE | B_NOT_MINIMIZABLE), Settings(bls)
{
	frame.OffsetTo(B_ORIGIN);
	Lock();
	View = new BLSettingsLoginView(frame, Settings);
	AddChild(View);
	Unlock();
	
	AddShortcut('A', B_COMMAND_KEY, new BMessage(B_ABOUT_REQUESTED));
	AddShortcut('W', B_COMMAND_KEY, new BMessage(B_QUIT_REQUESTED));
	AddShortcut('Q', B_COMMAND_KEY, new BMessage(B_QUIT_REQUESTED));
}

/*
 * ~BLSettingsLoginWindow();
 *
 * Currently void
 */
BLSettingsLoginWindow::~BLSettingsLoginWindow()
{
}

/*
 * bool QuitRequested();
 * 
 * B_QUIT_REQUESTED was send. Tell the BApplication that we want out...
 */
bool BLSettingsLoginWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}

/*
 * void MessageReceived(BMessage* Msg);
 *
 * This is were all BMessages for BeLogin is comming through
 * Sort them out, and redirect them to their approbiate place
 */
void BLSettingsLoginWindow::MessageReceived(BMessage* Msg)
{
	switch(Msg->what)
	{
		case BL_TRY_LOGIN:
		{
			/* Get Username and Password from view */
			BString Username(View->GetUsername());
			BString Password(View->GetPassword());
			
			/* Validate that something was typed before continuing */
			if(Username.Length() <= 0 || Password.Length() <= 0) {
				return;
			}
			
			/* Make hash */
			Password = Settings->MD5Encrypt(View->GetPassword());

			/* Check the combination */
			if(Settings->GetUsers()->IsAdministrator(Username, Password))
			{
				/* Valid */
				be_app->PostMessage(BL_LOGIN_SUCCESSFULL);
			}
			else		
			{
				/* Invalid */
				View->ClearPassword();
				system_beep(INVALID_SYSTEM_BEEP);
			}
			break;
		}

		/* About requested */
		case B_ABOUT_REQUESTED:
		{
			int Width  = 400; 
			int Height = 200;		
			
			BRect Desktop = BScreen(B_MAIN_SCREEN_ID).Frame();
	
			/* Calculate the center of the screen */
			BRect Center(Desktop.right  / 2.0 - Width  / 2.0,
							 Desktop.bottom / 2.0 - Height / 2.0,
			 	 			 Desktop.right  / 2.0 + Width  / 2.0,
			 	 			 Desktop.bottom / 2.0 + Height / 2.0);			
				
			AboutWindow = new BLSettingsAboutWindow(Center);
	
			AboutWindow->Show();
			break;
		}
		default:
		{
			/* If we're not going to use the message, send it along to the base class */
			BWindow::MessageReceived(Msg);
		}
	}
}