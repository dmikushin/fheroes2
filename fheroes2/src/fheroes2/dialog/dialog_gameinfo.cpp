/***************************************************************************
 *   Copyright (C) 2006 by Andrey Afletdinov                               *
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

#include "agg.h"
#include "settings.h"
#include "cursor.h"
#include "button.h"
#include "maps.h"
#include "dialog.h"

extern void RedrawOpponentsInfo(const Point &);
extern void RedrawClassInfo(const Point &);

void Dialog::GameInfo(void)
{
    Display & display = Display::Get();
    Cursor & cursor = Cursor::Get();
    Settings & conf = Settings::Get();

    cursor.Hide();
    cursor.SetThemes(cursor.POINTER);

    const Sprite & dlg = AGG::GetICN(ICN::SCENIBKG, 0);
    const Point pt((display.w() - dlg.w()) / 2, (display.h() - dlg.h()) / 2);
    Background back(pt, dlg.w(), dlg.h());

    back.Save();
    display.Blit(dlg, pt);

    TextBox text;

    text.Set(conf.MapsName(), Font::BIG, 350);
    text.Blit(pt.x + 52, pt.y + 30);

    text.Set(_("Map\nDifficulty"), Font::SMALL, 80);
    text.Blit(pt.x + 50, pt.y + 54);

    text.Set(_("Game\nDifficulty"), Font::SMALL, 80);
    text.Blit(pt.x + 140, pt.y + 54);

    text.Set(_("Rating"), Font::SMALL, 80);
    text.Blit(pt.x + 230, pt.y + 61);

    text.Set(_("Map Size"), Font::SMALL, 80);
    text.Blit(pt.x + 322, pt.y + 61);

    text.Set(Difficulty::String(conf.MapsDifficulty()), Font::SMALL, 80);
    text.Blit(pt.x + 50, pt.y + 80);

    text.Set(Difficulty::String(conf.GameDifficulty()), Font::SMALL, 80);
    text.Blit(pt.x + 140, pt.y + 80);

    std::string str;
    String::AddInt(str, Game::GetRating(conf.MapsDifficulty(), conf.GameDifficulty()));
    str.append(" %");
    text.Set(str, Font::SMALL, 80);
    text.Blit(pt.x + 230, pt.y + 80);

    text.Set(Maps::SizeString(conf.MapsWidth()), Font::SMALL, 80);
    text.Blit(pt.x + 322, pt.y + 80);

    text.Set(conf.MapsDescription(), Font::SMALL, 350);
    text.Blit(pt.x + 52, pt.y + 105);

    text.Set(_("Opponents"), Font::SMALL, 350);
    text.Blit(pt.x + 52, pt.y + 150);

    Point dst(pt.x + 40, pt.y + 165);
    RedrawOpponentsInfo(dst);

    text.Set(_("Class"), Font::SMALL, 350);
    text.Blit(pt.x + 52, pt.y + 225);

    dst.y = pt.y + 240;
    RedrawClassInfo(dst);

    text.Set(_("Victory\nConditions"), Font::SMALL, 80);
    text.Blit(pt.x + 40, pt.y + 345);

    text.Set(_("Loss\nConditions"), Font::SMALL, 80);
    text.Blit(pt.x + 40, pt.y + 390);

    Button button(pt.x + 180, pt.y + 425, ICN::SYSTEM, 1, 2);
    button.Draw();

    cursor.Show();
    display.Flip();

    LocalEvent & le = LocalEvent::GetLocalEvent();

    // message loop
    while(le.HandleEvents())
    {
	le.MousePressLeft(button) ? button.PressDraw() : button.ReleaseDraw();

        if(le.MouseClickLeft(button) ||
	   le.KeyPress(KEY_RETURN) ||
           le.KeyPress(KEY_ESCAPE)) break;
    }

    cursor.Hide();
    back.Restore();
}
