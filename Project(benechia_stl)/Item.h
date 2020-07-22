#pragma once
#include "Mecro.h"
class Item
{
protected:
public:
	Item();
	~Item();
	virtual ITEM ItemValue() = 0;
};

class BlindWord : public Item
{
public:
	BlindWord();
	~BlindWord();
	inline ITEM ItemValue() { return ITEM_BLIND; }
};

class ClearWord : public Item
{
public:
	ClearWord();
	~ClearWord();
	inline ITEM ItemValue() { return ITEM_CLEAR; }
};

class SpeedUpWord : public Item
{
public:
	SpeedUpWord();
	~SpeedUpWord();
	inline ITEM ItemValue() { return ITEM_SPEEDUP; }
};

class SpeedDownWord : public Item
{
public:
	SpeedDownWord();
	~SpeedDownWord();
	inline ITEM ItemValue() { return ITEM_SPEEDDOWN; }
};

class StopWord : public Item
{
public:
	StopWord();
	~StopWord();
	inline ITEM ItemValue() { return ITEM_STOP; }
};
