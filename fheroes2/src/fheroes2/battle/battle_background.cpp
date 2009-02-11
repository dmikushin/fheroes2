#include <cmath>
#include "battle.h"
#include "battle_types.h"
#include "engine.h"
#include "icn.h"
#include "mp2.h"
#include "world.h"
#include "agg.h"
#include "battle_troop.h"

#define display Display::Get()

namespace Battle
{
    Battlefield::Background::Background(const Point &pt, const Maps::Tiles & tile)
    : dst_pt(pt)
    {
        m_fringe = m_background = ICN::UNKNOWN;
         u16 index = tile.GetIndex();
         bool trees = false;
         u16 x = index % world.w(), y = index / world.w();
         if((x < world.w() - 1 && world.GetTiles(index + 1).GetObject() == MP2::OBJ_TREES) ||
            (x > 0 && world.GetTiles(index - 1).GetObject() == MP2::OBJ_TREES) ||
            (y < world.h() - 1 && world.GetTiles(index + world.w()).GetObject() == MP2::OBJ_TREES) ||
            (y > 0 && world.GetTiles(index - world.w()).GetObject() == MP2::OBJ_TREES) )
             trees = true;
         if(tile.GetObject() == MP2::OBJN_GRAVEYARD) {
             m_background = ICN::CBKGGRAV;
             m_fringe = ICN::FRNG0001;
         }
         else
         switch(tile.GetGround()) {
             case Maps::Ground::DESERT: 
                 m_background = ICN::CBKGDSRT;
                 m_fringe = ICN::FRNG0003; 
                 break;
             case Maps::Ground::SNOW: 
                 m_background = trees ? ICN::CBKGSNTR : ICN::CBKGSNMT; 
                 m_fringe = trees ? ICN::FRNG0006 : ICN::FRNG0007;
                 break;
             case Maps::Ground::SWAMP: 
                 m_background = ICN::CBKGSWMP; 
                 m_fringe = ICN::FRNG0008; 
                 break;
             case Maps::Ground::WASTELAND: 
                 m_background = ICN::CBKGCRCK; 
                 m_fringe = ICN::FRNG0002; 
                 break;
             case Maps::Ground::BEACH: 
                 m_background = ICN::CBKGBEAC; 
                 m_fringe = ICN::FRNG0004; 
                 break;
             case Maps::Ground::LAVA: 
                 m_background = ICN::CBKGLAVA; 
                 m_fringe = ICN::FRNG0005; 
                 break;
             case Maps::Ground::DIRT: 
                 m_background = trees ? ICN::CBKGDITR : ICN::CBKGDIMT; 
                 m_fringe = trees ? ICN::FRNG0010 : ICN::FRNG0009;
                 break;
             case Maps::Ground::GRASS:
                 m_background = trees ? ICN::CBKGGRTR : ICN::CBKGGRMT; 
                 m_fringe = trees ? ICN::FRNG0011 : ICN::FRNG0012;
                 break;
             case Maps::Ground::WATER: 
                 m_background = ICN::CBKGWATR; 
                 m_fringe = ICN::FRNG0013; 
                 break;
             default:
                 break;
         }

          int obj = Rand::Get(1,4);
          for(int i=0; i < obj; i++) {
              Point p;
              p.x = Rand::Get(2, BFW-4);
              p.y = Rand::Get(0, BFH-1);
              TerrainObject cobj;
              cobj.wide = false;
              if(tile.GetObject() == MP2::OBJN_GRAVEYARD) {
                  switch(Rand::Get(0,2)) {
                      case 0:
                          cobj.icn = ICN::COBJ0000;
                          break;
                      case 1:  
                          cobj.icn = ICN::COBJ0001;
                          break;
                      case 2:
                          cobj.icn = ICN::COBJ0025;
                          cobj.wide = true;
                          break;
                  }
              }
              else
              switch(tile.GetGround()) {
                  case Maps::Ground::DESERT: 
                      switch(Rand::Get(0,1)) {
                          case 0:
                              cobj.icn = ICN::COBJ0009;
                              break;
                          case 1:
                              cobj.icn = ICN::COBJ0024;
                              break;
                      }
                      break;
                  case Maps::Ground::SNOW: 
                      switch(Rand::Get(0,1)) {
                          case 0:
                              cobj.icn = ICN::COBJ0022;
                              cobj.wide = true;
                              break;
                          case 1:
                              cobj.icn = ICN::COBJ0026;
                              break;
                      }
                      break;
                  case Maps::Ground::SWAMP: 
                      switch(Rand::Get(0,3)) {
                          case 0:
                              cobj.icn = ICN::COBJ0004;
                              cobj.wide = true;
                              break;
                          case 1:
                              cobj.icn = ICN::COBJ0006;
                              break;
                          case 2:
                              cobj.icn = ICN::COBJ0015;
                              cobj.wide = true;
                              break;
                          case 3:
                              cobj.icn = ICN::COBJ0016;
                              cobj.wide = true;
                              break;
                      }
                      break;
                  case Maps::Ground::WASTELAND: 
                      switch(Rand::Get(0,3)) {
                          case 0:
                              cobj.icn = ICN::COBJ0013;
                              break;
                          case 1:
                              cobj.icn = ICN::COBJ0018;
                              cobj.wide = true;
                              break;
                          case 2:
                              cobj.icn = ICN::COBJ0020;
                              cobj.wide = true;
                              break;
                          case 3:
                              cobj.icn = ICN::COBJ0021;
                              break;
                      }
                      break;
                  case Maps::Ground::BEACH: 
                      switch(Rand::Get(0,0)) {
                          case 0:
                              cobj.icn = ICN::COBJ0017;
                              cobj.wide = true;
                              break;
                      }
                      break;
                  case Maps::Ground::LAVA: 
                      switch(Rand::Get(0,2)) {
                          case 0:
                              cobj.icn = ICN::COBJ0029;
                              break;
                          case 1:
                              cobj.icn = ICN::COBJ0030;
                              cobj.wide = true;
                              break;
                          case 2:
                              cobj.icn = ICN::COBJ0031;
                              cobj.wide = true;
                              break;
                      }
                      break;
                  case Maps::Ground::GRASS:
                  case Maps::Ground::DIRT: 
                      switch(Rand::Get(0,9)) {
                          case 0:
                              cobj.icn = ICN::COBJ0002;
                              break;
                          case 1:
                              cobj.icn = ICN::COBJ0005;
                              cobj.wide = true;
                              break;
                          case 2:
                              cobj.icn = ICN::COBJ0007;
                              cobj.wide = true;
                              break;
                          case 3:
                              cobj.icn = ICN::COBJ0011;
                              cobj.wide = true;
                              break;
                          case 4:
                              cobj.icn = ICN::COBJ0012;
                              break;
                          case 5:
                              cobj.icn = ICN::COBJ0014;
                              cobj.wide = true;
                              break;
                          case 6:
                              cobj.icn = ICN::COBJ0019;
                              cobj.wide = true;
                              break;
                          case 7:
                              cobj.icn = ICN::COBJ0027;
                              break;
                          case 8:
                              cobj.icn = ICN::COBJ0028;
                              break;
                          case 9:
                              cobj.icn = ICN::COBJ0008;
                              break;
                      }
                      break;
                  case Maps::Ground::WATER: 
                      switch(Rand::Get(0,2)) {
                          case 0:
                              cobj.icn = ICN::COBJ0003;
                              break;
                          case 1:
                              cobj.icn = ICN::COBJ0010;
                              break;
                          case 2:
                              cobj.icn = ICN::COBJ0023;
                              break;
                      }
                      break;
                  default:
                      cobj.icn = ICN::COBJ0000;
                      break;
              }
              cobj.bf = p;
              cobj.scr = Bf2Scr(p) + dst_pt;
              m_terrainObjects.push_back(cobj);
          }
    }

