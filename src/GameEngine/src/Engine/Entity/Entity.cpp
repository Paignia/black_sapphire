#include "Entity.h"
#include "BaseRenderer.h"
#include <cmath>
#include <iostream>
using std::cout;
using std::endl;

Entity::Entity(SDL_Texture  *t,int w,int h):tex(t),width(w),height(h)
{
  position.x=0;
  position.y=0;
  position.h=height;
  position.w=width;
}

Entity::Entity(const Entity &anentity)
{
  cout<<"COPYING"<<endl;
  this->width=anentity.width;
  this->height=anentity.height;
  
  position.x=0;
  position.y=0;
  position.h=height;
  position.w=width;
  //Create a duplicate texture trying to duplicate a texture created from a surface does not seem to work hacking the destructor to ignore if there is no texture and reusing the same texture for now//
  //SDL_RenderClear(BaseRenderer::Instance()->Renderer());
  this->tex=anentity.tex;
    /*this->tex=SDL_CreateTexture(BaseRenderer::Instance()->Renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width,height);
	      BaseRenderer::Instance()->RenderTexture(anentity.tex,tex,NULL,NULL);*/
}

Entity::~Entity()
{
  SDL_DestroyTexture(tex);
  tex=NULL;
}


void Entity::Draw(SDL_Texture *screen)
{

    SDL_Rect rect;
    rect.x=0;
    rect.y=0;
    rect.w=width;
    rect.h=height;
    SDL_Rect temprect;
    temprect=position;
    temprect.y=position.y-(height-TILE_SIZE-TILE_SIZE/4);
    temprect.x=position.x-(width/2-TILE_SIZE/2);
    //SDL_BlitSurface(surf,&rect,screen,&temprect);
    //SDL_RenderCopy(renderer,tex,NULL,&temprect);
    BaseRenderer::Instance()->RenderTexture(tex,screen,NULL,&temprect);
}

void Entity::Update(float time)
{

}
void Entity::setPosition(int x,int y,int w,int h)
{
    position.x=x;
    position.y=y;
    position.w=w;
    position.h=h;
}
void Entity::setPosition(int x,int y)
{
    this->position.x=x;
    this->position.y=y;
}

void Entity::setPosition(SDL_Rect pos)
  {
    position=pos;
  }

SDL_Rect Entity::getPosition()
  {
    return position;
  }

SDL_Rect Entity::getRect()
{

    SDL_Rect rect;
    rect.x=position.x;
    rect.y=position.y;
    rect.w=position.w;
    rect.h=position.h;
    return rect;

}



int Entity::distance(Entity *ent)
{
    SDL_Rect rect=getRect();
    return (int)sqrt( pow(float (ent->getRect().x-rect.x),2)+pow(float(ent->getRect().y-rect.y),2));
}
