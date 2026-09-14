/* Analysis pseudo-C, not buildable source. */

void FUN_8006aed4(ushort *param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  ushort *puVar5;
  short sVar6;
  int iVar7;
  
  piVar4 = &DAT_801a8000 + param_2 * 7;
  iVar1 = *piVar4;
  iVar7 = 0x18;
  (&DAT_801a8008)[param_2 * 0xe] = (short)param_3;
  *(char *)(iVar1 + 0x68) = (char)param_3;
  if (param_3 != 0) {
    iVar7 = 0x1a;
  }
  iVar1 = 0;
  sVar6 = 0;
  puVar5 = param_1 + 1;
  do {
    DAT_801bf990 = 0;
    *(ushort *)((int)piVar4 + 10) = *param_1;
    uVar2 = (uint)*param_1;
    iVar3 = 0;
    if (uVar2 != 0) {
      iVar3 = iVar7;
      if (0x13 < ((int)(&DAT_801d4244)[uVar2 - 1] >> 0x1a & 0x1fU)) {
        iVar3 = iVar7 + 1;
      }
      DAT_801bf890 = (uint)*puVar5;
      DAT_8009c6b8 = *param_1;
      DAT_801bf88c = uVar2;
    }
    iVar3 = FUN_80036184(param_2 + 1,iVar3,(int)(short)(&DAT_801a8004)[param_2 * 0xe],
                         (int)(short)(&DAT_801a8006)[param_2 * 0xe],0x120,0xb0);
    *(short *)(iVar3 + 0x3a) = sVar6;
    if (*puVar5 == 0) {
      *(undefined1 *)(iVar3 + 0x54) = 4;
      *(ushort *)((int)piVar4 + 10) = *(ushort *)((int)piVar4 + 10) | 0x8000;
      DAT_801bf990 = 4;
    }
    if (iVar1 != 0) {
      *(ushort *)(iVar3 + 0x34) = *(ushort *)(iVar3 + 0x34) | 0x80;
    }
    puVar5 = puVar5 + 2;
    FUN_800399f0();
    param_1 = param_1 + 2;
    piVar4 = (int *)((int)piVar4 + 2);
    iVar1 = iVar1 + 1;
    sVar6 = sVar6 + 0x16;
  } while (iVar1 < 8);
  return;
}

