/*
   MIT License

  Copyright (c) 2022 Felix Biego

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

  ______________  _____
  ___  __/___  /_ ___(_)_____ _______ _______
  __  /_  __  __ \__  / _  _ \__  __ `/_  __ \
  _  __/  _  /_/ /_  /  /  __/_  /_/ / / /_/ /
  /_/     /_.___/ /_/   \___/ _\__, /  \____/
                              /____/

*/

#define LGFX_USE_V1

#include <Arduino.h>
#include "main.h"
#include <lvgl.h>
#include <LovyanGFX.hpp>
#include <ESP32Time.h>
#include <Timber.h>

#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#ifdef USE_UI
#include "ui/ui.h"
#endif

#ifdef PLUS
#define SCR 30
class LGFX : public lgfx::LGFX_Device
{

  lgfx::Panel_ST7796 _panel_instance;

  lgfx::Bus_Parallel8 _bus_instance;

  lgfx::Light_PWM _light_instance;

  lgfx::Touch_FT5x06 _touch_instance;

public:
  LGFX(void)
  {
    {
      auto cfg = _bus_instance.config();

      cfg.port = 0;
      cfg.freq_write = 40000000;
      cfg.pin_wr = 47; // pin number connecting WR
      cfg.pin_rd = -1; // pin number connecting RD
      cfg.pin_rs = 0;  // Pin number connecting RS(D/C)
      cfg.pin_d0 = 9;  // pin number connecting D0
      cfg.pin_d1 = 46; // pin number connecting D1
      cfg.pin_d2 = 3;  // pin number connecting D2
      cfg.pin_d3 = 8;  // pin number connecting D3
      cfg.pin_d4 = 18; // pin number connecting D4
      cfg.pin_d5 = 17; // pin number connecting D5
      cfg.pin_d6 = 16; // pin number connecting D6
      cfg.pin_d7 = 15; // pin number connecting D7

      _bus_instance.config(cfg);              // Apply the settings to the bus.
      _panel_instance.setBus(&_bus_instance); // Sets the bus to the panel.
    }

    {                                      // Set display panel control.
      auto cfg = _panel_instance.config(); // Get the structure for display panel settings.

      cfg.pin_cs = -1;   // Pin number to which CS is connected (-1 = disable)
      cfg.pin_rst = 4;   // pin number where RST is connected (-1 = disable)
      cfg.pin_busy = -1; // pin number to which BUSY is connected (-1 = disable)

      // * The following setting values ​​are set to general default values ​​for each panel, and the pin number (-1 = disable) to which BUSY is connected, so please try commenting out any unknown items.

      cfg.memory_width = 320;  // Maximum width supported by driver IC
      cfg.memory_height = 480; // Maximum height supported by driver IC
      cfg.panel_width = 320;   // actual displayable width
      cfg.panel_height = 480;  // actual displayable height
      cfg.offset_x = 0;        // Panel offset in X direction
      cfg.offset_y = 0;        // Panel offset in Y direction
#ifdef PORTRAIT
      cfg.offset_rotation = 2;
#else
      cfg.offset_rotation = 3;
#endif
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits = 1;
      cfg.readable = false;
      cfg.invert = true;
      cfg.rgb_order = false;
      cfg.dlen_16bit = false;
      cfg.bus_shared = true;

      _panel_instance.config(cfg);
    }

    {                                      // Set backlight control. (delete if not necessary)
      auto cfg = _light_instance.config(); // Get the structure for backlight configuration.

      cfg.pin_bl = 45;     // pin number to which the backlight is connected
      cfg.invert = false;  // true to invert backlight brightness
      cfg.freq = 44100;    // backlight PWM frequency
      cfg.pwm_channel = 0; // PWM channel number to use

      _light_instance.config(cfg);
      _panel_instance.setLight(&_light_instance); // Sets the backlight to the panel.
    }

    { // Configure settings for touch screen control. (delete if not necessary)
      auto cfg = _touch_instance.config();

      cfg.x_min = 0;   // Minimum X value (raw value) obtained from the touchscreen
      cfg.x_max = 319; // Maximum X value (raw value) obtained from the touchscreen
      cfg.y_min = 0;   // Minimum Y value obtained from touchscreen (raw value)
      cfg.y_max = 479; // Maximum Y value (raw value) obtained from the touchscreen
      cfg.pin_int = 7; // pin number to which INT is connected
      cfg.bus_shared = false;
      cfg.offset_rotation = 0;

      // For I2C connection
      cfg.i2c_port = 0;    // Select I2C to use (0 or 1)
      cfg.i2c_addr = 0x38; // I2C device address number
      cfg.pin_sda = 6;     // pin number where SDA is connected
      cfg.pin_scl = 5;     // pin number to which SCL is connected
      cfg.freq = 400000;   // set I2C clock

      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance); // Set the touchscreen to the panel.
    }

