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

#include "BLLoginWindow.h"
#include "iostream.h"
#include <OS.h>

/* Create the message to reenable BeLogin */
const BMessage * kReenableMsg = new BMessage(BL_REENABLE_LOGIN);

/*
 * BLLoginWindow(BRect frame, BLSettings* bls);
 *
 * The constructor of the window adds the child to the view chain
 * and sets its own Settings to the one passed by parameter
 * The Aboutwindow is nulled too.
 */
BLLoginWindow::BLLoginWindow(BRect frame, BLSettings* bls)
: BWindow(frame, TITLE_LOGINWINDOW, B_TITLED_WINDOW_LOOK, B_MODAL_APP_WINDOW_FEEL, B_NOT_RESIZABLE | B_NOT_ZOOMABLE | B_NOT_MINIMIZABLE | B_NOT_CLOSABLE), Settings(bls), AboutWindow(NULL), Exiting(false), Attempts(1)
{
	/* Create the Menu*/
	BRect Rect(0, 0, 0, 0);
	MenuBar = new BMenuBar(Rect, "BeLoginMenu");

	BMenu* mnuSystem = new BMenu("System");
	BMenuItem* mniRestart = new BMenuItem("Restart", new BMessage(BL_MENU_RESTART));
	BMenuItem* mniShutdown = new BMenuItem("Shutdown", new BMessage(BL_MENU_SHUTDOWN));
	mnuSystem->AddItem(mniRestart);
	mnuSystem->AddItem(mniShutdown);

#ifdef BETA
	mnuSystem->AddSeparatorItem();
	mnuSystem->AddItem(new BMenuItem("BETA-QUIT", new BMessage(BL_BETA_QUIT_REQUESTED), 'Q'));
#endif		

	BMenu* mnuAbout = new BMenu("About");
	BMenuItem* mniAbout = new BMenuItem("About...", new BMessage(B_ABOUT_REQUESTED), 'A');
	mnuAbout->AddItem(mniAbout);
	
	MenuBar->AddItem(mnuSystem);
	MenuBar->AddItem(mnuAbout);		

	/* Add the menubar to the view. Its size wont be set until it has been added to the view */
	Lock();
	AddChild(MenuBar);
	Unlock();
	
	/* 
	 * Make the views size equal to that of the windows bounds minus the 
	 * height of the menubar 
	 */
	Rect = Bounds();
	Rect.InsetBy(0, MenuBar->Bounds().Height()/2);
	Rect.OffsetTo(0, MenuBar->Bounds().Height());
	
	Lock();
	View = new BLLoginView(Rect, Settings);
	AddChild(View);
	Unlock();

	/* 
	 * tell the BRoster to send us messages about launching of apps 
	 * The message will arrive at MessageReceived as a B_SOME_APP_LAUNCHED
	 */
	BMessenger msgr(this);
	be_roster->StartWatching(msgr, B_REQUEST_LAUNCHED | B_SOME_APP_ACTIVATED);
	
	TerminateApplications();
}

/*
 * ~BLLoginWindow();
 *
 * Currently void
 */
BLLoginWindow::~BLLoginWindow()
{
}

/*
 * bool QuitRequested();
 * 
 * B_QUIT_REQUESTED was send. Tell the BApplication that we want out...
 */
