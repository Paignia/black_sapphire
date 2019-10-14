#include "SpellEffects.h"
#include "MapIndex.h"
#include "KnowledgePool.h"
#include "BasicCharacter.h"
#include "Die.h"
#include "Effect.h"
#include "Distances.h"
SpellEffect spellarchives[]=
  {
    {"DeathEffect",DeathEffect},
    {"FireballEffect",FireballEffect},
    {"ArcaneBlastEffect",ArcaneBlastEffect},
    {"MageArmorEffect",MageArmorEffect},
    {"IceShardEffect",IceShardEffect},
    {"CureEffect",CureEffect},
    {"IceCageEffect",IceCageEffect},
    {"FlashFireEffect",FlashFireEffect},
    {"WhirlwindEffect",WhirlwindEffect},
    {"StinkingCloudEffect",StinkingCloudEffect},
    {"ForcePushEffect",ForcePushEffect},
    {"StoneWallEffect",StoneWallEffect},
    {"StoneWallBuiltEffect",StoneWallBuiltEffect},
    {"StoneWallExpiredEffect",StoneWallExpiredEffect},
    {"DisintegrationEffect",DisintegrationEffect},
    {"ConeOfColdEffect",ConeOfColdEffect},
    //Effects
    {"StunnedEffect",StunnedEffect},
    {"DisabledEffect",DisabledEffect},
    {"ShieldEffect",ShieldEffect},
    {NULL,NULL}
  };

int LookUpSpell(const char *spell_name)
{
  int i=0;
  while(spellarchives[i].spell_name!=NULL)
    {
      if(strcmp(spellarchives[i].spell_name,spell_name)==0)
	{
	  return i;
	}
      i++;
    }
  return -1;

}

void DeathEffect(SpellStats *sp_stats)
{

  if(sp_stats->GetAoeType()==DISK)
    {
      int xpos=sp_stats->GetTarget().second/MapIndex::Instance()->getMap()->getTileSize();
      int ypos=sp_stats->GetTarget().first/MapIndex::Instance()->getMap()->getTileSize();
  
      vector<CellInfo*> entities= MapIndex::Instance()->getEntitiesInRange(xpos,ypos,sp_stats->GetRadius());

      for(int i=0;i<entities.size();i++)
	{
	  if(entities[i]!=NULL && entities[i]->getType()==CHARACTER_T)
	    {
	      BaseCharacter *affected=KnowledgePool::Instance()->getCharacter(entities[i]->getID());
	      affected->getGeneralStats()->SetHp(affected->getGeneralStats()->getHp()-affected->getGeneralStats()->getHp());
	    }
	}
    }
}

void ArcaneBlastEffect(SpellStats *sp_stats)
{

  if(sp_stats->GetAoeType()==SINGLE)
    {
      int xpos=sp_stats->GetTarget().second/MapIndex::Instance()->getMap()->getTileSize();
      int ypos=sp_stats->GetTarget().first/MapIndex::Instance()->getMap()->getTileSize();
  
      CellInfo* entity= MapIndex::Instance()->getCell(xpos,ypos);
      if(entity!=NULL && entity->getType()==CHARACTER_T)
	{
	  BaseCharacter *affected=KnowledgePool::Instance()->getCharacter(entity->getID());
	  int damage=Die::Roll(4,sp_stats->GetLevel()+1)+sp_stats->GetMastery();
	  affected->getGeneralStats()->SetHp(affected->getGeneralStats()->getHp()-damage);
	  cout<<affected->getInfo()->getName()<<" took "<<damage<<" points of arcane damage"<<endl;
	}
	
    }
}


void FireballEffect(SpellStats *sp_stats)
{
  if(sp_stats->GetAoeType()==DISK)
    {
      int xpos=sp_stats->GetTarget().second/MapIndex::Instance()->getMap()->getTileSize();
      int ypos=sp_stats->GetTarget().first/MapIndex::Instance()->getMap()->getTileSize();
  
      vector<CellInfo*> entities= MapIndex::Instance()->getEntitiesInRange(xpos,ypos,sp_stats->GetRadius());

      for(int i=0;i<entities.size();i++)
	{
	  if(entities[i]!=NULL && entities[i]->getType()==CHARACTER_T)
	    {
	      //Effect-Logic
	      BaseCharacter *affected=KnowledgePool::Instance()->getCharacter(entities[i]->getID());
	      int damage=Die::Roll(6,sp_stats->GetMastery()*sp_stats->GetLevel());
	      affected->getGeneralStats()->SetHp(affected->getGeneralStats()->getHp()-damage);
	      cout<<affected->getInfo()->getName()<<" took "<<damage<<" points of fire damage"<<endl;
	    }
	}
    } 
}