    setPanel(&_panel_instance); // Sets the panel to use.
  }
};

#else
#define SCR 8
class LGFX : public lgfx::LGFX_Device
{

  lgfx::Panel_ST7796 _panel_instance;

  lgfx::Bus_SPI _bus_instance;

  lgfx::Light_PWM _light_instance;

  lgfx::Touch_FT5x06 _touch_instance;

public:
  LGFX(void)
  {
    {
      auto cfg = _bus_instance.config(); // Get the structure for bus configuration.

      // SPI bus settings
      cfg.spi_host = VSPI_HOST; // Select the SPI to use ESP32-S2,C3 : SPI2_HOST or SPI3_HOST / ESP32 : VSPI_HOST or HSPI_HOST
      // * With the ESP-IDF version upgrade, VSPI_HOST and HSPI_HOST descriptions are deprecated, so if an error occurs, use SPI2_HOST and SPI3_HOST instead.
      cfg.spi_mode = 3;                  // Set SPI communication mode (0 ~ 3)
      cfg.freq_write = 40000000;         // SPI clock when sending (up to 80MHz, rounded to 80MHz divided by an integer)
      cfg.freq_read = 6000000;           // SPI clock when receiving
      cfg.spi_3wire = false;             // set to true if receiving on MOSI pin
      cfg.use_lock = true;               // set to true to use transaction lock
      cfg.dma_channel = SPI_DMA_CH_AUTO; // Set the DMA channel to use (0=not use DMA / 1=1ch / 2=ch / SPI_DMA_CH_AUTO=auto setting)
      // * With the ESP-IDF version upgrade, SPI_DMA_CH_AUTO (automatic setting) is recommended for the DMA channel. Specifying 1ch and 2ch is deprecated.
      cfg.pin_sclk = 14; // set SPI SCLK pin number
      cfg.pin_mosi = 13; // Set MOSI pin number for SPI
      cfg.pin_miso = -1; // set SPI MISO pin number (-1 = disable)
      cfg.pin_dc = 21;   // Set SPI D/C pin number (-1 = disable)

      _bus_instance.config(cfg);              // Apply the settings to the bus.
      _panel_instance.setBus(&_bus_instance); // Sets the bus to the panel.
    }

    {                                      // Set display panel control.
      auto cfg = _panel_instance.config(); // Get the structure for display panel settings.

      cfg.pin_cs = 15;   // Pin number to which CS is connected (-1 = disable)
      cfg.pin_rst = 22;  // pin number where RST is connected (-1 = disable)
      cfg.pin_busy = -1; // pin number to which BUSY is connected (-1 = disable)

      // * The following setting values ​​are set to general default values ​​for each panel, and the pin number (-1 = disable) to which BUSY is connected, so please try commenting out any unknown items.

      cfg.memory_width = 320;  // Maximum width supported by driver IC
      cfg.memory_height = 480; // Maximum height supported by driver IC
      cfg.panel_width = 320;   // actual displayable width
      cfg.panel_height = 480;  // actual displayable height
      cfg.offset_x = 0;        // Panel offset in X direction
      cfg.offset_y = 0;        // Panel offset in Y direction
#ifdef PORTRAIT
      cfg.offset_rotation = 0;
#else
      cfg.offset_rotation = 1;
#endif
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits = 1;
      cfg.readable = false;
      cfg.invert = false;
      cfg.rgb_order = false;
      cfg.dlen_16bit = false;
      cfg.bus_shared = false;

      _panel_instance.config(cfg);
    }

    {                                      // Set backlight control. (delete if not necessary)
      auto cfg = _light_instance.config(); // Get the structure for backlight configuration.

      cfg.pin_bl = 23;     // pin number to which the backlight is connected
      cfg.invert = false;  // true to invert backlight brightness
      cfg.freq = 44100;    // backlight PWM frequency
      cfg.pwm_channel = 1; // PWM channel number to use

      _light_instance.config(cfg);
      _panel_instance.setLight(&_light_instance); // Sets the backlight to the panel.
    }

    { // Configure settings for touch screen control. (delete if not necessary)
      auto cfg = _touch_instance.config();

      cfg.x_min = 0;    // Minimum X value (raw value) obtained from the touchscreen
      cfg.x_max = 319;  // Maximum X value (raw value) obtained from the touchscreen
      cfg.y_min = 0;    // Minimum Y value obtained from touchscreen (raw value)
      cfg.y_max = 479;  // Maximum Y value (raw value) obtained from the touchscreen
      cfg.pin_int = 39; // pin number to which INT is connected
      cfg.bus_shared = false;
      cfg.offset_rotation = 0;

      // For I2C connection
      cfg.i2c_port = 1;    // Select I2C to use (0 or 1)
      cfg.i2c_addr = 0x38; // I2C device address number
      cfg.pin_sda = 18;    // pin number where SDA is connected
      cfg.pin_scl = 19;    // pin number to which SCL is connected
      cfg.freq = 400000;   // set I2C clock

      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance); // Set the touchscreen to the panel.
    }