    void Battlefield::Background::GetBlockedCells(PointList &blocked) const
    {
        for(u8 i = 0; i < m_terrainObjects.size(); i++)
        {
            Point p = m_terrainObjects[i].bf;
            blocked.push_back(p);
            if(m_terrainObjects[i].wide)
                blocked.push_back(p + Point(1, 0));
        }
    }
    
    void Battlefield::Background::Draw()
    {
        display.Blit(AGG::GetICN(m_background, 0), dst_pt);
        Point pt = dst_pt;
        pt.y += 200;
        display.Blit(AGG::GetICN(m_fringe, 0), pt);
        
        if(BattleSettings::Get().Modes(BattleSettings::OPT_GRID))
        {
            Point p(0,0);
            for(p.x = 0; p.x < BFW; p.x++)
                for(p.y = 0; p.y < BFH; p.y++)
                    DrawCell(p);
        }
    }

    void Battlefield::Background::DrawOverBackground(const PointList &movePoints, const Point &cur_pt, const Army::BattleTroop &troop)
    {
        if(BattleSettings::Get().Modes(BattleSettings::OPT_MOVESHADOW))
            for(u16 i = 0; i < movePoints.size(); i++)
                DrawShadow(movePoints[i]);
        if(BattleSettings::Get().Modes(BattleSettings::OPT_MOUSESHADOW))
            if(BfValid(cur_pt))
                DrawShadow(cur_pt);
        
        DrawMark(troop.Position(), 1);
        if(troop.isWide()) {
            Point p = troop.Position();
            p.x += troop.IsReflected() ? -1 : 1;
            DrawMark(p);
        }
    }

