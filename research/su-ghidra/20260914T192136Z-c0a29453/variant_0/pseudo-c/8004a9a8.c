/* Analysis pseudo-C, not buildable source. */

void FUN_8004a9a8(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined1 *puVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint *puVar7;
  uint uVar8;
  
  uVar8 = 0;
  iVar6 = 0;
  iVar4 = 0x518;
  *(undefined2 *)(DAT_8009c7d8 + 0x512) = 0x7f;
  do {
    iVar6 = iVar6 + 1;
    puVar1 = (undefined4 *)(DAT_8009c7d8 + iVar4);
    *puVar1 = 0;
    puVar1[1] = 0;
    *(undefined1 *)((int)puVar1 + 0x26) = 0;
    puVar1[7] = 0;
    puVar1[2] = 0;
    puVar1[3] = 0;
    *(undefined2 *)(puVar1 + 5) = 0x72;
    *(undefined2 *)((int)puVar1 + 0x16) = 0x72;
    *(undefined1 *)(puVar1 + 9) = 1;
    puVar1[4] = 0;
    *(undefined2 *)(puVar1 + 6) = 0;
    *(undefined1 *)((int)puVar1 + 0x27) = 0;
    *(undefined1 *)(puVar1 + 10) = 0xff;
    *(undefined1 *)((int)puVar1 + 0x29) = 0;
    *(undefined1 *)((int)puVar1 + 0x2b) = 0;
    iVar4 = iVar4 + 0x2c;
  } while (iVar6 < 0x10);
  iVar4 = 0;
  if (0 < *(short *)(DAT_8009c7d8 + 0x510)) {
    puVar7 = &DAT_80011360;
    iVar6 = 0x180;
    do {
      puVar3 = (undefined1 *)(DAT_8009c7d8 + iVar6);
      uVar5 = *puVar7;
      puVar3[3] = 99;
      *puVar3 = (char)iVar4;
      puVar3[0xd] = 0;
      puVar3[0xf] = 0;
      puVar3[0xc] = 0x40;
      *(undefined2 *)(puVar3 + 0x1a) = 0x40;
      *(undefined2 *)(puVar3 + 0x1c) = 0x40;
      *(undefined2 *)(puVar3 + 0x1e) = 0;
      FUN_8004abf4(iVar4);
      puVar7 = puVar7 + 1;
      iVar6 = iVar6 + 0x28;
      FUN_80077468(0,uVar5);
      iVar4 = iVar4 + 1;
      uVar8 = uVar8 | uVar5;
    } while (iVar4 < *(short *)(DAT_8009c7d8 + 0x510));
  }
  iVar6 = 0;
  iVar4 = 0;
  do {
    iVar6 = iVar6 + 1;
    iVar2 = DAT_8009c7d8 + iVar4;
    *(undefined1 *)(iVar2 + 1) = 0x40;
    *(undefined1 *)(iVar2 + 3) = 0x7f;
    *(undefined1 *)(iVar2 + 4) = 0;
    *(undefined1 *)(iVar2 + 5) = 0x7f;
    *(undefined1 *)(iVar2 + 7) = 0x40;
    *(undefined4 *)(iVar2 + 8) = 0x7f;
    *(undefined4 *)(iVar2 + 0xc) = 0x7f;
    *(undefined1 *)(iVar2 + 0x10) = 0;
    *(undefined2 *)(iVar2 + 0x14) = 0;
    *(undefined1 *)(iVar2 + 6) = 0;
    iVar4 = iVar4 + 0x18;
  } while (iVar6 < 0x10);
  FUN_80077468(0,uVar8);
  return;
}

