/*
*****   ****  *****         *****     ****   **** 
****** ****** ******       *******   ****** ******
**  ** **  *  **  **      **    ***  **  *  **  * 
**  **  **    **  **     **      **   **     **   
******   **   ****** *** **      **    **     **  
*****      ** *****  *** **      **     **     ** 
**         ** **         ***    **      **     ** 
**     ****** **          *******   ****** ****** 
**      ****  **           *****     ****   ****  

-PlayStation Portable Open-Source Shell Source

WwW.PsP-OsS.CoM

*/

#include <stdlib.h>
#include <malloc.h>
#include <pspdisplay.h>
#include <psputils.h>
#include <png.h>
#include <pspgu.h>

#include <jpeglib.h>
#include <jerror.h>
#include "OSSgraphics.h"
#include "OSSframebuffer.h"
#include "../main.h"

#define IS_ALPHA(color) (((color)&0xff000000)==0xff000000?0:1) // Alpha Check Macro
#define FRAMEBUFFER_SIZE (PSP_LINE_SIZE*SCREEN_HEIGHT*4) // Frame Buffer Size
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y)) // Maximum Macro

typedef struct
{
	unsigned short u, v;
	short x, y, z;
} Vertex;

FT_Library  ft_library;

extern u8 msx[];

unsigned int __attribute__((aligned(16))) list[262144];
static int dispBufferNumber;
static int initialized = 0;

// Next Power (Math)
int getNextPower2(int width)
{
	int b = width;
	int n;
	for (n = 0; b != 0; n++) b >>= 1;
	b = 1 << n;
	if (b == 2 * width) b >>= 1;
	return b;
}

// Virtual Ram Draw Buffer
Color* getVramDrawBuffer()
{
	Color* vram = (Color*) g_vram_base;
	if (dispBufferNumber == 0) vram += FRAMEBUFFER_SIZE / sizeof(Color);
	return vram;
}

// Virtual Ram Display Buffer
Color* getVramDisplayBuffer()
{
	Color* vram = (Color*) g_vram_base;
	if (dispBufferNumber == 1) vram += FRAMEBUFFER_SIZE / sizeof(Color);
	return vram;
}

void user_warning_fn(png_structp png_ptr, png_const_charp warning_msg)
{
}

// Load a Graphic into Memory
Image* LoadGFX(const char* filename)
{
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;
	png_uint_32 width, height;
	int bit_depth, color_type, interlace_type, x, y;
	u32* line;
	FILE *fp;
	Image* image = (Image*) malloc(sizeof(Image));
	if (!image) return NULL;

	if ((fp = fopen(filename, "rb")) == NULL) return NULL;
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		free(image);
		fclose(fp);
		return NULL;;
	}
	png_set_error_fn(png_ptr, (png_voidp) NULL, (png_error_ptr) NULL, user_warning_fn);
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		free(image);
		fclose(fp);
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
		return NULL;
	}
	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, sig_read);
	png_read_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, int_p_NULL, int_p_NULL);
	if(width>512 || height >512){
		image->imageWidth = 513;
		image->imageHeight = 513;
		image->textureWidth = getNextPower2(513);
		image->textureHeight = getNextPower2(513);
		image->data=0;
		return image;
	}else{
		image->imageWidth = width;
		image->imageHeight = height;
		image->textureWidth = getNextPower2(width);
		image->textureHeight = getNextPower2(height);}
	png_set_strip_16(png_ptr);
	png_set_packing(png_ptr);
	if (color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png_ptr);
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_gray_1_2_4_to_8(png_ptr);
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png_ptr);
	png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);
	image->data = (Color*) memalign(16, image->textureWidth * image->textureHeight * sizeof(Color));
	if (!image->data) {
		free(image);
		fclose(fp);
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
		return NULL;
	}
	line = (u32*) malloc(width * 4);
	if (!line) {
		free(image->data);
		free(image);
		fclose(fp);
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
		return NULL;
	}
	for (y = 0; y < height; y++) {
		png_read_row(png_ptr, (u8*) line, png_bytep_NULL);
		for (x = 0; x < width; x++) {
			u32 color = line[x];
			image->data[x + y * image->textureWidth] =  color;
		}
	}
	free(line);
	png_read_end(png_ptr, info_ptr);
	png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
	fclose(fp);
	return image;
}

