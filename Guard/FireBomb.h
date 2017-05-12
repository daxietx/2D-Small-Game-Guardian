#include "stdafx.h"
#include <string>
#include "DoubleBomb.h"
using namespace std;

class FireBomb : public Bomb
{
public:
	FireBomb();
	~FireBomb();

	virtual void Render();
	virtual void Init(HGE *hge);
	virtual void Launch(float startx,float starty,float endx,float endy);
	virtual void Update(float dt);

	virtual POINT GetTub1EndPosition();
	virtual POINT GetTub2EndPosition();
};