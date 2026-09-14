/* Analysis pseudo-C, not buildable source. */

void FUN_80023200(int *param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  DAT_8009c6d1 = '\0';
  DAT_8009c6d8 = 0;
  iVar4 = 0x50;
  if (((&DAT_801a7aee)[param_2 * 0xe] & 0x8000) != 0) {
    DAT_8009c6b8 = *(short *)(&DAT_801a7ae4 + param_2 * 0x1c);
    iVar2 = (&DAT_801d4244)[DAT_8009c6b8 + -1];
    DAT_8009c6d1 = '\x01';
    if ((iVar2 >> 0x1a & 0x1fU) < 0x14) {
      bVar1 = (byte)(iVar2 >> 0x12);
      if (((&DAT_801a7aee)[param_2 * 0xe] & 0x200) == 0) {
        bVar1 = (byte)(iVar2 >> 0x16);
      }
      DAT_8009c6c0 = (bVar1 & 0xf) + 0x17;
      iVar2 = FUN_80016fe4(&DAT_801a7ad8 + param_2 * 7);
      DAT_801bf88c = (int)(short)iVar2;
      DAT_801bf890 = iVar2 >> 0x10;
    }
    else {
      iVar4 = 0x51;
    }
    if (param_2 % 0xf < 5) {
      if (((&DAT_801a7aee)[param_2 * 0xe] & 0x2000) != 0) {
        DAT_8009c6d1 = '\0';
      }
    }
    else {
      DAT_8009c6d1 = '\x02';
      if (((&DAT_801a7aee)[param_2 * 0xe] & 0x1000) != 0) {
        DAT_8009c6d1 = '\x03';
      }
      if ((0xe < param_2 == (bool)DAT_8009c504) && (*(char *)(DAT_8009c500 + 0x1f) == '\0')) {
        DAT_8009c6d1 = '\x02';
      }
    }
  }
  if (*(char *)((int)param_1 + 0x17) == '\x03') {
    iVar4 = iVar4 + 4;
    DAT_801bf894 = (uint)(char)(&DAT_800eb291)[(DAT_8009c504 ^ 1) * 0x20];
    if (DAT_801bf894 != 0) {
      if (3 < DAT_801bf894) {
        DAT_801bf894 = 3;
      }
      DAT_8009c6d8 = 1;
    }
    if (DAT_8009c6d1 != '\0') {
      DAT_8009c6d8 = DAT_8009c6d8 | 2;
      DAT_8009c6e1 = FUN_8002314c(param_1,(uint)DAT_8009c504 * 0x70 + -0x7ff14c38);
    }
  }
  if ((*(char *)((int)param_1 + 0x17) == '\x02') && ((char)param_1[6] != '\0')) {
    uVar3 = (uint)DAT_8009c504;
    if ((char)param_1[4] < '\x02') {
      uVar3 = uVar3 ^ 1;
    }
    DAT_801bf894 = (uint)(char)(&DAT_800eb291)[uVar3 * 0x20];
    if (DAT_801bf894 != 0) {
      if (3 < DAT_801bf894) {
        DAT_801bf894 = 3;
      }
      DAT_8009c6d8 = 1;
    }
    iVar4 = iVar4 + 2;
  }
  iVar4 = FUN_80036184((char)param_1[5],iVar4,*(short *)(*param_1 + 0x30) + 0x10,
                       (int)*(short *)(*param_1 + 0x32) + (int)*(char *)((int)param_1 + 0x16),0x120,
                       0x40);
  *(char *)(iVar4 + 0x59) = *(char *)(*param_1 + 0x16) + '\x01';
  FUN_800399f0();
  return;
}

