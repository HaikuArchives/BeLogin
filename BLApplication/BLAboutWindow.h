/*
 *
 * -=BLAboutWindow=-
 * This is the About window
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#ifndef BLABOUTWINDOW_H
#define BLABOUTWINDOW_H

#include "../BLShared/BLDefines.h"
#include "BLAboutView.h"

class BLAboutWindow : public BWindow
{
public:
	BLAboutWindow(BRect);
	void MessageReceived(BMessage* Msg);
private:
	BLAboutView*	View;
};

#endif