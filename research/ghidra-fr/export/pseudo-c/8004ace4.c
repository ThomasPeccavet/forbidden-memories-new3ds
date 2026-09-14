/* Analysis pseudo-C, not buildable source. */

int FUN_8004ace4(char param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  ushort uVar4;
  int iVar5;
  
  iVar5 = -1;
  uVar4 = 0xffff;
  iVar2 = 0;
  if (0 < *(short *)(DAT_8009c7d8 + 0x510)) {
    iVar3 = 0;
    do {
      iVar1 = DAT_8009c7d8 + iVar3;
      if (((*(ushort *)(iVar1 + 0x19e) <= uVar4) && (*(char *)(iVar1 + 0x183) == param_1)) &&
         (*(char *)(iVar1 + 0x18d) != '\0')) {
        iVar5 = iVar2;
        uVar4 = *(ushort *)(iVar1 + 0x19e);
      }
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 0x28;
    } while (iVar2 < *(short *)(DAT_8009c7d8 + 0x510));
  }
  return iVar5;
}

