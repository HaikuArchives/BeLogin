/*
 *
 * -=BLSettingsAboutView=-
 * This is the Settings About View
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#ifndef BLSETTINGSABOUTVIEW_H
#define BLSETTINGSABOUTVIEW_H

#include "../BLShared/BLDefines.h"
#include <View.h>
#include <Message.h>
#include <Bitmap.h>
#include <Window.h>
#include <TranslationUtils.h>

class BLSettingsAboutView : public BView
{
public:
	BLSettingsAboutView(BRect canvas);
	~BLSettingsAboutView();	
	void Draw(BRect Region);
	void KeyDown(const char *bytes, int32 numBytes);
	void KeyUp(const char *key, int32 numBytes);
	void AttachedToWindow() { MakeFocus(); };
private:
	void LoadLogo();
	BBitmap* AboutPicture;
	BRect PictureBounds;
	BRect ViewBounds;
};

#endif	