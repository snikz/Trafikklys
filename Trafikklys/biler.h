#pragma once
class biler
{
public:
	biler();
	biler(bool vertical, int id, int speed);
	~biler();
	void move();
	int getId(){ return id; }
	int getX(){ return x; }
	int getY(){ return y; }
	void setSpeed(int speed){ this->speed = speed; }
	int getSpeed(){ return speed; }
	int getBool(){ return fromNorth; }
	RECT getRect(){ return rect; }
private:
	int id;
	int x;
	int y;
	int speed;
	RECT rect;
	bool fromNorth;

};

