#include"Castle.h"
Castle::Castle()
{
	lifeNum=MaxLife;
	x1=282;
	x2=554;
	y=230;
}

Castle::~Castle()
{
}
void Castle::AddFull()
{
	lifeNum=MaxLife;
}
void Castle::AddLife()
{
	if(lifeNum<MaxLife)
		lifeNum++;
}
void Castle::ReduceLife()
{
	if(lifeNum>0)
		lifeNum--;
}
void Castle::ReduceToZero()
{
	lifeNum=0;
}