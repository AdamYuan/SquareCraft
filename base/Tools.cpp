#ifndef RANDOM_H
#define RANDOM_H
#include<iostream>
using namespace std;
static int Random(int first,int last)
{
	return rand()%(last-first+1)+first;
}
#endif
