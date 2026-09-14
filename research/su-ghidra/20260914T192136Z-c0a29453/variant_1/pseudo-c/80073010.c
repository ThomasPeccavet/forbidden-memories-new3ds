/* Analysis pseudo-C, not buildable source. */

void FUN_80073010(void)

{
  short sVar1;
  int iVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  byte bVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  
  iVar2 = FUN_80070bb8();
  uVar7 = *(undefined4 *)(&DAT_800f6f20 + iVar2 * 4);
  iVar2 = FUN_80070bb8();
  uVar10 = *(undefined4 *)(&DAT_800f6f20 + iVar2 * 4);
  bVar6 = (char)uVar7 + 1;
  iVar2 = FUN_80070bb8();
  DAT_800f700c = FUN_80070d3c();
  DAT_800f7010 = 0;
  DAT_800f7012 = 0;
  DAT_800f700e = (undefined1)uVar10;
  DAT_800f700d = bVar6;
  if (DAT_800f700c != 0) {
    puVar3 = &DAT_800f6f70;
    iVar9 = 0;
    do {
      puVar3[0xaa] = 0;
      iVar8 = iVar9 + 1;
      puVar3 = &DAT_800f6f71 + iVar9;
      iVar9 = iVar8;
    } while (iVar8 < (int)(uint)DAT_800f700c);
  }
  iVar9 = 0;
  iVar8 = 0xc;
  do {
    sVar1 = *(short *)(&DAT_801ab000 + iVar8);
    if ((sVar1 != 0) && (iVar4 = FUN_80070f4c(uVar10,iVar9 + 1), iVar4 == 0)) {
      bVar6 = (byte)(iVar9 + 1);
      (&DAT_800f7014)[DAT_800f7012] = bVar6;
      if ((int)(uint)DAT_800f7010 < (int)*(short *)((int)&DAT_801ab002 + iVar8)) {
        DAT_800f6fa9 = '\0';
        DAT_800f7013 = DAT_800f7012;
        DAT_800f6fa8 = bVar6;
        DAT_800f7010 = *(ushort *)((int)&DAT_801ab002 + iVar8);
      }
      if ((int)(uint)DAT_800f7010 < (int)*(short *)(&DAT_801ab004 + iVar8)) {
        DAT_800f6fa9 = '\0';
        DAT_800f7013 = DAT_800f7012;
        DAT_800f6fa8 = bVar6;
        DAT_800f7010 = *(ushort *)(&DAT_801ab004 + iVar8);
      }
      if (1 < DAT_800f700d) {
        (&DAT_800f701a)[iVar9] = 1;
        DAT_800f7012 = DAT_800f7012 + 1;
        FUN_80072d88((int)sVar1);
        (&DAT_800f701a)[iVar9] = 0;
        DAT_800f7012 = DAT_800f7012 - 1;
      }
    }
    iVar9 = iVar9 + 1;
    iVar8 = iVar8 + 0xc;
  } while (iVar9 < 5);
  iVar9 = 0;
  if (DAT_800f700c != 0) {
    iVar8 = 0x84;
    do {
      sVar1 = *(short *)(&DAT_801ab000 + iVar8);
      if ((sVar1 != 0) && (iVar4 = FUN_80070f4c(uVar10,iVar9 + 0xb), iVar4 == 0)) {
        bVar6 = (byte)(iVar9 + 0xb);
        (&DAT_800f7014)[DAT_800f7012] = bVar6;
        if ((int)(uint)DAT_800f7010 < (int)*(short *)((int)&DAT_801ab002 + iVar8)) {
          DAT_800f6fa9 = '\0';
          DAT_800f7013 = DAT_800f7012;
          DAT_800f6fa8 = bVar6;
          DAT_800f7010 = *(ushort *)((int)&DAT_801ab002 + iVar8);
        }
        if ((int)(uint)DAT_800f7010 < (int)*(short *)(&DAT_801ab004 + iVar8)) {
          DAT_800f6fa9 = '\0';
          DAT_800f7013 = DAT_800f7012;
          DAT_800f6fa8 = bVar6;
          DAT_800f7010 = *(ushort *)(&DAT_801ab004 + iVar8);
        }
        if (2 < DAT_800f700d) {
          (&DAT_800f701a)[iVar9] = 1;
          DAT_800f7012 = DAT_800f7012 + 1;
          FUN_80072d88((int)sVar1);
          (&DAT_800f701a)[iVar9] = 0;
          DAT_800f7012 = DAT_800f7012 - 1;
        }
      }
      iVar9 = iVar9 + 1;
      iVar8 = iVar8 + 0xc;
    } while (iVar9 < (int)(uint)DAT_800f700c);
  }
  if (DAT_800f6fa8 == 0) {
    puVar5 = (undefined4 *)(&DAT_800f6f20 + iVar2 * 4);
    uVar7 = 3;
  }
  else {
    if (5 < DAT_800f6fa8) {
      *(undefined4 *)(&DAT_800f6f20 + iVar2 * 4) = 0;
      return;
    }
    if (DAT_800f6fa9 == '\0') {
      puVar5 = (undefined4 *)(&DAT_800f6f20 + iVar2 * 4);
      uVar7 = 2;
    }
    else {
      puVar5 = (undefined4 *)(&DAT_800f6f20 + iVar2 * 4);
      uVar7 = 1;
    }
  }
  *puVar5 = uVar7;
  return;
}

