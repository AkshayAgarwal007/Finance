/*
 * Copyright 2009, Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 * Copyright 2017, Akshay Agarwal <agarwal.akshay.akshay8@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef ACC_SETTINGS_WINDOW_H
#define ACC_SETTINGS_WINDOW_H

#include <Button.h>
#include <StringView.h>
#include <TextControl.h>
#include <View.h>
#include <Window.h>

#include "Acc.h"

#define AccSetOKButtonMSG		1001
#define AccSetCancelButtonMSG		1002
#define AccSetReturnMSG			1003


class AccSettingsWindow:public BWindow {
public:

		AccSettingsWindow(Acc* acc, BHandler* returnHandler,
					Prefs* prefs);
	void	MessageReceived(BMessage* msg);

private:

	Acc*			fAcc;
	Prefs*			fPrefs;
	BHandler*		fReturnHandler;
	BTextControl*		fOpenBalTC;
	BStringView*		fOpenBalLbl;
	BButton*		fBtnOk;
	BButton*		fBtnCancel;
	BView* 			fBackView;
};

#endif
