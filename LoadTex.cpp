#include "LoadTex.h"

bool Texture::LoadFromFile(std::string path)
{
	Texture::freeTex();

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadSurface = IMG_Load(path.c_str());
	if (loadSurface == NULL)
	{
		std::cout << "Can't load image! - " << IMG_GetError() << std::endl;
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(texRenderer, loadSurface);
		if (newTexture == NULL)
		{
			std::cout << "can't create texture from " << path.c_str() << " - " << SDL_GetError() << std::endl;
		}
		else
		{
			texWidth = loadSurface->w;
			texHeight = loadSurface->h;
		}
		SDL_FreeSurface(loadSurface);
	}
	texObj = newTexture;
	return (texObj != NULL);
}

bool Texture::loadFont(std::string texturetext, SDL_Color textColor, TTF_Font *font)
{
	Texture::freeTex();

	SDL_Surface* fontSurface = TTF_RenderText_Solid(font, texturetext.c_str(), textColor);
	if (fontSurface == NULL)
	{
		std::cout << "Failed to load font - " << TTF_GetError() << std::endl;
	}
	else
	{
		texObj = SDL_CreateTextureFromSurface(texRenderer, fontSurface);

		if (texObj == NULL)
		{
			std::cout << "Failed to create texture from font - " << SDL_GetError() << std::endl;
		}
		else
		{
			texWidth = fontSurface->w;
			texHeight = fontSurface->h;
		}

		SDL_FreeSurface(fontSurface);

	}
	return (texObj != NULL);
}

void Texture::freeTex()
{
	if (texObj != NULL)
	{
		SDL_DestroyTexture(texObj);
		texObj = NULL;
		texWidth = 0;
		texHeight = 0;
	}
}

void Texture::render(int tX, int tY, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { tX, tY, texWidth, texHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
		SDL_RenderCopyEx(texRenderer, texObj, clip, &renderQuad,angle,center,flip);
	}
	else
	{
		SDL_RenderCopyEx(texRenderer, texObj, NULL, &renderQuad,angle,center,flip);
	}
}

void Texture::loadRenderer(SDL_Renderer &renderer)
{
	texRenderer = &renderer;
}



void Sprite::setAsAnimation(int keyFrames, int aniDelay)
{
	totalFrames = keyFrames - 1;
	animationDelay = aniDelay;
	currentFrame = totalFrames;
}

SDL_Rect* Sprite::animate(int animateXPos, int animateYPos, int clipWidth, int clipHeight)
{
	aniKeyFrame = { animateXPos + (currentFrame * clipWidth), animateYPos, clipWidth, clipHeight};
	
	if (totalFrames >= 0)
	{
		if (delayFramesLeft == 0)
		{
			delayFramesLeft = animationDelay;
			++currentFrame;
		}
		else
		{
			--delayFramesLeft;
		}
	}
	if (currentFrame > totalFrames)
	{
		currentFrame = 0;
	}

	return &aniKeyFrame;
}

void Background::toggleParallax()
{
	if (isParallax)
		isParallax = false;
	else
		isParallax = true;
}

void Background::bgRender(int delay)
{
	if (isParallax)
	{
		render(xOffset, 0, NULL);
		render(xOffset - getWidth(), 0, NULL);

		if (parallaxDelay < delay)
		{
			parallaxDelay++;
		}
		else
		{
			xOffset++;
			parallaxDelay = 0;
			if (xOffset > getWidth())
				xOffset = 0;
		}
	}
	else
	{
		render(0, 0, NULL);
	}
}

Texture::Texture()
{
	texObj = NULL;
	texWidth = 0;
	texHeight = 0;
	texRenderer = nullptr;
}

Texture::~Texture()
{
	freeTex();
}

int Texture::getWidth()
{
	return texWidth;
}

int Texture::getHeight()
{
	return texHeight;
}

SDL_Texture* Texture::getTexture()
{
	return texObj;
}

Sprite::Sprite()
{
	totalFrames = 0;	//0 if just standard texture, >= 1 if animated
	currentFrame = 0;	//0 if texture, incremental if animated.
	animationDelay = 0; //0 if texture, check increment if animated
	delayFramesLeft = 0;//>0 if animated, otherwise textured
	aniKeyFrame = { 0,0,0,0 };
}

Sprite::~Sprite()
{
	totalFrames = 0;
	currentFrame = 0;
	animationDelay = 0;
	delayFramesLeft = 0;
	aniKeyFrame = { 0,0,0,0 };
}

Background::Background()
{
	isParallax = false;
	parallaxDelay = 0;
	xOffset = 0;
}

Background::~Background()
{
	isParallax = false;
	parallaxDelay = 0;
	xOffset = 0;
}