// Load a Jpeg into Memory
Image* loadJpegImage(const char* filename)
{
	int x=0;
	struct jpeg_decompress_struct dinfo;
	struct jpeg_error_mgr jerr;
	dinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&dinfo);
	FILE* inFile = fopen(filename, "rb");
	if (!inFile) {
		jpeg_destroy_decompress(&dinfo);
		return NULL;
	}
	jpeg_stdio_src(&dinfo, inFile);
	jpeg_read_header(&dinfo, TRUE);
	int width = dinfo.image_width;
	int height = dinfo.image_height;
	jpeg_start_decompress(&dinfo);
	Image* image = (Image*) malloc(sizeof(Image));
	if (!image) {
		jpeg_destroy_decompress(&dinfo);
		return NULL;
	}
	image->imageWidth = width;
	image->imageHeight = height;
	image->textureWidth = getNextPower2(width);
	image->textureHeight = getNextPower2(height);
	image->data = (Color*) memalign(16, image->textureWidth * image->textureHeight * sizeof(Color));
	u8* line = (u8*) malloc(width * 3);
	if (!line) {
		jpeg_destroy_decompress(&dinfo);
		return NULL;
	}
	if (dinfo.jpeg_color_space == JCS_GRAYSCALE) {
		while (dinfo.output_scanline < dinfo.output_height) {
			int y = dinfo.output_scanline;
			jpeg_read_scanlines(&dinfo, &line, 1);
			for (x = 0; x < width; x++) {
				Color c = line[x];
				image->data[x + image->textureWidth * y] = c | (c << 8) | (c << 16) | 0xff000000;;
			}
		}
	} else {
		while (dinfo.output_scanline < dinfo.output_height) {
			int y = dinfo.output_scanline;
			jpeg_read_scanlines(&dinfo, &line, 1);
			u8* linePointer = line;
			for (x = 0; x < width; x++) {
				Color c = *(linePointer++);
				c |= (*(linePointer++)) << 8;
				c |= (*(linePointer++)) << 16;
				image->data[x + image->textureWidth * y] = c | 0xff000000;
			}
		}
	}
	jpeg_finish_decompress(&dinfo);
	jpeg_destroy_decompress(&dinfo);
	free(line);
	return image;
}

// Place a Graphic at the specified coordinates
void PutGFX(int sx, int sy, int width, int height, Image* source, int dx, int dy)
{
	if (!initialized) return;

	sceKernelDcacheWritebackInvalidateAll();
	guStart();
	sceGuTexImage(0, source->textureWidth, source->textureHeight, source->textureWidth, (void*) source->data);
	float u = 1.0f / ((float)source->textureWidth);
	float v = 1.0f / ((float)source->textureHeight);
	sceGuTexScale(u, v);

	int j = 0;
	while (j < width) {
		Vertex* vertices = (Vertex*) sceGuGetMemory(2 * sizeof(Vertex));
		int sliceWidth = 64;
		if (j + sliceWidth > width) sliceWidth = width - j;
		vertices[0].u = sx + j;
		vertices[0].v = sy;
		vertices[0].x = dx + j;
		vertices[0].y = dy;
		vertices[0].z = 0;
		vertices[1].u = sx + j + sliceWidth;
		vertices[1].v = sy + height;
		vertices[1].x = dx + j + sliceWidth;
		vertices[1].y = dy + height;
		vertices[1].z = 0;
		sceGuDrawArray(GU_SPRITES, GU_TEXTURE_16BIT | GU_VERTEX_16BIT | GU_TRANSFORM_2D, 2, 0, vertices);
		j += sliceWidth;
	}

	sceGuFinish();
	sceGuSync(0, 0);
}

