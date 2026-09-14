/* Analysis pseudo-C, not buildable source. */

void FUN_8003fa7c(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  FUN_8008f868(&DAT_800f0cb0,param_3);
  DAT_8009c74d = 0;
  DAT_8009c752 = (undefined2)param_2;
  DAT_8009c754 = 0x200;
  DAT_8009c768 = (undefined1)(param_2 + 0x1fff >> 0xd);
  if (param_2 + 0x1fff < 0) {
    DAT_8009c768 = (undefined1)(param_2 + 0x3ffe >> 0xd);
  }
  DAT_8009c75c = param_1;
  FUN_8003fa64(param_4);
  return;
}

