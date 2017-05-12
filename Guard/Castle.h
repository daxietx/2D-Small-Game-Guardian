#include "stdafx.h"
#include <string>
using namespace std;
#define MaxLife 5
class Castle
{
public:
	Castle();
	~Castle();
	bool life;
	int x1;
	int x2;
	int y;
	float lifeNum;
	void AddLife();
	void AddFull();
	void ReduceLife();
	void ReduceToZero();
};