bool BLLoginWindow::QuitRequested()
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
void BLLoginWindow::MessageReceived(BMessage* Msg)
{
	switch(Msg->what)
	{
	
#ifdef BETA	
		/* Beta Quit*/
		case BL_BETA_QUIT_REQUESTED:
		{
			Exiting = true;
			app_info AppInfo; 
			BString ScriptPath = "\"";
	   	if(be_app->GetAppInfo(&AppInfo) == B_OK)
	   	{
		  		BEntry	ProgramEntry(&AppInfo.ref);    	
				BPath Path;
				ProgramEntry.GetPath(&Path);
	
				Path.GetParent(&Path);
				ScriptPath.Append(Path.Path());
				ScriptPath.Append("/LoginScript\"");
				
				/* Hide the window first */
				Hide();
				
				/* Execute the script */
				system(ScriptPath.String());			//Has to be a better way??
			}
			PostMessage(B_QUIT_REQUESTED);
			break;
		}
#endif
	
		/* Restart menuentry was selected */
		case BL_MENU_RESTART:
		{
			/* Hide the window first */
			Hide();

			system("shutdown -r");
			PostMessage(B_QUIT_REQUESTED);
			break;
		}

		/* Shutdown menuentry was selected */
		case BL_MENU_SHUTDOWN:
		{
			/* Hide the window first */
			Hide();

			system("shutdown");
			PostMessage(B_QUIT_REQUESTED);
			break;
		}

		/* Ok button was pushed */
		case BL_TRY_LOGIN:
		{
			/* Get Username and Password from view */
			BString Username(View->GetUsername());
			BString Password(Settings->MD5Encrypt(View->GetPassword()));
			
			/* Check the combination */
			if(Settings->GetUsers()->IsValid(Username, Password))
			{
				/* Valid */
				
				//Perform exit code... ie. fire a script or something like that...

				Settings->SetLastUser(Username);
				Settings->Save();
				system_beep(VALID_SYSTEM_BEEP);

				Exiting = true;
				app_info AppInfo; 
				BString ScriptPath = "\"";
		   	if(be_app->GetAppInfo(&AppInfo) == B_OK)
		   	{
			  		BEntry	ProgramEntry(&AppInfo.ref);    	
					BPath Path;
					ProgramEntry.GetPath(&Path);
		
					Path.GetParent(&Path);
					ScriptPath.Append(Path.Path());
					ScriptPath.Append("/LoginScript\"");
					
					/* Add username as parameter */
					ScriptPath.Append(" \"");
					ScriptPath.Append(Username);
					ScriptPath.Append("\"");
					
					/* Hide the window first */
					Hide();

					/* Execute Script */
					system(ScriptPath.String());			//Has to be a better way??
				}
				PostMessage(B_QUIT_REQUESTED);
			}
			else		
			{
				/* Invalid */
				View->ClearPassword();
				system_beep(INVALID_SYSTEM_BEEP);

				switch(Attempts)
				{
					case 8:
					{
						(new BAlert("Info", "Persistent aren't we ?", "Oh yes I am..."))->Go(NULL);
						break;
					}
					case 32:
					{
						(new BAlert("Info", "This is getting ridiculous...", "I know!"))->Go(NULL);
						break;
					}
					case 64:
					{
						(new BAlert("Info", "Getting kinda booring...", "*Yawn*"))->Go(NULL);
						break;
					}
					case 128:
					{
						(new BAlert("Info", "Now you know why you haven't got a significant other!!", ":-)"))->Go(NULL);
						break;
					}
					case 256:
					{
						(new BAlert("Info", "Do it one more time and i'll reboot your machine\nI mean it!!", "Sure you do..."))->Go(NULL);
						break;
					}
					case 512:
					{
						(new BAlert("Info", "I warned you!!", "bugger"))->Go(NULL);
						Hide();
						system("shutdown -r");
						break;
					}
				}
				//while user is reading message, disable widgets
				View->GetUserNameControl()->SetEnabled(false);
				View->GetPasswordControl()->SetEnabled(false);
				View->GetButton()->SetEnabled(false);
				
				// We'll use a BMessageRunner to re-enable the controls after
				// the elapsed time.
				BMessenger messenger(this);
				Runner = new BMessageRunner(messenger, kReenableMsg, 100000 * Attempts, 1);
				
				Attempts = Attempts * 2;
			}
			break;
		}
		
		/* Returning back from persistent user */
		case BL_REENABLE_LOGIN:
		{
			// don't need our MessageRunner any more...
			if(Runner != NULL)
				delete Runner;
			Runner = NULL;
			
			// re-enable the controls
			View->GetUserNameControl()->SetEnabled(true);
			View->GetPasswordControl()->SetEnabled(true);
			View->GetButton()->SetEnabled(true);

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
				
			AboutWindow = new BLAboutWindow(Center);
	
			AboutWindow->Show();
			break;
		}
		
		/* The roster detected the launch of an app */
		case B_SOME_APP_LAUNCHED:
		{
			if(Exiting != true)
			{
				/* Call the ApplicationLaunch function, which deals with this */
				ApplicationLaunch(Msg);
			}
			break;
		}

		/*  The roster detected the activation of an app 
		 *  Since the Team Monitor is the property of the input server
		 *  no B_SOME_APP_LAUNCHED is send. Therefore the B_SOME_APP_ACTIVATED
		 */
		case B_SOME_APP_ACTIVATED:
		{
			BString strSignature;

			/* Retreive the application signature */
			Msg->FindString("be:signature", &strSignature);
			
			/* Compare it against the Input servers mimetype */
			if(strSignature.ICompare("application/x-vnd.Be-input_server") == 0)
			{
				app_info info;
				be_roster->GetAppInfo(strSignature.String(), &info);

				BMessage msgGetProperty, msgSetProperty, msgReply;
				status_t result;

				/* Create the scripting stack */
				msgGetProperty.what = B_GET_PROPERTY;
				msgGetProperty.AddSpecifier("Messenger");
				msgGetProperty.AddSpecifier("Window", "Team Monitor");

				/* Send the message to the input server */
				result =	BMessenger(info.signature, info.team).SendMessage(&msgGetProperty, &msgReply);
			
				if(result == B_OK)
				{
					BMessenger msng;
					/* Get the messenger from the reply */
					if(msgReply.FindMessenger("result", &msng) == B_OK)
					{
						/* 
						 * Send the cancel command 
						 * Thanks to Dianne Kyra Hackborn for the command 
						 */
						msng.SendMessage(QUIT_TEAM_MONITOR);
						
						/* Get some info om me, and activate BeLogin, based on the team info */
						app_info blinfo;
						be_app->GetAppInfo(&blinfo);
						be_roster->ActivateApp(blinfo.team);
					}
				}
			}
			break;
		}

		default:
		{
			/* If we're not going to use the message, send it along to the base class */
			BWindow::MessageReceived(Msg);
		}
	}
}

