#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include <psptypes.h>
#include <pspkerneltypes.h>
#include <pspiofilemgr.h>
#include <pspiofilemgr_fcntl.h>

#define	PSP_LINE_SIZE 512
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

typedef u32 Color;
#define A(color) ((u8)(color >> 24 & 0xFF))
#define B(color) ((u8)(color >> 16 & 0xFF))
#define G(color) ((u8)(color >> 8 & 0xFF))
#define R(color) ((u8)(color & 0xFF))

typedef struct
{
	int textureWidth;  // the real width of data, 2^n with n>=0
	int textureHeight;  // the real height of data, 2^n with n>=0
	int imageWidth;  // the image width
	int imageHeight;
	Color* data;
} Image;

typedef struct {
	char* name;
	FT_Face face;
	u8* data;
} Font;

int getNextPower2(int width);
Color* getVramDrawBuffer();
Color* getVramDisplayBuffer();
Image* LoadGFX(const char* filename);
Image* loadJpegImage(const char* filename);
void PutPixel(int x, int y, Color color);
void PutGFX(int sx, int sy, int width, int height, Image* source, int dx, int dy);
void PutText(int x, int y, const char* text, Color color);
void freeImage(Image* image);
void Screenshot(const char* filename, Color* data, int width, int height, int lineSize, int saveAlpha);
void PrintScreen();
Font* LoadFont(const char* filename);
void fontPrintTextScreen(FT_Bitmap* bitmap, int x, int y, Color color);
void fontPrintTextImpl(FT_Bitmap* bitmap, int xofs, int yofs, Color color, Color* framebuffer, int width, int height, int lineSize);
Font* SetPixelSize(Font* font, int width, int height);
Font* SetPointSize(Font* font, int width, int height, int dpiX, int dpiY);
void FontPrint(Font* font, int x, int y, const char* text, Color color);
void PutTextFont(int x, int y, const char* text, Color color);
void initGraphics();
void disableGraphics();
void guStart();
#endif
