/*************************************************************************** 
 *   Copyright (C) 2008 by Andrey Afletdinov                               * 
 *   afletdinov@mail.dc.baikal.ru                                          * 
 *                                                                         * 
 *   This program is free software; you can redistribute it and/or modify  * 
 *   it under the terms of the GNU General Public License as published by  * 
 *   the Free Software Foundation; either version 2 of the License, or     * 
 *   (at your option) any later version.                                   * 
 *                                                                         * 
 *   This program is distributed in the hope that it will be useful,       * 
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        * 
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         * 
 *   GNU General Public License for more details.                          * 
 *                                                                         * 
 *   You should have received a copy of the GNU General Public License     * 
 *   along with this program; if not, write to the                         * 
 *   Free Software Foundation, Inc.,                                       * 
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             * 
 ***************************************************************************/

#ifndef H2HEROESIND_H
#define H2HEROESIND_H

#include <list>
#include <string>
#include "morale.h"
#include "luck.h"

class Heroes;

class HeroesIndicator
{
public:
    HeroesIndicator(const Heroes &);

    const Rect & GetArea(void) const;
    const std::list<std::string> & GetLists(void) const;
    void SetPos(const Point &);

protected:
    const Heroes & 	hero;
    Rect		area;
    Background		back;
    std::list<std::string> lists;
};

class LuckIndicator : public HeroesIndicator
{
public:
    LuckIndicator(const Heroes &);

    void Redraw(void);
    static void QueueEventProcessing(LuckIndicator &);

private:
    Luck::luck_t luck;
};

class MoraleIndicator : public HeroesIndicator
{
public:
    MoraleIndicator(const Heroes &);

    void Redraw(void);
    static void QueueEventProcessing(MoraleIndicator &);

private:
    Morale::morale_t morale;
};

#endif