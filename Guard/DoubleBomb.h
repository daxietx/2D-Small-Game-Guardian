#include "stdafx.h"
#include <string>
#include "Bomb.h"
using namespace std;

class DoubleBomb : public Bomb
{
public:
	DoubleBomb();
	~DoubleBomb(void);
	virtual POINT GetTub1EndPosition();
	virtual POINT GetTub2EndPosition();
	POINT tube1Position;
	POINT tube2Position;
	virtual void Render();
	virtual void Init(HGE *hge);
	virtual void Launch(float startx,float starty,float endx,float endy);
};