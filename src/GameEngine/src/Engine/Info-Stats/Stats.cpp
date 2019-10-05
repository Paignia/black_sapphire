#include "Stats.h"
#include <cstring>
#include <iostream>
Stats::Stats(int Str,int Dex,int Int,int Con)
{
  this->Int=Int;
  this->Dex=Dex;
  this->Str=Str;
  this->Con=Con;
  canMove=true;
  canAttack=true;
  prone=false;
  canCast=true;
  UpdateStats();
}

Stats::Stats(int Str,int Dex,int Int,int Con,int Hp,int Def,int Dmg,int ToHit,int Speed, bool canMove,bool canCast,bool canAttack,bool prone)
{
  this->Str=Str;
  this->Dex=Dex;
  this->Int=Int;
  this->Con=Con;
  this->Hp=Hp;
  this->Def=Def;
  this->Dmg=Dmg;
  this->ToHit=ToHit;
  this->Speed=Speed;
  this->canMove=canMove;
  this->canCast=canCast;
  this->canAttack=canAttack;
  this->prone=prone;
}

Stats::Stats()
{
  this->Int=0;
  this->Dex=0;
  this->Str=0;
  this->Con=0;
  canMove=true;
  canAttack=true;
  prone=false;
  canCast=true;
  UpdateStats();
}

void Stats::UpdateStats()
{
  this->Hp=(Str+Con)/2;
  this->Def=(Dex+Int+Str+Con)/4;
  this->Dmg=Str/2;
  this->ToHit=(Str+Dex)/10;
  this->Speed=(Dex+Str/2)/4;

}

void Stats::PrintStats()
{
  std::cout<<"Int:"<<Int<<" Dex:"<<Dex<<" Str:"<<Str<<" Con:"<<Con<<std::endl;
  std::cout<<"Hp:"<<Hp<<" Def:"<<Def<<" Dmg:"<<Dmg<<" ToHit:"<<ToHit<<" Speed:"<<Speed<<std::endl;
  std::cout<<"CanMove:"<<canMove<<" CanCast:"<<canCast<<"CanAttack:"<<canAttack<<" Prone:"<<prone<<std::endl;


}


int Stats::getStat(const char *stat)
{
  std::cout<<stat<<std::endl;
  if(strncmp(stat,"Dex",3)==0)
    {
      return this->Dex;
    }
  else if(strncmp(stat,"Int",3)==0)
    {
      return this->Int;
    }
  else if(strncmp(stat,"Str",3)==0)
    {
      return this->Str;
    }

  else if(strncmp(stat,"Con",3)==0)
    {
      return this->Str;
    }
  else
    return -1;


}


void Stats::setStat(const char *stat,int value)
{
  if(strncmp(stat,"Dex",3)==0)
    {
      this->Dex=value;
      UpdateStats();
    }
  else if(strncmp(stat,"Int",3)==0)
    {
      Int=value;
      UpdateStats();
    }
  else if(strncmp(stat,"Str",3)==0)
    {
      this->Str=value;
      UpdateStats();
    }

  else if(strncmp(stat,"Con",3)==0)
    {
      this->Str=value;
      UpdateStats();
    }
  else
    return;
}


void Stats::Apply(Stats *s)
{

  std::cout<<"Before:"<<std::endl;
  PrintStats();
  Int+=s->getInt();
  Dex+=s->getDex();
  Str+=s->getStr();
  Con+=s->getCon();
  Hp+=s->getHp();
  Def+=s->getDef();
  Dmg+=s->getDmg();
  ToHit+=s->getToHit();
  Speed+=s->getSpeed();
  canMove=s->CanMove();
  if(canCast==true)
    canCast=s->CanCast();
  canAttack=s->CanAttack();
  prone=s->Prone();
  UpdateStats();
  std::cout<<"After:"<<std::endl;
  PrintStats();
}




