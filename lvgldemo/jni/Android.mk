# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE  := lvgldemo

LOCAL_CFLAGS := -std=c99

LOCAL_SRC_FILES :=
LOCAL_SRC_FILES += com_example_lvgldemo_LVGLDemo.c


LOCAL_SRC_FILES += lv_examples/src/lv_demo_widgets/lv_demo_widgets.c

LOCAL_SRC_FILES += lv_my_dev/tft.c
LOCAL_SRC_FILES += lv_my_dev/touchpad.c

LOCAL_SRC_FILES += sdl_api.c
LOCAL_SRC_FILES += lvgldemo.c



LOCAL_SRC_FILES += lvgl/src/lv_core/lv_disp.c
LOCAL_SRC_FILES += lvgl/src/lv_core/lv_group.c
LOCAL_SRC_FILES += lvgl/src/lv_core/lv_indev.c
LOCAL_SRC_FILES += lvgl/src/lv_core/lv_obj.c
LOCAL_SRC_FILES += lvgl/src/lv_core/lv_refr.c
LOCAL_SRC_FILES += lvgl/src/lv_core/lv_style.c

LOCAL_SRC_FILES += lvgl/src/lv_draw/lv_draw_arc.c
LOCAL_SRC_FILES += lvgl/src/lv_draw/lv_draw_blend.c
LOCAL_SRC_FILES += lvgl/src/lv_draw/lv_draw_img.c
LOCAL_SRC_FILES += lvgl/src/lv_draw/lv_draw_label.c
LOCAL_SRC_FILES += lvgl/src/lv_draw/lv_draw_line.c
LOCAL_SRC_FILES += lvgl/src/lv_draw/lv_draw_mask.c
LOCAL_SRC_FILES += lvgl/src/lv_draw/lv_draw_rect.c
LOCAL_SRC_FILES += lvgl/src/lv_draw/lv_draw_triangle.c
LOCAL_SRC_FILES += lvgl/src/lv_draw/lv_img_buf.c
LOCAL_SRC_FILES += lvgl/src/lv_draw/lv_img_cache.c
LOCAL_SRC_FILES += lvgl/src/lv_draw/lv_img_decoder.c

LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_dejavu_16_persian_hebrew.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_fmt_txt.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_loader.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_8.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_10.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_12.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_12_subpx.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_14.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_16.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_18.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_20.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_22.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_24.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_26.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_28.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_28_compressed.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_30.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_32.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_34.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_36.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_38.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_40.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_42.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_44.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_46.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_montserrat_48.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_simsun_16_cjk.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_unscii_8.c
LOCAL_SRC_FILES += lvgl/src/lv_font/lv_font_unscii_16.c

LOCAL_SRC_FILES += lvgl/src/lv_gpu/lv_gpu_nxp_pxp.c
LOCAL_SRC_FILES += lvgl/src/lv_gpu/lv_gpu_nxp_pxp_osa.c
LOCAL_SRC_FILES += lvgl/src/lv_gpu/lv_gpu_nxp_vglite.c
LOCAL_SRC_FILES += lvgl/src/lv_gpu/lv_gpu_stm32_dma2d.c

LOCAL_SRC_FILES += lvgl/src/lv_hal/lv_hal_disp.c
LOCAL_SRC_FILES += lvgl/src/lv_hal/lv_hal_indev.c
LOCAL_SRC_FILES += lvgl/src/lv_hal/lv_hal_tick.c

LOCAL_SRC_FILES += lvgl/src/lv_misc/lv_anim.c
LOCAL_SRC_FILES += lvgl/src/lv_misc/lv_area.c
LOCAL_SRC_FILES += lvgl/src/lv_misc/lv_async.c
LOCAL_SRC_FILES += lvgl/src/lv_misc/lv_bidi.c
LOCAL_SRC_FILES += lvgl/src/lv_misc/lv_color.c
LOCAL_SRC_FILES += lvgl/src/lv_misc/lv_debug.c
LOCAL_SRC_FILES += lvgl/src/lv_misc/lv_fs.c
LOCAL_SRC_FILES += lvgl/src/lv_misc/lv_gc.c
LOCAL_SRC_FILES += lvgl/src/lv_misc/lv_ll.c
LOCAL_SRC_FILES += lvgl/src/lv_misc/lv_log.c
LOCAL_SRC_FILES += lvgl/src/lv_misc/lv_math.c
LOCAL_SRC_FILES += lvgl/src/lv_misc/lv_mem.c
LOCAL_SRC_FILES += lvgl/src/lv_misc/lv_printf.c
LOCAL_SRC_FILES += lvgl/src/lv_misc/lv_task.c
LOCAL_SRC_FILES += lvgl/src/lv_misc/lv_templ.c
LOCAL_SRC_FILES += lvgl/src/lv_misc/lv_txt.c
LOCAL_SRC_FILES += lvgl/src/lv_misc/lv_txt_ap.c
LOCAL_SRC_FILES += lvgl/src/lv_misc/lv_utils.c

LOCAL_SRC_FILES += lvgl/src/lv_themes/lv_theme.c
LOCAL_SRC_FILES += lvgl/src/lv_themes/lv_theme_empty.c
LOCAL_SRC_FILES += lvgl/src/lv_themes/lv_theme_material.c
LOCAL_SRC_FILES += lvgl/src/lv_themes/lv_theme_mono.c
LOCAL_SRC_FILES += lvgl/src/lv_themes/lv_theme_template.c

LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_arc.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_bar.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_btn.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_btnmatrix.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_calendar.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_canvas.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_chart.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_checkbox.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_cont.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_cpicker.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_dropdown.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_gauge.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_img.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_imgbtn.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_keyboard.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_label.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_led.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_line.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_linemeter.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_list.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_msgbox.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_objmask.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_objx_templ.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_page.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_roller.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_slider.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_spinbox.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_spinner.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_switch.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_table.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_tabview.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_textarea.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_tileview.c
LOCAL_SRC_FILES += lvgl/src/lv_widgets/lv_win.c

LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)
