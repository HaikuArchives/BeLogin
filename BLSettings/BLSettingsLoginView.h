/*
 *
 * -=BLSettingsLoginView=-
 * This is the login view.  
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#ifndef BLSETTINGSLOGINVIEW_H
#define BLSETTINGSLOGINVIEW_H

#include <Window.h>
#include <View.h>
#include <TextControl.h>
#include <Button.h>
#include "../BLShared/BLDefines.h"
#include "BLSettings.h"
#include <Bitmap.h>
#include <TranslationUtils.h>
#include <TranslatorFormats.h>

class BLSettingsLoginView : public BView
{
public:
	BLSettingsLoginView(BRect canvas, BLSettings* bls);
	~BLSettingsLoginView();
	void AttachedToWindow();
	inline const char* GetUsername() 	{ return this->Username->Text(); };
	inline const char* GetPassword()		{ return this->Password->Text(); };
	inline void 		 ClearPassword()	{ Password->SetText(""); };
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
