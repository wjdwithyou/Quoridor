#ifndef __CHARACTER_H
#define __CHARACTER_H

#include <vector>
#include <d3d9.h>
#include "common.h"
#include "image.h"
#include "bar.h"

class Square;

using namespace std;

class Character{
private:
	const Location dest;

	int num;
	Location loc;
	IDirect3DTexture9* texture_;

	vector<Location> moveableList;
	int numMoveable;

public:
	Character();
	Character(int, Location, Location, IDirect3DTexture9*);
	~Character();

	void Draw() const;
	void Move(Square*);
	bool Check() const;
	bool Check(Location) const;

	void SearchMoveable();
	void RevealMoveable() const;
	void HideMoveable() const;
	void ResetMoveable();

	//bool CheckReachable() const;
	bool CheckReachable(Location, Bdir) const;
	bool CheckReachable(Location) const;	// recursive?
	//bool CheckWall(Location, Location, Bdir) const;

	int get_num() const{ return num; }
	Location get_loc() const{ return loc; }
	Location* get_moveableList() { return &moveableList[0]; }
	int get_numMoveable() const{ return numMoveable; }
};

#endif // __CHARACTER_H