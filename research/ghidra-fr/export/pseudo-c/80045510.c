/* Analysis pseudo-C, not buildable source. */

int FUN_80045510(void)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  short *psVar4;
  int iVar5;
  
  iVar3 = FUN_800772b8(DAT_8009c7e0 + 0x53c,5);
  iVar5 = DAT_8009c7e0;
  *(int *)(DAT_8009c7e0 + 0x538) = iVar3;
  iVar2 = DAT_8009c7e0;
  if (iVar3 == 0) {
    psVar4 = *(short **)(iVar5 + 0x153c);
  }
  else {
    psVar4 = *(short **)(iVar5 + 0x1540);
  }
  iVar5 = 0;
  *(undefined4 *)(DAT_8009c7e0 + 0x154c) = 0;
  *(undefined4 *)(iVar2 + 0x1550) = 0;
  do {
    iVar5 = iVar5 + 1;
    *(uint *)(iVar2 + 0x154c) =
         *(int *)(iVar2 + 0x154c) + ((uint)((int)*psVar4 * (int)*psVar4) >> 8);
    iVar3 = DAT_8009c7e0;
    psVar4 = psVar4 + 1;
  } while (iVar5 < 0x100);
  iVar5 = (int)*(short *)(DAT_8009c7e0 + 0x154e);
  uVar1 = *(ushort *)(DAT_8009c7e0 + 0x40);
  psVar4 = (short *)(DAT_8009c7e0 + 0x1552);
  *(int *)(DAT_8009c7e0 + 0x154c) = iVar5;
  *(int *)(iVar3 + 0x1550) = (int)*psVar4;
  if ((uVar1 & 3) != 0) {
    iVar5 = 0;
  }
  return iVar5;
}

