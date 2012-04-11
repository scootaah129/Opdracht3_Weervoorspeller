/*
 * TextueelScherm.cpp
 *
 *  Created on: 11 mrt. 2012
 *      Author: acer
 */

#include "TextueelScherm.hpp"

TextueelScherm::TextueelScherm( WeerData* weerData )
{
	//sla de weerdata op in het attribuut
	this->weerData = weerData;

	//ken font en skin toe
	this->font = new MAUI::Font(RES_FONT);
	this->skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false );
	//maak een achtergrond label om alle andere widgets in op te slaan, en te tonen

	Label* achtergrond = new Label(0,0,0,0,NULL);
	achtergrond->setBackgroundColor(0xFFFFFF);

	//maak een listbox waar update en visueelknop aan toegevoegd worden
	this->listBox = new ListBox(5,0,105,40,achtergrond);


	//knop om data te updaten
	this->updateKnop = new Label(5,0, 50, 25, achtergrond, "update",0, font);
	this->updateKnop->setSkin( this->skin );

	//knop om naar visueel scherm te schakelen
	this->visueelKnop = new Label(55,0,50,25, achtergrond, "visueel", 0, font);
	this->visueelKnop->setSkin( this->skin );

	//label veld voor weer data, beslaat de rest van het scherm (zie onder)
	this->weerDataLabel = new Label(5,50, 230, 200, achtergrond, "weersverwachting komende dagen", 0 , font);


	//info label
	this->weerInfo = new Label(5,80, 230, 30, achtergrond, "Verwa: vnd, morgn, overmorgn", 0, font);

	//zonneschijn label
	this->weerInfoZon = new Label(5,110, 230, 30, achtergrond, "", 0, font);

	//neerslag label
	this->weerInfoNeerslag = new Label(5,130, 230, 30, achtergrond,"", 0, font);

	//minimum temperatuur label
	this->weerInfoMintemp = new Label(5,150, 230, 30, achtergrond,"", 0, font);

	//update labels met text, etc.

	//stel achtergrond label in als main widget, en maakt alles zichtbaar
	this->setMain(achtergrond);
	this->update();
}

TextueelScherm::~TextueelScherm()
{
}



void TextueelScherm::toonWeerData()
{
	//tijdelijke data buffer voor sprintf operaties
	char data[500];

	//stel tekst in voor info label
	sprintf( data, "Data: Nu / Morgen / Overmorgen" );
	this->weerInfo->setCaption(data);

	//stel tekst in voor zonneschijn label
	sprintf( data, "Zonneschijn: %i%%	/ %i%% / %i%%", weerData->zonneschijn[0], weerData->zonneschijn[1], weerData->zonneschijn[3] );
	this->weerInfoZon->setCaption( data );

	//stel tekst in voor neerslag label
	sprintf( data, "Neerslag: %i%%	/ %i%% / %i%%", weerData->neerslag[0], weerData->neerslag[1], weerData->neerslag[3] );
	this->weerInfoNeerslag->setCaption(data);

	//stel tekst in voor minimum temperatuur label
	sprintf( data, "Minimum: %i	/ %i / %i", weerData->minimumtemperatuur[0], weerData->minimumtemperatuur[1], weerData->minimumtemperatuur[3] );
	this->weerInfoMintemp->setCaption(data);
}


void TextueelScherm::setToggleScherm( Screen* toggleScherm )
{
	//switch naar andere scherm (visueel scherm)
	this->toggleScherm = toggleScherm;
}



void TextueelScherm::update()
{
	//update weerdata en geef alles weer (update labels met nieuwe data)
	this->weerData->update();
	this->toonWeerData();
}



void TextueelScherm::pointerPressEvent( MAPoint2d maPoint )
{
	Point point;
	point.x = maPoint.x;
	point.y = maPoint.y;

	//update knop is ingedrukt
	if( this->updateKnop->contains(point) )
	{
		this->updateKnop->setSelected( true );
		this->update();
	}
	else
	{
		this->updateKnop->setSelected( false );
	}


	//visueel knop is ingedrukt
	if( this->visueelKnop->contains( point ) )
	{
		this->visueelKnop->setSelected( true );
		this->hide();
		this->toggleScherm->show();
	}
	else
	{
		this->visueelKnop->setSelected( false );
	}
}


