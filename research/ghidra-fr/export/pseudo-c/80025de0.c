/* Analysis pseudo-C, not buildable source. */

void FUN_80025de0(void)

{
  short sVar1;
  undefined2 uVar2;
  int iVar3;
  uint uVar4;
  undefined2 *puVar5;
  int iVar6;
  int iVar7;
  
  iVar3 = FUN_80024ee0();
  if (iVar3 == 0) {
    DAT_8009c4e4 = 0;
    DAT_8009c5c2 = 0;
  }
  if ((DAT_8009c550 & 0x40) == 0) {
    DAT_8009c4e4 = DAT_8009c4e4 - 1;
    if ((int)((uint)DAT_8009c4e4 << 0x10) < 1) {
      DAT_8009c4e4 = 0x10;
      uVar4 = (uint)(byte)(&DAT_800919e5)[(int)DAT_8009c5c2 + (uint)DAT_8009c504 * 0x14];
      iVar3 = uVar4 * 0x1c;
      if (((&DAT_801a7aee)[uVar4 * 0xe] & 0x8000) != 0) {
        iVar7 = (&DAT_801a7ad8)[uVar4 * 7];
        puVar5 = (undefined2 *)FUN_8002c7d8(0xd);
        *puVar5 = *(undefined2 *)(iVar7 + 0x30);
        iVar6 = (int)DAT_8009c5c2;
        puVar5[1] = *(undefined2 *)(iVar7 + 0x32);
        sVar1 = DAT_8009c5c4;
        uVar2 = *(undefined2 *)(iVar7 + 0x34);
        *(int *)(puVar5 + 10) = *(int *)(puVar5 + 10) + iVar6 * 0x4000;
        puVar5[2] = uVar2;
        if (sVar1 == 0x15d) {
          puVar5[0xd] = 2;
          *(short *)(&DAT_801a7aea + iVar3) = *(short *)(&DAT_801a7aea + iVar3) + -500;
          uVar2 = 0xfe0c;
        }
        else {
          puVar5[0xd] = 1;
          *(short *)(&DAT_801a7aea + iVar3) = *(short *)(&DAT_801a7aea + iVar3) + -1000;
          uVar2 = 0xfc18;
        }
        puVar5[9] = uVar2;
        FUN_80040204(0x21);
      }
      DAT_8009c5c2 = DAT_8009c5c2 + 1;
      if (4 < DAT_8009c5c2) {
        DAT_8009c550 = DAT_8009c550 | 0x40;
      }
    }
  }
  else if ((DAT_8009c5f8 & 1) == 0) {
    DAT_8009c550 = 0;
  }
  return;
}

