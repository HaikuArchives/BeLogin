/*
 *
 * -=BLSettingsWindow=-
 * This is the main window, which is shown upon a login
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#include "BLSettingsWindow.h"

/*
 * BLSettingsWindow(BRect frame);
 *
 * The constructor of the window adds the child to the view chain
 */
BLSettingsWindow::BLSettingsWindow(BRect frame, BLSettings* bls)
: BWindow(frame, SETTINGS_TITLE_WINDOW, B_TITLED_WINDOW_LOOK, B_MODAL_APP_WINDOW_FEEL, B_NOT_RESIZABLE | B_NOT_ZOOMABLE | B_NOT_MINIMIZABLE), Settings(bls)
{
	/* Offset to windows coordinates*/
	frame.OffsetTo(B_ORIGIN);
	BTab* tab;

	/* Create the background box (grey) */
	Box = new BBox(frame, "Background", B_FOLLOW_ALL_SIDES, B_PLAIN_BORDER);
	AddChild(Box);
	
	/* Create our rect and inset it by 5 px */
	BRect r = Bounds();
	r.InsetBy(5, 5);

	/* Create a TabView, and set its color. Then add it to the Box's Hierachy */
	TabView = new BTabView(r, "tabview");
	TabView->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	Box->AddChild(TabView);

	/* Calc the size of the views and inset by 5 px*/
	r = TabView->Bounds();
	r.InsetBy(5, 5);
	r.bottom -= TabView->TabHeight();
	
	/* Create the users tab */
	tab = new BTab();
	UserView = new BLSettingsUserView(r, Settings);
	TabView->AddTab(UserView, tab);
	tab->SetLabel("Users");
	
	/* Create the Blocked tab */
	tab = new BTab();
	BlockedView = new BLSettingsBlockedView(r, Settings);
	TabView->AddTab(BlockedView, tab);
	tab->SetLabel("Blocked");

	/* Create the Runnable tab */
	tab = new BTab();
	RunnableView = new BLSettingsRunnableView(r, Settings);
	TabView->AddTab(RunnableView, tab);
	tab->SetLabel("Runnable");

	/* Select the first one (users) */
	TabView->Select(0);

	/* Add some shortcuts */
	AddShortcut('A', B_COMMAND_KEY, new BMessage(B_ABOUT_REQUESTED));
	AddShortcut('W', B_COMMAND_KEY, new BMessage(B_QUIT_REQUESTED));
	AddShortcut('Q', B_COMMAND_KEY, new BMessage(B_QUIT_REQUESTED));
}
/*
 * ~BLSettingsWindow();
 *
 * Currently void
 */
BLSettingsWindow::~BLSettingsWindow()
{
}

/*
 * bool QuitRequested();
 * 
 * B_QUIT_REQUESTED was send. Tell the BApplication that we want out...
 */
bool BLSettingsWindow::QuitRequested()
{
	bool modified = Settings->HasBeenModified();
	if(modified == true)
	{
		BAlert* alert = new BAlert("Save changes", "Do you want to save your changes?", "Cancel", "Don't save", "Save", B_WIDTH_AS_USUAL, B_OFFSET_SPACING, B_INFO_ALERT);
		alert->SetShortcut(0, B_ESCAPE);
		alert->ButtonAt(2)->MakeDefault(true);
		int32 index = alert->Go();
		switch(index)
		{
			/* Cancel */
			case 0:
			{
				return false;
			}
			
			/* Yes */
			case 1:
			{
				be_app->PostMessage(B_QUIT_REQUESTED);
				return true;
			}
			
			/* No */
			case 2:
			{
				Settings->Save();
				be_app->PostMessage(B_QUIT_REQUESTED);
				return true;
			}
		}
	}
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}

/*
 * void MessageReceived(BMessage* Msg);
 *
 * This is were all BMessages for BeLogin is comming through
 * Sort them out, and redirect them to their approbiate place
 */
void BLSettingsWindow::MessageReceived(BMessage* Msg)
{
	switch(Msg->what)
	{
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