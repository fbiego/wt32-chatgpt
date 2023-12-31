// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.2.3
// LVGL version: 8.3.4
// Project name: ChatGPT

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_homeScreen;
lv_obj_t *ui_titlePanel;
lv_obj_t *ui_appIcon;
lv_obj_t *ui_titleText;
lv_obj_t *ui_wifiIcon;
lv_obj_t *ui_appPanel;
lv_obj_t *ui_scrollPanel;
lv_obj_t *ui_chatPanel;
lv_obj_t *ui_actionPanel;
void ui_event_promptText( lv_event_t * e);
lv_obj_t *ui_promptText;
void ui_event_sendButton( lv_event_t * e);
lv_obj_t *ui_sendButton;
lv_obj_t *ui_keyboard;
lv_obj_t *ui____initial_actions0;
const lv_img_dsc_t *ui_imgset_electron_[1] = {&ui_img_electron_32_png};

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_promptText( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_FOCUSED) {
      _ui_flag_modify( ui_keyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
}
if ( event_code == LV_EVENT_DEFOCUSED) {
      _ui_flag_modify( ui_keyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
}
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      onTextChanged( e );
}
}
void ui_event_sendButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_state_modify( ui_sendButton, LV_STATE_DISABLED, _UI_MODIFY_STATE_ADD);
      onSendPrompt( e );
}
}