    setPanel(&_panel_instance); // Sets the panel to use.
  }
};

#endif

// Create an instance of the prepared class.
LGFX tft;

ESP32Time rtc;
WiFiMulti wifiMulti;
HTTPClient http;

DynamicJsonDocument gptRequest(2048);
DynamicJsonDocument gptMessage(2048);

static lv_disp_draw_buf_t draw_buf;
static lv_disp_drv_t disp_drv;

static lv_color_t disp_draw_buf[screenWidth * SCR];
static lv_color_t disp_draw_buf2[screenWidth * SCR];

void addItem(const char *name, const void *src, const char *text, bool success);

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  if (tft.getStartCount() == 0)
  {
    tft.endWrite();
  }

  tft.pushImageDMA(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (lgfx::swap565_t *)&color_p->full);

  lv_disp_flush_ready(disp); /* tell lvgl that flushing is done */
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  uint16_t touchX, touchY;

  bool touched = tft.getTouch(&touchX, &touchY);

  if (!touched)
  {
    data->state = LV_INDEV_STATE_REL;
  }
  else
  {
    data->state = LV_INDEV_STATE_PR;

    /*Set the coordinates*/
    data->point.x = touchX;
    data->point.y = touchY;
  }
}

void requestResult(int requestCode, int statusCode, String payload, long time)
{

  Serial.printf("Request %d received, time %dms, code: %d\n", requestCode, time, statusCode);

  // if (statusCode == HTTP_CODE_OK)
  // {
  //   // Serial.println(payload);
  // }
  Serial.println(payload);

  switch (requestCode)
  {
  case TIME_REQUEST:
    if (statusCode == HTTP_CODE_OK)
    {
      DynamicJsonDocument json(100);
      deserializeJson(json, payload);
      long t = json["timestamp"].as<long>();
      rtc.setTime(t);
    }
    break;
  case GPT_REQUEST:
    if (statusCode == HTTP_CODE_OK)
    {
      DynamicJsonDocument json(2048);
      deserializeJson(json, payload);
      
      String response = json["choices"][0]["message"]["content"].as<String>();
      
      addItem("ChatGPT", &ui_img_electron_png, response.c_str(), true);

      gptMessage[msgIndex]["role"] = "assistant";
      gptMessage[msgIndex]["content"] = response;
      msgIndex++;
    }
    else
    {
      addItem("ChatGPT", &ui_img_electron_png, "Error while parsing your request, please check the serial monitor logs", false);
    }
    break;
  }
}

void sendRequest(void *parameter)
{
  long t;

  for (int r = 0; r < MAX_REQUEST; r++)
  {
    if (request[r].active)
    {
      t = millis();
      http.begin(request[r].url);
      for (int i = 0; i < request[r].headerSize; i++)
      {
        http.addHeader(request[r].headers[i].key, request[r].headers[i].value);
      }
      int httpCode;
      if (request[r].method)
      {
        Serial.println(request[r].data);
        httpCode = http.POST(request[r].data);
      }
      else
      {
        httpCode = http.GET();
      }

      String payload = http.getString();

      // http.end();
      t = millis() - t;
      requestResult(request[r].code, httpCode, payload, t);
      request[r].active = false;
    }
  }
  http.end();
  activeRequest = false;
  // When you're done, call vTaskDelete. Don't forget this!
  vTaskDelete(NULL);
}

