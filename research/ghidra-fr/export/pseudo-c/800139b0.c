/* Analysis pseudo-C, not buildable source. */

undefined4 * FUN_800139b0(uint param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  if ((DAT_8009c460 & 0x20) == 0) {
    puVar1 = &DAT_800eb200;
    FUN_8001385c(&DAT_800eb200,param_1 & 0xf,param_2,0);
    DAT_800eb246 = 0;
    DAT_800eb22c = 0x100000;
    DAT_8009c460 = DAT_8009c460 | 0x20;
  }
  else {
    puVar1 = (undefined4 *)0x0;
  }
  return puVar1;
}

