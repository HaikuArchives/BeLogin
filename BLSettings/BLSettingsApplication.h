/*
 *
 * -=BLSettingsApplication=-
 * This is the main class. It is a requirement for all BeOS Applications
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#ifndef BLSETTINGSAPPLICATION_H
#define BLSETTINGSAPPLICATION_H

#include <Application.h>
#include <Alert.h>
#include <Screen.h>
#include <FindDirectory.h>
#include <Directory.h>
#include <stdio.h>
#include "../BLShared/BLDefines.h"
#include "BLSettings.h"
#include "BLSettingsLoginWindow.h"
#include "BLSettingsWindow.h"

class BLSettingsApplication : public BApplication
{
public:
	BLSettingsApplication(BLSettings* bls);
	~BLSettingsApplication();
	void MessageReceived(BMessage* Msg);

private:
	BLSettings* Settings;
	BLSettingsLoginWindow* LoginWindow;
	BLSettingsWindow* Window;
};

#endif
