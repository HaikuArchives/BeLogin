/*
 *
 * -=BLSettingsRunnableView=-
 * This is the Runnable view.  
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#ifndef BLSETTINGSRUNNABLEVIEW_H
#define BLSETTINGSRUNNABLEVIEW_H

#include <View.h>
#include <Rect.h>
#include <ScrollView.h>
#include <ListView.h>
#include <Alert.h>
#include <Button.h>
#include <TextControl.h>
#include <FilePanel.h>
#include <Mime.h>
#include "../BLShared/BLDefines.h"
#include "BLSettings.h"

class BLSettingsRunnableView : public BView
{
public:
	BLSettingsRunnableView(BRect canvas, BLSettings* bls);
	~BLSettingsRunnableView();
	void AttachedToWindow();
	void MessageReceived(BMessage* Msg);
private:
	BListView* ListView;
	BButton* btnAdd;
	BTextControl* txtSignature;
	BLSettings* Settings;
	BFilePanel* FilePanel;
};

#endif