#include "stdafx.h"
#include "biler.h"


biler::biler()
{
}
biler::biler(bool vertical, int id, int speed){
	fromNorth = vertical;
	this->speed = speed;
	this->id = id;
	if (fromNorth){
		x = 800;
		y = 0;
		rect.top = (y-speed);
		rect.bottom = (y + 48);
		rect.left = x;
		rect.right = (x + 20);
	}
	else{
		x = 0;
		y = 426;
		rect.top = y;
		rect.bottom = (y+20);
		rect.left = (x-speed);
		rect.right = (x + 48);
	}
}
void biler::move(){
	if (fromNorth){
		y = y + speed;
		rect.top = (y-speed);
		rect.bottom = (y + 48);
		rect.left = x;
		rect.right = (x + 20);
	}
	else{
		x = x + speed;
		rect.top = y;
		rect.bottom = (y + 20);
		rect.left = (x-speed);
		rect.right = (x + 48);
	}
}
biler::~biler()
{
}
