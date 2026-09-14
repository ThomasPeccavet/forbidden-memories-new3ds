/* Analysis pseudo-C, not buildable source. */

int FUN_8004add0(char param_1,char param_2)

{
  int iVar1;
  int iVar2;
  char cVar3;
  ushort uVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = -1;
  iVar2 = 0;
  iVar5 = DAT_8009c7d8;
  if (0 < *(short *)(DAT_8009c7d8 + 0x510)) {
    do {
      if (*(char *)(iVar5 + 0x183) == 'c') {
        return iVar2;
      }
      iVar2 = iVar2 + 1;
      iVar5 = iVar5 + 0x28;
    } while (iVar2 < *(short *)(DAT_8009c7d8 + 0x510));
  }
  iVar1 = (int)*(short *)(DAT_8009c7d8 + 0x510);
  iVar2 = 0;
  iVar5 = DAT_8009c7d8;
  if (0 < iVar1) {
    do {
      cVar3 = param_1;
      if (*(char *)(iVar5 + 0x18d) == '\0') goto LAB_8004af74;
      iVar2 = iVar2 + 1;
      iVar5 = iVar5 + 0x28;
    } while (iVar2 < iVar1);
    iVar1 = (int)*(short *)(DAT_8009c7d8 + 0x510);
  }
  iVar2 = 0;
  if (0 < iVar1) {
    iVar5 = 0;
    do {
      cVar3 = *(char *)(DAT_8009c7d8 + iVar5 + 0x183);
      if ((cVar3 == param_1) && (*(char *)(DAT_8009c7d8 + iVar5 + 0x185) == param_2))
      goto LAB_8004af74;
      iVar2 = iVar2 + 1;
      iVar5 = iVar5 + 0x28;
    } while (iVar2 < *(short *)(DAT_8009c7d8 + 0x510));
  }
  iVar2 = 0;
  iVar5 = DAT_8009c7d8;
  if (0 < *(short *)(DAT_8009c7d8 + 0x510)) {
    do {
      cVar3 = param_1;
      if (*(char *)(iVar5 + 0x18d) == '\0') goto LAB_8004af74;
      iVar2 = iVar2 + 1;
      iVar5 = iVar5 + 0x28;
    } while (iVar2 < *(short *)(DAT_8009c7d8 + 0x510));
  }
  uVar4 = 0xffff;
  iVar1 = 0;
  iVar5 = DAT_8009c7d8;
  iVar2 = iVar6;
  if (0 < *(short *)(DAT_8009c7d8 + 0x510)) {
    do {
      iVar2 = iVar6;
      if (*(ushort *)(iVar5 + 0x19e) < uVar4) {
        iVar2 = iVar1;
        uVar4 = *(ushort *)(iVar5 + 0x19e);
      }
      iVar1 = iVar1 + 1;
      iVar5 = iVar5 + 0x28;
      iVar6 = iVar2;
    } while (iVar1 < *(short *)(DAT_8009c7d8 + 0x510));
  }
  iVar5 = -1;
  cVar3 = param_1;
  if (uVar4 != 0xffff) {
LAB_8004af74:
    iVar5 = FUN_8004ad74(iVar2,cVar3);
  }
  return iVar5;
}

