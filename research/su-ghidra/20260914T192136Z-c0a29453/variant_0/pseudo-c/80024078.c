/* Analysis pseudo-C, not buildable source. */

void FUN_80024078(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0xffffffff;
  if ((DAT_8009c710 & 0xf000) != 0) {
    if ((DAT_8009c710 & 0x2000) != 0) {
      uVar1 = 0;
    }
    if ((DAT_8009c710 & 0x4000) != 0) {
      uVar1 = 1;
    }
    if ((DAT_8009c710 & 0x8000) != 0) {
      uVar1 = 2;
    }
    if ((DAT_8009c710 & 0x1000) != 0) {
      uVar1 = 3;
    }
  }
  FUN_80023dc4(param_1,uVar1);
  return;
}

