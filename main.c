
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <windows.h>

#include "lvgl/lvgl.h"


/*********************
 *      DEFINES
 *********************/
#define HOR_RES 90
#define VER_RES 49
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_disp_drv_t disp_drv;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t disp_buf1[HOR_RES * VER_RES];
lv_color_t buf[HOR_RES * VER_RES];
static lv_disp_t * dispplay = NULL;

static void flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    LV_UNUSED(area);
    LV_UNUSED(color_p);

    static int i,j;
    for(j=area->y1; j<=area->y2; j++)
    {
        for(i=area->x1; i<=area->x2; i++)
        {
            buf[j*HOR_RES + i].full = color_p->full;
            color_p++;
        }
    }

    
    i = 0;
    do
    {   if(i%HOR_RES == 0)
        printf("\r\n");

        if(buf[i].full)
        {
            putchar('8');
        }
        else
        {
            putchar(' ');
        }
    } while (++ i < HOR_RES*VER_RES);

    lv_disp_flush_ready(disp_drv);
}

static void hal_init(void)
{
    memset(buf, 0, sizeof(buf));

    lv_disp_draw_buf_init(&draw_buf, disp_buf1, NULL, HOR_RES * VER_RES);

    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &draw_buf;
    disp_drv.flush_cb = flush_cb;
    disp_drv.hor_res = HOR_RES;
    disp_drv.ver_res = VER_RES;
    // disp_drv.full_refresh = 1;
    // disp_drv.direct_mode = 1;
    dispplay = lv_disp_drv_register(&disp_drv);
    // if(dispplay != NULL)
    // {
    //     printf("create display ok\r\n");
    // }

    // static lv_indev_drv_t indev_mouse_drv;
    // lv_indev_drv_init(&indev_mouse_drv);
    // indev_mouse_drv.type = LV_INDEV_TYPE_POINTER;
    // indev_mouse_drv.read_cb = lv_test_mouse_read_cb;
    // lv_test_mouse_indev = lv_indev_drv_register(&indev_mouse_drv);

    // static lv_indev_drv_t indev_keypad_drv;
    // lv_indev_drv_init(&indev_keypad_drv);
    // indev_keypad_drv.type = LV_INDEV_TYPE_KEYPAD;
    // indev_keypad_drv.read_cb = lv_test_keypad_read_cb;
    // lv_test_keypad_indev = lv_indev_drv_register(&indev_keypad_drv);

    // static lv_indev_drv_t indev_encoder_drv;
    // lv_indev_drv_init(&indev_encoder_drv);
    // indev_encoder_drv.type = LV_INDEV_TYPE_ENCODER;
    // indev_encoder_drv.read_cb = lv_test_encoder_read_cb;
    // lv_test_encoder_indev = lv_indev_drv_register(&indev_encoder_drv);
}

static void my_widget(void)
{
    // lv_obj_t * label1 = lv_label_create(lv_scr_act());
    // lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
    // lv_label_set_recolor(label1, true);                      /*Enable re-coloring by commands in the text*/
    // lv_label_set_text(label1, "#0000ff Re-color# #ff00ff words# #ff0000 of a# label, align the lines to the center "
    //                   "and wrap long text automatically.");
    // lv_obj_set_width(label1, 150);  /*Set smaller width to make the lines wrap*/
    // lv_obj_set_style_text_align(label1, LV_TEXT_ALIGN_CENTER, 0);
    // lv_obj_align(label1, LV_ALIGN_CENTER, 0, -40);

    lv_obj_t * label2 = lv_label_create(lv_scr_act());
    lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL_CIRCULAR);     /*Circular scroll*/
    lv_obj_set_width(label2, 80);
    lv_label_set_text(label2, "It is a circularly scrolling text. ");
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, 0);

    // lv_obj_t *ta = lv_textarea_create(lv_scr_act());
    // lv_textarea_set_text(ta, "ABCDE abcde");
    // lv_obj_set_size(ta, 148, 40);
    // lv_obj_align(ta, LV_ALIGN_CENTER, 0, 0);

}

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
    /*Initialize LittlevGL*/
    lv_init();

    /*Initialize the HAL for LittlevGL*/
    hal_init();

    /*Output prompt information to the console, you can also use printf() to print directly*/
    LV_LOG_USER("LVGL initialization completed!");

    /*Run the demo*/
    my_widget();

    while(1) {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        Sleep(10);
        lv_tick_inc(10);
    }
    return 0;
}