void connectWiFi(void *parameter)
{
  uint8_t status;
  while (true)
  {
    status = wifiMulti.run();
    Serial.printf("WiFi trying: %d\n", status);
    if (status == WL_CONNECTED || status == WL_CONNECT_FAILED || status == WL_DISCONNECTED || status == WL_NO_SSID_AVAIL)
    {
      break;
    }
  }
  Serial.printf("WiFi exit: %d\n", status);
  // When you're done, call vTaskDelete. Don't forget this!
  vTaskDelete(NULL);
}

bool runRequest()
{
  // returns true if the task was created
  // returns false if the previous task has not completed, new one cannot be created
  if (!activeRequest)
  {
    activeRequest = true;
    // xTaskCreatePinnedToCore(
    xTaskCreate(
        sendRequest,     // Function that should be called
        "HTTP Requests", // Name of the task (for debugging)
        8192,            // Stack size (bytes)
        NULL,            // Parameter to pass
        1,               // Task priority
        NULL
        // NULL,               // Task handle
        // 1
    );

    return true;
  }
  else
  {
    return false;
  }
}

void addItem(const char *name, const void *src, const char *text, bool success)
{
  lv_obj_t *ui_chatItemPanel = lv_obj_create(ui_chatPanel);
  lv_obj_set_width(ui_chatItemPanel, 320);
  lv_obj_set_height(ui_chatItemPanel, LV_SIZE_CONTENT); /// 67
  lv_obj_set_align(ui_chatItemPanel, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(ui_chatItemPanel, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(ui_chatItemPanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
  lv_obj_clear_flag(ui_chatItemPanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
  lv_obj_set_style_radius(ui_chatItemPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui_chatItemPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_chatItemPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(ui_chatItemPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(ui_chatItemPanel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(ui_chatItemPanel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(ui_chatItemPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(ui_chatItemPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_row(ui_chatItemPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_column(ui_chatItemPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_userTitlePanel = lv_obj_create(ui_chatItemPanel);
  lv_obj_set_width(ui_userTitlePanel, 290);
  lv_obj_set_height(ui_userTitlePanel, LV_SIZE_CONTENT); /// 50
  lv_obj_set_align(ui_userTitlePanel, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(ui_userTitlePanel, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(ui_userTitlePanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
  lv_obj_clear_flag(ui_userTitlePanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
  lv_obj_set_style_radius(ui_userTitlePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui_userTitlePanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_userTitlePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(ui_userTitlePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(ui_userTitlePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(ui_userTitlePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(ui_userTitlePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(ui_userTitlePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_userIcon = lv_img_create(ui_userTitlePanel);
  lv_img_set_src(ui_userIcon, src);
  lv_obj_set_width(ui_userIcon, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_userIcon, LV_SIZE_CONTENT); /// 1
  lv_obj_set_align(ui_userIcon, LV_ALIGN_CENTER);
  lv_obj_add_flag(ui_userIcon, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
  lv_obj_clear_flag(ui_userIcon, LV_OBJ_FLAG_SCROLLABLE); /// Flags

  lv_obj_t *ui_userName = lv_label_create(ui_userTitlePanel);
  lv_obj_set_width(ui_userName, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_userName, LV_SIZE_CONTENT); /// 1
  lv_obj_set_align(ui_userName, LV_ALIGN_CENTER);
  lv_label_set_text(ui_userName, name);
  lv_obj_set_style_text_font(ui_userName, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_textLabel = lv_label_create(ui_chatItemPanel);
  lv_obj_set_width(ui_textLabel, 290);
  lv_obj_set_height(ui_textLabel, LV_SIZE_CONTENT); /// 1
  lv_obj_set_align(ui_textLabel, LV_ALIGN_CENTER);
  lv_label_set_text(ui_textLabel, text);
  lv_obj_set_style_text_font(ui_textLabel, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
  if (success)
  {
    lv_obj_set_style_text_color(ui_textLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  }
  else
  {
    lv_obj_set_style_text_color(ui_textLabel, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
  }
}

void onSendPrompt(lv_event_t *e)
{
  const char *text = lv_textarea_get_text(ui_promptText);

  if (strlen(text) > 0)
  {
    addItem("You", &ui_img_user_a_png, text, true);

    String txt(text);

    gptMessage[msgIndex]["role"] = "user";
    gptMessage[msgIndex]["content"] = txt;
    msgIndex++;
    gptRequest["messages"] = gptMessage;

    String data;
    serializeJson(gptRequest, data);

    request[1].data = data;   // set the request data
    request[1].active = true; // activate the request

    // serializeJsonPretty(gptRequest, Serial);
    // Serial.println();

    if (!runRequest())
    {
      addItem("ChatGPT", &ui_img_user_a_png, "Failed to create a request. Try again later", false);
    }

    lv_textarea_set_text(ui_promptText, "");
  }
}

void onTextChanged(lv_event_t *e)
{
  const char *text = lv_textarea_get_text(ui_promptText);
  if (String(text).equals(""))
  {
    lv_obj_add_state(ui_sendButton, LV_STATE_DISABLED);
  }
  else
  {
    lv_obj_clear_state(ui_sendButton, LV_STATE_DISABLED);
  }
}

void setWifi()
{
  // your wifi credentials
  wifiMulti.addAP("wifi_name", "wifi_password");
}

void logCallback(Level level, unsigned long time, String message)
{
  Serial.print(message);

  switch (level)
  {
  case ERROR:
    // maybe save only errors to local storage
    break;
  }
}

void setup()
{
  Serial.begin(115200);

  Timber.setLogCallback(logCallback);

  tft.init();
  tft.initDMA();
  tft.startWrite();

  lv_init();

  Timber.i("Width %d\tHeight %d", screenWidth, screenHeight);

  if (!disp_draw_buf)
  {
    Timber.e("LVGL disp_draw_buf allocate failed!");
  }
  else
  {

    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, disp_draw_buf2, screenWidth * SCR);

    /* Initialize the display */
    lv_disp_drv_init(&disp_drv);
    /* Change the following line to your display resolution */
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /* Initialize the input device driver */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

#ifdef USE_UI
    ui_init();

    lv_keyboard_set_textarea(ui_keyboard, ui_promptText);

    // addItem("You", &ui_img_user_a_png, "Hello ChatGPT", true);
    // addItem("ChatGPT", &ui_img_electron_png, "Hello there, how can I help you? Make sure you have setup your wifi credentials", false);
#else
    lv_obj_t *label1 = lv_label_create(lv_scr_act());
    lv_obj_align(label1, LV_ALIGN_TOP_MID, 0, 100);
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label1, screenWidth - 30);
    lv_label_set_text(label1, "Hello there! You have not included UI files, add you UI files and "
                              "uncomment this line\n'//#define USE_UI' in include/main.h\n"
                              "You should be able to move the slider below");

    /*Create a slider below the label*/
    lv_obj_t *slider1 = lv_slider_create(lv_scr_act());
    lv_obj_set_width(slider1, screenWidth - 40);
    lv_obj_align_to(slider1, label1, LV_ALIGN_OUT_BOTTOM_MID, 0, 50);
#endif

    Timber.i("Setup done");
  }

  setWifi();

  xTaskCreate(
      connectWiFi,    // Function that should be called
      "WIFI Connect", // Name of the task (for debugging)
      8192,           // Stack size (bytes)
      NULL,           // Parameter to pass
      1,              // Task priority
      NULL);

  gptMessage[msgIndex]["role"] = "user";
  gptMessage[msgIndex]["content"] = "Hello ChatGPT";

  gptRequest["model"] = "gpt-3.5-turbo";
  gptRequest["messages"] = gptMessage;
  gptRequest["temperature"] = 0.7;

  request[0].active = true;
  request[0].method = false;
  request[0].code = TIME_REQUEST;
  request[0].url = "https://iot.fbiego.com/api/v1/time";

  request[1].active = false;
  request[1].method = true;
  request[1].code = GPT_REQUEST;
  request[1].url = "https://api.openai.com/v1/chat/completions";

  request[1].headers[0].key = "Authorization";
  request[1].headers[0].value = bearer;
  request[1].headers[1].key = "Content-Type";
  request[1].headers[1].value = "application/json";
  request[1].headerSize = 2;
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);

  if (WiFi.isConnected())
  {
    lv_obj_set_style_img_recolor_opa(ui_wifiIcon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    if (!onConnect)
    {
      Serial.println("WiFi Connected");
      runRequest();
      onConnect = true;
    }
  }
  else
  {
    onConnect = false;
    lv_obj_set_style_img_recolor_opa(ui_wifiIcon, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
  }
}