/*
 *
 * -=BLSettingsAboutView=-
 * This is the Settings About View
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#include "BLSettingsAboutView.h"

/*
 * BLAboutView(BRect canvas);
 *
 * This is the Aboutviews constructor.
 * The correct drawing mode is set, and the AboutPicture is loaded
 * The size of the AboutPicture and the size of the view is cached
 * for performance
 */
BLSettingsAboutView::BLSettingsAboutView(BRect canvas)
: BView(canvas, "aboutview", B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_NAVIGABLE), AboutPicture(NULL)
{
	/* Set colors and drawing mode */
	SetViewColor(B_TRANSPARENT_32_BIT);
	SetHighColor(0, 0, 0);
	SetDrawingMode(B_OP_OVER);
	
	/* Load the logo */
	LoadLogo();
	
	/* Cache size */
	PictureBounds = AboutPicture->Bounds();
	ViewBounds = Bounds();
}

/*
 * ~BLAboutView();
 * 
 * The About views destructor simply deletes the AboutPicture 
 */
BLSettingsAboutView::~BLSettingsAboutView()
{
	if(AboutPicture != NULL)
		delete AboutPicture;
}

/*
 * void Draw(BRect Region);
 *
 * This is the draw handler for the view
 * The AboutPicture is drawn and the version is written on top 
 */
void BLSettingsAboutView::Draw(BRect Region)
{
	if(AboutPicture != NULL)
	{
		/* If resource loaded */
		DrawBitmap(AboutPicture, PictureBounds, ViewBounds);
		MovePenTo(155, 135);
		DrawString(SETTINGS_VERSION);
	}
	else
	{
		MovePenTo(100, 100);
		DrawString(RESOURCE_ERROR);
	}
}

/*
 * void KeyDown(const char *key, int32 numBytes);
 *
 * This is the key down handler.
 * it is used to test for the escape key or the enter key.
 * If one of these two are pressed, post a B_QUIT_REQUESTED
 * message to the window.
 */
void BLSettingsAboutView::KeyDown(const char *key, int32 numBytes)
{
	switch(key[0])
	{
		case B_ENTER:
		case B_ESCAPE:
		{
			Window()->PostMessage(B_QUIT_REQUESTED);
			break;
		}
		default:
		{
			BView::KeyUp(key, numBytes);
		}
	}
}

/*
 * void KeyUp(const char *key, int32 numBytes); 
 *
 * This is the Key Up handler.
 * It is needed for the testing of B_COMMAND_KEY + 'w'
 * This event is only send as a Key up, and not as Key Down
 */
void BLSettingsAboutView::KeyUp(const char *key, int32 numBytes)
{
	switch(key[0])
	{
		/* Yup 'w' is the key */
		case 'w':
		{
			/* Get the current message from the queue */
			BMessage *msg = NULL;
			msg = Window()->CurrentMessage();
			if (msg != NULL)
			{
				/* Get the modifiers */
				int32 modifier;
				msg->FindInt32("modifiers", &modifier);
				
				if((modifier & B_COMMAND_KEY) != 0)
					Window()->PostMessage(B_QUIT_REQUESTED);
			}
			break;
		}
		default:
		{
			BView::KeyUp(key, numBytes);
		}
	}
}

/*
 * void LoadLogo();
 *
 * Load the bitmap resource from the resource part of the binary file
 */
void BLSettingsAboutView::LoadLogo()
{
	/* Use translator utils to load the picture */
	AboutPicture = BTranslationUtils::GetBitmap("About");
}