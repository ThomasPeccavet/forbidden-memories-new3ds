/* Analysis pseudo-C, not buildable source. */

void FUN_80013fbc(char param_1)

{
  if (param_1 == '\x05') {
    DAT_8009c480 = DAT_8009c480 + 1;
    FUN_8007ba00(0xa0,&DAT_8009c4b4,6,FUN_80013fbc,0xffffffff);
  }
  else if (param_1 == '\x02') {
    FUN_8007e3d0(1);
    FUN_8007e2e8(FUN_80013b44,0xffffffff);
    DAT_8009c4ac = 0;
    DAT_8009c478 = 0;
    DAT_8009c460 = DAT_8009c460 & 0xfffffbff;
  }
  return;
}

