// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Component.h"
#include "SDL2/SDL.h"
/**
 * @brief texturemanager. SDL_Texture에 대한 동작을 다룬다.
 * 텍스처를 할당하고, Draw Order에 따른 Draw를 구현한다.
 */
class SpriteComponent : public Component
{
public:
	// (Lower draw order corresponds with further back)
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }
protected:
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};
