/*
 *
 * -=BLApplication=-
 * This is the main class. It is a requirement for all BeOS Applications
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#ifndef BLAPPLICATION_H
#define BLAPPLICATION_H

#include "../BLShared/BLDefines.h"
#include "../BLSettings/BLSettings.h"
#include "BLLoginWindow.h"

class BLApplication : public BApplication
{
public:
	BLApplication(BLSettings* bls);
	~BLApplication();

private:
	BLSettings* Settings;
	BLLoginWindow* Window;
};

#endif
