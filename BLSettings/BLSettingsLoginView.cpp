/*
 *
 * -=BLSettingsLoginView=-
 * This is the login view.  
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#include "BLSettingsLoginView.h"

/*
 * BLLoginView(BRect canvas, BLSettings* bls);
 *
 * Void!
 */
BLSettingsLoginView::BLSettingsLoginView(BRect canvas, BLSettings* bls)
: BView(canvas, "loginview", B_FOLLOW_ALL_SIDES, B_WILL_DRAW), Settings(bls)
{
}

/*
 * ~BLLoginView();
 * 
 * The destructor is currently void
 */
BLSettingsLoginView::~BLSettingsLoginView()
{
}

/*
 * void AttachedToWindow();
 *
 * The view has now been attached to the window.
 * Now do all the initialization stuff
 */
void BLSettingsLoginView::AttachedToWindow()
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	BRect ViewSize(Bounds());
	
	float TopPadding						= 15;
	float LeftPadding 					= 15;
	float RightPadding 					= 15;
	float TextControlHeight 			= 20;
	float TextControlPadding 			= 30;
	float TextControlLabelPadding 	= 15;
	float ButtonPadding					= 2;
		
	BRect TextControlRect(	LeftPadding, 
									TopPadding, 
									ViewSize.right - RightPadding, 
									LeftPadding + TextControlHeight);

	/* Create and add the username Textcontrol */
	Username = new BTextControl(TextControlRect, "BeLoginView_Username", "Username", "", NULL);
	Username->SetDivider(StringWidth(Username->Label()) + TextControlLabelPadding);
	AddChild(Username);
	
	/* Move a notch down on the y-axis */
	TextControlRect.OffsetBy(0, TextControlPadding);
	
	/* Create and add the password Textcontrol */
	Password = new BTextControl(TextControlRect, "BeLoginView_Password", "Password", "", NULL);
	Password->SetDivider(StringWidth(Password->Label()) + TextControlLabelPadding);
	Password->TextView()->HideTyping(true);
	AddChild(Password);
	
	/* Calculate the size of the button */
	BRect ButtonRect(0, 0, Password->TextView()->Bounds().Width() / 2, 0);
	ButtonRect.OffsetBy(Bounds().Width() - RightPadding - ButtonRect.Width() - ButtonPadding, TopPadding + TextControlPadding + TextControlPadding + ButtonPadding);
		
	/* Create and add the button */
	Button = new BButton(ButtonRect, "BeLoginView_Button", "Ok", new BMessage(BL_TRY_LOGIN));
	Button->MakeDefault(true);
	AddChild(Button);
	
	Username->SetText("Administrator");
	Username->SetEnabled(false);
	Password->MakeFocus(true);
}