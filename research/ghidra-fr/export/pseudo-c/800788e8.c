/* Analysis pseudo-C, not buildable source. */

void FUN_800788e8(void)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)(DAT_800f70e4 + DAT_800f70d8 * 0x20);
  *puVar1 = 2;
  DAT_800f7108 = *(undefined4 *)(puVar1 + 0xe);
  DAT_800f710c = *(undefined4 *)(puVar1 + 4);
  DAT_800f70d8 = DAT_800f70d4;
  if (DAT_800f7118 != (code *)0x0) {
    (*DAT_800f7118)();
  }
  DAT_800f7100 = 0;
  return;
}

