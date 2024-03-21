/**
 * @file disp.c
 * 
 */
#if !defined(ANDROID)
/*********************
 *      INCLUDES
 *********************/
#include "lv_conf.h"
#include "lvgl/lv_core/lv_vdb.h"
#include "lvgl/lv_hal/lv_hal.h"
#include <string.h>

#include "tft.h"
#include "lcd.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/*These 3 functions are needed by LittlevGL*/
void tft_fill(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t color);
static void tft_map(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p);
static void tft_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p);
//#if TFT_USE_GPU != 0
////static void gpu_mem_blend(lv_color_t * dest, const lv_color_t * src, uint32_t length, lv_opa_t opa);
////static void gpu_mem_fill(lv_color_t * dest, uint32_t length, lv_color_t color);
//#endif


/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Initialize your display here
 */
void tft_init(void)
{
	lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);

//#if TFT_EXT_FB != 0
//	SDRAM_Init();
//#endif
//	LCD_Config();
//	DMA_Config();

	disp_drv.disp_fill = tft_fill;
	disp_drv.disp_map = tft_map;
	disp_drv.disp_flush = tft_flush;
//#if TFT_USE_GPU != 0
//	DMA2D_Config();
//	disp_drv.mem_blend = gpu_mem_blend;
//	disp_drv.mem_fill = gpu_mem_fill;
//#endif
	lv_disp_drv_register(&disp_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Flush a color buffer
 * @param x1 left coordinate of the rectangle
 * @param x2 right coordinate of the rectangle
 * @param y1 top coordinate of the rectangle
 * @param y2 bottom coordinate of the rectangle
 * @param color_p pointer to an array of colors
 */
static void tft_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p)
{
//	LCD_Color_Fill(x1,y1,x2,y2,color_p);
	u16 height,width;
	u16 i,j;
	width=x2-x1+1; 			//得到填充的宽度
	height=y2-y1+1;			//高度
 	for(i=0;i<height;i++)
	{
 		LCD_SetCursor(x1,y1+i);   	//设置光标位置 
		LCD_WriteRAM_Prepare();     //开始写入GRAM
		for(j=0;j<width;j++)
		{
			LCD->LCD_RAM=color_p->full;//写入数据
			color_p++;	
		}
	}	
	lv_flush_ready();
}

/**
 * Fill a rectangular area with a color
 * @param x1 left coordinate of the rectangle
 * @param x2 right coordinate of the rectangle
 * @param y1 top coordinate of the rectangle
 * @param y2 bottom coordinate of the rectangle
 * @param color fill color
 */
void tft_fill(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t color)
{
		LCD_Fill(x1,y1,x2,y2,color.full);		   				//填充单色
}


/**
 * Put a color map to a rectangular area
 * @param x1 left coordinate of the rectangle
 * @param x2 right coordinate of the rectangle
 * @param y1 top coordinate of the rectangle
 * @param y2 bottom coordinate of the rectangle
 * @param color_p pointer to an array of colors
 */
static void tft_map(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p)
{
	u16 height,width;
	u16 i,j;
	width=x2-x1+1; 			//得到填充的宽度
	height=y2-y1+1;			//高度
 	for(i=0;i<height;i++)
	{
 		LCD_SetCursor(x1,y1+i);   	//设置光标位置 
		LCD_WriteRAM_Prepare();     //开始写入GRAM
		for(j=0;j<width;j++)
		{
			LCD->LCD_RAM=color_p->full;//写入数据
			color_p++;	
		}
	}
}
#else


/*********************
*      INCLUDES
*********************/
#include "lv_conf.h"
//#include "lvgl/src/lv_core/lv_vdb.h"
#include "lvgl/src/lv_hal/lv_hal.h"
#include <string.h>

#include "tft.h"

#include "../sdl_api.h"

/*********************
*      DEFINES
*********************/

/**********************
*  STATIC PROTOTYPES
**********************/

/*These 3 functions are needed by LittlevGL*/
void tft_fill(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t color);
static void tft_map(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p);
static void tft_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

#if LV_USE_GPU
static void gpu_blend(lv_disp_drv_t * disp_drv, lv_color_t * dest, const lv_color_t * src, uint32_t length, lv_opa_t opa);
static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width, const lv_area_t * fill_area, lv_color_t color);
#endif


/**********************
*      MACROS
**********************/

/*
//https://www.cnblogs.com/qinjunni/archive/2012/02/20/2359056.html
#define RGB565_MASK_RED		0xF800
#define RGB565_MASK_GREEN	0x07E0
#define RGB565_MASK_BLUE	0x001F
void rgb565_2_rgb24(BYTE *rgb24, WORD rgb565)
{
//extract RGB
rgb24[2] = (rgb565 & RGB565_MASK_RED) >> 11;
rgb24[1] = (rgb565 & RGB565_MASK_GREEN) >> 5;
rgb24[0] = (rgb565 & RGB565_MASK_BLUE);
//amplify the image
rgb24[2] <<= 3;
rgb24[1] <<= 2;
rgb24[0] <<= 3;
}
*/


/**********************
*   GLOBAL FUNCTIONS
**********************/

