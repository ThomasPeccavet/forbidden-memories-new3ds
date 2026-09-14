/* Analysis pseudo-C, not buildable source. */

void FUN_80047910(void)

{
  ushort uVar1;
  ushort uVar2;
  ushort *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  *(undefined1 *)(DAT_8009c7e0 + 0x21a) = 0;
  *(undefined1 *)((int)DAT_8009c7e0 + 0x435) = 0;
  iVar6 = 0;
  do {
    *(undefined1 *)((int)DAT_8009c7e0 + iVar6 + 0x40c) = 0;
    *(undefined1 *)((int)DAT_8009c7e0 + iVar6 + 0x410) = 0;
    puVar3 = DAT_8009c7e0;
    DAT_8009c7e0[iVar6 + 0x202] = 0;
    puVar3[iVar6 + 0x20a] = 0;
    puVar3[iVar6 + 0x20e] = 0;
    *(undefined1 *)((int)puVar3 + iVar6 + 0x428) = 0;
    iVar5 = iVar6 + 1;
    DAT_8009c7e0[iVar6 + 0x216] = 0;
    iVar6 = iVar5;
  } while (iVar5 < 4);
  FUN_800777a8(0);
  puVar3 = DAT_8009c7e0;
  DAT_8009c7e0[0x1ca] = 0x3fff;
  puVar3[0x1cb] = 0x3fff;
  puVar3[0x1cc] = 0x1000;
  puVar3[0x1ce] = 0x3c00;
  puVar3[0x1d4] = 1;
  puVar3[0x1d5] = 0;
  puVar3[0x1d6] = 1;
  puVar3[0x1d7] = 0;
  puVar3[0x1d8] = 3;
  puVar3[0x1d9] = 0;
  uVar1 = *puVar3;
  iVar6 = 0;
  puVar3[0x224] = 0x2800;
  puVar3[0x225] = 0x801e;
  puVar3[0x21c] = 0x1010;
  puVar3[0x21d] = 0;
  uVar2 = *puVar3;
  puVar3[0x1c4] = 0xffff;
  puVar3[0x1c5] = 0;
  puVar3[0x1c8] = 0;
  puVar3[0x1c9] = 0;
  puVar3[0x1da] = 0;
  puVar3[0x1db] = 0;
  puVar3[0x1dc] = 0;
  puVar3[0x1dd] = 0;
  puVar3[0x1de] = 0;
  puVar3[0x21e] = 0x4000;
  puVar3[0x21f] = 0x801e;
  puVar3[0x220] = 0;
  puVar3[0x221] = 0xffff;
  *(uint *)(puVar3 + 0x222) = ((uint)uVar1 * 2 + 0xf & 0xfff0) + 0x801e4000;
  if (uVar2 != 0) {
    do {
      *(undefined2 *)(iVar6 * 2 + *(int *)(puVar3 + 0x21e)) = 0xffff;
      iVar6 = iVar6 + 1;
    } while (iVar6 < (int)(uint)*puVar3);
  }
  puVar3 = DAT_8009c7e0;
  iVar6 = 0;
  do {
    iVar4 = 0;
    iVar5 = iVar6 << 6;
    do {
      *(undefined2 *)((int)puVar3 + iVar5 + 0x44c) = 0xffff;
      iVar4 = iVar4 + 1;
      iVar5 = iVar5 + 2;
    } while (iVar4 < 0x20);
    iVar6 = iVar6 + 1;
  } while (iVar6 < 2);
  return;
}

