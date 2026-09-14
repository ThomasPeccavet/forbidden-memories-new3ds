/* Analysis pseudo-C, not buildable source. */

void FUN_80025a1c(void)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 *puVar3;
  undefined4 uVar4;
  int *piVar5;
  
  iVar2 = FUN_80024ee0();
  if (iVar2 == 0) {
    DAT_8009c4e4 = 0;
    puVar3 = (undefined2 *)FUN_8002c7d8(0x10);
    iVar2 = (DAT_8009c4e4 + 5) * 4 + (uint)DAT_8009c504 * 0x50;
    uVar1 = *(undefined2 *)(&DAT_80091a08 + iVar2);
    DAT_8009c598 = puVar3;
    puVar3[1] = 0;
    *puVar3 = uVar1;
    uVar4 = 0x15;
    puVar3[2] = *(undefined2 *)(&DAT_80091a0a + iVar2);
  }
  else {
    if ((DAT_8009c5f8 & 1) == 0) {
      DAT_8009c550 = 0;
      return;
    }
    if ((uint)*(byte *)((int)DAT_8009c598 + 0x1d) != (int)DAT_8009c4e4 + 1U) {
      return;
    }
    FUN_80040204(0x15);
    iVar2 = (int)DAT_8009c4e4;
    piVar5 = &DAT_801a7ad8 + (uint)(byte)(&DAT_800919e5)[iVar2 + (uint)DAT_8009c504 * 0x14] * 7;
    DAT_8009c4e4 = DAT_8009c4e4 + 1;
    if (((&DAT_801a7aee)[(uint)(byte)(&DAT_800919e5)[iVar2 + (uint)DAT_8009c504 * 0x14] * 0xe] &
        0x8000) == 0) {
      return;
    }
    puVar3 = (undefined2 *)FUN_8002c7d8(0xb);
    *(int *)(puVar3 + 10) = *(int *)(puVar3 + 10) + DAT_8009c4e4 * 0x3000;
    *puVar3 = *(undefined2 *)(*piVar5 + 0x30);
    puVar3[1] = *(undefined2 *)(*piVar5 + 0x32);
    puVar3[2] = *(undefined2 *)(*piVar5 + 0x34);
    uVar1 = FUN_8001817c(*piVar5);
    puVar3[0xd] = uVar1;
    FUN_80024a10(piVar5);
    uVar4 = 0x1f;
  }
  FUN_80040204(uVar4);
  return;
}

