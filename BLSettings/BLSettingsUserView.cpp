/*
 *
 * -=BLSettingsUserView=-
 * This is the user view.  
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#include "BLSettingsUserView.h"

/*
 * BLSettingsUserView(BRect canvas);
 *
 */
BLSettingsUserView::BLSettingsUserView(BRect canvas, BLSettings* bls)
: BView(canvas, "userview", B_FOLLOW_ALL_SIDES, B_WILL_DRAW), Settings(bls)
{
	float Padding = 5.0;
	float ButtonHeight = 25.0;
	
	/* Calculate list view position */
	BRect rectLVPos = BRect(canvas.left + Padding, canvas.top + Padding, (canvas.Width()/2) - Padding, canvas.bottom - (Padding + 3));

	/* Create and add listview and scrollview*/
	ListView = new BListView(rectLVPos, "Users");
	AddChild(new BScrollView("scroll_users", ListView, B_FOLLOW_LEFT | B_FOLLOW_TOP, B_NO_BORDER, false, true));	

	/* Add users to list */
	BLUsers* users = Settings->GetUsers(); 
	for(int i=0;i<users->CountItems();i++)
		ListView->AddItem(new BStringItem((users->ItemAt(i))->GetUsername().String()));

	/* Set up messaging */
	ListView->SetSelectionMessage(new BMessage(BL_USER_SELECTED));
	ListView->SetInvocationMessage(new BMessage(BL_USER_EDIT));
	
	/* calculate button position */
	BRect ButtonRect = BRect(canvas.Width()/2 + 30, canvas.Height()/2 - ((3*ButtonHeight + 2*20.0)/2), canvas.right - 20, canvas.top + Padding + ButtonHeight);

	/* Add add button */
	btnAdd = new BButton(ButtonRect, "Button_Add", "Add user", new BMessage(BL_USER_ADD));
	
	/* Move down a notch and add the edit button */
	ButtonRect.OffsetBy(0, ButtonHeight + 20.0);
	btnEdit = new BButton(ButtonRect, "Button_Edit", "Edit user", new BMessage(BL_USER_EDIT));
	btnEdit->SetEnabled(false);

	/* Move down a notch and add the delete button */
	ButtonRect.OffsetBy(0, ButtonHeight + 20.0);
	btnDelete = new BButton(ButtonRect, "Button_Delete", "Delete user", new BMessage(BL_USER_DELETE));
	btnDelete->SetEnabled(false);
	
	AddChild(btnAdd);
	AddChild(btnEdit);
	AddChild(btnDelete);
	
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
}

/*
 * ~BLSettingsUserView();
 * 
 * The destructor is currently void
 */
BLSettingsUserView::~BLSettingsUserView()
{
}

/*
 * void AttachedToWindow();
 *
 * The view has now been attached to the window.
 * Now do all the initialization stuff
 */
void BLSettingsUserView::AttachedToWindow()
{
	ListView->SetTarget(this);
	btnAdd->SetTarget(this);
	btnEdit->SetTarget(this);
	btnDelete->SetTarget(this);
}

/*
 * void MessageReceived(BMessage* Msg);
 *
 */