void CureEffect(SpellStats *sp_stats)
{
  if(sp_stats->GetAoeType()==SINGLE)
    {
      int xpos=sp_stats->GetTarget().second/MapIndex::Instance()->getMap()->getTileSize();
      int ypos=sp_stats->GetTarget().first/MapIndex::Instance()->getMap()->getTileSize();

      CellInfo* entity= MapIndex::Instance()->getCell(xpos,ypos); 
      if(entity!=NULL && entity->getType()==CHARACTER_T)
	{

	  BaseCharacter *affected=KnowledgePool::Instance()->getCharacter(entity->getID());
	  int health=Die::Roll(8,sp_stats->GetMastery());
	  affected->getGeneralStats()->SetHp(affected->getGeneralStats()->getHp()+health);
	  if(affected->getGeneralStats()->getHp()>affected->getOriginalStats()->getHp())
	    affected->getGeneralStats()->SetHp(affected->getOriginalStats()->getHp()+health);
	  cout<<affected->getInfo()->getName()<<" heals for "<<health<<" points of damage"<<endl;
	}
    }
}


void MageArmorEffect(SpellStats *sp_stats)
{


}


void IceCageEffect(SpellStats *sp_stats)
{
  cout<<"Ice Cage Effect"<<endl;
  //Really Stupid
   if(sp_stats->GetAoeType()==DISK)
    {
      int xpos=sp_stats->GetTarget().second/MapIndex::Instance()->getMap()->getTileSize();
      int ypos=sp_stats->GetTarget().first/MapIndex::Instance()->getMap()->getTileSize();
  
      CellInfo* entity= MapIndex::Instance()->getCell(xpos,ypos);


      if(entity!=NULL && entity->getType()==CHARACTER_T)
	{
	  BaseCharacter *affected=KnowledgePool::Instance()->getCharacter(entity->getID());
	  int damage=Die::Roll(4*sp_stats->GetMastery(),sp_stats->GetLevel()*sp_stats->GetMastery());
	  affected->getGeneralStats()->SetHp(affected->getGeneralStats()->getHp()-damage);

	  //Also Disable For D4 turns
	  int duration=Die::Roll(4,1);
	  cout<<affected->getInfo()->getName()<<" took "<<damage<<" points of ice damage and will be stunned for "<<duration<<" rounds"<<endl;
	  SpellStats *effect_stats=new SpellStats(0,0,sp_stats->GetMastery(),sp_stats->GetLevel(),SINGLE,sp_stats->GetTarget(),true);
	  Effect *effect=new Effect("Stunned",duration,duration,false,StunnedEffect,effect_stats);
	  affected->Add_Effect(effect);
	  
	}
	
    }
}

void IceShardEffect(SpellStats *sp_stats)
{
if(sp_stats->GetAoeType()==SINGLE)
    {
      int xpos=sp_stats->GetTarget().second/MapIndex::Instance()->getMap()->getTileSize();
      int ypos=sp_stats->GetTarget().first/MapIndex::Instance()->getMap()->getTileSize();
  
      CellInfo* entity= MapIndex::Instance()->getCell(xpos,ypos);
      if(entity!=NULL && entity->getType()==CHARACTER_T)
	{
	  BaseCharacter *affected=KnowledgePool::Instance()->getCharacter(entity->getID());
	  int damage=Die::Roll(8,sp_stats->GetLevel())*sp_stats->GetMastery();
	  affected->getGeneralStats()->SetHp(affected->getGeneralStats()->getHp()-damage);
	  int duration=Die::Roll(4,sp_stats->GetMastery());
	  SpellStats *effect_stats=new SpellStats(0,0,sp_stats->GetMastery(),sp_stats->GetLevel(),SINGLE,sp_stats->GetTarget(),true);
	  Effect *effect=new Effect("Imobilized",duration,duration,false,DisabledEffect,effect_stats);
	  cout<<affected->getInfo()->getName()<<" took "<<damage<<" points of frost damage and is imobilized for "<<duration<<endl;
	  affected->Add_Effect(effect);
	}
	
    }
  

}

