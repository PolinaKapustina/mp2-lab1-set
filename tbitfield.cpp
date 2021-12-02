// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len >= 0)
	{
		BitLen = len;
		MemLen = (len + (sizeof(TELEM) * 8 - 1)) >> sizeof(TELEM);
		pMem = new TELEM[MemLen];
		if (pMem != NULL) {
			for (int i = 0; i < MemLen; i++)
				pMem[i] = 0;
		}
	}
	else
	{
		throw("Wrong length");
	}
	
}


TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	if (bf.BitLen <= 0) throw;
	else
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		if (pMem != NULL) {
			for (int i = 0; i < MemLen; i++)
				pMem[i] = bf.pMem[i];
		}
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}


int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0 || n >= BitLen) throw ("Wrong length");
	else return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n >= BitLen) throw ("Wrong length");
	else return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > -1) || (n < BitLen))
	pMem[GetMemIndex(n)] |= GetMemMask(n);
	else throw;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > -1) || (n < BitLen))
	{
		pMem[GetMemIndex(n)] &= GetMemMask(n);
	}
	else throw;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n > -1) || (n < BitLen))
	return (pMem[GetMemIndex(n)] & GetMemMask(n)) == 0 ? 0 : 1;
	else throw;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	delete[] pMem;
	pMem = new TELEM[BitLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (bf.BitLen == BitLen) {
		for (int i = 0; i < MemLen; i++) {
			if (pMem[i] != bf.pMem[i]) return 0;
		}
		return 1;
	}
	return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (bf.BitLen == BitLen) {
		for (int i = 0; i < MemLen; i++) {
			if (pMem[i] != bf.pMem[i]) return 1;
		}
		return 0;
	}
	return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len = BitLen;
	if (len < bf.BitLen) len = bf.BitLen;

	TBitField tbf(len);

	for (int i = 0; i < MemLen; i++) {
		tbf.pMem[i] = pMem[i];
	}

	for (int i = 0; i < bf.MemLen; i++) {
		tbf.pMem[i] |= bf.pMem[i];
	}

	return tbf;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len = BitLen;
	if (len < bf.BitLen) len = bf.BitLen;

	TBitField tbf(len);

	for (int i = 0; i < MemLen; i++) {
		tbf.pMem[i] = pMem[i];
	}

	for (int i = 0; i < bf.MemLen; i++) {
		tbf.pMem[i] &= bf.pMem[i];
	}

	return tbf;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tbf(BitLen);
	for (int i = 0; i < BitLen; i++)
	{
	if (GetBit(i) == 0)
		tbf.SetBit(i);
	else
		tbf.ClrBit(i);
	}
	return tbf;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	size_t a;
	for (int i = 0; i < bf.GetLength(); i++)
	{
		istr >> a;
		if (a == 0)
		{
			bf.ClrBit(i);
		}
		else
		{
			bf.SetBit(i);
		}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++) {
		ostr << bf.GetBit(i);
	}
	return ostr;
}
