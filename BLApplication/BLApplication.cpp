/*
 *
 * -=BLApplication=-
 * This is the main class. It is a requirement for all BeOS Applications
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#include "BLApplication.h"

/*
 * BLApplication(BLSettings* bls);
 *
 * The BLApplications constructor.
 * load the settings and test the validity of the settings.
 * Then construct and show the window
 */
BLApplication::BLApplication(BLSettings* bls)
: BApplication("application/x-vnd.BeLogin-BeLogin"), Settings(bls)
{
	status_t settingserr = Settings->Load();
	if(settingserr == BL_LOAD_ERROR)
		(new BAlert("Warning", "Unable to load settings. Aborting...\n(See documentation for information on changing settings)", "Ok"))->Go();
	
	/* If an error was encountered, exit */
	if(settingserr != B_OK)
	{
		PostMessage(B_QUIT_REQUESTED);
		return;
	}
		
	/* Create and show the window in the center of the screen */	
	float Width = 270.0;
	
	/* 
	 * If font size is larger that 9 (the smallest) add one pixel to window height
	 * for each pixel larger than 9
	 */
	float Height = 145.0 + (int)be_plain_font->Size() % 9;
	
	/* Get the resolution of the main screen */
	BRect Desktop = BScreen(B_MAIN_SCREEN_ID).Frame();
	
	/* Calculate the center of the screen */
	BRect Center(Desktop.right  / 2.0 - Width  / 2.0,
				 	 Desktop.bottom / 2.0 - Height / 2.0,
				 	 Desktop.right  / 2.0 + Width  / 2.0,
				 	 Desktop.bottom / 2.0 + Height / 2.0);
	Window = new BLLoginWindow(Center, bls);
	Window->Show();
}

/*
 * ~BLApplication();
 *
 * The BLApplications destructor. Currently void
 */
BLApplication::~BLApplication()
{
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
	find_directory(B_USER_SETTINGS_DIRECTORY, &path);

	/* Add 'Settings' to path, and pass to BLSettings */
	path.Append("BeLogin/Settings");
	BLSettings BLS(path);
	
	BLApplication* BLApp = new BLApplication(&BLS);
	BLApp->Run();

	delete BLApp;
	return B_NO_ERROR;
}
