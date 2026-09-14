/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8004cc0c(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = DAT_8009c7d8;
  *(undefined4 *)(DAT_8009c7d8 + 0x804) = 0;
  *(undefined1 *)(iVar4 + 0x800) = 0;
  FUN_8004c178();
  iVar4 = 0;
  if (*(short *)(DAT_8009c7d8 + 0x7fa) != 0) {
    iVar5 = 0x518;
    do {
      puVar3 = (undefined4 *)(DAT_8009c7d8 + iVar5);
      puVar3[1] = *puVar3;
      uVar2 = FUN_8004bfc4(puVar3);
      *(undefined1 *)(puVar3 + 9) = 0;
      *(undefined1 *)((int)puVar3 + 0x27) = 0;
      *(undefined1 *)((int)puVar3 + 0x29) = 0;
      *(undefined1 *)(puVar3 + 10) = 0;
      iVar1 = DAT_8009c7d8;
      puVar3[7] = uVar2;
      *(undefined2 *)(puVar3 + 6) = 0;
      if (*(int *)(iVar1 + 0x804) != 0) {
        FUN_8004ca58(puVar3);
      }
      iVar4 = iVar4 + 1;
      iVar5 = iVar5 + 0x2c;
    } while (iVar4 < (int)(uint)*(ushort *)(DAT_8009c7d8 + 0x7fa));
  }
  return 0;
}

