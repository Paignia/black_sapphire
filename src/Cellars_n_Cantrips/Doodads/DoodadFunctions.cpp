#include "DoodadFunctions.h"
#include "MapIndex.h"
#include "KnowledgePool.h"

DoodadFunction_Entry DoodadFunctions[]=
  { {"DoorOpen",DoorOpen},
    {"DoorClose",DoorClose},
    {NULL,NULL}
  };


int LookUpDoodadFunction(const char *doodfunc_name)
{
  int i=0;
  while(DoodadFunctions[i].doodfunc_name!=NULL)
    {
      if(strcmp(DoodadFunctions[i].doodfunc_name,doodfunc_name)==0)
	{
	  return i;
	}
      i++;
    }
  return -1;
}


void DoorOpen(Doodad *doodad)
{
  doodad->GetEntity()->setAnimation(1);
  int tile_size=MapIndex::Instance()->getMap()->getTileSize();
  int xpos=doodad->GetEntity()->getPosition().x/tile_size;
  int ypos=doodad->GetEntity()->getPosition().y/tile_size;
  MapIndex::Instance()->getMap()->Set(xpos,ypos,0,LCOLISION);
  //Switch to current if we ever get into a multicharacter scenario÷
  MapIndex::Instance()->ComputeVision(KnowledgePool::Instance()->getCharacter(1)->getPosition());
}
void DoorClose(Doodad *doodad)
{
  doodad->GetEntity()->setAnimation(0);
  int tile_size=MapIndex::Instance()->getMap()->getTileSize();
  int xpos=doodad->GetEntity()->getPosition().x/tile_size;
  int ypos=doodad->GetEntity()->getPosition().y/tile_size;
  MapIndex::Instance()->getMap()->Set(xpos,ypos,doodad->getVisibility(),LCOLISION);
  //Switch to current if we ever get into a multicharacter scenario÷
  MapIndex::Instance()->ComputeVision(KnowledgePool::Instance()->getCharacter(1)->getPosition());
}