/**
* Initialize your display here
*/
void tft_init(void)
{
	lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);

	//#if TFT_EXT_FB != 0
	//	SDRAM_Init();
	//#endif
	//	LCD_Config();
	//	DMA_Config();

	/* Example for 1) */
	static lv_disp_buf_t disp_buf_1;
	static lv_color_t buf1_1[LV_HOR_RES_MAX * 10];                      /*A buffer for 10 rows*/
	lv_disp_buf_init(&disp_buf_1, buf1_1, NULL, LV_HOR_RES_MAX * 10);   /*Initialize the display buffer*/

	/* Example for 2) */
	static lv_disp_buf_t disp_buf_2;
	static lv_color_t buf2_1[LV_HOR_RES_MAX * 10];                        /*A buffer for 10 rows*/
	static lv_color_t buf2_2[LV_HOR_RES_MAX * 10];                        /*An other buffer for 10 rows*/
	lv_disp_buf_init(&disp_buf_2, buf2_1, buf2_2, LV_HOR_RES_MAX * 10);   /*Initialize the display buffer*/

	/* Example for 3) */
	static lv_disp_buf_t disp_buf_3;
    static lv_color_t buf3_1[LV_HOR_RES_MAX * LV_VER_RES_MAX];            /*A screen sized buffer*/
    static lv_color_t buf3_2[LV_HOR_RES_MAX * LV_VER_RES_MAX];            /*An other screen sized buffer*/
    lv_disp_buf_init(&disp_buf_3, buf3_1, NULL/*buf3_2*/, LV_HOR_RES_MAX * LV_VER_RES_MAX);   /*Initialize the display buffer*/
	//new for LVGL v6
	disp_drv.buffer = &disp_buf_3;

	disp_drv.flush_cb = tft_flush;
#if LV_USE_GPU
	//disp_drv.gpu_blend_cb = gpu_blend;
	//disp_drv.gpu_fill_cb = gpu_fill;
#endif

	lv_disp_drv_register(&disp_drv);
}

#if LV_USE_GPU
static void gpu_blend(lv_disp_drv_t * disp_drv, lv_color_t * dest, const lv_color_t * src, uint32_t length, lv_opa_t opa)
{
	uint32_t i;
	for (i = 0; i < length; i++) {
		dest[i] = lv_color_mix(dest[i], src[i], opa);
	}
}
static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
	const lv_area_t * fill_area, lv_color_t color)
{
#if 1
	int32_t x, y;
	dest_buf += dest_width * fill_area->y1;
	for (y = fill_area->y1; y < fill_area->y2; y++) {
		for (x = fill_area->x1; x < fill_area->x2; x++) {
			dest_buf[x] = color;
		}
		dest_buf += dest_width;    /*Go to the next line*/
	}
#else
	tft_fill(fill_area->x1, fill_area->y1, fill_area->x2, fill_area->y2, color);
#endif
}
#endif


/**********************
*   STATIC FUNCTIONS
**********************/

/**
* Flush a color buffer
* @param x1 left coordinate of the rectangle
* @param x2 right coordinate of the rectangle
* @param y1 top coordinate of the rectangle
* @param y2 bottom coordinate of the rectangle
* @param color_p pointer to an array of colors
*/
static void tft_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
	int32_t x1; int32_t y1; int32_t x2; int32_t y2;
	x1 = area->x1;
	y1 = area->y1;
	x2 = area->x2;
	y2 = area->y2;

	//FIXME:PORT
	int32_t height, width;
	int32_t x, y;
	width = x2 - x1 + 1;
	height = y2 - y1 + 1;
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			uint16_t color = color_p->full;
			int color2;
			unsigned char R = (color & 0xF800) >> 11;
			unsigned char G = (color & 0x07E0) >> 5;
			unsigned char B = (color & 0x001F);
			R <<= 3;
			G <<= 2;
			B <<= 3;
			color2 = (R << 0) | (G << 8) | (B << 16);
			CanvasDrawPixel(x1 + x, y1 + y, color2, 0xff);
			color_p++;
		}
	}

	lv_disp_flush_ready(disp_drv);
}

/**
* Fill a rectangular area with a color
* @param x1 left coordinate of the rectangle
* @param x2 right coordinate of the rectangle
* @param y1 top coordinate of the rectangle
* @param y2 bottom coordinate of the rectangle
* @param color fill color
*/
void tft_fill(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t color)
{
	//FIXME:PORT
	int color2;
	unsigned char R = (color.full & 0xF800) >> 11;
	unsigned char G = (color.full & 0x07E0) >> 5;
	unsigned char B = (color.full & 0x001F);
	R <<= 3;
	G <<= 2;
	B <<= 3;
	color2 = (R << 0) | (G << 8) | (B << 16);
	CanvasFillRect(x1, y1, x2, y2, color2);
}


/**
* Put a color map to a rectangular area
* @param x1 left coordinate of the rectangle
* @param x2 right coordinate of the rectangle
* @param y1 top coordinate of the rectangle
* @param y2 bottom coordinate of the rectangle
* @param color_p pointer to an array of colors
*/
static void tft_map(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p)
{
	//FIXME:PORT
	int32_t height, width;
	int32_t x, y;
	width = x2 - x1 + 1; 	
	height = y2 - y1 + 1;
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			uint16_t color = color_p->full;
			int color2;
			unsigned char R = (color & 0xF800) >> 11;
			unsigned char G = (color & 0x07E0) >> 5;
			unsigned char B = (color & 0x001F);
			R <<= 3;
			G <<= 2;
			B <<= 3;
			color2 = (R << 0) | (G << 8) | (B << 16);
			CanvasDrawPixel(x1 + x, y1 + y, color2, 0xff);
			color_p++;
		}
	}
}

#endif

