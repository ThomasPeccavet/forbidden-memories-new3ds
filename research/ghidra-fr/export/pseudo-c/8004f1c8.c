/* Analysis pseudo-C, not buildable source. */

/* WARNING: Removing unreachable block (ram,0x8004f250) */
/* WARNING: Removing unreachable block (ram,0x8004f260) */
/* WARNING: Removing unreachable block (ram,0x8004f268) */

int FUN_8004f1c8(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined1 auStack_10 [6];
  short local_a;
  
  if (param_1 < 2) {
    FUN_8005c108(param_1,auStack_10);
    if (local_a < 0x32) {
      local_a = 0x32;
    }
    iVar2 = (int)(short)(local_a + -300);
    if (iVar2 != 0) {
      iVar1 = param_2;
      if (0 < iVar2) {
        iVar1 = param_2 / 2;
      }
      param_2 = param_2 + (iVar2 * iVar1) / 0x2ee;
    }
  }
  return param_2;
}

