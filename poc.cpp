#pragma leco tool
import stbtt;

#include <stdio.h>

unsigned char ttf_buffer[1 << 25];

int main(int argc, char **argv) {
  stbtt_fontinfo font{};
  unsigned char *bitmap;
  int w, h, i, j, c = 'a', s = 20;

  fread(ttf_buffer, 1, 1 << 25, fopen("c:\\Windows\\Fonts\\arial.ttf", "rb"));

  stbtt_InitFont(&font, ttf_buffer, stbtt_GetFontOffsetForIndex(ttf_buffer, 0));
  bitmap = stbtt_GetCodepointBitmap(
      &font, 0, stbtt_ScaleForPixelHeight(&font, s), c, &w, &h, 0, 0);

  for (j = 0; j < h; ++j) {
    for (i = 0; i < w; ++i)
      putchar(" .:ioVM@"[bitmap[j * w + i] >> 5]);
    putchar('\n');
  }
  return 0;
}
