#pragma leco tool
import stbtt;

#include <math.h>
#include <stdio.h>

unsigned char buffer[24 << 20];
unsigned char screen[20][100];

int main(int arg, char **argv) {
  stbtt_fontinfo font;
  int i, j, ascent, baseline, ch = 0;
  float scale,
      xpos = 2; // leave a little padding in case the character extends left
  const char *text =
      "Heljo World!"; // intentionally misspelled to show 'lj' brokenness

  fread(buffer, 1, 1000000, fopen("c:/windows/fonts/arialbd.ttf", "rb"));
  stbtt_InitFont(&font, buffer, 0);

  scale = stbtt_ScaleForPixelHeight(&font, 15);
  stbtt_GetFontVMetrics(&font, &ascent, 0, 0);
  baseline = (int)(ascent * scale);

  while (text[ch]) {
    int advance, lsb, x0, y0, x1, y1;
    float x_shift = xpos - (float)floor(xpos);
    stbtt_GetCodepointHMetrics(&font, text[ch], &advance, &lsb);
    stbtt_GetCodepointBitmapBoxSubpixel(&font, text[ch], scale, scale, x_shift,
                                        0, &x0, &y0, &x1, &y1);
    stbtt_MakeCodepointBitmapSubpixel(
        &font, &screen[baseline + y0][(int)xpos + x0], x1 - x0, y1 - y0, 100,
        scale, scale, x_shift, 0, text[ch]);
    // note that this stomps the old data, so where character boxes overlap
    // (e.g. 'lj') it's wrong because this API is really for baking character
    // bitmaps into textures. if you want to render a sequence of characters,
    // you really need to render each bitmap to a temp buffer, then "alpha
    // blend" that into the working buffer
    xpos += (advance * scale);
    if (text[ch + 1])
      xpos +=
          scale * stbtt_GetCodepointKernAdvance(&font, text[ch], text[ch + 1]);
    ++ch;
  }

  for (j = 0; j < 20; ++j) {
    for (i = 0; i < 100; ++i)
      putchar(" .:ioVM@"[screen[j][i] >> 5]);
    putchar('\n');
  }

  return 0;
}
