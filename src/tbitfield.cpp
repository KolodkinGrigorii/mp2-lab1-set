// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Битовое поле

#include <limits>
#include <iostream>
#include "tbitfield.h"
#include <math.h>

TBitField::TBitField(size_t len)
{
    bitLen = len;
    if (len % (sizeof(elType) * 8) != 0)
        memLen = len / (sizeof(elType) * 8) + 1;
    else
        memLen = len / (sizeof(elType) * 8);
    pMem = new elType[memLen];
    for (int i = 0; i < memLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    pMem = new elType[memLen];
    for (int i = 0; i < memLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

size_t TBitField::getIndex(const size_t n) const  // индекс в pМем для бита n
{
    return n % (sizeof(elType) * 8);
}

elType TBitField::getMask(const size_t n) const // битовая маска для бита n
{
    return (elType)1<<n;
}

// доступ к битам битового поля
elType TBitField::getLength() const // получить длину (к-во битов)
{
    return (elType)bitLen;
}

size_t TBitField::getNumBytes() const // получить количество байт выделенной памяти
{
    return memLen * sizeof(elType);
}

void TBitField::setBit(const size_t n) // установить бит
{
    if (n > bitLen) {
        throw 'FALL';
    }
    elType mask = getMask(getIndex(n));
    pMem[n / (sizeof(elType) * 8)] = pMem[n / (sizeof(elType) * 8)] | mask;
}

void TBitField::clrBit(const size_t n) // очистить бит
{
    if (n > bitLen) {
        throw 'FALL';
    }
    elType mask = ~getMask(getIndex(n));
    pMem[n / (sizeof(elType) * 8)] = pMem[n / (sizeof(elType) * 8)] & mask;
}

bool TBitField::getBit(const size_t n) const // получить значение бита
{
    if (n > bitLen) {
        throw 'FALL';
    }
    elType pos = pMem[n / (sizeof(elType) * 8)];
    elType mask = getMask(getIndex(n));
    if (pos & mask) {
        return true;
    }
    else {
        return false;
    }
}

// битовые операции
TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    pMem = new elType[memLen];
    for (int i = 0; i < memLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

bool TBitField::operator==(const TBitField& bf) const // сравнение
{
    for (int i = 0; i < memLen; i++) {
        if (pMem[i] != bf.pMem[i]) {
            return false;
        }
    }
    return true;
}

bool TBitField::operator!=(const TBitField& bf) const // сравнение
{
    for (int i = 0; i < memLen; i++) {
        if (pMem[i] != bf.pMem[i]) {
            return true;
        }
    }
    return false;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    TBitField b(bitLen);
    for (int i = 0; i < memLen; i++) {
        b.pMem[i] = pMem[i] | bf.pMem[i];
    }
    return b;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    TBitField b(bitLen);
    for (int i = 0; i < memLen; i++) {
        b.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return b;
}

TBitField TBitField::operator~() // отрицание
{
    TBitField n(bitLen);
    for (int i = 0; i < memLen - 1; i++) {
        n.pMem[i] = ~pMem[i];
    }
    n.pMem[memLen - 1] = pMem[memLen - 1] ^ (getMask(getIndex(0)));
    for (int i = 1; i < bitLen % (sizeof(elType)*8); i++) {
        n.pMem[memLen - 1] = (n.pMem[memLen - 1]) ^ (getMask(getIndex(i)));
    }
    return n;
}

TBitField::~TBitField()
{
    delete[] pMem;
}

// ввод/вывод
std::istream& operator>>(std::istream& istr, TBitField& bf) // ввод
{
    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TBitField& bf) // вывод
{
    for (int i = bf.bitLen; i >= 0; i--) {
        if (bf.pMem[i / sizeof(elType) * 8] & bf.getMask(bf.getIndex(i))) {
            return ostr << 1;
        }
        else {
            return ostr << 0;
        }
    }
}
