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

#include <View.h>
#include <TextControl.h>
#include <Button.h>
#include "../BLShared/BLDefines.h"
#include "BLSettings.h"

class BLSettingsLoginView : public BView
{
public:
	BLSettingsLoginView(BRect canvas, BLSettings* bls);
	~BLSettingsLoginView();
	void AttachedToWindow();
	inline const char* GetUsername() 	{ return this->Username->Text(); };
	inline const char* GetPassword()		{ return this->Password->Text(); };
	inline void 		 ClearPassword()	{ Password->SetText(""); };
private:
	BLSettings* Settings;
	BTextControl* Username;
	BTextControl* Password;
	BButton* Button;
};

#endif
