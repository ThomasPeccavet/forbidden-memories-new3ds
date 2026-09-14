/* Analysis pseudo-C, not buildable source. */

void FUN_80183d58(void)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = DAT_80184820;
  iVar2 = DAT_80184818;
  if (DAT_80185ef4 == '\0') {
    *(char *)(DAT_80184818 + 0xc) = *(char *)(DAT_80184818 + 0xc) + *(char *)(DAT_80184818 + 0x60);
    *(char *)(iVar2 + 0xd) = *(char *)(iVar2 + 0xd) + *(char *)(iVar2 + 0x60);
    *(char *)(iVar2 + 0xe) = *(char *)(iVar2 + 0xe) + *(char *)(iVar2 + 0x60);
    if ((*(byte *)(iVar2 + 0xc) < 0x41) || (*(char *)(iVar2 + 0xc) < '\0')) {
      sVar1 = -*(short *)(iVar2 + 0x60);
      goto LAB_80183e6c;
    }
  }
  else {
    FUN_80184680(0);
    *(undefined1 *)(iVar2 + 0xe) = 0x40;
    *(undefined1 *)(iVar2 + 0xd) = 0x40;
    *(undefined1 *)(iVar2 + 0xc) = 0x40;
    sVar1 = 2;
LAB_80183e6c:
    *(short *)(iVar2 + 0x60) = sVar1;
  }
  if (DAT_80185ef5 == '\0') {
    *(char *)(iVar3 + 0xc) = *(char *)(iVar3 + 0xc) + *(char *)(iVar3 + 0x60);
    *(char *)(iVar3 + 0xd) = *(char *)(iVar3 + 0xd) + *(char *)(iVar3 + 0x60);
    *(char *)(iVar3 + 0xe) = *(char *)(iVar3 + 0xe) + *(char *)(iVar3 + 0x60);
    if ((0x40 < *(byte *)(iVar3 + 0xc)) && (-1 < *(char *)(iVar3 + 0xc))) goto LAB_80183f58;
    sVar1 = -*(short *)(iVar3 + 0x60);
  }
  else {
    FUN_80184680(1);
    *(undefined1 *)(iVar3 + 0xe) = 0x40;
    *(undefined1 *)(iVar3 + 0xd) = 0x40;
    *(undefined1 *)(iVar3 + 0xc) = 0x40;
    sVar1 = 2;
  }
  *(short *)(iVar3 + 0x60) = sVar1;
LAB_80183f58:
  iVar2 = 0;
  if (DAT_80185ec8 != 0) {
    do {
      iVar4 = iVar2 + 1;
      iVar3 = (iVar2 % 5) * 0x1c + 0x10;
      iVar2 = (iVar2 / 5) * 0x11 + 0xd2;
      FUN_801840b8(iVar3,iVar2,(&DAT_80185ec8)[iVar4]);
      FUN_80184570(iVar3,iVar2,(&DAT_80185ec8)[iVar4]);
      iVar2 = iVar4;
    } while (iVar4 < (int)(uint)DAT_80185ec8);
  }
  iVar2 = 0;
  if (DAT_80185ede != 0) {
    do {
      iVar4 = iVar2 + 1;
      iVar3 = (iVar2 % 5) * 0x1c + 0xb0;
      iVar2 = (iVar2 / 5) * 0x11 + 0xd2;
      FUN_801840b8(iVar3,iVar2,(&DAT_80185ede)[iVar4]);
      FUN_80184570(iVar3,iVar2,(&DAT_80185ede)[iVar4]);
      iVar2 = iVar4;
    } while (iVar4 < (int)(uint)DAT_80185ede);
  }
  return;
}

