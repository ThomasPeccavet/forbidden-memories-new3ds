/* Analysis pseudo-C, not buildable source. */

void FUN_80073388(void)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  char cVar6;
  undefined4 uVar7;
  
  iVar1 = FUN_80070bb8();
  uVar7 = *(undefined4 *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  cVar6 = (char)*(undefined4 *)(&DAT_800f6f20 + iVar1 * 4) + '\x01';
  iVar1 = FUN_80070bb8();
  uVar5 = *(undefined4 *)(&DAT_800f6f20 + iVar1 * 4);
  iVar1 = FUN_80070bb8();
  DAT_800f700c = FUN_80070d3c();
  DAT_800f7010 = 0;
  DAT_800f7012 = 0;
  DAT_800f7013 = '\0';
  DAT_800f700e = (undefined1)uVar5;
  DAT_800f700d = cVar6;
  if (DAT_800f700c != 0) {
    puVar2 = &DAT_800f6f70;
    iVar3 = 0;
    do {
      puVar2[0xaa] = 0;
      iVar4 = iVar3 + 1;
      puVar2 = &DAT_800f6f71 + iVar3;
      iVar3 = iVar4;
    } while (iVar4 < (int)(uint)DAT_800f700c);
  }
  iVar3 = FUN_8002cdc8(uVar7,0);
  iVar4 = FUN_8002cdc8(uVar7,1);
  DAT_800f7010 = FUN_8002cdc8(uVar7,iVar3 <= iVar4);
  FUN_80072d88(uVar7);
  if (DAT_800f7013 == '\0') {
    *(undefined4 *)(&DAT_800f6f20 + iVar1 * 4) = 1;
  }
  else {
    *(undefined4 *)(&DAT_800f6f20 + iVar1 * 4) = 0;
  }
  return;
}