    void Battlefield::Background::DrawShadow(const Point &pt)
    {
        const int delta = (int)(((double)CELLW)/6.928);
        static Surface shadow(CELLW, CELLH+2*delta, true);
        static bool prep = true;
        if(prep) {
            prep = false;
            u32 gr = shadow.MapRGB(0,0,0, 0x30);
            u32 tr = shadow.MapRGB(255,255,255, 1);
            Rect r(0,0,shadow.w(), shadow.h());
            shadow.FillRect(tr, r);
            r.y += 2*delta-1;
            r.h -= 4*delta-2;
            shadow.FillRect(gr, r);
            r.x ++;
            r.w -= 2;
            for(int i=1; i<CELLW/2; i+=2) {
                r.y--, r.h +=2;
                shadow.FillRect(gr, r);
                r.x += 2;
                r.w -= 4;
            }
            //shadow.SetAlpha(0x30);
        }
        Point p = Bf2Scr(pt) + dst_pt;
        p.y -= CELLH+delta;
        p.x -= CELLW/2;
        display.Blit(shadow, p);
    }

    void Battlefield::Background::DrawCell(const Point&pt)
    {
        const int delta = (int)(((double)CELLW)/6.928);
        static Surface shadow(CELLW, CELLH+2*delta, true);
        static bool prep = true;
        if(prep) {
            prep = false;
            u32 gr = shadow.MapRGB(0,128,0, 128);
            u32 tr = shadow.MapRGB(255,255,255, 1);
            Rect r(0,0,shadow.w(), shadow.h());
            shadow.FillRect(tr, r);
            r.y += 2*delta-1;
            r.h -= 4*delta-2;
            shadow.FillRect(gr, r);
            r.x ++;
            r.w -= 2;
            shadow.FillRect(tr, r);
            for(int i=1; i<CELLW/2; i+=2) {
                r.y--, r.h +=2;
                shadow.FillRect(gr, r);
                r.y++, r.h -=2;
                shadow.FillRect(tr, r);
                r.y--, r.h +=2;
                r.x += 2;
                r.w -= 4;
            }
            //shadow.SetAlpha(0x80);
        }
        Point p = Bf2Scr(pt) + dst_pt;
        p.y -= CELLH+delta;
        p.x -= CELLW/2;
        display.Blit(shadow, p);
    }

