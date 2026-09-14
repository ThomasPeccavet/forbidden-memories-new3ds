/* Analysis pseudo-C, not buildable source. */

void FUN_80014d38(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  uint uVar1;
  undefined4 *puVar2;
  
  if (DAT_8009c4a8 == (code *)0x0) {
    uVar1 = DAT_8009c460 & 0x2000030;
    puVar2 = (undefined4 *)0x0;
    DAT_8009c460 = DAT_8009c460 | 0x40;
    if (uVar1 != 0 || DAT_8009c484 != 0) goto LAB_80014de0;
  }
  else {
    DAT_8009c460 = DAT_8009c460 | 0x40;
    (*DAT_8009c4a8)();
  }
  puVar2 = &DAT_800eb1b8;
  FUN_800138b4(&DAT_800eb1b8,param_1,param_2,param_3,param_4,param_5,param_6,param_7);
LAB_80014de0:
  DAT_8009c460 = puVar2[0xb] | 0x10;
  return;
}

