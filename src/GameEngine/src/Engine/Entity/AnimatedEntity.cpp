#include "AnimatedEntity.h"
#include <fstream>
#include <iostream>
#include <string>
using std::ifstream;
using std::ios;
using std::string;
using std::cout;
#include "Tokenizer.h"
#include "BaseRenderer.h"


AnimatedEntity::AnimatedEntity(SDL_Texture *t,int w,int h):MovingEntity(t,w,h)
{
  cur_anim=NULL;
  animloop=NO;
}

AnimatedEntity::AnimatedEntity(const AnimatedEntity &anentity):MovingEntity(anentity)
{
  cout<<"COPYING"<<endl;
  //animations.resize(anentity.animations.size());
  for(int i=0;i<anentity.animations.size();i++)
    {
      Anim *a=new Anim(*anentity.animations[i]);	
      animations.push_back(a);
    }
  cur_anim=anentity.cur_anim;
  animloop=anentity.animloop;
}

AnimatedEntity::~AnimatedEntity()
{
  for( int i=0;i<animations.size();i++)
    {
      delete animations[i];
    }
  
}


void AnimatedEntity::Update(float time)
{
  Point2d prevdir=dir;
  MovingEntity::Update(time);
  if(cur_anim!=NULL)
    cur_anim->run();
  if(animloop==YES)
    if(cur_anim->Done())
      {
	cur_anim->Reset();
      }

}

/*
Anim* AnimatedEntity::getCur_Anim()
{
  return cur_anim;
}
int AnimatedEntity::getNumAnims()
{
  return animations.size();
}
*/  




void AnimatedEntity::Draw(SDL_Texture *screen)
{
  if(cur_anim==NULL)
    {
      Entity::Draw(screen);

    }
  else
    {

      SDL_Rect temprect;
      temprect=position;
      temprect.y=position.y-(height-TILE_SIZE);
      temprect.x=position.x-(width-TILE_SIZE)/2;
      BaseRenderer::Instance()->RenderTexture(tex,screen,cur_anim->getCurFrame(),&temprect);
    }
}

void AnimatedEntity::DrawAt(int x,int y,SDL_Texture *screen)
{
  if(cur_anim==NULL)
    {
      Entity::Draw(screen);

    }
  else
    {
      SDL_Rect temprect;
      temprect=position;
      temprect.y=y+position.y-(height-TILE_SIZE);
      temprect.x=x+position.x-(width-TILE_SIZE)/2;

      BaseRenderer::Instance()->RenderTexture(tex,screen,cur_anim->getCurFrame(),&temprect);
    }
  
}

void AnimatedEntity::DrawFrame(int framenum,int x,int y,SDL_Texture *screen)
{
  SDL_Rect temprect;
  temprect=position;
  temprect.y=y+position.y-(height-TILE_SIZE);
  temprect.x=x+position.x-(width-TILE_SIZE)/2;
  BaseRenderer::Instance()->RenderTexture(tex,screen,cur_anim->getFrame(framenum),&temprect);
}

bool AnimatedEntity::LoadAnimations(char *file)
{
  
  ifstream in;
  in.open(file,ios::in);
  string line;
  Tokenizer tok;
  tok.setDelimeter(",");
  if(!in.is_open())
    {
      cout<<"ERROR OPENING"<<file<<endl;
      in.close();
      return false;
    }
  while(getline(in,line))
    {

      tok.setInput(line);
      vector<string> animstats=tok.split();
      int startx=atoi(animstats[0].c_str());
     
      int starty=atoi(animstats[1].c_str());
     
      int width=atoi(animstats[2].c_str());
     
      int height=atoi(animstats[3].c_str());
     
      int numframes=atoi(animstats[4].c_str());
     
      // cout<<"animation loaded:"<<startx<<','<<starty<<','<<width<<','<<height<<','<<numframes<<endl;
      try
        {
	  this->animations.push_back(new Anim(startx,starty,width,height,numframes));
        }
      catch(std::exception e)
        {
	  cout<<e.what()<<endl;
        }



    }

  in.close();
  if(this->animations.size()>0)
    return true;
  return false;

}



void AnimatedEntity::setAnimLoop(ANIMLOOP animloop)
{
  this->animloop=animloop;
}


/*void AnimatedEntity::setAnimation(Anim *anim)
  {
  this->cur_anim=anim;
  cur_anim->Reset();
  }*/
void AnimatedEntity::setAnimation(int animnum)
{
  this->cur_anim=animations[animnum];
  cur_anim->Reset();

}



void AnimatedEntity::setAnimation(ANIMS a)
{
  this->cur_anim=animations[a];
  cur_anim->Reset();

}
