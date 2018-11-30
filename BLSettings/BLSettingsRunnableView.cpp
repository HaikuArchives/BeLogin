/*
 *
 * -=BLSettingsRunnableView=-
 * This is the Runnable view.  
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 *
 */

#include "BLSettingsRunnableView.h"

/*
 * BLSettingsRunnableView(BRect canvas);
 *
 */
BLSettingsRunnableView::BLSettingsRunnableView(BRect canvas, BLSettings* bls)
: BView(canvas, "runnableview", B_FOLLOW_ALL_SIDES, B_WILL_DRAW), Settings(bls), FilePanel(NULL)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	float Padding = 5.0;
	float ButtonHeight = 25.0;
	
	/* Calculate list view position */
	BRect rectLVPos = BRect(canvas.left + Padding, canvas.top + Padding, canvas.right - (Padding + B_V_SCROLL_BAR_WIDTH + 3), canvas.bottom - (Padding + 3 + B_H_SCROLL_BAR_HEIGHT + 35));

	/* Create and add listview and scrollview*/
	ListView = new BListView(rectLVPos, "Runnable");
	BScrollView* scrollview = new BScrollView("scroll_runnable", ListView, B_FOLLOW_LEFT | B_FOLLOW_TOP, B_NO_BORDER, true, true);
	scrollview->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	AddChild(scrollview);	

	/* Calculate the size and position of the Add button */
	BRect btnAddRect(Bounds().right - (Padding + 60), Bounds().bottom - (Padding + ButtonHeight + 3), scrollview->Bounds().right, Bounds().bottom - (Padding + 3));
		
	/* Create and add the Add button */
	btnAdd = new BButton(btnAddRect, "BeLoginSettings_AddButton", "Add", new BMessage(BL_ADD_ITEM));
	btnAdd->MakeDefault(true);
	btnAdd->SetTarget(this);
	AddChild(btnAdd);

	/* Calculate the size and position of the Add button */
	BRect TextControlRect(ListView->Bounds().left , Bounds().bottom - (Padding + ButtonHeight), Bounds().right - (Padding*2 + btnAdd->Bounds().Width()) , ListView->Bounds().bottom - Padding);

	/* Create and add the password Textcontrol */
	txtSignature = new BTextControl(TextControlRect, "BeLoginView_signature", "", "", NULL);
	txtSignature->SetDivider(0.0);
	AddChild(txtSignature);	


	/* Add Runnable to list */
	BLRunnable* runnable = Settings->GetRunnable(); 
	for(int i=0;i<runnable->CountItems();i++)
		ListView->AddItem(new BStringItem((runnable->ItemAt(i))->String()));

	/* Set up messaging */
	ListView->SetInvocationMessage(new BMessage(BL_REMOVE_ITEM));

	ListView->SetTarget(this);
	txtSignature->SetText("application/");
}

/*
 * ~BLSettingsRunnableView();
 * 
 * The destructor is currently void
 */
BLSettingsRunnableView::~BLSettingsRunnableView()
{
	if(FilePanel != NULL)
		delete FilePanel;
}

/*
 * void AttachedToWindow();
 *
 * The view has now been attached to the window.
 * Now do all the initialization stuff
 */
void BLSettingsRunnableView::AttachedToWindow()
{
	ListView->SetTarget(this);
	btnAdd->SetTarget(this);
}

/*
 * void MessageReceived(BMessage* Msg);
 *
 */
