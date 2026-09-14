/* Analysis pseudo-C, not buildable source. */

void FUN_8003b708(int param_1,int param_2)

{
  char cVar1;
  ushort uVar2;
  byte bVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  bVar3 = *(byte *)(param_1 + 0x32);
  if ((bVar3 & 0x10) != 0) {
    *(byte *)(param_1 + 0x32) = bVar3 & 0xfc;
    return;
  }
  if (*(int *)(param_1 + 4) != 0) {
    if ((bVar3 & 1) == 0) {
      uVar2 = *(short *)(param_1 + 0x3e) - 1;
      *(ushort *)(param_1 + 0x3e) = uVar2;
      uVar5 = 1;
      if (0 < (int)((uint)uVar2 << 0x10)) goto LAB_8003b7c4;
      uVar4 = *(undefined4 *)(param_1 + 4);
      *(byte *)(param_1 + 0x32) = *(byte *)(param_1 + 0x32) | 1;
    }
    else {
      if (*(short *)(*(int *)(param_1 + 4) + 0x5a) != 0) goto LAB_8003b7c4;
      uVar2 = FUN_8008f708();
      uVar5 = 0;
      uVar4 = *(undefined4 *)(param_1 + 4);
      *(ushort *)(param_1 + 0x3e) = (uVar2 & 0xff) + 0x3c;
      *(byte *)(param_1 + 0x32) = *(byte *)(param_1 + 0x32) & 0xfe;
    }
    FUN_80040734(uVar4,uVar5);
  }
LAB_8003b7c4:
  if (*(int *)(param_1 + 8) == 0) {
    return;
  }
  if ((*(byte *)(param_1 + 0x32) & 2) == 0) {
    if (param_2 < 0) {
      cVar1 = *(char *)(param_1 + 0x3b) + '\x01';
      *(char *)(param_1 + 0x3b) = cVar1;
      if (cVar1 < '\x06') {
        return;
      }
      FUN_80040748(*(undefined4 *)(param_1 + 8),0);
      return;
    }
    *(byte *)(param_1 + 0x32) = *(byte *)(param_1 + 0x32) | 2;
  }
  else {
    bVar3 = *(char *)(param_1 + 0x3b) - 1;
    *(byte *)(param_1 + 0x3b) = bVar3;
    if (*(short *)(*(int *)(param_1 + 8) + 0x5a) != 0) {
      return;
    }
    if (0 < (int)((uint)bVar3 << 0x18)) {
      return;
    }
    if (param_2 < 1) {
      *(undefined1 *)(param_1 + 0x3b) = 0;
      *(byte *)(param_1 + 0x32) = *(byte *)(param_1 + 0x32) & 0xfd;
      return;
    }
  }
  *(undefined1 *)(param_1 + 0x3b) = 6;
  *(char *)(param_1 + 0x3a) = (char)param_2;
  FUN_80040734(*(undefined4 *)(param_1 + 8));
  return;
}

