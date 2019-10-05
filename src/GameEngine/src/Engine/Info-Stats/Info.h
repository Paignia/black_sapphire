#include <string>
using namespace std;

#ifndef __INFO__
#define __INFO__
class Info
{
private:
    string Name;
    string Class;
    string Race;
    string Gender;
public:
    Info(string Name="UNKNOWN",string Class="UNKNOWN",string Race="UNKNOWN",string Gender="UNKNOWN");
    string getName()
    {
        return Name;
    }
    string getClass()
    {
        return Class;
    }
    string getRace()
    {
        return Race;
    }
    string getGender()
    {
        return Gender;
    }
};


class SpellInfo
{
private:
    string Name;
    string Class;
    string School;
    string Description;
public:
    SpellInfo(string Name="UNKNOWN",string Class="UNKNOWN",string School="UNKNOWN",string Description="UNKNOWN");
    string getName()
    {
        return Name;
    }
    string getClass()
    {
        return Class;
    }
    string getSchool()
    {
        return School;
    }
    string getDescription()
    {
        return Description;
    }
};

enum ITEMSLOT {Head=0,Chest,Legs,MainWeapon,SecondWeapon,Ammo,Neck,Hand1,Hand2,NONE};
enum ITEMTYPE {WEAPON=0,ARMOR,ONHEAD,OTHER};
class ItemInfo
{
protected:
    string name;
    string description;
    ITEMSLOT slot;
    ITEMTYPE type;
public:
    ItemInfo(string name="UNKNOWN",string description="UNKNOWN",ITEMSLOT is=NONE,ITEMTYPE it=OTHER):name(name),description(description),slot(is),type(it)
    {

    }
    string getName()
    {
        return name;
    }
    string getDescription()
    {
        return description;
    }
    ITEMSLOT getItemSlot()
    {
        return slot;
    }
    ITEMTYPE getItemType()
    {
        return type;
    }
    void setItemSlot(ITEMSLOT slot)
    {
      this->slot=slot;
    }

    virtual string InfoString();

};

enum WEAPONTYPE{DAGGER,SWORD,BOW,SPEAR,QUARTERSTAFF,WEAPON_SECONDARY,WEAPON_OTHER};
enum BASEDAMAGETYPE {SLASHING=0,PIERCING,BLUDGEONING,FORCE,FIRE,FROST,ACID,ELECTRICAL,SONIC,RAW,NO_DMG};
class WeaponInfo:public ItemInfo
{
private:
    int range;
    int dmg;
    int tohitbonus;
    int dmgbonus;
    WEAPONTYPE wpntype;
    BASEDAMAGETYPE  dmgtype;

public:
    WeaponInfo(string name,string description,int range,int dmg,int tohitbonus,int dmgbonus,BASEDAMAGETYPE dmgt,WEAPONTYPE wpntype);

    int getRange()
    {
        return range;
    }
    int getDamage()
    {
        return dmg;
    }
    int getToHitBonus()
    {
        return tohitbonus;
    }
    int getDamageBonus()
    {
        return dmgbonus;
    }
    BASEDAMAGETYPE getDamageType()
    {
        return dmgtype;
    }
    
    WEAPONTYPE getWeaponType()
    {
      return wpntype;
    }


    virtual string InfoString();

};


enum ARMORTYPE{ARMOR_LIGHT=0,ARMOR_MEDIUM,ARMOR_HEAVY,ARMOR_OTHER};
class ArmorInfo:public ItemInfo
{
private:
    int BaseDeff;
    int Armor;
    int BonusDeff;
    ARMORTYPE armtype;

    //STATSOBJECT?

public:
    ArmorInfo(string name="UNKNOWN",string description="UNKNOWN",ITEMSLOT slot=Chest,ITEMTYPE it=ARMOR,int BaseDef=0,int BonusDef=0,int Armor=0,ARMORTYPE armtype=ARMOR_OTHER);


    int getBaseDef()
    {
        return BaseDeff;
    }
    int getArmor()
    {
        return Armor;
    }
    int getBonusDeff()
    {
        return BonusDeff;
    }

    ARMORTYPE getArmorType()
    {
      return armtype;
    }

    virtual string InfoString();

};





#endif