void FlashFireEffect(SpellStats *sp_stats)
{

  cout<<"Flash Fire Effect"<<endl;
  //Really Stupid
   if(sp_stats->GetAoeType()==DISK)
    {
      int xpos=sp_stats->GetTarget().second/MapIndex::Instance()->getMap()->getTileSize();
      int ypos=sp_stats->GetTarget().first/MapIndex::Instance()->getMap()->getTileSize();
  
      CellInfo* entity= MapIndex::Instance()->getCell(xpos,ypos);


      if(entity!=NULL && entity->getType()==CHARACTER_T)
	{
	  BaseCharacter *affected=KnowledgePool::Instance()->getCharacter(entity->getID());
	  int damage=Die::Roll(8,sp_stats->GetLevel()*sp_stats->GetMastery());
	  affected->getGeneralStats()->SetHp(affected->getGeneralStats()->getHp()-damage);

	  //Also Disable For D4 turns
	  int duration=Die::Roll(4,1);
	  cout<<affected->getInfo()->getName()<<" took "<<damage<<" points of fire damage"/* and will be stunned for "<<duration<<" rounds"*/<<endl;
	  //	  Effect *effect=new Effect("Burn",duration,duration,false,BurnedEffect,sp_stats);
	  // affected->Add_Effect(effect);
	  
	}
	
    }
  
}


void WhirlwindEffect(SpellStats *sp_stats)
{

   if(sp_stats->GetAoeType()==DISK)
    {
      int xpos=sp_stats->GetTarget().second/MapIndex::Instance()->getMap()->getTileSize();
      int ypos=sp_stats->GetTarget().first/MapIndex::Instance()->getMap()->getTileSize();
  
      vector<CellInfo*> entities= MapIndex::Instance()->getEntitiesInRange(xpos,ypos,sp_stats->GetRadius());

      for(int i=0;i<entities.size();i++)
	{
	  if(entities[i]!=NULL && entities[i]->getType()==CHARACTER_T)
	    {
	      //Effect-Logic
	      BaseCharacter *affected=KnowledgePool::Instance()->getCharacter(entities[i]->getID());
	      int damage=Die::Roll(6,sp_stats->GetMastery()*sp_stats->GetLevel()/2);
	      affected->getGeneralStats()->SetHp(affected->getGeneralStats()->getHp()-damage);
	      cout<<affected->getInfo()->getName()<<" took "<<damage<<" points of ?wind? damage"<<endl;
	      //Displace
		int tile_size=MapIndex::Instance()->getMap()->getTileSize();
		int affected_x=affected->getPosition().x/tile_size;
		int affected_y=affected->getPosition().y/tile_size;
		cout<<"affected x:"<<affected_x<<" y:"<<affected_y<<endl;
		cout<<"xpos:"<<xpos<<" ypos:"<<ypos<<endl;
		if(affected_x<ypos   )
		  {
		    if( affected_x > 0)
		    affected_x--;
		  }
		else if(affected_x>ypos  )
		  {
		    if(affected_x<MapIndex::Instance()->getMap()->getWidth()-1)
		    affected_x++;
		  }
		if(affected_y<xpos)
		  {
		      if(affected_y > 0)
		    affected_y--;
		  }
		else if(affected_y>xpos  )
		  {
		    if(affected_y<MapIndex::Instance()->getMap()->getHeight()-1)
		    affected_y++;
		  }
		affected->SetPosition(affected_x*tile_size,affected_y*tile_size);
	      cout<<"Index Update:"<<MapIndex::Instance()->CharIndexUpdate(affected,0,0)<<endl;
	    }
	}
    }
  
}

void StoneWallEffect(SpellStats *sp_stats)
{
 
}

