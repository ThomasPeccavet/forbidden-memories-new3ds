/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8002314c(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_8001eda4(&DAT_801a7ad8 +
                       (uint)(byte)(&DAT_800919e0)
                                   [*(char *)(param_1 + 0x10) * 5 + (int)*(char *)(param_1 + 0xf) +
                                    (uint)DAT_8009c504 * 0x14] * 7,
                       &DAT_801a7ad8 +
                       (uint)(byte)(&DAT_800919e0)
                                   [*(char *)(param_2 + 0x10) * 5 + (int)*(char *)(param_2 + 0xf) +
                                    (uint)DAT_8009c504 * 0x14] * 7);
  uVar2 = 4;
  if ((iVar1 != 0) && (uVar2 = 1, -1 < iVar1)) {
    uVar2 = 6;
  }
  return uVar2;
}

