/* Analysis pseudo-C, not buildable source. */

void FUN_80026180(void)

{
  byte bVar1;
  undefined2 uVar2;
  int iVar3;
  undefined2 *puVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  
  iVar3 = FUN_80024ee0();
  if (iVar3 == 0) {
    DAT_8009c4e4 = -1;
    DAT_8009c5c2 = 0;
  }
  DAT_8009c5c2 = DAT_8009c5c2 - 1;
  if ((int)((uint)DAT_8009c5c2 << 0x10) < 1) {
    DAT_8009c5c2 = 0x10;
    DAT_8009c4e4 = DAT_8009c4e4 + 1;
    if (DAT_8009c4e4 < 5) {
      bVar1 = (&DAT_800919ea)[(int)DAT_8009c4e4 + (uint)DAT_8009c504 * 0x14];
      iVar3 = (uint)bVar1 * 0x1c;
      puVar4 = (undefined2 *)FUN_8002c7d8(8);
      iVar7 = (int)DAT_8009c4e4;
      uVar5 = (uint)DAT_8009c504;
      puVar4[0xd] = 3;
      iVar6 = (iVar7 + 10) * 4 + uVar5 * 0x50;
      uVar2 = *(undefined2 *)(&DAT_80091a08 + iVar6);
      puVar4[1] = 0;
      *puVar4 = uVar2;
      uVar2 = *(undefined2 *)(&DAT_80091a0a + iVar6);
      *(int *)(puVar4 + 10) = *(int *)(puVar4 + 10) + iVar7 * 0x3000;
      puVar4[2] = uVar2;
      FUN_80040204(0x14);
      if ((((&DAT_801a7aee)[(uint)bVar1 * 0xe] & 0x8000) != 0) &&
         (*(short *)(&DAT_801a7aea + iVar3) < 0)) {
        *(undefined2 *)(&DAT_801a7aea + iVar3) = 0;
        puVar4[0xd] = 5;
      }
    }
    else {
      DAT_8009c550 = 0;
    }
  }
  return;
}