void BLSettingsUserView::MessageReceived(BMessage* Msg)
{
	switch(Msg->what)
	{
		/* User selected from userlist */
		case BL_USER_SELECTED:
		{
			if(ListView->CurrentSelection() < 0)
			{
				/* Nothing is selected */
				btnEdit->SetEnabled(false);
				btnDelete->SetEnabled(false);
			}
			else
			{
				/* A selection has been made */
				btnEdit->SetEnabled(true);
				btnDelete->SetEnabled(true);
			}
			break;
		}

		/* Add user clicked*/
		case BL_USER_ADD:
		{
			/* Create and show the window in the center of the screen */	
			float Width = 300.0;
	
			/* 
			 * If font size is larger that 9 (the smallest) add one pixel to window height
			 * for each pixel larger than 9
			 * This window is 20 px smaller than BeLogin since there's no Menu
			 */
			float Height = 150.0 + (int)be_plain_font->Size() % 9;
	
			/* Get the resolution of the main screen */
			BRect Desktop = BScreen(B_MAIN_SCREEN_ID).Frame();
	
			/* Calculate the center of the screen */
			BRect Center(Desktop.right  / 2.0 - Width  / 2.0,
						 	 Desktop.bottom / 2.0 - Height / 2.0,
						 	 Desktop.right  / 2.0 + Width  / 2.0,
						 	 Desktop.bottom / 2.0 + Height / 2.0);
			AddUserWindow = new BLSettingsAddUserWindow(Center, Settings, this);
			AddUserWindow->Show();
			
			break;
		}
		
		/* Edit user clicked */
		case BL_USER_EDIT:
		{
			if(ListView->CurrentSelection() >= 0)
			{
				/* Create and show the window in the center of the screen */	
				float Width = 300.0;
		
				/* 
				 * If font size is larger that 9 (the smallest) add one pixel to window height
				 * for each pixel larger than 9
				 * This window is 20 px smaller than BeLogin since there's no Menu
				 */
				float Height = 180.0 + (int)be_plain_font->Size() % 9;
	
				/* Get the resolution of the main screen */
				BRect Desktop = BScreen(B_MAIN_SCREEN_ID).Frame();
	
				/* Calculate the center of the screen */
				BRect Center(Desktop.right  / 2.0 - Width  / 2.0,
							 	 Desktop.bottom / 2.0 - Height / 2.0,
							 	 Desktop.right  / 2.0 + Width  / 2.0,
							 	 Desktop.bottom / 2.0 + Height / 2.0);
				BString* User = new BString(((BStringItem*) ListView->ItemAt(ListView->CurrentSelection()))->Text());
				EditUserWindow = new BLSettingsEditUserWindow(Center, Settings, this, User);
				EditUserWindow->Show();
			}
			break;
		}
		
		/* Delete user clicked*/
		case BL_USER_DELETE:
		{
			/* If only one user left, break */
			if(ListView->CountItems() == 1)
			{
				(new BAlert("Info", "You cannot delete the last user!", "Ok"))->Go();
				break;
			}
			/* Verify that user different from Administrator */
			BString admin(((BStringItem*) ListView->ItemAt(ListView->CurrentSelection()))->Text());
			if(admin.ICompare("Administrator") == 0)
			{
				(new BAlert("Info", "You cannot delete the Administrator!", "Ok"))->Go();
				break;
			}
		
			/* Get name of selection and verify that the user indeed wants to delete the entry */
			int32 index;
			BString text = "Are you certain that you want to delete ";
			text.Append(((BStringItem*) ListView->ItemAt(ListView->CurrentSelection()))->Text());
			text.Append(" ?");
					  
			BAlert* alert = new BAlert("Delete user", text.String(), "Cancel", "Delete", NULL, B_WIDTH_AS_USUAL, B_WARNING_ALERT);
			alert->SetShortcut(0, B_ESCAPE);
			index = alert->Go();
			if(index == 1)
			{
				/* Delete the user from the Listview and the settings userlist */
				BString User(((BStringItem*) ListView->ItemAt(ListView->CurrentSelection()))->Text());
				Settings->GetUsers()->RemoveUser(User);
				if(User.ICompare(Settings->GetLastUser()) == 0)
					Settings->SetLastUser(Settings->GetUsers()->GetUser(BString("Administrator"))->GetUsername());
				ListView->RemoveItem(ListView->CurrentSelection());
			}
			break;
		}

		/* Receive update */
		case BL_USER_UPDATE:
		{
			/* Empty Listview */
			ListView->MakeEmpty();
			
			/* Fill'er up again */
			BLUsers* users = Settings->GetUsers(); 
			for(int i=0;i<users->CountItems();i++)
				ListView->AddItem(new BStringItem((users->ItemAt(i))->GetUsername().String()));
			
			btnDelete->SetEnabled(false);
			btnEdit->SetEnabled(false);
			
		}
		default:
		{
			BView::MessageReceived(Msg);
		}
	}
}
