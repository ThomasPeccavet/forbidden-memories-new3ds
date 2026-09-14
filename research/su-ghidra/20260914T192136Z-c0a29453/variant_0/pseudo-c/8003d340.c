/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8003d340(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  uVar1 = FUN_8003d084(param_1,0x340);
  piVar4 = (int *)(param_1 + 0x378);
  iVar3 = 0xf;
  DAT_8009c2ec = uVar1 & 0xffff | uVar1 << 0x10;
  s_UUUU__8009c2f0._0_4_ = DAT_8009c2ec;
  do {
    iVar2 = FUN_8003d040();
    if (*piVar4 != iVar2) {
      return 0;
    }
    iVar3 = iVar3 + -1;
    piVar4 = piVar4 + -1;
  } while (iVar3 != 0);
  uVar1 = FUN_8003d084(param_1 + 0x380,0x6c);
  piVar4 = (int *)(param_1 + 0x3f8);
  iVar3 = 4;
  DAT_8009c2ec = uVar1 & 0xffff | uVar1 << 0x10;
  s_UUUU__8009c2f0._0_4_ = DAT_8009c2ec;
  do {
    iVar2 = FUN_8003d040();
    if (*piVar4 != iVar2) {
      return 0;
    }
    iVar3 = iVar3 + -1;
    piVar4 = piVar4 + -1;
  } while (iVar3 != 0);
  uVar1 = FUN_8003d084(param_1 + 0x400,0x204);
  piVar4 = (int *)(param_1 + 0x624);
  iVar3 = 8;
  DAT_8009c2ec = uVar1 & 0xffff | uVar1 << 0x10;
  s_UUUU__8009c2f0._0_4_ = DAT_8009c2ec;
  do {
    iVar2 = FUN_8003d040();
    if (*piVar4 != iVar2) {
      return 0;
    }
    iVar3 = iVar3 + -1;
    piVar4 = piVar4 + -1;
  } while (iVar3 != 0);
  return 1;
}