void StoneWallBuiltEffect(SpellStats *sp_stats)
{
  int ypos=sp_stats->GetTarget().second/MapIndex::Instance()->getMap()->getTileSize();
  int xpos=sp_stats->GetTarget().first/MapIndex::Instance()->getMap()->getTileSize();
  for(int i=-sp_stats->GetRadius()+1;i<sp_stats->GetRadius();i++)
	{

	  if( (sp_stats->GetDirection()==S_LEFT || sp_stats->GetDirection()==S_RIGHT ) )
	    {
	      MapIndex::Instance()->getMap()->Set(xpos+i,ypos,2,LCOLISION);
	    }
	  else if( (sp_stats->GetDirection()==S_UP || sp_stats->GetDirection()==S_DOWN ) )
	    {
	      MapIndex::Instance()->getMap()->Set(xpos,ypos+i,2,LCOLISION);
	    }
	}
}
void StoneWallExpiredEffect(SpellStats *sp_stats)
{
  cout<<"StoneWall Expired"<<endl;
  int ypos=sp_stats->GetTarget().second/MapIndex::Instance()->getMap()->getTileSize();
  int xpos=sp_stats->GetTarget().first/MapIndex::Instance()->getMap()->getTileSize();
  for(int i=-sp_stats->GetRadius()+1;i<sp_stats->GetRadius();i++)
	{
	   if( (sp_stats->GetDirection()==S_LEFT || sp_stats->GetDirection()==S_RIGHT )  && i>=0 && i<MapIndex::Instance()->getMap()->getWidth() )
	    {
	      MapIndex::Instance()->getMap()->Set(xpos+i,ypos,0,LCOLISION);
	    }
	  else if( (sp_stats->GetDirection()==S_UP || sp_stats->GetDirection()==S_DOWN )  && i<MapIndex::Instance()->getMap()->getHeight() )
	    {
	      MapIndex::Instance()->getMap()->Set(xpos,ypos+i,0,LCOLISION);
	    }
	}
  cout<<"StoneWall Expired Done"<<endl;
}

void DisintegrationEffect(SpellStats *sp_stats)
{
  cout<<"Disintegration Effect"<<endl;
  int tile_size=MapIndex::Instance()->getMap()->getTileSize();
  if(sp_stats->GetAoeType()==LINE)
    {
      int xpos=sp_stats->GetTarget().second/MapIndex::Instance()->getMap()->getTileSize();
      int ypos=sp_stats->GetTarget().first/MapIndex::Instance()->getMap()->getTileSize();

      DIRECTION dir;
      if(sp_stats->GetDirection()==S_LEFT)
	dir=LEFT;
      else if(sp_stats->GetDirection()==S_RIGHT)
	dir=RIGHT;
      else if(sp_stats->GetDirection()==S_UP)
	dir=UP;
      else if(sp_stats->GetDirection()==S_DOWN)
	dir=DOWN;
      else
	return;
      vector<CellInfo*> entities= MapIndex::Instance()->getEntitiesInLine(xpos,ypos,sp_stats->GetRadius(),dir);
      cout<<"Num Entities:"<<endl;
      for(int i=0;i<entities.size();i++)
	{
	  if(entities[i]!=NULL && entities[i]->getType()==CHARACTER_T)
	    {
	      //Effect-Logic
	      BaseCharacter *affected=KnowledgePool::Instance()->getCharacter(entities[i]->getID());
	      affected->getGeneralStats()->SetHp(0);
	    }
	}
    }
}

void ConeOfColdEffect(SpellStats *sp_stats)
{
  cout<<"Cone Of Cold Effect"<<endl;
}


