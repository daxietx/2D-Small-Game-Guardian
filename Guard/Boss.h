#include "stdafx.h"
#include <string>
#include"Monster.h"
using namespace std;
class Boss : public Monster
{
public:
	Boss();
	~Boss();
	int b;
	int c;
	bool d;
	virtual void Move();
	virtual void Init(HGE *hge);
};