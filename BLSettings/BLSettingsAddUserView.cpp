/*
 *
 * -=BLSettingsAddUserView=-
 * This is the Add User View
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#include "BLSettingsAddUserView.h"

/*
 * BLSettingsAddUserView(BRect canvas, BLSettings* bls);
 * 
 * The constructor, initializes some parameters...
 *
 */
BLSettingsAddUserView::BLSettingsAddUserView(BRect canvas, BLSettings* bls)
: BView(canvas, "adduserview", B_FOLLOW_ALL_SIDES, B_NAVIGABLE), Settings(bls)
{
}

/*
 * ~BLSettingsAddUserView();
 * 
 * Void
 */
BLSettingsAddUserView::~BLSettingsAddUserView()
{
}

/*
 *
 * AttachedToWindow();
 *
 * Initialize the view, and places it's buttons and stuff
 */
void BLSettingsAddUserView::AttachedToWindow()
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	BRect ViewSize(Bounds());
	
	float TopPadding						= 15;
	float LeftPadding 					= 15;
	float RightPadding 					= 15;
	float TextControlHeight 			= 20;
	float TextControlPadding 			= 30;
	float TextControlLabelPadding 	= 15;
	float ButtonPadding					= 10;
	float Divider							= StringWidth("Confirmed password") + + TextControlLabelPadding;
		
	BRect TextControlRect(	LeftPadding, 
									TopPadding, 
									ViewSize.right - RightPadding, 
									LeftPadding + TextControlHeight);

	/* Create and add the username Textcontrol */
	txtUsername = new BTextControl(TextControlRect, "BeLoginSettings_Username", "Username", "", NULL);
	txtUsername->SetDivider(Divider);
	AddChild(txtUsername);
	
	/* Move a notch down on the y-axis */
	TextControlRect.OffsetBy(0, TextControlPadding);
	
	/* Create and add the password Textcontrol */
	txtPassword = new BTextControl(TextControlRect, "BeLoginView_Password", "Password", "", NULL);
	txtPassword->SetDivider(Divider);
	txtPassword->TextView()->HideTyping(true);
	AddChild(txtPassword);

	/* Move a notch down on the y-axis */
	TextControlRect.OffsetBy(0, TextControlPadding);
	
	/* Create and add the password Textcontrol */
	txtConfirmedPassword = new BTextControl(TextControlRect, "BeLoginView_Password", "Confirmed Password", "", NULL);
	txtConfirmedPassword->SetDivider(Divider);
	txtConfirmedPassword->TextView()->HideTyping(true);
	AddChild(txtConfirmedPassword);

	
	/* Calculate the size and position of the Ok button */
	BRect ButtonRect(0, 0, StringWidth("Cancel"), 0);
	ButtonRect.OffsetTo(TextControlRect.right - StringWidth("Canacel"), TextControlRect.bottom + TextControlHeight - 5);
		
	/* Create and add the Ok button */
	btnOk = new BButton(ButtonRect, "BeLoginSettings_OkButton", "Ok", new BMessage(B_OK));
	btnOk->MakeDefault(true);
	btnOk->SetTarget(this);
	AddChild(btnOk);

	/* Calculate the size and position of the Cancel button */
	BRect cancelRect(0, 0, StringWidth("Cancel") + 20, 0);
	cancelRect.OffsetTo(TextControlRect.right - (StringWidth("Cancel") + 30) - ButtonPadding - StringWidth("Cancel"), TextControlRect.bottom + TextControlHeight - 5);

	/* Create and add the button */
	btnCancel = new BButton(cancelRect, "BeLoginSettings_CancelButton", "Cancel", new BMessage(B_CANCEL));
	btnCancel->SetTarget(this);
	AddChild(btnCancel);
	
	txtUsername->MakeFocus();
}

/* 
 * MessageReceived(BMessage* Msg);
 *
 * Message handling
 */
void BLSettingsAddUserView::MessageReceived(BMessage* Msg)
{
	switch(Msg->what)
	{
		/* Ok clicked */
		case B_OK:
		{
			/* Validate username */
			BString username = txtUsername->Text();
			if(Settings->GetUsers()->UserExists(username, true) == true)
			{
				(new BAlert("Error", "Username already taken", "Ok"))->Go();
				txtUsername->MakeFocus();
				break;
			}
			
			/* Validate username */
			if(username.Length() == 0)
			{
				(new BAlert("Error", "Username cannot be zero-length", "Ok"))->Go();
				txtUsername->MakeFocus();
				break;
			}				
				
			/* Validate password */
			BString password 	= txtPassword->Text();
			BString cpassword = txtConfirmedPassword->Text();
			BString length;
					  length.Append(password);
					  length.Append(cpassword);
			if(length.Length() == 0)
			{
				(new BAlert("Error", "Password cannot be zero-length", "Ok"))->Go();
				txtPassword->MakeFocus();
				break;
			} 
			if(password.Compare(cpassword) != 0)
			{ 
				(new BAlert("Error", "Password and Confirmed password differ", "Ok"))->Go();
				txtPassword->MakeFocus();
				break;
			}

			/* User verified. Add the user to the list */
			BString Username(txtUsername->Text());
			BString Password(Settings->MD5Hash(txtPassword->Text()));
			BLUser* User = new BLUser(Username, Password);
			User->HasBeenModified(true);
			Settings->GetUsers()->AddItem(User);
								
			Window()->PostMessage(BL_USER_UPDATE);
			Window()->PostMessage(B_QUIT_REQUESTED);
			break;
		}
		
		/* Cancel clicked*/
		case B_CANCEL:
		{
			BString string = txtUsername->Text();
					  string.Append(txtPassword->Text());
					  string.Append(txtConfirmedPassword->Text());
			if(string.Length() <= 0)
			{
				Window()->PostMessage(B_QUIT_REQUESTED);
				break;
			}
			else
			{
				BAlert* alert = new BAlert("Abort?", "Do you really want to discard this user?", "No", "Yes", NULL, B_WIDTH_AS_USUAL, B_INFO_ALERT);
				alert->SetShortcut(0, B_ESCAPE);
				int32 index = alert->Go();
				if(index == 1)
				{	
					Window()->PostMessage(B_QUIT_REQUESTED);
				}
			}	
			break;
		}
		default:
		{
			BView::MessageReceived(Msg);
		}
	}
}