    void Battlefield::Background::DrawMark(const Point&pt, int animframe)
    {
        static int frame = 0;
        const int delta = (int)(((double)CELLW)/6.928);
        static Surface shadow(CELLW, CELLH+2*delta, true);
        static bool prep = true;
        frame += animframe;
        /*if(prep)*/ {
            prep = false;
            u32 gr = shadow.MapRGB(255,255,0, abs((frame%21)-10)*20+55);
            //u32 tr = shadow.MapRGB(255,255,255, 1);
            Rect r(0,0,shadow.w(), shadow.h());
            //shadow.FillRect(tr, r);
            r.y += 2*delta-1;
            r.h -= 4*delta-2;
            for(int i=r.y; i<r.y+r.h; i++) shadow.SetPixel(r.x, i, gr), shadow.SetPixel(r.x+r.w-1, i, gr);
            //shadow.FillRect(gr, r);
            r.x ++;
            r.w -= 2;
            //shadow.FillRect(tr, r);
            for(; r.x<CELLW/2; r.x++, r.w-=2) {
                if(r.x%2) r.y--, r.h +=2;
                for(int x = r.x; x < r.x+r.w; x += r.w-1)
                    for(int y = r.y; y < r.y+r.h; y += r.h-1)
                        shadow.SetPixel(x, y, gr);
                //shadow.FillRect(gr, r);
            }
        }
        Point p = Bf2Scr(pt) + dst_pt;
        p.y -= CELLH+delta;
        p.x -= CELLW/2;
        display.Blit(shadow, p);
    }

    void Battlefield::Background::DrawPath(const PointList &path)
    {
        for(u16 i = 0; i < path.size(); i++)
            DrawShadow(path[i]);
    }

    void Battlefield::Background::DrawObject(const Point &pt) const
    {
        for(u16 i = 0; i < m_terrainObjects.size(); i++)
            if(m_terrainObjects[i].bf == pt)
            {
                const Sprite &spr = AGG::GetICN(m_terrainObjects[i].icn, 0);
                display.Blit(spr, m_terrainObjects[i].scr.x + spr.x(), m_terrainObjects[i].scr.y + spr.y());
                break;
            }
    }

    void Battlefield::Background::DrawCaptain(const Race::race_t race, u16 animframe, bool reflect) const
    {
        ICN::icn_t cap;
        switch(race) {
            case Race::BARB: cap = ICN::CMBTCAPB; break;
            case Race::KNGT: cap = ICN::CMBTCAPK; break;
            case Race::NECR: cap = ICN::CMBTCAPN; break;
            case Race::SORC: cap = ICN::CMBTCAPS; break;
            case Race::WRLK: cap = ICN::CMBTCAPW; break;
            case Race::WZRD: cap = ICN::CMBTCAPZ; break;
            default: return;
        }
        display.Blit(AGG::GetICN(cap, animframe, reflect), dst_pt.x + (reflect?550:0), dst_pt.y + 75);
    }
    
    Rect Battlefield::Background::DrawHero(const Heroes & hero, u16 animframe, bool reflect, int fframe)
    {
        static int flagframe = 0;
        flagframe += fframe;
        Rect r;
        ICN::icn_t cap;
        switch(hero.GetRace()) {
            case Race::BARB: cap = ICN::CMBTHROB; break;
            case Race::KNGT: cap = ICN::CMBTHROK; break;
            case Race::NECR: cap = ICN::CMBTHRON; break;
            case Race::SORC: cap = ICN::CMBTHROS; break;
            case Race::WRLK: cap = ICN::CMBTHROW; break;
            case Race::WZRD: cap = ICN::CMBTHROZ; break;
            default: return r;
        }
        const Sprite & sp = AGG::GetICN(cap, animframe, reflect);
        r.x = dst_pt.x + (reflect?640-sp.w():0);
        r.y = dst_pt.y + 75;
        r.w = sp.w();
        r.h = sp.h();
        display.Blit(sp, r.x, r.y);
        ICN::icn_t flag = ICN::UNKNOWN;
        switch(hero.GetColor()) {
            case Color::BLUE: flag = ICN::HEROFL00; break;
            case Color::GREEN: flag = ICN::HEROFL01; break;
            case Color::RED: flag = ICN::HEROFL02; break;
            case Color::YELLOW: flag = ICN::HEROFL03; break;
            case Color::ORANGE: flag = ICN::HEROFL04; break;
            case Color::PURPLE: flag = ICN::HEROFL05; break;
            case Color::GRAY: flag = ICN::HEROFL06; break;
        }
        display.Blit(AGG::GetICN(flag, flagframe%5, reflect), dst_pt.x + (reflect?640-sp.w()-17:17), dst_pt.y + 80);
        return r;
    }
    
