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
	if(Icon != NULL)
		delete Icon;
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
	
	float TopPadding					= 40;
	float LeftPadding 					= 50;
	float RightPadding 					= 15;
	float TextControlHeight 			= 20;
	float TextControlPadding 			= 30;
	float TextControlLabelPadding 		= 15;
	float ButtonPadding					= 2;
	float ButtonPaddingBottom			= 7;
	float IconPaddingTop				= 10;
	float IconPaddingLeft				= 19;
		
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
	ButtonRect.OffsetBy(Bounds().Width() - RightPadding - ButtonRect.Width() - ButtonPadding, TopPadding + TextControlPadding*2 + ButtonPaddingBottom);
		
	/* Create and add the login button */
	Button = new BButton(ButtonRect, "BeLoginView_Button", "Login", new BMessage(BL_TRY_LOGIN));
	Button->MakeDefault(true);
	AddChild(Button);
	
	/* Create and add the quit button */
	ButtonRect.OffsetBy(-(ButtonRect.Width() + 10), 0);
	Button = new BButton(ButtonRect, "BeLoginView_Button", "Quit", new BMessage(B_QUIT_REQUESTED));
	AddChild(Button);	
	
	Username->SetText("Administrator");
	Username->SetEnabled(false);
	Password->MakeFocus(true);
	
	/* Pre calculate filled box */
	FilledBox = new BRect(0, 0, 32, Bounds().Height());		
	
	/* Prepare Icon image */
	/* Use translator utils to load the picture */
	Icon = BTranslationUtils::GetBitmap(B_PNG_FORMAT, 101);
	IconLocation = new BPoint(IconPaddingLeft, IconPaddingTop);
	IconExtent = new BRect(IconPaddingLeft, IconPaddingTop, IconPaddingLeft + Icon->Bounds().right, IconPaddingTop + Icon->Bounds().bottom);
}

/*
 * void Draw(BRect updaterect);
 * Draw the filled box to the left, and paint the BeOS icon too
 */
void BLSettingsLoginView::Draw(BRect updaterect) {
	//set color and paint filled box to the left
	SetHighColor(184, 184, 184);
	FillRect(*FilledBox);
	
	//draw bitmap
	DrawBitmap(Icon, *IconLocation);
}

/*
 * void MouseUp(BPoint point);
 * Catch MouseUp event, and determine if inside BeOS icon. If so
 * display the about window.
 */
void BLSettingsLoginView::MouseUp(BPoint point)
{
	//if cursor inside icon rect - display about
	if(IconExtent->Contains(point)) {
//		Window()->PostMessage(B_ABOUT_REQUESTED);
	} else {
		BView::MouseUp(point);
	}
}