// Place text at the specified coordinates
void PutText(int x, int y, const char* text, Color color)
{
	int c, i, j, l;
	u8 *font;
	Color *vram_ptr;
	Color *vram;

	if (!initialized) return;

	for (c = 0; c < strlen(text); c++) {
		if (x < 0 || x + 8 > SCREEN_WIDTH || y < 0 || y + 8 > SCREEN_HEIGHT) break;
		char ch = text[c];
		vram = getVramDrawBuffer() + x + y * PSP_LINE_SIZE;

		font = &msx[ (int)ch * 8];
		for (i = l = 0; i < 8; i++, l += 8, font++) {
			vram_ptr  = vram;
			for (j = 0; j < 8; j++) {
				if ((*font & (128 >> j))) *vram_ptr = color;
				vram_ptr++;
			}
			vram += PSP_LINE_SIZE;
		}
		x += 8;
	}
}

// Place a pixel at the specified coordinates
void PutPixel(int x, int y, Color color)
{
	Color* vram = getVramDrawBuffer();
	vram[PSP_LINE_SIZE * y + x] = color;
}


// Release an image from memory
void freeImage(Image* image)
{
	free(image->data);
	free(image);
}

// Take a screenshot
void Screenshot(const char* filename, Color* data, int width, int height, int lineSize, int saveAlpha)
{
	png_structp png_ptr;
	png_infop info_ptr;
	FILE* fp;
	int i, x, y;
	u8* line;

	if ((fp = fopen(filename, "wb")) == NULL) return;
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) return;
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
		return;
	}
	png_init_io(png_ptr, fp);
	png_set_IHDR(png_ptr, info_ptr, width, height, 8,
		saveAlpha ? PNG_COLOR_TYPE_RGBA : PNG_COLOR_TYPE_RGB,
		PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	png_write_info(png_ptr, info_ptr);
	line = (u8*) malloc(width * (saveAlpha ? 4 : 3));
	for (y = 0; y < height; y++) {
		for (i = 0, x = 0; x < width; x++) {
			Color color = data[x + y * lineSize];
			u8 r = color & 0xff; 
			u8 g = (color >> 8) & 0xff;
			u8 b = (color >> 16) & 0xff;
			u8 a = saveAlpha ? (color >> 24) & 0xff : 0xff;
			line[i++] = r;
			line[i++] = g;
			line[i++] = b;
			if (saveAlpha) line[i++] = a;
		}
		png_write_row(png_ptr, line);
	}
	free(line);
	png_write_end(png_ptr, info_ptr);
	png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
	fclose(fp);
}

// Capture screen
void PrintScreen()
{
	if (!initialized) return;
	sceGuSwapBuffers();
	dispBufferNumber ^= 1;
}

// Load Font
Font* LoadFont(const char* filename) {
	Font* font = (Font*) malloc(sizeof(Font));
	SceUID file;
	file=sceIoOpen(file, PSP_O_RDONLY, 0);
	int filesize = sceIoLseek(file, 0, SEEK_END);
	u8* fontData = (u8*) malloc(filesize);
	if (!fontData) {
		sceIoClose(file);
	}
	sceIoLseek(file, 0, SEEK_SET);
	sceIoRead(file, fontData, filesize);
	sceIoClose(file);
	int error = FT_New_Memory_Face(ft_library, fontData, filesize, 0, &font->face);
	if (error) {
		free(font);
		free(fontData);
	}
	font->data = fontData;
	font->name = strdup(filename);
	return font;
}

// Set font size in pixels
Font* SetPixelSize(Font* font, int width, int height) {
	FT_Set_Pixel_Sizes(font->face, width, height);
	return font;
}

// Set font size in point at certain dpi
Font* SetPointSize(Font* font, int width, int height, int dpiX, int dpiY) {
	FT_Set_Char_Size(font->face, width, height, dpiX, dpiY);
	return font;
}

// Print text using FT font
void FontPrint(Font* font, int x, int y, const char* text, Color color) {
	int num_chars = strlen(text);
	int n = 0;
	FT_GlyphSlot slot = font->face->glyph;
	while (n < num_chars) {
		FT_UInt glyph_index = FT_Get_Char_Index(font->face, text[n]);
		int error = FT_Load_Glyph(font->face, glyph_index, FT_LOAD_DEFAULT);
		if (error) continue;
		error = FT_Render_Glyph(font->face->glyph, ft_render_mode_normal);
		if (error) continue;
		fontPrintTextScreen(&slot->bitmap, x + slot->bitmap_left, y - slot->bitmap_top, color);
		x += slot->advance.x >> 6;
		y += slot->advance.y >> 6;
		n++;
	}
}