void ForcePushEffect(SpellStats *sp_stats)
{
  int tile_size=MapIndex::Instance()->getMap()->getTileSize();
  int c_xpos=KnowledgePool::Instance()->getCharacter(1)->getPosition().x/tile_size;//
  int c_ypos=KnowledgePool::Instance()->getCharacter(1)->getPosition().y/tile_size;//
  int xpos=sp_stats->GetTarget().second/MapIndex::Instance()->getMap()->getTileSize();
  int ypos=sp_stats->GetTarget().first/MapIndex::Instance()->getMap()->getTileSize();
  CellInfo* entity= MapIndex::Instance()->getCell(xpos,ypos);
  BaseCharacter *affected=KnowledgePool::Instance()->getCharacter(entity->getID());
  //Displace

  int affected_x=affected->getPosition().x/tile_size;
  int affected_y=affected->getPosition().y/tile_size;
  cout<<"affected x:"<<affected_x<<" y:"<<affected_y<<endl;
  cout<<"xpos:"<<xpos<<" ypos:"<<ypos<<endl;
  if(affected_x<c_xpos   )
    {
      if( affected_x > 0)
	affected_x-=2;
    }
  else if(affected_x>c_xpos  )
    {
      if(affected_x<MapIndex::Instance()->getMap()->getWidth()-1)
	affected_x+=2;
    }
  if(affected_y<c_ypos)
    {
      if(affected_y > 0)
	affected_y-=2;
    }
  else if(affected_y>c_ypos  )
    {
      if(affected_y<MapIndex::Instance()->getMap()->getHeight()-1)
	affected_y+=2;
    }
  affected->SetPosition(affected_x*tile_size,affected_y*tile_size);
  cout<<"Index Update:"<<MapIndex::Instance()->CharIndexUpdate(affected,0,0)<<endl; 
}

void StinkingCloudEffect(SpellStats *sp_stats)
{

  if(sp_stats->GetAoeType()==CLOUD)
    {
      int xpos=sp_stats->GetTarget().second/MapIndex::Instance()->getMap()->getTileSize();
      int ypos=sp_stats->GetTarget().first/MapIndex::Instance()->getMap()->getTileSize();
  
      vector<CellInfo*> entities= MapIndex::Instance()->getEntitiesInRange(xpos,ypos,sp_stats->GetRadius());

      for(int i=0;i<entities.size();i++)
	{
	  if(entities[i]!=NULL && entities[i]->getType()==CHARACTER_T)
	    {
	      //Effect-Logic
	      BaseCharacter *affected=KnowledgePool::Instance()->getCharacter(entities[i]->getID());
	      int duration=Die::Roll(4,sp_stats->GetMastery()*sp_stats->GetLevel()/2);
	      cout<<affected->getInfo()->getName()<<" is Nauseated for "<<duration<<" rounds"<<endl;
	      SpellStats *effect_stats=new SpellStats(0,0,sp_stats->GetMastery(),sp_stats->GetLevel(),SINGLE,sp_stats->GetTarget(),true);
	      Effect *effect=new Effect("Nauseated",duration,duration,false,DisabledEffect,effect_stats);
	      affected->Add_Effect(effect);
	    }
	}
    }

}

void StunnedEffect(SpellStats *sp_stats)
{
   if(sp_stats->GetAoeType()==SINGLE)
    {
      int xpos=sp_stats->GetTarget().second/MapIndex::Instance()->getMap()->getTileSize();
      int ypos=sp_stats->GetTarget().first/MapIndex::Instance()->getMap()->getTileSize();

      CellInfo* entity= MapIndex::Instance()->getCell(xpos,ypos);

      
      if(entity!=NULL && entity->getType()==CHARACTER_T)
	{

	 BaseCharacter *affected=KnowledgePool::Instance()->getCharacter(entity->getID());
	  cout<<affected->getInfo()->getName()<<" is Stunned"<<endl;
	  affected->SetMoved(true);
	  affected->SetActionDone(true);
	}
	
    }
}

void DisabledEffect(SpellStats *sp_stats)
{
  if(sp_stats->GetAoeType()==SINGLE)
    {
      int xpos=sp_stats->GetTarget().second/MapIndex::Instance()->getMap()->getTileSize();
      int ypos=sp_stats->GetTarget().first/MapIndex::Instance()->getMap()->getTileSize();

      CellInfo* entity= MapIndex::Instance()->getCell(xpos,ypos);

      
      if(entity!=NULL && entity->getType()==CHARACTER_T)
	{
	 BaseCharacter *affected=KnowledgePool::Instance()->getCharacter(entity->getID());
	  cout<<affected->getInfo()->getName()<<" is Disabled"<<endl;
	  affected->SetMoved(true);
	}
	
    }
}


void ShieldEffect(SpellStats *sp_stats)
{


}
