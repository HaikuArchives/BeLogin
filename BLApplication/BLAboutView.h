/*
*
* -=BLAboutView=-
* This is the About View
*
* Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
* This software and its sourcecode is covered by the "Gnu General Public License". 
*
*/

#ifndef BLABOUTVIEW_H
#define BLABOUTVIEW_H

#include <View.h>
#include <Rect.h>
#include <Window.h>
#include <Message.h>
#include <Bitmap.h>
#include <TranslationUtils.h>

#include "../BLShared/BLDefines.h"

class BLAboutView : public BView
{
public:
	BLAboutView(BRect canvas);
	~BLAboutView();	
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