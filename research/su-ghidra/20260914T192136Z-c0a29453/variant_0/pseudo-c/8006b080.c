/* Analysis pseudo-C, not buildable source. */

void FUN_8006b080(short param_1,undefined2 param_2,short param_3,undefined2 param_4)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined2 *puVar5;
  int *piVar6;
  
  piVar6 = &DAT_801a8000;
  iVar4 = 7;
  iVar2 = -0x7fe57ff2;
  DAT_801a8004 = param_1 + 2;
  DAT_801a8020 = param_3 + 2;
  DAT_801a8006 = param_2;
  DAT_801a8022 = param_4;
  do {
    *(undefined2 *)(iVar2 + 10) = 0;
    iVar4 = iVar4 + -1;
    iVar2 = iVar2 + -2;
  } while (-1 < iVar4);
  iVar2 = 0;
  puVar5 = &DAT_801a8006;
  do {
    puVar5[1] = 0;
    uVar3 = FUN_80040350();
    iVar4 = FUN_800403d0(uVar3,6);
    *(undefined1 *)(iVar4 + 0x68) = 0;
    *(undefined1 *)(iVar4 + 0x69) = 0;
    *(undefined2 *)(iVar4 + 0x30) = puVar5[-1];
    uVar1 = *puVar5;
    *(char *)(iVar4 + 0x6a) = (char)iVar2;
    iVar2 = iVar2 + 1;
    puVar5 = puVar5 + 0xe;
    *(undefined2 *)(iVar4 + 0x32) = uVar1;
    FUN_80042c48(iVar4);
    *(code **)(iVar4 + 0x4c) = FUN_8006ab9c;
    *piVar6 = iVar4;
    piVar6 = piVar6 + 7;
  } while (iVar2 < 2);
  DAT_8009c4c2 = 0;
  DAT_8009c4c0 = 0;
  return;
}