///////////////////// SCREENS ////////////////////
void ui_homeScreen_screen_init(void)
{
ui_homeScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_homeScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_titlePanel = lv_obj_create(ui_homeScreen);
lv_obj_set_width( ui_titlePanel, 320);
lv_obj_set_height( ui_titlePanel, 40);
lv_obj_set_align( ui_titlePanel, LV_ALIGN_TOP_MID );
lv_obj_set_flex_flow(ui_titlePanel,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_titlePanel, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_titlePanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_titlePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_titlePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_titlePanel, 10, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_titlePanel, 10, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_titlePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_titlePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_row(ui_titlePanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_column(ui_titlePanel, 10, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_appIcon = lv_img_create(ui_titlePanel);
lv_img_set_src(ui_appIcon, &ui_img_electron_32_png);
lv_obj_set_width( ui_appIcon, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_appIcon, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_appIcon, LV_ALIGN_LEFT_MID );
lv_obj_add_flag( ui_appIcon, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_appIcon, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_titleText = lv_label_create(ui_titlePanel);
lv_obj_set_width( ui_titleText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_titleText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_titleText, LV_ALIGN_TOP_RIGHT );
lv_label_set_text(ui_titleText,"ChatGPT ESP32");
lv_obj_set_style_text_font(ui_titleText, &lv_font_montserrat_18, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_wifiIcon = lv_img_create(ui_titlePanel);
lv_img_set_src(ui_wifiIcon, &ui_img_wifi_w_png);
lv_obj_set_width( ui_wifiIcon, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_wifiIcon, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_wifiIcon, LV_ALIGN_LEFT_MID );
lv_obj_add_flag( ui_wifiIcon, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_wifiIcon, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_img_recolor(ui_wifiIcon, lv_color_hex(0x000000), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_img_recolor_opa(ui_wifiIcon, 200, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_appPanel = lv_obj_create(ui_homeScreen);
lv_obj_set_width( ui_appPanel, 320);
lv_obj_set_height( ui_appPanel, 440);
lv_obj_set_align( ui_appPanel, LV_ALIGN_BOTTOM_MID );
lv_obj_set_flex_flow(ui_appPanel,LV_FLEX_FLOW_COLUMN);
lv_obj_set_flex_align(ui_appPanel, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_appPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_appPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_appPanel, lv_color_hex(0x353740), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_appPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_appPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_appPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_appPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_appPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_appPanel, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_row(ui_appPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_column(ui_appPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_scrollPanel = lv_obj_create(ui_appPanel);
lv_obj_set_width( ui_scrollPanel, 320);
lv_obj_set_height( ui_scrollPanel, 380);
lv_obj_set_align( ui_scrollPanel, LV_ALIGN_CENTER );
lv_obj_set_scroll_dir(ui_scrollPanel, LV_DIR_VER);
lv_obj_set_style_radius(ui_scrollPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_scrollPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_scrollPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_scrollPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_scrollPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_scrollPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_scrollPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_scrollPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_chatPanel = lv_obj_create(ui_scrollPanel);
lv_obj_set_width( ui_chatPanel, 320);
lv_obj_set_height( ui_chatPanel, LV_SIZE_CONTENT);   /// 134
lv_obj_set_align( ui_chatPanel, LV_ALIGN_TOP_MID );
lv_obj_set_flex_flow(ui_chatPanel,LV_FLEX_FLOW_COLUMN);
lv_obj_set_flex_align(ui_chatPanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_chatPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_chatPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_chatPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_chatPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_chatPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_chatPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_chatPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_chatPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_chatPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_row(ui_chatPanel, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_column(ui_chatPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_actionPanel = lv_obj_create(ui_appPanel);
lv_obj_set_width( ui_actionPanel, 320);
lv_obj_set_height( ui_actionPanel, 51);
lv_obj_set_align( ui_actionPanel, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_actionPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_actionPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_actionPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_actionPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_actionPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_actionPanel, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_actionPanel, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_actionPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_actionPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_promptText = lv_textarea_create(ui_actionPanel);
lv_obj_set_width( ui_promptText, 267);
lv_obj_set_height( ui_promptText, LV_SIZE_CONTENT);   /// 70
lv_obj_set_align( ui_promptText, LV_ALIGN_LEFT_MID );
lv_textarea_set_placeholder_text(ui_promptText,"Send a message");
lv_obj_set_style_radius(ui_promptText, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_text_color(ui_promptText, lv_color_hex(0x808080), LV_PART_TEXTAREA_PLACEHOLDER | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_promptText, 255, LV_PART_TEXTAREA_PLACEHOLDER| LV_STATE_DEFAULT);

ui_sendButton = lv_img_create(ui_actionPanel);
lv_img_set_src(ui_sendButton, &ui_img_up_arrow_png);
lv_obj_set_width( ui_sendButton, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_sendButton, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_sendButton, LV_ALIGN_RIGHT_MID );
lv_obj_add_state( ui_sendButton, LV_STATE_DISABLED | LV_STATE_USER_2 );     /// States
lv_obj_add_flag( ui_sendButton, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_sendButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_img_recolor(ui_sendButton, lv_color_hex(0x000000), LV_PART_MAIN| LV_STATE_CHECKED|LV_STATE_PRESSED);
lv_obj_set_style_img_recolor_opa(ui_sendButton, 0, LV_PART_MAIN| LV_STATE_CHECKED|LV_STATE_PRESSED);
lv_obj_set_style_img_recolor(ui_sendButton, lv_color_hex(0x000000), LV_PART_MAIN| LV_STATE_DISABLED);
lv_obj_set_style_img_recolor_opa(ui_sendButton, 200, LV_PART_MAIN| LV_STATE_DISABLED);

ui_keyboard = lv_keyboard_create(ui_appPanel);
lv_obj_set_width( ui_keyboard, 310);
lv_obj_set_height( ui_keyboard, 150);
lv_obj_set_align( ui_keyboard, LV_ALIGN_BOTTOM_MID );
lv_obj_add_flag( ui_keyboard, LV_OBJ_FLAG_HIDDEN );   /// Flags
lv_obj_set_style_radius(ui_keyboard, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_keyboard, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_keyboard, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_promptText, ui_event_promptText, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_sendButton, ui_event_sendButton, LV_EVENT_ALL, NULL);

}

void ui_init( void )
{
lv_disp_t *dispp = lv_disp_get_default();
lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
lv_disp_set_theme(dispp, theme);
ui_homeScreen_screen_init();
ui____initial_actions0 = lv_obj_create(NULL);
lv_disp_load_scr( ui_homeScreen);
}
