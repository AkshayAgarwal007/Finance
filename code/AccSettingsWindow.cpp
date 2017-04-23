/*
 * Copyright 2009, Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 * Copyright 2017, Akshay Agarwal <agarwal.akshay.akshay8@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "AccSettingsWindow.h"

#include <stdio.h>

#include <LayoutBuilder.h>


AccSettingsWindow::AccSettingsWindow(Acc* acc, BHandler* returnHandler,
					Prefs* prefs)
	:
	BWindow(BRect(), (acc->name + " Settings").c_str(),
		B_FLOATING_WINDOW_LOOK, B_MODAL_APP_WINDOW_FEEL,
	B_AUTO_UPDATE_SIZE_LIMITS | B_NOT_RESIZABLE)
{
	MoveTo(100,100);
	fReturnHandler = returnHandler;
	fAcc = acc;
	fPrefs = prefs;

	fBackView = new BView("AccChooseBackView", B_WILL_DRAW);
	rgb_color bgcolor = ui_color(B_PANEL_BACKGROUND_COLOR);
	fBackView->SetViewColor(bgcolor);

	fOpenBalTC = new BTextControl("openBalTC", NULL,fPrefs->currencyToString(fAcc->openBal).c_str(),
					NULL);
	fOpenBalLbl = new BStringView("OpenBalLbl", "Opening Balance");
	fBtnOk = new BButton("okB","OK", new BMessage(AccSetOKButtonMSG));
	fBtnOk->MakeDefault(true);
	fBtnCancel = new BButton("cancelB", "Cancel", new BMessage(AccSetCancelButtonMSG));

	BLayoutBuilder::Group<>(fBackView, B_VERTICAL)
		.SetInsets(20)
		.AddGroup(B_HORIZONTAL)
			.Add(fOpenBalLbl)
			.Add(fOpenBalTC)
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
		.Add(fBackView)
		.AddGlue()
	.End();
}

void AccSettingsWindow::MessageReceived(BMessage* msg)
{
	switch (msg->what)
	{
		case AccSetOKButtonMSG:
		{
			string openbaltext = fOpenBalTC->Text();
			fAcc->openBal = fPrefs->stringToCurrency(openbaltext);

			#ifdef DEBUG
			printf("%s %li\n", openbaltext.c_str(), fAcc->openBal);
			#endif
			BMessenger msngr(fReturnHandler);
			BMessage* msg = new BMessage(AccSetReturnMSG);
			msg->AddPointer("acc", fAcc);
			msngr.SendMessage(msg);
			Quit();
		}
		break;
		case AccSetCancelButtonMSG:
			Quit();
		break;
	}
}
