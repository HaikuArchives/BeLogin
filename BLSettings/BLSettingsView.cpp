/*
 *
 * -=BLSettingsView=-
 * This is the main view.  
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#include "BLSettingsView.h"

/*
 * BLSettingsView(BRect canvas);
 *
 * Void!
 */
BLSettingsView::BLSettingsView(BRect canvas)
: BView(canvas, "BLSettingsView", B_FOLLOW_ALL_SIDES, B_WILL_DRAW)
{
	(new BAlert("", "Used", "Ok", NULL, NULL, B_WIDTH_AS_USUAL, B_WARNING_ALERT))->Go();
}

/*
 * ~BLSettingsView();
 * 
 * The destructor is currently void
 */
BLSettingsView::~BLSettingsView()
{
}

/*
 * void AttachedToWindow();
 *
 * The view has now been attached to the window.
 * Now do all the initialization stuff
 */
void BLSettingsView::AttachedToWindow()
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
}