void Stats::Remove(Stats *s)
{
  Int-=s->getInt();
  Dex-=s->getDex();
  Str-=s->getStr();
  Con-=s->getCon();
  Hp-=s->getHp();
  Def-=s->getDef();
  Dmg-=s->getDmg();
  ToHit-=s->getToHit();
  Speed-=s->getSpeed();
  if(s->CanMove()==false)
    canMove=true;
  if(canCast==false)
    canCast=true;
  if(canAttack==false)
    canAttack=true;
  if(prone==true)
    prone=false;


}


Attributes::Attributes(int str,int dex,int con,int iint,int spi):Strength(str),Dexterity(dex),Intelligence(iint),Constitution(con),Spirit(spi)
{


}
void Attributes::SetStr(int str)
{
  this->Strength=str;

}
void Attributes::SetDex(int dex)
{
  this->Dexterity=dex;

}

void Attributes::SetCon(int Con)
{
  this->Constitution=Con;
}
void Attributes::SetInt(int iint)
{
  this->Intelligence=iint;
}
void Attributes::SetSpi(int spi)
{
  this->Spirit=spi;

}
int Attributes::getStr()
{
  return this->Strength;
}
int Attributes::getDex()
{
  return this->Dexterity;

}
int Attributes::getCon()
{
  return this->Constitution;

}
int Attributes::getInt()
{

  return this->Intelligence;
}
int Attributes::getSpi()
{
  return this->Spirit;

}


GeneralStats::GeneralStats(int hp,int sp,int xp):HealthPoints(hp),Speed(sp),Experience(xp)
{
  canMove=true;
  canCast=true;
  canAttack=true;


}
GeneralStats::GeneralStats(int hp,int sp,int xp,bool CM,bool CC,bool CA):HealthPoints(hp),Speed(sp),Experience(xp),canMove(CM),canCast(CC),canAttack(CA)
{

}
void GeneralStats::SetHp(int hp)
{
  this->HealthPoints=hp;

}
void  GeneralStats::SetSpeed(int speed)
{
  this->Speed=speed;

}
void GeneralStats::SetXp(int xp)
{
  this->Experience=xp;
}
int GeneralStats::getHp()
{
  return this->HealthPoints;
}
int GeneralStats::getSpeed()
{

  return this->Speed;

}
int GeneralStats::getXp()
{
  return this->Experience;

}

int GeneralStats::getLevel()
{
  for(int i=1;i<7;i++)
    {
      if(Experience<(i+1)*(i)*500)
	return i;
    }
  return -1;
}

bool GeneralStats::CanCast()
{
  return this->canCast;
}
bool GeneralStats::CanMove()
{
  return this->canMove;

}
bool GeneralStats::CanAttack()
{
  return this->canAttack;

}
void GeneralStats::SetCast(bool cast)
{
  this->canCast=cast;
}
void GeneralStats::SetMove(bool move)
{

  this->canMove=move;
}
void GeneralStats::SetAttacK(bool attack)
{

  this->canAttack=attack;
}




CombatStats::CombatStats(int BAB,int tohit,int Dmg,int AC,int SR):BaseAttackBonus(BAB),ToHitBonus(tohit),Damage(Dmg),ArmorClass(AC),SpellResistance(SR)
{

}
int CombatStats::getBAB()
{
  return this->BaseAttackBonus;
}
int CombatStats::getTohitBonus()
{
  return this->ToHitBonus;
}
int CombatStats::getDamage()
{
  return this->Damage;
}
int CombatStats::getArmorClass()
{

  return this->ArmorClass;

}
int CombatStats::getSR()
{

  return this->SpellResistance;

}
void CombatStats::SetBAB(int BAB)
{

  this->BaseAttackBonus=BAB;
}
void CombatStats::SetToHitBonus(int tohit)
{
  this->ToHitBonus=tohit;

}
void CombatStats::SetDamage(int dmg)
{
  this->Damage=dmg;

}
void CombatStats::SetArmorClass(int ac)
{

  this->ArmorClass=ac;

}
void CombatStats::SetSR(int sr)
{
  this->SpellResistance=sr;

}

