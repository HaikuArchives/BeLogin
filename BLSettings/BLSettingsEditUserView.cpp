/*
*
* -=BLSettingsAddUserView=-
* This is the Edit User View
*
* Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
* This software and its sourcecode is covered by the "Gnu General Public License". 
*
*/

#include "BLSettingsEditUserView.h"

/*
* BLSettingsEditUserView(BRect canvas, BLSettings* bls, BString* user);
* 
* The constructor, initializes some parameters...
*
*/
BLSettingsEditUserView::BLSettingsEditUserView(BRect canvas, BLSettings* bls, BString* user)
: BView(canvas, "edituserview", B_FOLLOW_ALL_SIDES, B_NAVIGABLE), Settings(bls), Username(user)
{
}

/*
* ~BLSettingsAddUserView();
* 
* Void
*/
BLSettingsEditUserView::~BLSettingsEditUserView()
{
}

/*
*
* AttachedToWindow();
*
* Initialize the view, and place it's buttons and stuff
*/
void BLSettingsEditUserView::AttachedToWindow()
{
	/* Get the user, the user wants to edit */
	BLUser* user = Settings->GetUsers()->GetUser(*Username);
	
	/* Change the title */
	BString title = SETTINGS_TITLE_EDITUSERWINDOW;
	title.Append("(");
	title.Append(*Username);
	title.Append(")");
	Window()->SetTitle(title.String());

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
	txtUsername->SetText(user->GetUsername().String());
	AddChild(txtUsername);
	
	/* Lock field if name == Administrator */
	if(user->GetUsername().ICompare("Administrator") == 0)
		txtUsername->SetEnabled(false);
	
	
	/* Move a notch down on the y-axis */
	TextControlRect.OffsetBy(0, TextControlPadding);
	
	/* Create and add the Old password Textcontrol */
	txtOldPassword = new BTextControl(TextControlRect, "BeLoginView_OldPassword", "Old password", "", NULL);
	txtOldPassword->SetDivider(Divider);
	txtOldPassword->TextView()->HideTyping(true);
	AddChild(txtOldPassword);

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
	ButtonRect.OffsetTo(TextControlRect.right - StringWidth("Cancel"), TextControlRect.bottom + TextControlHeight - 5);
		
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
}

/* 
* MessageReceived(BMessage* Msg);
*
* Message handling
*/
void BLSettingsEditUserView::MessageReceived(BMessage* Msg)
{
	switch(Msg->what)
	{
		/* Ok clicked */
		case B_OK:
		{
			BLUser* User = Settings->GetUsers()->GetUser(*Username);

			/* Check username length > 0 */
			BString unlength = txtUsername->Text();
			if(unlength.Length() == 0)
			{
				(new BAlert("Error", "Username cannot be zero-length", "Ok"))->Go();
				txtUsername->MakeFocus();
				break;
			}
			
			/* Validate username */
			BString username = txtUsername->Text();
			if(Username->ICompare(username) != 0)
			{
				if(Settings->GetUsers()->UserExists(username, true) == true)
				{
					(new BAlert("Error", "Username already taken", "Ok"))->Go();
					txtUsername->MakeFocus();
					break;
				}
			}
			
			/* Validate correct Old Password */
			if(User->GetPassword().Compare(txtOldPassword->Text()) != 0)
			{
				(new BAlert("Error", "Incorrect old password", "Ok"))->Go();
				txtOldPassword->MakeFocus();
				break;
			}
						
			/* Validate new password */
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
			if(password.ICompare(cpassword) != 0)
			{ 
				(new BAlert("Error", "Password and Confirmed password differ", "Ok"))->Go();
				txtPassword->MakeFocus();
				break;
			}
				
			/* User verified. Add the user to the list */
			BString newUsername(txtUsername->Text());
			BString newPassword(txtPassword->Text());
			User->SetUsername(newUsername);
			User->SetPassword(newPassword);
			User->HasBeenModified(true);
												
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
					  string.Append(txtOldPassword->Text());
			if(string.Length() <= Username->Length())
			{
				Window()->PostMessage(B_QUIT_REQUESTED);
				break;
			}
			else
			{
				BAlert* alert = new BAlert("Abort?", "Do you really want to discard the changes?", "No", "Yes", NULL, B_WIDTH_AS_USUAL, B_INFO_ALERT);
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