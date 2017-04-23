/*
 * Copyright 2009, Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 * Copyright 2017, Akshay Agarwal <agarwal.akshay.akshay8@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef PREFS_WINDOW_H
#define PREFS_WINDOW_H

#include <Button.h>
#include <MenuField.h>
#include <StringView.h>
#include <TextControl.h>
#include <Window.h>

#include "Acc.h"
#include "Prefs.h"

#define PrefsOKButtonMSG		1401
#define PrefsCancelButtonMSG	1402
#define PrefsReturnMSG			1403
#define PrefsCurrencyChangeMSG	1404
#define PrefsDateChangeMSG		1405


class PrefsWindow:public BWindow {
public:

	PrefsWindow(BHandler* returnHandler, Prefs* oldPrefs);
	void MessageReceived(BMessage* msg);

private:

	BHandler*	returnHandler;
	BTextControl*	curSymTC;
	BMenuField*	curPlaceMF;
	BTextControl*	curSepTC;
	BTextControl*	curDecTC;
	BMenuField*	curDecPlaceMF;
	BMenuField*	dateFormatMF;
	BTextControl*	dateSepTC;
	BStringView*	curSV;
	BStringView*	dateSV;
	BStringView*	fCurSymLbl;
	BStringView*	fCurPlaceLbl;
	BStringView*	fCurSepLbl;
	BStringView*	fCurDecLbl;
	BStringView*	fCurDecPlaceLbl;
	BStringView*	fDateFormatLbl;
	BStringView*	fDateSepLbl;
	BButton*	fBtnOk;
	BButton*	fBtnCancel;
	Prefs*		prefs;
};

#endif