SpellStats::SpellStats(int range,int radius,int mastery,int level,AOE aoe_type,pair<int,int> target,bool target_req,SPELL_DIRECTION dir)
  :range(range),radius(radius),mastery(mastery),level(level),aoe_type(aoe_type),target(target),requires_target(target_req),dir(dir)
{
  
}

SpellStats::SpellStats(int range,int radius,int mastery,int level,AOE aoe_type,pair<int,int> target,bool target_req)
  :range(range),radius(radius),mastery(mastery),level(level),aoe_type(aoe_type),target(target),requires_target(target_req)
{
  dir=S_NONE;
}
SpellStats::SpellStats(int range,int radius,int mastery,int level,AOE aoe_type,bool target_req)
  :range(range),radius(radius),mastery(mastery),level(level),aoe_type(aoe_type),requires_target(target_req)
{
  dir=S_NONE;
  target.first=-1;//INVALID
  target.second=-1;//INVALID
}
int SpellStats::GetRange()
{

  return this->range;
}
									 

int SpellStats::GetRadius()
{
  return this->radius;
}
int SpellStats::GetMastery()
{
  return this->mastery;
}

int SpellStats::GetLevel()
{
  return this->level;
}
AOE SpellStats::GetAoeType()
{
  return this->aoe_type;
}

bool SpellStats::GetTargetReq()
{
  return this->requires_target;
}

SPELL_DIRECTION SpellStats::GetDirection()
{
  return this->dir;
}

pair<int,int> SpellStats::GetTarget()
{
  return this->target;
}
void SpellStats::SetRange(int range)
{
  this->range=range;
}
void SpellStats::SetRadius(int radius)
{
  this->radius=radius;
}
void SpellStats::SetMastery(int mastery)
{
  this->mastery=mastery;
}

void SpellStats::SetLevel(int level)
{
  this->level=level;
}
void SpellStats::SetAoeType(AOE aoe_t)
{
  this->aoe_type=aoe_t;
}

void SpellStats::SetTarget(pair<int,int> target)
{
  this->target=target;
}

void SpellStats::SetTargetReq(bool target_req)
{
  this->requires_target=target_req;
}

void SpellStats::SetDirection(SPELL_DIRECTION dir)
{
  this->dir=dir;
}
// convert to int instead
enum SPELL_SCHOOL school_string_to_enum(std::string school_name)
{
  if(school_name=="Abjuration")
    return ABJURATION;
  else  if(school_name=="Conjuration")
    return CONJURATION;
  else  if(school_name=="Divination")
    return DIVINATION;
  else  if(school_name=="Enchantment")
    return ENCHANTMENT;
  else  if(school_name=="Evocation")
    return EVOCATION;
  else  if(school_name=="Illusion")
    return ILLUSION;
  else  if(school_name=="Necromancy")
    return NECROMANCY;
  else  if(school_name=="Transmutation")
    return TRANSMUTATION;
}

CasterStats::CasterStats(int spell_slots[6][10],int mastery[8])
{

  for(int i=0;i<6;i++)
    for(int j=0;j<10;j++)
      this->spell_slots[i][j]=spell_slots[i][j];

  for(int i=0;i<8;i++)
    this->mastery[i]=mastery[i];
}
int CasterStats::GetSpellSlots(int char_level,int spell_level)
{
  if(char_level<6 && char_level>=0 && spell_level<10 && spell_level >=0)
  return spell_slots[char_level][spell_level];
  return -1;
}
int CasterStats::GetMastery(enum SPELL_SCHOOL school)
{
  return mastery[school];
}

int CasterStats::GetMastery(int school)
{
  return mastery[school];
}


void CasterStats::SetSpellSlots(int char_level,int spell_level,int slots)
{
  spell_slots[char_level][spell_level]=slots;
}
void CasterStats::SetMastery(enum SPELL_SCHOOL school,int rankz)
{
  mastery[school]=rankz;
}

void CasterStats::SetMastery(int school,int rankz)
{
  mastery[school]=rankz;
}
