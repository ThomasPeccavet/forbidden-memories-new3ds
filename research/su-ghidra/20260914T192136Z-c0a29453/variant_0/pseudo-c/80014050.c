/* Analysis pseudo-C, not buildable source. */

void FUN_80014050(char param_1)

{
  if (param_1 == '\x05') {
    DAT_8009c480 = DAT_8009c480 + 1;
    FUN_8007ba00(0xa0,&DAT_8009c4b4,0x15,FUN_80014050,0xffffffff);
  }
  else if (param_1 == '\x02') {
    DAT_8009c460 = DAT_8009c460 & 0xfffffbff;
  }
  return;
}

