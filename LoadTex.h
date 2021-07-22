#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/// <summary>
/// Base Class - Defines textures and loads them as appropriate
/// </summary>
class Texture
{
public:
	Texture();
	~Texture();
	
	/// <summary>
	/// Loads a texture from file
	/// </summary>
	/// <param name="path:">File path for texture, relevant to project/executable.</param>
	/// <returns>true if texture object != NULL, false otherwise</returns>
	bool LoadFromFile(std::string path);
	
	/// <summary>
	/// Loads a texture font using SDL_ttf
	/// </summary>
	/// <param name="texturetext:"> String of text to display for font</param>
	/// <param name="textColor:"> SDL_Color {R,G,B,A} struct for font</param>
	/// <param name="font:"> TTF_Font* font loaded in initialization</param>
	/// <returns>true if texture object != NULL, false otherwise</returns>
	bool loadFont(std::string texturetext, SDL_Color textColor, TTF_Font *font);
	
	/// <summary>
	/// Loads the renderer for use of the sprite.
	/// </summary>
	/// <param name="renderer"></param>
	void loadRenderer(SDL_Renderer &renderer);
	
	/// <summary>
	/// Free texture, destroy allocations
	/// </summary>
	void freeTex();
	
	/// <summary>
	/// Renders the texture
	/// </summary>
	/// <param name="tX:"> Texture X position</param>
	/// <param name="tY:"> Texture Y position</param>
	/// <param name="renderer:"> Reference to SDL_Renderer (most likely the main renderer)</param>
	/// <param name="clip:"> an SDL_Rect {x,y,w,h} clipping area</param>
	/// <param name="angle:"> Rotate the sprite in a certain angle</param>
	/// <param name="center:"> Center of rotation</param>
	/// <param name="flip:"> Sprite flipping using SDL_FLIP</param>
	void render(int tX, int tY, SDL_Rect* clip, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE); //Render texture - Set clip to NULL if not used
	
	int getWidth();
	int getHeight();
	SDL_Texture* getTexture();

private:
	SDL_Renderer* texRenderer;
	SDL_Texture* texObj;
	int texWidth;
	int texHeight;

};

/// <summary>
/// Sprite (Extends Texture) - Allows small chunks of textures to be loaded, and animated if necessary.
/// </summary>
class Sprite : public Texture
{
public:

	Sprite();
	~Sprite();

	/// <summary>
	/// Sets the current Texture up for animation
	/// </summary>
	/// <param name="keyFrames:"> The amount of keyframes to use for the animation</param>
	/// <param name="aniDelay:"> How many frames to delay for the animation (more is slower)</param>
	void setAsAnimation(int keyFrames, int aniDelay);

	/// <summary>
	/// animate the current Texture, provided it has keyframes to animate from.  If no keyframes exist, nothing will happen
	/// </summary>
	/// <param name="animateXPos:"> top left position of starting animation frame (X)</param>
	/// <param name="animateYPos:"> top left position of starting animation frame (Y)</param>
	/// <param name="clipWidth:"> width of the sprite (animated)</param>
	/// <param name="clipHeight:"> height of the sprite (animated)</param>
	/// <returns>SDL_Rect* clip</returns>
	SDL_Rect* animate(int animateXPos, int animateYPos, int clipWidth, int clipHeight);

private:
	SDL_Rect aniKeyFrame;
	int totalFrames;
	int animationDelay;
	int delayFramesLeft;
	int currentFrame;
};

/// <summary>
/// Background (Extends Texture) - loads background chunks, and allows for parallaxing.
/// </summary>
class Background : public Texture
{
public:

	Background();
	~Background();

	/// <summary>
	/// Toggles the parallaxing effect for the background
	/// </summary>
	void toggleParallax();

	/// <summary>
	/// Renders the background, given the delay.
	/// </summary>
	/// <param name="renderer:"> Renderer to push to (usually main renderer)</param>
	/// <param name="delay:"> Render delay for scrolling if parallaxed background.</param>
	void bgRender(int delay);

private:
	bool isParallax;
	int parallaxDelay;
	int xOffset;
};