void BLSettingsRunnableView::MessageReceived(BMessage* Msg)
{
	switch(Msg->what)
	{
		/* Add user clicked*/
		case BL_ADD_ITEM:
		{
			/* Retreive text */
			BString Signature(txtSignature->Text());

			/* dupecheck */
			if(Settings->GetRunnable()->Exists(Signature))
			{
				if(BL_VERBOSE)
					(new BAlert("Signature exists", "Unable to add item since that would cause duplicates.", "Ok", NULL, NULL, B_WIDTH_AS_USUAL, B_WARNING_ALERT))->Go();
				
				break;				
			}

			/* !zero-length */
			if(Signature.Length() <= 0 || Signature.ICompare("application/") == 0)
			{	
				/* Create the filepanel */
				if(FilePanel == NULL)
					FilePanel = new BFilePanel(B_OPEN_PANEL, NULL, NULL, B_FILE_NODE, true, NULL, NULL, true);

				/* Set target */
				FilePanel->SetTarget(this);
				
				/* Show the FilePanel */
				FilePanel->Show();
			}
			else
			{
				/* Validity */
				BMimeType mime(Signature.String());
				if(!mime.IsValid())
				{
					BString errmsg("The string '");
					errmsg.Append(Signature);
					errmsg.Append("' isn't a valid mimetype.");
					(new BAlert("Invalid mimetype", errmsg.String(), "Ok", NULL, NULL, B_WIDTH_AS_USUAL, B_WARNING_ALERT))->Go();
					break;
				}
			
				/* !supertype */
				if(mime.IsSupertypeOnly() == true)
				{
					BString errmsg("The string '");
					errmsg.Append(Signature);
					errmsg.Append("' isn't a valid subtype.");
					(new BAlert("Invalid mimetype", errmsg.String(), "Ok", NULL, NULL, B_WIDTH_AS_USUAL, B_WARNING_ALERT))->Go();
					break;
				}
				
				/* AppHint */
				entry_ref ref;
				if(mime.GetAppHint(&ref) != B_OK)
				{
					/* Invalid mimetype, check with user */
					int32 index;
					BString text = "The mimetype '";
					text.Append(Signature);
					text.Append("' doesn't seem to be a registered application. Do you want to add it anyway?");
				  
					BAlert* alert = new BAlert("Add signature", text.String(), "Yes", "No", NULL, B_WIDTH_AS_USUAL, B_WARNING_ALERT);
					alert->SetShortcut(0, B_ESCAPE);
					index = alert->Go();
					if(index == 1)
					{
						break;
					}					
				}
				Settings->GetRunnable()->AddItem(new BString(Signature));
				Settings->GetRunnable()->HasBeenModified(true);
				txtSignature->SetText("application/");

				/* Add it to the listview */
				ListView->AddItem(new BStringItem(Signature.String()));
			}			
			break;
		}
		
		/* Drag 'n' drop support */
  		case B_SIMPLE_DATA:
  		{
  			entry_ref ref;
			type_code typeCode;
			int32 itemCount;
			if(Msg->GetInfo("refs", &typeCode, &itemCount) != B_OK)
			{
				(new BAlert("Error", "Unable to read application placement.", "Ok", NULL, NULL, B_WIDTH_AS_USUAL, B_OFFSET_SPACING, B_WARNING_ALERT))->Go();
				break;
			}
			
  			for (int i=0;i<itemCount; i++)
  			{
	
  				if(Msg->FindRef("refs", i, &ref) == B_OK)
  				{
  					BEntry entry(&ref, true);
	  				BString Signature;
  					char* buf = new char[B_ATTR_NAME_LENGTH];
  					off_t off = 0;
					size_t L = 255;
	  				BNode Node(&entry);
  					if(Node.ReadAttr("BEOS:APP_SIG", B_STRING_TYPE, off, buf, L) <= 0)
  					{
						if(BL_VERBOSE)
							(new BAlert("Error", "Unable to read the application signature.", "Ok", NULL, NULL, B_WIDTH_AS_USUAL, B_OFFSET_SPACING, B_WARNING_ALERT))->Go();
	  				}
					else
					{	
  						Signature.Append(buf);
	
  						if(Settings->GetRunnable()->Exists(Signature))
  						{
  							if(BL_VERBOSE)
								(new BAlert("Signature exists", "Unable to add item since that would cause duplicates.", "Ok", NULL, NULL, B_WIDTH_AS_USUAL, B_WARNING_ALERT))->Go();
	  					}
	  					else
	  					{
							Settings->GetRunnable()->AddItem(new BString(Signature));
							Settings->GetRunnable()->HasBeenModified(true);
							txtSignature->SetText("application/");

							/* Add it to the listview */
							ListView->AddItem(new BStringItem(Signature.String()));
						}
					}
  				}
  			}
			break;
		}

		/* Filepanel message received */
		case B_REFS_RECEIVED:
		{
  			entry_ref ref;
			type_code typeCode;
			int32 itemCount;
			if(Msg->GetInfo("refs", &typeCode, &itemCount) != B_OK)
			{
				(new BAlert("Error", "Unable to read application placement.", "Ok", NULL, NULL, B_WIDTH_AS_USUAL, B_OFFSET_SPACING, B_WARNING_ALERT))->Go();
				break;
			}
			  			
  			for (int i=0;i<itemCount; i++)
  			{
  				if(Msg->FindRef("refs", i, &ref) == B_OK)
  				{
 	 				BEntry entry(&ref, true);
  					BString Signature;
  					char* buf = new char[B_ATTR_NAME_LENGTH];
  					off_t off = 0;
					size_t L = 255;
	  				BNode Node(&entry);
  					if(Node.ReadAttr("BEOS:APP_SIG", B_STRING_TYPE, off, buf, L) <= 0)
  					{
  						if(BL_VERBOSE)
							(new BAlert("Error", "Unable to read the application signature.", "Ok", NULL, NULL, B_WIDTH_AS_USUAL, B_OFFSET_SPACING, B_WARNING_ALERT))->Go();
  					}
					else
					{
	  					Signature.Append(buf);
						delete buf;

		  				if(Settings->GetRunnable()->Exists(Signature))
  						{
							if(BL_VERBOSE)
								(new BAlert("Signature exists", "Unable to add item since that would cause duplicates.", "Ok", NULL, NULL, B_WIDTH_AS_USUAL, B_WARNING_ALERT))->Go();
  						}
  						else
  						{
							Settings->GetRunnable()->AddItem(new BString(Signature));
							Settings->GetRunnable()->HasBeenModified(true);
							txtSignature->SetText("application/");
							
							/* Add it to the listview */
							ListView->AddItem(new BStringItem(Signature.String()));
						}
					}
				}
  			}
			break;
		}

		/* Edit user clicked */
		case BL_REMOVE_ITEM:
		{
			if(ListView->CurrentSelection() >= 0)
			{
				/* Get name of selection and verify that the user indeed wants to delete the entry */
				int32 index;
				BString text = "Are you certain that you want to delete\n";
				text.Append(((BStringItem*) ListView->ItemAt(ListView->CurrentSelection()))->Text());
				text.Append(" ?");
					  
				BAlert* alert = new BAlert("Delete entry", text.String(), "Cancel", "Delete", NULL, B_WIDTH_AS_USUAL, B_WARNING_ALERT);
				alert->SetShortcut(0, B_ESCAPE);
				index = alert->Go();
				if(index == 1)
				{
					/* Delete the entry from the Listview and the settings Blockedlist */
					BString strRunnable(((BStringItem*) ListView->ItemAt(ListView->CurrentSelection()))->Text());
					Settings->GetRunnable()->RemoveRunnable(strRunnable);
					ListView->RemoveItem(ListView->CurrentSelection());
					txtSignature->SetText("application/");
				}
			}
			break;
		}

		default:
		{
			BView::MessageReceived(Msg);
		}
	}
}
