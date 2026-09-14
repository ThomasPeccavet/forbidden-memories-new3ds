/* Analysis pseudo-C, not buildable source. */

int FUN_8004c0bc(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  iVar1 = FUN_8004bf74();
  uVar2 = FUN_8004bf74(param_1);
  uVar3 = FUN_8004bf74(param_1);
  uVar4 = FUN_8004bf74(param_1);
  return (uVar4 & 0xff) + (uVar3 & 0xff) * 0x100 + (uVar2 & 0xff) * 0x10000 + iVar1 * 0x1000000;
}

