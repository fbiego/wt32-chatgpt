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


#define PORTRAIT // comment for landscape
#define USE_UI  // uncomment to use ui files exported on /ui/ folder from squareline studio



/* Change to your screen resolution */
#ifdef PORTRAIT
static const uint32_t screenWidth = 320;
static const uint32_t screenHeight = 480;
#else
static const uint32_t screenWidth = 480;
static const uint32_t screenHeight = 320;
#endif


#define TIME_REQUEST 1
#define GPT_REQUEST 2

#define MAX_REQUEST 5

// your openai API key
String bearer =  "Bearer xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

long currentMillis;
bool onConnect;
bool activeRequest;
long timeout;

int msgIndex = 0;

struct Header
{
   String key;
   String value;
};

struct Request
{
  String url;
  int code;
  bool method;
  String data;
  bool active;
  Header headers[5];
  int headerSize = 0;
};

struct Request request[MAX_REQUEST];