void fontPrintTextScreen(FT_Bitmap* bitmap, int x, int y, Color color)
{
	fontPrintTextImpl(bitmap, x, y, color, getVramDrawBuffer(), SCREEN_WIDTH, SCREEN_HEIGHT, PSP_LINE_SIZE);
}

void fontPrintTextImpl(FT_Bitmap* bitmap, int xofs, int yofs, Color color, Color* framebuffer, int width, int height, int lineSize)
{
	u8 rf = color & 0xff; 
	u8 gf = (color >> 8) & 0xff;
	u8 bf = (color >> 16) & 0xff;
	
	u8* line = bitmap->buffer;
	Color* fbLine = framebuffer + xofs + yofs * lineSize;
	int y = 0;
	int x;
	while (y < bitmap->rows) {
		u8* column = line;
		Color* fbColumn = fbLine;
		x=0;
		while (x < bitmap->width) {
			if (x + xofs < width && x + xofs >= 0 && y + yofs < height && y + yofs >= 0) {
				u8 val = *column;
				color = *fbColumn;
				u8 r = color & 0xff; 
				u8 g = (color >> 8) & 0xff;
				u8 b = (color >> 16) & 0xff;
				u8 a = (color >> 24) & 0xff;
				r = rf * val / 255 + (255 - val) * r / 255;
				g = gf * val / 255 + (255 - val) * g / 255;
				b = bf * val / 255 + (255 - val) * b / 255;
				*fbColumn = r | (g << 8) | (b << 16) | (a << 24);
			}
			column++;
			fbColumn++;
			x++;
		}
		line += bitmap->pitch;
		fbLine += lineSize;
		y++;
	}
}

// Print text using default FT font
void PutTextFont(int x, int y, const char* text, Color color) {
    PutText(x,y,text,color);//TEMPORMARY
    
    //This is what we SHOULD use:
	//FontPrint(defaultFont,x,y,text,color);
}

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */

// Initiate graphical parameters
void initGraphics()
{
	dispBufferNumber = 0;

	sceGuInit();

	guStart();
	sceGuDrawBuffer(GU_PSM_8888, (void*)FRAMEBUFFER_SIZE, PSP_LINE_SIZE);
	sceGuDispBuffer(SCREEN_WIDTH, SCREEN_HEIGHT, (void*)0, PSP_LINE_SIZE);
	sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);
	sceGuDepthBuffer((void*) (FRAMEBUFFER_SIZE*2), PSP_LINE_SIZE);
	sceGuOffset(2048 - (SCREEN_WIDTH / 2), 2048 - (SCREEN_HEIGHT / 2));
	sceGuViewport(2048, 2048, SCREEN_WIDTH, SCREEN_HEIGHT);
	sceGuDepthRange(0xc350, 0x2710);
	sceGuScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuAlphaFunc(GU_GREATER, 0, 0xff);
	sceGuEnable(GU_ALPHA_TEST);
	sceGuDepthFunc(GU_GEQUAL);
	sceGuEnable(GU_DEPTH_TEST);
	sceGuFrontFace(GU_CW);
	sceGuShadeModel(GU_SMOOTH);
	sceGuEnable(GU_CULL_FACE);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuEnable(GU_CLIP_PLANES);
	sceGuTexMode(GU_PSM_8888, 0, 0, 0);
	sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGBA);
	sceGuTexFilter(GU_NEAREST, GU_NEAREST);
	sceGuAmbientColor(0xffffffff);
	sceGuEnable(GU_BLEND);
	sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
	sceGuFinish();
	sceGuSync(0, 0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);
	initialized = 1;
}

// Disable graphical buffer usage
void disableGraphics()
{
	initialized = 0;
}

// Enable graphical buffer usage
void guStart()
{
	sceGuStart(GU_DIRECT, list);
}
