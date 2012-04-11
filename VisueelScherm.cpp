/*
 * VisueelScherm.cpp
 *
 *  Created on: 11 mrt. 2012
 *      Author: acer
 */

#include "VisueelScherm.hpp"

VisueelScherm::VisueelScherm( WeerData* weerData )
{
	//sla de weerdata op in het attribuut
	this->weerData = weerData;

	//ken font en skin toe
	this->font = new MAUI::Font(RES_FONT);
	this->skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false );

	//maak een achtergrond label om alle andere widgets in op te slaan, en te tonen
	Label* achtergrond = new Label(0,0,0,0, NULL);
	achtergrond->setBackgroundColor(0xFFFFFF);


	//maak een listbox met update en textueelknop
	this->listBox = new ListBox(0,0,150,30,achtergrond);

	//knop om data te updaten
	this->updateKnop = new Label(10, 5, 50, 20, achtergrond,"update", 0, font);
	this->updateKnop->setSkin(skin);

	//knop om naar visueel te schakelen
	this->textueelKnop = new Label(60, 5, 50, 20, achtergrond,"tekst", 0, font);
	this->textueelKnop->setSkin(skin);


	//staafdiagram

	//maak eerst een placeholder
	this->diagramTekening = maCreatePlaceholder();

	//laat de placeholder tekenbaar zijn
	maCreateDrawableImage( this->diagramTekening, EXTENT_X( maGetScrSize() ), EXTENT_Y( maGetScrSize() ) - 30 );

	//mak een nieuwe image met de placeholder
	this->diagramImage = new Image( 0, 30, EXTENT_X( maGetScrSize() ), EXTENT_Y( maGetScrSize() ) - 30, achtergrond, true, true, this->diagramTekening );


	this->setMain( achtergrond );
	this->update();
}


VisueelScherm::~VisueelScherm()
{
}


void VisueelScherm::update()
{
	//update waarden vam weerdata
	this->weerData->update();

	//stel draw target in op onze tekening
	maSetDrawTarget( this->diagramTekening );

	//teken een staaf diagram


	//legenda
	//teken blokje en text met zonneschijn, neerslag en temperatuur
	maSetColor(0xFFFFFF);
	maDrawText(10, 10,"Legenda");

	maDrawText(10, 25,"Zonneschijn");
	maSetColor(0xFF0000);
	maFillRect(100, 25, 20,20);

	maSetColor(0xFFFFFF);
	maDrawText(10, 50,"Neerslag");
	maSetColor(0x00FF00);
	maFillRect(100, 50, 20,20);

	maSetColor(0xFFFFFF);
	maDrawText(10, 75,"Temperatuur");
	maSetColor(0x0000FF);
	maFillRect(100, 75, 20,20);

	//teken 10-stap lijnen
	maSetColor(0xFFFFFF);
	//onderste
	maLine(20, 230, 200, 230 );

	maLine(20, 220, 200, 220 );
	maLine(20, 210, 200, 210 );
	maLine(20, 200, 200, 200 );
	maLine(20, 190, 200, 190 );
	maLine(20, 180, 200, 180 );
	maLine(20, 170, 200, 170 );
	maLine(20, 160, 200, 160 );
	maLine(20, 150, 200, 150 );
	//bovenste
	maLine(20, 140, 200, 140 );
	maLine(20, 130, 200, 130 );

	//teken de staven van zonneschijn, neerslag en minimum temperatuur
	//zonneschijn
	maSetColor(0xFF0000);
	maFillRect(30, 130 + (100-this->weerData->zonneschijn[0]) , 40, this->weerData->zonneschijn[0]);

	maSetColor(0x00FF00);
	maFillRect(80, 130 + (100-this->weerData->neerslag[0]) , 40, this->weerData->neerslag[0]);

	maSetColor(0xFF0000);
	maFillRect(130, 130 + (100-this->weerData->minimumtemperatuur[0]) , 40, this->weerData->minimumtemperatuur[0]);


	//altijd draw target na tekenen teruggeven naar scherm!
	maSetDrawTarget( HANDLE_SCREEN );

	//update de image met de nieuwe tekening
	this->diagramImage->setResource( this->diagramTekening );
}



void VisueelScherm::setToggleScherm( Screen* toggleScherm )
{
	//switch naar andere scherm (textueel scherm)
	this->toggleScherm = toggleScherm;
}




void VisueelScherm::pointerPressEvent( MAPoint2d maPoint )
{
	Point point;
	point.x = maPoint.x;
	point.y = maPoint.y;

	//update knop is ingedrukt
	if( this->updateKnop->contains( point ) )
	{
		this->updateKnop->setSelected( true );
		this->update();
	}
	else
	{
		this->updateKnop->setSelected( false );
	}


	//textueel knop is ingedrukt
	if( this->textueelKnop->contains( point ) )
	{
		this->textueelKnop->setSelected( true );
		this->hide();
		this->toggleScherm->show();

	}
	else
	{
		this->textueelKnop->setSelected( false );
	}
}


