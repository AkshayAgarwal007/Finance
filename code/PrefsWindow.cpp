/*
 * Copyright 2009, Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 * Copyright 2017, Akshay Agarwal <agarwal.akshay.akshay8@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "PrefsWindow.h"

#include <stdio.h>
#include <stdlib.h>

#include <LayoutBuilder.h>
#include <MenuItem.h>
#include <PopUpMenu.h>
#include <String.h>



PrefsWindow::PrefsWindow(BHandler* returnHandler, Prefs* oldPrefs)
	:
	BWindow(BRect(), "Preferences", B_FLOATING_WINDOW_LOOK,
		B_MODAL_APP_WINDOW_FEEL,
	B_AUTO_UPDATE_SIZE_LIMITS | B_NOT_RESIZABLE)
{
	MoveTo(100,100);

	this->returnHandler = returnHandler;
	prefs = new Prefs;
	prefs->Set(oldPrefs);

	BView* backview = new BView("PrefsBackView", B_WILL_DRAW);
	rgb_color bgcolor = ui_color(B_PANEL_BACKGROUND_COLOR);
	backview->SetViewColor(bgcolor);

	string str = "";
	str += prefs->curSym;
	curSymTC = new BTextControl("curSymTC", NULL, str.c_str(), NULL);
	curSymTC->SetModificationMessage(new BMessage(PrefsCurrencyChangeMSG));
	fCurSymLbl = new BStringView("CurSymLbl", "Currency Symbol");

	BMenuItem* mmi = 0;
	BPopUpMenu* m = new BPopUpMenu("");

	BMenuItem* mi = new BMenuItem("Before", new BMessage(PrefsCurrencyChangeMSG));
	if (prefs->curSymPlaceBefore)
		mmi = mi;
	m->AddItem(mi);

	mi = new BMenuItem("After", new BMessage(PrefsCurrencyChangeMSG));
	if (!prefs->curSymPlaceBefore)
		mmi = mi;
	m->AddItem(mi);

	curPlaceMF = new BMenuField("curPlaceMF", NULL, m);
	mmi->SetMarked(true);
	fCurPlaceLbl = new BStringView("CurPlaceLbl", "Currency Placement");

	str = prefs->curSep;
	curSepTC = new BTextControl("curSepTC", NULL, str.c_str(), NULL);
	curSepTC->SetModificationMessage(new BMessage(PrefsCurrencyChangeMSG));
	fCurSepLbl = new BStringView("CurSepLbl", "Currency Separator");

	str = prefs->curDec;
	curDecTC = new BTextControl("curDecTC", NULL, str.c_str(), NULL);
	curDecTC->SetModificationMessage(new BMessage(PrefsCurrencyChangeMSG));
	fCurDecLbl = new BStringView("CurDecLbl", "Currency Decimal");

	m = new BPopUpMenu("");
	mi = new BMenuItem("2", new BMessage(PrefsCurrencyChangeMSG));
	if (prefs->curDecPlace == 2)
		mmi = mi;
	m->AddItem(mi);
	mi = new BMenuItem("1", new BMessage(PrefsCurrencyChangeMSG));
	if (prefs->curDecPlace == 1)
		mmi = mi;
	m->AddItem(mi);
	mi = new BMenuItem("0", new BMessage(PrefsCurrencyChangeMSG));
	if (prefs->curDecPlace == 0)
		mmi = mi;
	m->AddItem(mi);

	curDecPlaceMF = new BMenuField("curDecPlaceMF", NULL, m);
	mmi->SetMarked(true);
	fCurDecPlaceLbl = new BStringView("CurDecPlaceLbl","Digits after Decimal in Currency");
	
	curSV = new BStringView("curSV", prefs->currencyToString(103425).c_str());

	m = new BPopUpMenu("");
	mi = new BMenuItem("mm-dd-yy", new BMessage(PrefsDateChangeMSG));
	if (prefs->dateFormat == 0)
		mmi = mi;
	m->AddItem(mi);
	mi = new BMenuItem("dd-mm-yy", new BMessage(PrefsDateChangeMSG));
	if (prefs->dateFormat == 1)
		mmi = mi;
	m->AddItem(mi);

	dateFormatMF = new BMenuField("dateFormatMF", NULL, m);
	mmi->SetMarked(true);
	fDateFormatLbl = new BStringView("dateFormatLbl", "Format of Date");

	str = prefs->dateSep;
	dateSepTC = new BTextControl("dateSepTC", NULL, str.c_str(), NULL);
	dateSepTC->SetModificationMessage(new BMessage(PrefsDateChangeMSG));
	fDateSepLbl = new BStringView("dateSepLbl", "Date Separator");

	struct tm timestruct;
	timestruct.tm_year = 104;
	timestruct.tm_mon = 9;
	timestruct.tm_mday = 25;
	timestruct.tm_sec = 0; 
	timestruct.tm_min = 0; 
	timestruct.tm_hour = 0;
	timestruct.tm_isdst = -1;
	time_t datetime = mktime(&timestruct);

	dateSV = new BStringView("dateSV", prefs->dateToString(datetime).c_str());

	fBtnOk = new BButton("okB", "OK", new BMessage(PrefsOKButtonMSG));
	fBtnOk->MakeDefault(true);
	fBtnCancel = new BButton("cancelB", "Cancel", new BMessage(PrefsCancelButtonMSG));

	BLayoutBuilder::Group<>(backview, B_VERTICAL)
		.SetInsets(20)
		.AddGrid()
			.Add(fCurSymLbl, 0, 0)
			.Add(curSymTC, 1, 0)
			.Add(fCurPlaceLbl, 0, 1)
			.Add(curPlaceMF, 1, 1)
			.Add(fCurSepLbl, 0, 2)
			.Add(curSepTC, 1, 2)
			.Add(fCurDecLbl, 0, 3)
			.Add(curDecTC, 1, 3)
			.Add(fCurDecPlaceLbl, 0, 4)
			.Add(curDecPlaceMF, 1, 4)
		.End()
		.AddGroup(B_HORIZONTAL)
			.AddGlue()
			.Add(curSV)
			.AddGlue()
		.End()
		.AddGrid()
			.Add(fDateFormatLbl, 0, 0)
			.Add(dateFormatMF, 1, 0)
			.Add(fDateSepLbl, 0, 1)
			.Add(dateSepTC, 1, 1)
		.End()
		.AddGroup(B_HORIZONTAL)
			.AddGlue()
			.Add(dateSV)
			.AddGlue()
		.End()
		.AddStrut(0)
		.AddGroup(B_HORIZONTAL)
			.AddGlue()
			.Add(fBtnOk)
			.Add(fBtnCancel)
		.End()
	.End();

	BLayoutBuilder::Group<>(this, B_VERTICAL)
		.AddGlue()
		.Add(backview)
		.AddGlue()
	.End();

}

void PrefsWindow::MessageReceived(BMessage* msg)
{
	switch (msg->what)
	{
		case PrefsOKButtonMSG:
		{
			BMessenger msngr(returnHandler);
			BMessage* msg = new BMessage(PrefsReturnMSG);
			msg->AddPointer("prefs", prefs);
			msngr.SendMessage(msg);
			Quit();
		}
		break;
		case PrefsCancelButtonMSG:
			Quit();
		break;
		case PrefsCurrencyChangeMSG:
		{
			prefs->curSym = curSymTC->Text();
			prefs->curSymPlaceBefore = 
				strcmp(curPlaceMF->Menu()->FindMarked()->Label(), "Before") ? false : true;
			prefs->curSep = curSepTC->Text();
			prefs->curDec = curDecTC->Text();
			prefs->curDecPlace = atoi(curDecPlaceMF->Menu()->FindMarked()->Label());
			curSV->SetText(prefs->currencyToString(103425).c_str());
		}
		break;
		case PrefsDateChangeMSG:
		{
			struct tm timestruct;
			timestruct.tm_year = 104;
			timestruct.tm_mon = 9;
			timestruct.tm_mday = 25;
			timestruct.tm_sec = 0; 
			timestruct.tm_min = 0; 
			timestruct.tm_hour = 0;
			timestruct.tm_isdst = -1;
			time_t datetime = mktime(&timestruct);
		
			prefs->dateFormat = strcmp(dateFormatMF->Menu()->FindMarked()->Label(), "mm-dd-yy") ? 1 : 0;
			prefs->dateSep = dateSepTC->Text();
			dateSV->SetText(prefs->dateToString(datetime).c_str());
		}
		break;
		default:
			BWindow::MessageReceived(msg);
	}
}
