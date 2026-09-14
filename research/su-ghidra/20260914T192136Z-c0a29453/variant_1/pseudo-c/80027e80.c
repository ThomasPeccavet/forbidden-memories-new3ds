/* Analysis pseudo-C, not buildable source. */

void FUN_80027e80(short *param_1,int param_2)

{
  short sVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 *puVar5;
  short *psVar6;
  short *psVar7;
  short *psVar8;
  byte *pbVar9;
  int iVar10;
  int *piVar11;
  
  iVar4 = param_2 * 0x1a4;
  piVar11 = &DAT_801a7b64 + param_2 * 0x69;
  iVar10 = 0;
  psVar7 = (short *)(&DAT_801a7b70 + iVar4);
  pbVar9 = (byte *)((int)param_1 + 9);
  do {
    psVar6 = param_1;
    *psVar6 = 0;
    if ((psVar7[5] & 0x8000U) != 0) {
      *psVar6 = *psVar7;
      uVar3 = FUN_80016fe4(piVar11);
      *(short *)(pbVar9 + -7) = (short)uVar3;
      *(short *)(pbVar9 + -5) = (short)((uint)uVar3 >> 0x10);
      *(short *)(pbVar9 + -3) = psVar7[5];
      pbVar9[-1] = *(byte *)(*piVar11 + 0x68);
      if ((psVar7[5] & 0x200U) == 0) {
        bVar2 = (byte)((int)(&DAT_801d4244)[*psVar7 + -1] >> 0x16);
      }
      else {
        bVar2 = (byte)((int)(&DAT_801d4244)[*psVar7 + -1] >> 0x12);
      }
      *pbVar9 = bVar2 & 0xf;
    }
    iVar10 = iVar10 + 1;
    pbVar9 = pbVar9 + 0xc;
    psVar7 = psVar7 + 0xe;
    piVar11 = piVar11 + 7;
    param_1 = psVar6 + 6;
  } while (iVar10 < 5);
  piVar11 = (int *)(&DAT_801a7bf0 + iVar4);
  iVar10 = 0;
  psVar8 = (short *)(&DAT_801a7bfc + iVar4);
  pbVar9 = (byte *)((int)psVar6 + 0x15);
  psVar7 = psVar6 + 6;
  do {
    psVar6 = psVar7;
    *psVar6 = 0;
    if ((psVar8[5] & 0x8000U) != 0) {
      *psVar6 = *psVar8;
      uVar3 = FUN_80016fe4(piVar11);
      *(short *)(pbVar9 + -7) = (short)uVar3;
      *(short *)(pbVar9 + -5) = (short)((uint)uVar3 >> 0x10);
      *(short *)(pbVar9 + -3) = psVar8[5];
      pbVar9[-1] = *(byte *)(*piVar11 + 0x68);
      if ((psVar8[5] & 0x200U) == 0) {
        bVar2 = (byte)((int)(&DAT_801d4244)[*psVar8 + -1] >> 0x16);
      }
      else {
        bVar2 = (byte)((int)(&DAT_801d4244)[*psVar8 + -1] >> 0x12);
      }
      *pbVar9 = bVar2 & 0xf;
    }
    iVar10 = iVar10 + 1;
    pbVar9 = pbVar9 + 0xc;
    psVar7 = psVar6 + 6;
    psVar8 = psVar8 + 0xe;
    piVar11 = piVar11 + 7;
  } while (iVar10 < 5);
  iVar4 = 0;
  pbVar9 = (byte *)(psVar6 + 0xb);
  do {
    if (-1 < (char)(&DAT_800eb292)[iVar4 + param_2 * 0x20]) {
      sVar1 = (&DAT_801a7e20)[(char)(&DAT_800eb292)[iVar4 + param_2 * 0x20] * 3];
      *psVar7 = sVar1;
      piVar11 = &DAT_801d4244 + sVar1 + -1;
      *(ushort *)(pbVar9 + -8) = ((ushort)*piVar11 & 0x1ff) * 10;
      iVar10 = *piVar11;
      pbVar9[-0xffffffff00000004] = 0;
      pbVar9[-0xffffffff00000003] = 0;
      *(ushort *)(pbVar9 + -6) = ((ushort)(iVar10 >> 9) & 0x1ff) * 10;
      pbVar9[-2] = (byte)(*piVar11 >> 0x1a) & 0x1f;
      pbVar9[-1] = (byte)(*piVar11 >> 0x16) & 0xf;
      psVar7 = psVar7 + 6;
      *pbVar9 = (byte)(*piVar11 >> 0x12) & 0xf;
      pbVar9 = pbVar9 + 0xc;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 5);
  iVar4 = (int)(char)(&DAT_800eb290)[param_2 * 0x20];
  psVar6 = &DAT_801a7e20 + (iVar4 + param_2 * 0x28) * 3;
  if (iVar4 < 0x28) {
    puVar5 = (undefined1 *)((int)psVar7 + 0xb);
    do {
      sVar1 = *psVar6;
      *psVar7 = sVar1;
      piVar11 = &DAT_801d4244 + sVar1 + -1;
      *(ushort *)(puVar5 + -9) = ((ushort)*piVar11 & 0x1ff) * 10;
      iVar10 = *piVar11;
      *(undefined2 *)(puVar5 + -5) = 0;
      *(ushort *)(puVar5 + -7) = ((ushort)(iVar10 >> 9) & 0x1ff) * 10;
      puVar5[-3] = (byte)(*piVar11 >> 0x1a) & 0x1f;
      iVar4 = iVar4 + 1;
      puVar5[-2] = (byte)(*piVar11 >> 0x16) & 0xf;
      psVar7 = psVar7 + 6;
      puVar5[-1] = (byte)(*piVar11 >> 0x12) & 0xf;
      psVar8 = psVar6 + 1;
      psVar6 = psVar6 + 3;
      *puVar5 = (char)*psVar8;
      puVar5 = puVar5 + 0xc;
    } while (iVar4 < 0x28);
  }
  *psVar7 = 0;
  return;
}

