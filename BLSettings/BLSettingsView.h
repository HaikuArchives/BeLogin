/*
 *
 * -=BLSettingsView=-
 * This is the main view.  
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#ifndef BLSETTINGSVIEW_H
#define BLSETTINGSVIEW_H

#include <Be.h>
#include "../BLShared/BLDefines.h"
#include "BLSettings.h"

class BLSettingsView : public BView
{
public:
	BLSettingsView(BRect canvas);
	~BLSettingsView();
	void AttachedToWindow();
private:
};

#endif
