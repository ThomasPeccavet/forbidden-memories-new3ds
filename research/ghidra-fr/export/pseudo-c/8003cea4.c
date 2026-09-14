/* Analysis pseudo-C, not buildable source. */

void FUN_8003cea4(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  byte bVar4;
  byte *pbVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  
  uVar1 = DAT_8009c70c;
  uVar6 = 0;
  iVar9 = 0x1f;
  pbVar5 = &DAT_800f0a0f;
  DAT_8009c70c = 0;
  uVar10 = (DAT_8009c720 ^ uVar1) & uVar1;
  DAT_8009c720 = uVar1;
  uVar7 = uVar10;
  uVar8 = uVar1;
  do {
    uVar6 = uVar6 << 1;
    if ((uVar8 & 0x80000000) == 0) {
      *pbVar5 = 0;
    }
    else {
      if ((uVar7 & 0x80000000) != 0) {
        uVar6 = uVar6 | 1;
      }
      bVar4 = *pbVar5 + (char)DAT_8009c43c;
      *pbVar5 = bVar4;
      if (DAT_8009c71c <= bVar4) {
        uVar6 = uVar6 | 1;
        *pbVar5 = DAT_8009c724;
      }
    }
    uVar3 = DAT_8009c718;
    uVar2 = DAT_8009c714;
    uVar8 = uVar8 << 1;
    uVar7 = uVar7 << 1;
    iVar9 = iVar9 + -1;
    pbVar5 = pbVar5 + -1;
  } while (-1 < iVar9);
  if (DAT_8009c428 == 0) {
    DAT_8009c714 = 0;
    DAT_8009c718 = 0;
    uVar10 = uVar10 | uVar3;
    uVar6 = uVar6 | uVar2;
  }
  else {
    DAT_8009c714 = DAT_8009c714 | uVar6;
    DAT_8009c718 = DAT_8009c718 | uVar10;
  }
  DAT_8009c710 = (short)uVar1;
  DAT_8009c712 = (short)(uVar1 >> 0x10);
  DAT_8009c72c = (short)uVar10;
  DAT_8009c72e = (short)(uVar10 >> 0x10);
  DAT_8009c728 = (short)uVar6;
  DAT_8009c72a = (short)(uVar6 >> 0x10);
  return;
}

