/*
 *
 * -=BLSettingsApplication=-
 * This is the main class. It is a requirement for all BeOS Applications
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#include "BLSettingsApplication.h"

/*
 * BLApplication(BLSettings* bls);
 *
 * The BLApplications constructor.
 * load the settings and test the validity of the settings.
 * Then construct and show the window
 */
BLSettingsApplication::BLSettingsApplication(BLSettings* bls)
: BApplication("application/x-vnd.BeLogin-BeLoginSettings"), Settings(bls)
{
	status_t settingserr = Settings->Load();
	if(settingserr == BL_LOAD_ERROR)
		(new BAlert("Warning", "Unable to load settings.\nUse Administrator as password to change settings.", "Ok"))->Go();
	
	/* If an error was encountered add the Administrator */
	if(settingserr != B_OK)
	{
		/* Add some defaults */
		
		/* Add an Administrator */
		BString Username("Administrator");
		BString Password(Settings->MD5Encrypt("Administrator"));
		BLUser* User = new BLUser(Username, Password);
		Settings->GetUsers()->AddItem(User);

		Settings->SetLastUser(Username);

		/* Add some applications under Blocked (Tracker, Terminal, Deskbar) */
		BLBlocked* blocked = Settings->GetBlocked();
		
		BString* Tracker = new BString("application/x-vnd.Be-TRAK");
		blocked->AddItem(Tracker);
		
		BString* Terminal = new BString("application/x-vnd.Be-SHEL");
		blocked->AddItem(Terminal);

		BString* Deskbar = new BString("application/x-vnd.Be-TSKB");
		blocked->AddItem(Deskbar);
		
		BLRunnable* runnable = Settings->GetRunnable();
		BString* ScreenSaver = new BString("application/x-vnd.Be.screenblanker");
		runnable->AddItem(ScreenSaver);
		
		/* Save settings */
		Settings->Save();
	}

	/* Create and show the window in the center of the screen */	
	float Width = 260.0;
	
	/* 
	 * If font size is larger that 9 (the smallest) add one pixel to window height
	 * for each pixel larger than 9
	 * This window is 20 px smaller than BeLogin since there's no Menu
	 */
	float Height = 115.0 + (int)be_plain_font->Size() % 9;
	
	/* Get the resolution of the main screen */
	BRect Desktop = BScreen(B_MAIN_SCREEN_ID).Frame();
	
	/* Calculate the center of the screen */
	BRect Center(Desktop.right  / 2.0 - Width  / 2.0,
				 	 Desktop.bottom / 2.0 - Height / 2.0,
				 	 Desktop.right  / 2.0 + Width  / 2.0,
				 	 Desktop.bottom / 2.0 + Height / 2.0);
	LoginWindow = new BLSettingsLoginWindow(Center, bls);
	LoginWindow->Show();
}

/*
 * ~BLApplication();
 *
 * The BLApplications destructor. Currently void
 */
BLSettingsApplication::~BLSettingsApplication()
{
}

/*
 * MessageReceived(BMessage* Msg);
 *
 * This is the message handler for the application
 * It has been overwritten, to catch the BL_LOGIN_SUCCESSFULL
 * If one such arrives, Quit the login window, and show the
 * "real" window...
 */
void BLSettingsApplication::MessageReceived(BMessage* Msg)
{
	switch(Msg->what)
	{
		/* A successfull login was received, show da goods */
		case BL_LOGIN_SUCCESSFULL:
		{
			LoginWindow->Lock();
			LoginWindow->Quit();

			/* Create and show the window in the center of the screen */	
			float Width = 350.0;
	
			/* 
			* If font size is larger that 9 (the smallest) add one pixel to window height
			* for each pixel larger than 9
			*/
			float Height = 200.0 + (int)be_plain_font->Size() % 9;
			
			/* Get the resolution of the main screen */
			BRect Desktop = BScreen(B_MAIN_SCREEN_ID).Frame();
	
			/* Calculate the center of the screen */
			BRect Center(Desktop.right  / 2.0 - Width  / 2.0,
					 	 Desktop.bottom / 2.0 - Height / 2.0,
					 	 Desktop.right  / 2.0 + Width  / 2.0,
					 	 Desktop.bottom / 2.0 + Height / 2.0);
			Window = new BLSettingsWindow(Center, Settings);
			Window->Show();
		}
		default:
		{
			BApplication::MessageReceived(Msg);
		}
	}
}

/*
 * Application entry point.
 * Create the settings object in main, so that it may be used
 * in future commandline switches
 */	
int main(int argc, char** argv)
{
	/* Find the settings path */
	BPath path;
	find_directory(B_COMMON_SETTINGS_DIRECTORY, &path);

	/* Create the 'BeLogin' directory */
	path.Append("BeLogin");
	create_directory(path.Path(), 0777);

	/* Add 'Settings' to path, and pass to BLSettings */
	path.Append("Settings");
	BLSettings BLS(path);
	
	/* commandline */
	if(argc > 1)
		printf("%s: commandline isn't supported\n", argv[0]);
	
	/* gui */
	BLSettingsApplication* BLSApp = new BLSettingsApplication(&BLS);
	BLSApp->Run();

	delete BLSApp;
	return B_NO_ERROR;
}