/*
 * void ApplicationLaunch(BMessage* Msg);
 *
 * This is where we check to see if an application is allowed to run
 * If it isn't (checked against the BLRunnable list) it is killed.
 * The killing process first sends a friendly shutdown request
 * If the app is alive 30000 uS later, its team(threads) is killed.
 */
void BLLoginWindow::ApplicationLaunch(BMessage* Msg)
{
	const char* signature;
	
	/* The Roster has put the signature of the app in the BMessage. Retrieve it.*/
	if(Msg->FindString("be:signature", &signature) != B_OK)
	{	
		(new BAlert("Error", "Couldn't find signature", "Ok"))->Go();
		return; 
	}
	
	/* Check against BLRunnable List */	
	if(Settings->GetRunnable()->IsAllowedToRun(signature))
	{	
		return; 
	}	
	/* Construct a messenger, and send a B_QUIT_REQUESTED message */
	BMessenger Shredder(signature);
	Shredder.SendMessage(B_QUIT_REQUESTED);

	snooze(30000);
	
	/* if still alive, kill it! */
	if(Shredder.IsValid())
	{
		kill_team(Shredder.Team());
	}
}

/*
 * void TerminateApplications();
 *
 * Terminate all applications in the BLBlocked list
 */
void BLLoginWindow::TerminateApplications()
{
	BLBlocked* blocked = Settings->GetBlocked(); 
	for(int i=0;i<blocked->CountItems();i++)
	{
		/* Construct a messenger, and send a B_QUIT_REQUESTED message */
		BMessenger Shredder(blocked->ItemAt(i)->String());
		Shredder.SendMessage(B_QUIT_REQUESTED);

		snooze(30000);
	
		/* if still alive, kill it! */
		if(Shredder.IsValid())
		{
			kill_team(Shredder.Team());
		}
	}
}