/* Analysis pseudo-C, not buildable source. */

void FUN_80038eb8(int param_1)

{
  byte bVar1;
  byte bVar2;
  undefined2 uVar3;
  byte *pbVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  undefined *puVar8;
  uint uVar9;
  
  DAT_8009c6cc = 1;
  puVar6 = (undefined4 *)(param_1 + *(char *)(param_1 + 0x58) * 4);
  pbVar4 = (byte *)*puVar6;
  bVar1 = *pbVar4;
  uVar7 = (uint)bVar1;
  *puVar6 = pbVar4 + 1;
  puVar8 = &DAT_800ec2a8;
  puVar6 = (undefined4 *)(param_1 + *(char *)(param_1 + 0x58) * 4);
  pbVar4 = (byte *)*puVar6;
  bVar2 = *pbVar4;
  *puVar6 = pbVar4 + 1;
  if (uVar7 < 0x41) {
    if (((int)DAT_800ec2d8 != uVar7) && (puVar8 = &DAT_800ec2f4, (int)DAT_800ec324 != uVar7)) {
      puVar8 = (undefined *)0x0;
    }
  }
  else {
    puVar8 = &DAT_800ec340;
  }
  if ((bVar2 & 0x80) != 0) {
    if (puVar8 == (undefined *)0x0) {
      return;
    }
    if ((bVar2 & 2) != 0) {
      DAT_8009c6ac = puVar8;
      FUN_8003a364(puVar8);
      return;
    }
    if ((bVar2 & 1) != 0) {
      DAT_8009c6ac = puVar8;
      *(undefined1 *)(param_1 + 0x51) = 0xe;
      return;
    }
    uVar3 = 0x178;
    if (puVar8[0x3c] == '\0') {
      uVar3 = 0xffc8;
    }
    DAT_8009c6ac = puVar8;
    *(undefined2 *)(puVar8 + 0x40) = uVar3;
    *(undefined2 *)(puVar8 + 0x42) = 0xb2;
    *(undefined2 *)(puVar8 + 0x44) = 0x10;
    *(undefined1 *)(param_1 + 0x51) = 7;
    puVar8[0x33] = 3;
    if (uVar7 < 0x41) {
      return;
    }
    puVar8[0x33] = 5;
    *(undefined2 *)(puVar8 + 0x40) = 1;
    return;
  }
  if ((bVar2 & 0x60) != 0) {
    if (puVar8 == (undefined *)0x0) {
      return;
    }
    if (0x40 < uVar7) {
      return;
    }
    if ((bVar2 & 0x40) != 0) {
      DAT_8009c6ac = puVar8;
      puVar8[0x31] = bVar2 & 3;
      *(undefined1 *)(param_1 + 0x51) = 9;
      return;
    }
    DAT_8009c6ac = puVar8;
    if ((bVar2 & 0x20) != 0) {
      bVar1 = puVar8[0x32];
      puVar8[0x32] = bVar1 & 0xef;
      if ((bVar2 & 1) == 0) {
        return;
      }
      puVar8[0x32] = bVar1 & 0xef | 0x10;
      return;
    }
  }
  uVar9 = bVar2 & 1;
  if (0x40 < uVar7) {
    uVar9 = 2;
  }
  iVar5 = uVar9 * 0x4c;
  puVar8 = &DAT_800ec2a8 + iVar5;
  FUN_8003a2d4(puVar8);
  (&DAT_800ec2d8)[iVar5] = bVar1;
  (&DAT_800ec2e4)[iVar5] = (char)uVar9;
  if (uVar9 == 0) {
    uVar3 = 0xffc8;
  }
  else {
    uVar3 = 0x178;
  }
  *(undefined2 *)(&DAT_800ec2dc + iVar5) = uVar3;
  *(undefined1 *)(param_1 + 0x51) = 6;
  DAT_8009c6ac = puVar8;
  if (uVar7 < 0x41) {
    (&DAT_800ec2db)[iVar5] = 2;
    *(undefined2 *)(iVar5 + -0x7ff13d18) = 3;
    if ((bVar2 & 8) != 0) {
      *(undefined2 *)(&DAT_800ec2dc + iVar5) = 0x400;
      *(undefined2 *)(iVar5 + -0x7ff13d18) = 7;
    }
    if ((bVar2 & 0x10) != 0) {
      (&DAT_800ec2d9)[iVar5] = (byte)((int)(uint)bVar2 >> 1) & 3;
    }
  }
  else {
    (&DAT_800ec2db)[iVar5] = 5;
    (&DAT_800ec2e4)[iVar5] = 2;
    *(undefined2 *)(&DAT_800ec2dc + iVar5) = 0xf0;
    *(undefined2 *)(iVar5 + -0x7ff13d18) = 0;
    *(undefined2 *)(iVar5 + -0x7ff13d22) = 0x60;
  }
  return;
}

