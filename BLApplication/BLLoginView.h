/*
 *
 * -=BLLoginView=- 
 * This is the login view.  
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#ifndef BLLOGINVIEW_H
#define BLLOGINVIEW_H

#include <View.h>
#include <TextControl.h>
#include <Window.h>
#include <Application.h>
#include <Alert.h>
#include <Rect.h>
#include <Screen.h>
#include <FindDirectory.h>
#include <Button.h>
#include <Bitmap.h>
#include <TranslationUtils.h>
#include <TranslatorFormats.h>

#include "../BLShared/BLDefines.h"
#include "../BLSettings/BLSettings.h"

class BLLoginView : public BView
{
public:
	BLLoginView(BRect canvas, BLSettings* bls);
	~BLLoginView();
	void AttachedToWindow();
	inline const char* GetUsername() 	{ return this->Username->Text(); }
	inline const char* GetPassword()		{ return this->Password->Text(); }
	inline void 		 ClearPassword()	{ Password->SetText(""); }
	BTextControl* GetUserNameControl() 	{ return Username; }
	BTextControl* GetPasswordControl() 	{ return Password; }
	BButton* GetButton() 					{ return Button; }
	void Draw(BRect updaterect);
	void MouseUp(BPoint point);
private:
	BLSettings* Settings;
	BTextControl* Username;
	BTextControl* Password;
	BButton* Button;
	BBitmap* Icon;
	BPoint* IconLocation;
	BRect* IconExtent;
	BRect* FilledBox;
};
#endif