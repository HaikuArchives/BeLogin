/*
 *
 * -=BLDefines=-
 * This is simply the definitions file.
 *
 * Copyright (C) 2000 Brian Matzon [brian@matzon.dk]. All Rights Reserved.
 * This software and its sourcecode is covered by the "Gnu General Public License". 
 */

#ifndef BL_INCLUDES
#define BL_INCLUDES

#include <String.h>
//#define BL_DEBUG																								// Miscellaneous
#define BL_VERBOSE									true																				// Miscellaneous
#define BL_BETA_QUIT_REQUESTED						'bequ'														// BLLoginWindow
#define BL_LOAD_ERROR								'lerr'														// BLSettings
#define BL_SAVE_ERROR								'serr'														// BLSettings
#define BL_TRY_LOGIN								'tlog'														// BLLoginView, BLSettingsLoginView
#define BL_SHUTDOWN_REQUESTED						'stdw'														// BLLoginView
#define BL_DO_SHUTDOWN								'dsdw'														// BLLoginView
#define BL_LOGIN_SUCCESSFULL						'succ'														// BLSettingsLoginWindow, BLSettingsApplication
#define BL_USER_SELECTED							'ussl'														// BLSettingsUserView
#define BL_USER_INVOKED								'usin'														// BLSettingsUserView
#define BL_USER_ADD									'usad'														// BLSettingsUserView
#define BL_USER_EDIT								'used'														// BLSettingsUserView
#define BL_USER_DELETE								'usdl'														// BLSettingsUserView
#define BL_USER_UPDATE								'usup'														// BLSettingsAddUserView
#define BL_ITEM_SELECTED							'itsl'														// BLSettingsBlockedView
#define BL_ITEM_INVOKED								'itiv'														// BLSettingsBlockedView
#define BL_ADD_ITEM									'adit'														// BLSettingsBlockedView
#define BL_REMOVE_ITEM								'reit'														// BLSettingsBlockedView
#define QUIT_TEAM_MONITOR							'Dsab'														// BLLoginWindow
#define BL_REENABLE_LOGIN							'renl'														// BLLoginWindow

const char VERSION[] 							= "BeLogin 1.4.0";												// Miscellaneous
const char SETTINGS_VERSION[] 					= "BeLoginSettings 1.4.0";										// BLSettingsAboutView
const char TITLE_LOGINWINDOW[] 					= "BeLogin";													// BLLoginWindow
const char SETTINGS_TITLE_WINDOW[] 				= "BeLoginSettings";											// BLSettingsWindow
const char SETTINGS_TITLE_LOGIN_WINDOW[] 		= "BeLoginSettings - Login";									// BLSettingsLoginWindow
const char TITLE_ABOUTWINDOW[] 					= "BeLogin - About";											// BLAboutWindow
const char SETTINGS_TITLE_ABOUTWINDOW[] 		= "BeLoginSettings - About";									// BLSettingsAboutWindow
const char RESOURCE_ERROR[]						= "Unable to load resource. Please reinstall";					// BLAboutView
const char DEFAULT_USERNAME[]					= "Administrator";												// BLSettings
const char DEFAULT_PASSWORD[]					= "Administrator";												// BLSettings
const char VALID_SYSTEM_BEEP[]					= "BeLogin - Valid login";										// BLLoginWindow, BLSettingsWindow
const char INVALID_SYSTEM_BEEP[]				= "BeLogin - Invalid login";									//	BLLoginWindow, BLSettingsWindow
const char SETTINGS_TITLE_ADDUSERWINDOW[]		= "BeLoginSettings - Add user";									// BLSettingsAddUserWindow
const char SETTINGS_TITLE_EDITUSERWINDOW[]		= "BeLoginSettings - Edit user";								// BLSettingsEditUserWindow

#endif