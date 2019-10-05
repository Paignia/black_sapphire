#include "AnimatedEntity.h"
#include "Info.h"
#include "Effect.h"
#include "Weapon.h"
#include "Armor.h"
#include "Projectile.h"
#include "InfoSurface.h"
#include <list>
#include "State.h"
using std::list;

#ifndef __BASICCHARACTER
#define __BASICCHARACTER


class CharacterHandler;
class BaseCharacter
{
private:
  //ID
  int ID;
  //Print Stuff to log
  InfoSurface *Log;
  //PORTRAIT
  SDL_Texture *portrait;
  //CHARACTER INFO AND STATS
  Info *info;
  Attributes *BaseAttributes;
  GeneralStats *originalStats;
  CombatStats  *BaseCombatStats;
  Attributes *currentAttributes;
  GeneralStats *generalStats;
  CombatStats *combatStats;

  //STATUS EFFECTS
  vector<Effect*> status_effects;
  vector<Item*> Inventory;
  //TURN BOOLEANS
  bool hasMoved;
  bool standardActionDone;
  bool reactiondone; 
  //Movement
  list<DIRECTION> path;
  int movementleft;

  //TARGET OF ATTACKS
  BaseCharacter *target;

  
 protected:
  //ENTITIES
  AnimatedEntity *BaseEntity;
  //ITEMS
  VisibleItem *legs,*head;
  Armor *chest;
  Weapon *mainHand,*secondaryHand;
  VisibleItem *ammo;
  Item *neck,*hand1,*hand2;
 //Facing Direction
  DIRECTION dir;
  //Projectile
  Projectile *projectile;
  //STATE HANDLER
  CharacterHandler* stateHandler;
public:
  //CTORS
  BaseCharacter(AnimatedEntity *base,Info *myinfo, Attributes *BaseAttributes,GeneralStats *generalStats,CombatStats *combatStats);
  //if we need to overload the statehandler pass whichever handler we want
  BaseCharacter(AnimatedEntity *base,Info *myinfo, Attributes *BaseAttributes,GeneralStats *generalStats,CombatStats *combatStats,CharacterHandler *s_handler);
  //DTOR
  virtual ~BaseCharacter();//Destroy everything
  //PORTRAIT
  void SetPortrait(SDL_Texture *portrait);
  SDL_Texture* GetPortrait();
  //ID
  void setID(int id);
  int getID();
  //LOGSTRING
  void SetLog(InfoSurface *mylog)
  {
    Log=mylog;
  }
  void ToLog(string s);

  //BaseEntity get
  AnimatedEntity* GetBaseEntity();

  //Items Equiped
  Armor* GetChest();
  Weapon* GetMainHand();

  //INFO AND STATS STUFF
  Attributes* getOriginalAttributes()
  {
    return BaseAttributes;

  }
  Attributes* getCurrentAttributes()
  {
    return currentAttributes;
  }
  GeneralStats* getGeneralStats()
  {
    return generalStats;
  }
  GeneralStats* getOriginalStats()
  {
    return originalStats;
  }
  virtual void CalculateCombatStats();
  CombatStats* getCombatStats()
  {
    if(combatStats != NULL)
      return combatStats;

    return NULL;
  }
  Info* getInfo()
  {
    return info;
  }

  vector<Item*>& getInventory(){return Inventory;}



  //ACTIONS
  virtual void Move(list<DIRECTION> path);//Plan path using map
  virtual bool Attack(BaseCharacter *ent);//empty overide in implementation
  virtual void Ability();//empty overide in implementation
  virtual bool Reaction(BaseCharacter *ent);//empty overide in implementation
    

  
  //GetPath
  list<DIRECTION>* GetPath();
  //Movement Info
  int GetMovementLeft();
  void SetMovementLeft(int movementleft);

  //Direction
  void SetDirection(DIRECTION dir);
  DIRECTION GetDirection();
    
    

  //DRAWABLE ABSTRACT {INTERFACE}
  virtual void Draw(SDL_Texture *screen);
  virtual void Update(float time);


  //ITEM STUFF
  Item* getSlot(ITEMSLOT slot);
  void AddItemToInventory(Item* item)
  {
    Inventory.push_back(item);
  }
  Item* getInventorySlot(int slotnum);
  Item* getInventoryItem(string name);
  void Equip(Item* item);
  virtual void SwitchMainWeapon(Weapon *mhand);
  virtual void SwitchSecondaryWeapon(Weapon *shand);
  virtual void SwitchArmor(Armor  *armor);
  virtual void SwitchHead(VisibleItem  *item);
  virtual void SwitchLegs(VisibleItem  *item);
  virtual void SwitchNeck(Item  *item);

  virtual void SwitchHand1(Item  *item);
  virtual void SwitchHand2(Item  *item);

  //ENTITY GROUP FUNCTIONS
  void SetPosition(int xpos,int ypos);
  void SetVelocity(int xvel,int yvel);
  SDL_Rect getPosition()
  {
    return BaseEntity->getPosition();
  }


  //EFFECTS
  void Add_Effect(Effect *eff)
  {
    this->status_effects.push_back(eff);
  }
  //Animation
  void SetAnimation(ANIMS anim);
  void SetUpAttackAnimation(BaseCharacter *ent);


  //STATES
  void setState(int s);
  int getState();

  //Move to the RuleSet??
  virtual bool AttackRoll(BaseCharacter *ent);
  virtual bool DamageRoll(BaseCharacter *ent);
  void Walk(DIRECTION dir);

  //TURN BOOLEANS 
  void SetMoved(bool moved);
  void SetActionDone(bool actiondone);
  void SetReactionDone(bool reactiondone);
  bool Moved();
  bool ActionDone();
  bool ReactionDone();
    


  //TEMP Probably remove later and map to (ranged) weapon    
  void SetProjectile(Projectile *proj);
  Projectile* getProjectile();


  //ACTIVE ACTIONS
  virtual bool Active();

  //Base Handlers
  void HandleState(float t);
  void HandleProjectile(float t);
  void HandleEffects();
  virtual void OnTurnStart();

  //StateHandler
  void SetStateHandler(CharacterHandler *s_handler);
  CharacterHandler* GetStateHandler();

  //Target
  void SetTarget(BaseCharacter *target);
  BaseCharacter* GetTarget();

};
#endif // __BASICCHARACTER
