// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Множество - реализация через битовые поля

#include <iostream>
#include "tbitfield.h"
#include "tset.h"

TSet::TSet(size_t mp) : bitField(1) {
    TBitField n(mp);
    maxPower = mp;
    bitField = n;
}

// конструктор копирования
TSet::TSet(const TSet &s) : bitField(s.bitField) {
    maxPower = s.maxPower;
    bitField = s.bitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : bitField(bf) {}

TSet::operator TBitField()
{
    return TBitField(1);
}

size_t TSet::getMaxPower() const // получить макс. к-во эл-тов
{
    return maxPower;
}

bool TSet::isMember(const elType elem) const // элемент множества?
{
    if (bitField.getBit(elem) == 1) {
        return true;
    }
    else {
        return false;
    }
}

void TSet::insElem(const elType elem) // включение элемента множества
{
    if (elem > maxPower) {
        throw 'FALL';
    }
    else {
        bitField.setBit(elem);
    }
}

void TSet::delElem(const elType elem) // исключение элемента множества
{
    if (elem > maxPower) {
        throw 'FALL';
    }
    else {
        bitField.clrBit(elem);
    }
}

// теоретико-множественные операции
TSet& TSet::operator=(const TSet &s) // присваивание
{
        maxPower = s.maxPower;
        bitField = s.bitField;
    return *this;
}

bool TSet::operator==(const TSet &s) const // сравнение
{
    if (maxPower == s.maxPower) {
        if (bitField == s.bitField) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool TSet::operator!=(const TSet &s) const // сравнение
{
    if (maxPower == s.maxPower) {
        if (bitField == s.bitField) {
            return false;
        }
        else {
            return true;
        }
    }
    else {
        return true;
    }
}

TSet TSet::operator+(const TSet &s) // объединение
{
    if (maxPower <= s.maxPower) {
        TSet n(s.maxPower);
        for (int i = 0; i < s.maxPower; i++) {
            if (s.isMember(i)) {
                n.insElem(i);
            }
        }
        for (int i = 0; i < maxPower; i++) {
            if (isMember(i)) {
                n.insElem(i);
            }
        }
        return n;
    }
    if (maxPower > s.maxPower) {
        TSet n(maxPower);
        for (int i = 0; i < maxPower; i++) {
            if (isMember(i)) {
                n.insElem(i);
            }
        }
        for (int i = 0; i < s.maxPower; i++) {
            if (s.isMember(i)) {
                n.insElem(i);
            }
        }
        return n;
    }
}

TSet TSet::operator+(const elType elem) // объединение с элементом
{
    TSet n(maxPower += 1);
    n.bitField.setBit(elem);
    return n;
}

TSet TSet::operator-(const elType elem) // разность с элементом
{
    TSet n(maxPower -= 1);
    bitField.clrBit(elem);
    return n;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    if (maxPower <= s.maxPower) {
        TSet n(s.maxPower);
        for (int i = 0; i < maxPower; i++) {
            if (s.isMember(i) && isMember(i)) {
                n.insElem(i);
            }
        }
        return n;
    }
    if (maxPower > s.maxPower) {
        TSet n(maxPower);
        for (int i = 0; i < s.maxPower; i++) {
            if (isMember(i) && s.isMember(i)) {
                n.insElem(i);
            }
        }
        return n;
    }
}

TSet TSet::operator~() // дополнение
{
    TSet n(maxPower);
    n.bitField = ~bitField;
    return n;
}

// перегрузка ввода/вывода
std::istream &operator>>(std::istream &istr, TSet &s) // ввод
{
    return istr;
}

std::ostream& operator<<(std::ostream &ostr, const TSet &s) // вывод
{
    return ostr;
}
