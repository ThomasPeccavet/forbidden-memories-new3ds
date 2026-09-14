/* Analysis pseudo-C, not buildable source. */

uint FUN_8004c138(undefined4 param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = FUN_8004bf74();
  uVar2 = FUN_8004bf74(param_1);
  return uVar2 & 0xff | (uVar1 & 0xff) << 8;
}

