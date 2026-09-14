/* Analysis pseudo-C, not buildable source. */

void FUN_80014224(char param_1)

{
  if (param_1 == '\x05') {
    DAT_8009c480 = DAT_8009c480 + 1;
    FUN_8007ba00(0x4a,&DAT_8009c4b4,0x1b,FUN_80014224,0xffffffff);
  }
  else if (param_1 == '\x02') {
    DAT_8009c464 = 5;
    DAT_8009c460 = DAT_8009c460 & 0xfffffbff | 0x1000;
  }
  return;
}