    void Battlefield::Background::DrawArmies(Army::BattleArmy_t & army1, Army::BattleArmy_t & army2, int animframe, bool idleAnimations)
    {
        for(u16 i = 0; i < m_bodies.size(); i++)
            DrawTroop(m_bodies[i]);
        
        Army::BattleTroop *inMotion = NULL;
        for(u16 i = 0; i < army1.size(); i++)
            if(army1[i].isValid() && army1[i].isMoving())
                inMotion = &army1[i];
        for(u16 i = 0; i < army2.size(); i++)
            if(army2[i].isValid() && army2[i].isMoving())
                inMotion = &army2[i];
        
        Point p;
        Point adjusted = inMotion ? Scr2BfDirect(inMotion->ScreenPosition() - dst_pt) : Point(-1, -1);
        int t= -1;
        for(p.y = 0; p.y < BFH; p.y++) 
            for(p.x = 0; p.x < BFW; p.x++) {
                DrawObject(p);
                if(t = FindTroopExact(army1, p), t >= 0 && !army1[t].isMoving())
                {
                    DrawTroop(army1[t], animframe);
                    army1[t].Animate();
                    if(idleAnimations && army1[t].astate == Monster::AS_NONE && !Rand::Get(0, 30))
                        army1[t].Animate(Monster::AS_IDLE);
                }
                if(t = FindTroopExact(army2, p), t >= 0 && !army2[t].isMoving())
                {
                    DrawTroop(army2[t], animframe);
                    army2[t].Animate();
                    if(idleAnimations && army2[t].astate == Monster::AS_NONE && !Rand::Get(0, 30))
                        army2[t].Animate(Monster::AS_IDLE);
                }
                if(BfValid(adjusted) && p == adjusted)
                {
                    inMotion->Blit(inMotion->ScreenPosition(), inMotion->IsReflected());
                    inMotion->Animate();
                }
            }
    }

    void Battlefield::Background::DrawTroop(Army::BattleTroop & troop, int animframe)
    {
        if(troop() == Monster::UNKNOWN) return;
        bool reflect = troop.IsReflected();
        bool wide = troop.isWide();
        Point pos = troop.isMoving() ? Scr2BfDirect(troop.ScreenPosition()) : troop.Position();
        Point tp = Bf2Scr(pos) + dst_pt;
        troop.Blit(tp, reflect, animframe);

        // No count if troop is in motion
        if(troop.isMoving())
            return;
        
        // draw count
        if(troop.Count() == 0) return;
        int offset = wide ? CELLW : 0;
        tp.x += reflect ? -30 + offset : 10 + offset;
        tp.y -= 10;
        // TODO color
        u16 ind = 10;  // blue
        // ind = 11;  // blue 2
        // ind = 12;  // green
        // ind = 13;  // yellow
        // ind = 14;  // red
        display.Blit(AGG::GetICN(ICN::TEXTBAR, ind), tp);
        std::string str;
        int count = troop.Count();
        if(count < 1000)
            String::AddInt(str, count);
        else if(count < 1000000)
            String::AddInt(str, count / 1000), str += NOL10N("K");
        else 
            String::AddInt(str, count / 1000000), str += NOL10N("M");
        Text text(str, Font::SMALL);
        tp.x += 10 - text.w() / 2;
        tp.y -= 1;
        text.Blit(tp);
    }

