// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Битовое поле

#include <limits>
#include <iostream>
#include "tbitfield.h"

TBitField::TBitField(size_t len)
{
    bitLen = len;
    if (len % (sizeof(uint) * 8) != 0)
        memLen = len / (sizeof(uint) * 8) + 1;
    else
        memLen = len / (sizeof(uint) * 8);
    pMem = new uint[memLen];
    for (int i = 0; i < memLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    delete[] pMem;
    pMem = new uint[memLen];
    for (int i = 0; i < memLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

size_t TBitField::getIndex(const size_t n) const  // индекс в pМем для бита n
{
    return n%(sizeof(uint)*8);
}

uint TBitField::getMask(const size_t n) const // битовая маска для бита n
{
    return (1 << n);
}

// доступ к битам битового поля
uint TBitField::getLength() const // получить длину (к-во битов)
{
    return (uint)bitLen;
}

size_t TBitField::getNumBytes() const // получить количество байт выделенной памяти
{
    return memLen * sizeof(uint);
}

void TBitField::setBit(const size_t n) // установить бит
{
    uint mask = getMask(getIndex(n));
    pMem[n / (sizeof(uint) * 8)] = pMem[n / (sizeof(uint) * 8)] | mask;
}

void TBitField::clrBit(const size_t n) // очистить бит
{
    uint mask = ~getMask(getIndex(n));
    pMem[n / (sizeof(uint) * 8)] = pMem[n / (sizeof(uint) * 8)] | mask;
}

bool TBitField::getBit(const size_t n) const // получить значение бита
{
    uint pos = pMem[n / (sizeof(uint) * 8)];
    uint mask = getMask(getIndex(n));
    if (pos & mask) {
        return true;
    }
    else {
        return false;
    }
}

// битовые операции
TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    pMem = new uint[memLen];
    for (int i = 0; i < memLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
    return true;
}

bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return false;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField b(bitLen);
    for (int i = 0; i < memLen; i++) {
        b.pMem[i] = pMem[i] | bf.pMem[i];
    }
    return b;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField b(bitLen);
    for (int i = 0; i < memLen; i++) {
        b.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return b;
}

TBitField TBitField::operator~() // отрицание
{
    TBitField b(bitLen);
    for (int i = 0; i < memLen; i++) {
        b.pMem[i] = ~pMem[i];
    }
    return b;
}

TBitField::~TBitField()
{

}

// ввод/вывод
std::istream &operator>>(std::istream &istr, TBitField &bf) // ввод
{
    return istr;
}

std::ostream &operator<<(std::ostream &ostr, const TBitField &bf) // вывод
{
    return ostr;
}
