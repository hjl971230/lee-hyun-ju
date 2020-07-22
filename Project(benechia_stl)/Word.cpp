#include "Word.h"

Word::Word()
{
	m_ix = 0;
	m_iy = 1;
	if (rand() % 100 >= 10)
		m_bitemflag = false;
	else
		m_bitemflag = true;
	m_bstrflag = false;
	m_bhideflag = false;
	m_Item = NULL;
}

Word::~Word()
{
	deleteItem();
}

void Word::draw()
{
	if (m_bstrflag)
	{
		for (int i = 0; i < m_str.length(); i++)
			MapDraw::GetInstance()->DrawPoint("  ", m_ix + i, m_iy - 1);
		if (!m_bhideflag)
		{
			if (!m_bitemflag)
			{
				BLUE
					MapDraw::GetInstance()->DrawPoint(m_str, m_ix, m_iy);
				ORIGINAL
			}
			else
			{
				PUPPLE
					MapDraw::GetInstance()->DrawPoint(m_str, m_ix, m_iy);
				ORIGINAL
			}
		}
		else
		{
			if (!m_bitemflag)
			{
				BLUE
					MapDraw::GetInstance()->DrawPoint("======", m_ix, m_iy);
				ORIGINAL
			}
			else
			{
				PUPPLE
					MapDraw::GetInstance()->DrawPoint("======", m_ix, m_iy);
				ORIGINAL
			}
		}
	}
}

void Word::drop()
{
	m_iy++;
	BLUE
		draw();
	ORIGINAL
}

void Word::Live()
{
	m_bstrflag = true;
	m_ix = (rand() % (X - 4)) + 2;
	while (true)
	{
		if (m_ix + m_str.length() >= X || m_ix - m_str.length() <= 1)
			m_ix = (rand() % (X - 4)) + 2;
		else
			break;
	}
}

void Word::Die()
{
	m_bstrflag = false;
	for (int i = 0; i < m_str.length(); i++)
		MapDraw::GetInstance()->DrawPoint("  ", m_ix + i, m_iy);
	m_ix = 0;
	m_iy = 1;
}

void Word::MakeItem()
{
	deleteItem();
	int rnd = rand() % ITEM_END;
	switch (rnd)
	{
	case ITEM_BLIND:
		m_Item = new BlindWord;
		break;
	case ITEM_CLEAR:
		m_Item = new ClearWord;
		break;
	case ITEM_SPEEDUP:
		m_Item = new SpeedUpWord;
		break;
	case ITEM_SPEEDDOWN:
		m_Item = new SpeedDownWord;
		break;
	case ITEM_STOP:
		m_Item = new StopWord;
		break;
	default:
		break;
	}
}