    void Battlefield::Background::AddBody(const Army::BattleTroop &body)
    {
        m_bodies.push_back(body);
    }

    void Battlefield::Background::DrawMorale(bool goodMorale, const Army::BattleTroop &troop)
    {
        ICN::icn_t icn = goodMorale ? ICN::MORALEG : ICN::MORALEB;
        M82::m82_t m82 = goodMorale ? M82::GOODMRLE : M82::BADMRLE;

        AGG::PlaySound(m82);
        for(u16 i=0; i < AGG::GetICNCount(icn); i++) {
            const Sprite &sp = AGG::GetICN(icn, i);
            Rect pos_rt = sp;
            pos_rt += Bf2Scr(troop.Position());
            ::Background back(pos_rt);
            back.Save();
            display.Blit(sp, pos_rt);
            display.Flip();
            int animat = 0;
            while(LocalEvent::GetLocalEvent().HandleEvents()) {
                if(Game::ShouldAnimateInfrequent(++animat, 4)) break;
            }
            back.Restore();
        }
    }

    void Battlefield::Background::MagicAnimation(std::vector<Army::BattleTroop*> &affected, Heroes *hero1, Heroes *hero2, bool reflect, Spell::spell_t spell)
    {
        ::Background back(Rect(g_baseOffset.x, g_baseOffset.y, 640, 480));
        back.Save();
        ICN::icn_t icn = ICN::UNKNOWN;
        int maxframe = 0, icnframe=-1;
        switch(spell) {
            case Spell::COLDRAY:
            case Spell::DISRUPTINGRAY:
            case Spell::ARROW:
                if(affected.size() == 1) {
                    Point start, end;
                    if(reflect && hero2) {
                        Rect hrect = DrawHero(*hero2, 1, reflect);
                        start = hrect + Point(hrect.w, hrect.h/2);
                        end = Bf2Scr(affected[0]->Position())+dst_pt;
                    } else if(!reflect && hero1) {
                        Rect hrect = DrawHero(*hero1, 1, reflect);
                        start = hrect + Point(0, hrect.h/2);
                        end = Bf2Scr(affected[0]->Position())+dst_pt;
                    } else break;
                    int animat = 0;
                    int frame = 0;
                    Point delta = end - start;
                    switch(spell) {
                        case Spell::COLDRAY:
                            icn = ICN::COLDRAY;
                            maxframe = AGG::GetICNCount(icn);
                            break;
                        case Spell::DISRUPTINGRAY:
                            icn = ICN::DISRRAY;
                            maxframe = AGG::GetICNCount(icn);
                            break;
                        case Spell::ARROW: {
                            icn = ICN::KEEP;
                            maxframe = 8;
                            int maxind = AGG::GetICNCount(icn);
                            if(maxind > 1) {
                                double angle = M_PI_2 - atan2(-delta.y, delta.x);
                                icnframe = (int)(angle/M_PI * maxind);
                            } else icnframe = 0;
                            break;
                        }
                        default:
                            break;
                    }
                    delta.x /= maxframe;
                    delta.y /= maxframe;
                    while(LocalEvent::GetLocalEvent().HandleEvents()) {
                        if(Game::ShouldAnimateInfrequent(animat++, 3)) {
                            back.Restore();
                            display.Blit(AGG::GetICN(icn, icnframe>=0? icnframe : frame, reflect), start);
                            display.Flip();
                            start += delta;
                            frame ++;
                            if(frame >= maxframe) break;
                        }
                    }
                }
                break;
            case Spell::LIGHTNINGBOLT:
            case Spell::CHAINLIGHTNING:
            case Spell::HOLYWORD:
            case Spell::HOLYSHOUT:
            case Spell::ARMAGEDDON:
            case Spell::ELEMENTALSTORM:
            case Spell::METEORSHOWER:
            case Spell::DEATHRIPPLE:
            case Spell::DEATHWAVE:
            case Spell::EARTHQUAKE:
                // TODO
            default:
                break;
        }
    }
}