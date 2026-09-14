/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80181408(void)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined1 uVar5;
  char cVar6;
  char cVar7;
  
  cVar6 = *(int *)(DAT_801847dc + 0x24) != 0;
  uVar4 = (uint)DAT_801847ec;
  uVar2 = (uint)DAT_801847ee;
  cVar7 = *(int *)(DAT_801847e0 + 0x24) != 0;
  if (uVar4 != uVar2) {
    iVar3 = uVar4 - uVar2;
    if (iVar3 < 0) {
      iVar3 = uVar2 - uVar4;
    }
    if (uVar2 < 2) {
      iVar3 = 99;
    }
    else if (100 < iVar3) {
      iVar3 = 100;
    }
    sVar1 = (short)iVar3;
    if (DAT_801847ec <= DAT_801847ee) {
      sVar1 = -sVar1;
    }
    DAT_801847ee = DAT_801847ee + sVar1;
    cVar6 = cVar6 + '\x01';
  }
  uVar4 = (uint)DAT_801847f8;
  uVar2 = (uint)DAT_801847fa;
  if (uVar4 != uVar2) {
    iVar3 = uVar4 - uVar2;
    if (iVar3 < 0) {
      iVar3 = uVar2 - uVar4;
    }
    if (uVar2 < 2) {
      iVar3 = 99;
    }
    else if (100 < iVar3) {
      iVar3 = 100;
    }
    sVar1 = (short)iVar3;
    if (DAT_801847f8 <= DAT_801847fa) {
      sVar1 = -sVar1;
    }
    DAT_801847fa = DAT_801847fa + sVar1;
    cVar7 = cVar7 + '\x01';
  }
  if (cVar6 != '\0') goto LAB_80181708;
  if (cVar7 == '\0') {
    if (((DAT_8009c72c & 0x20) != 0) || ((DAT_8009c72e & 0x20) != 0)) {
      FUN_80048ae8(8,0xff,0);
      return 0xffffffff;
    }
    if (((DAT_8009c72c & 0x800) != 0) || ((DAT_8009c72e & 0x800) != 0)) {
      FUN_80048ae8(7,0xff,0);
      return 1;
    }
  }
  if (DAT_801847e8 < 2) {
    if ((DAT_8009c728 & 0xa000) != 0) {
      FUN_80048ae8(6,0xff,0);
      DAT_801847e8 = (DAT_8009c728 & 0x8000) == 0;
      DAT_801847ea = DAT_801847e8;
      if (DAT_801847e9 < 2) {
        DAT_801847e9 = DAT_801847e8;
      }
      goto LAB_80181708;
    }
    if ((DAT_8009c728 & 0x4000) == 0) goto LAB_80181708;
    uVar5 = 2;
  }
  else {
    if ((DAT_8009c728 & 0xa000) != 0) {
      uVar2 = (uint)DAT_801847ec;
      FUN_80048ae8(6,0xff,0);
      if ((DAT_8009c728 & 0x8000) == 0) {
        uVar4 = 500;
        if ((1 < uVar2) && (uVar4 = uVar2 + 500, 8000 < uVar4)) {
          uVar4 = 8000;
        }
      }
      else {
        uVar4 = uVar2 - 500;
        if ((int)uVar4 < 1) {
          uVar4 = 1;
        }
      }
      DAT_801847ec = (ushort)uVar4;
      goto LAB_80181708;
    }
    uVar5 = DAT_801847ea;
    if ((DAT_8009c728 & 0x1000) == 0) goto LAB_80181708;
  }
  FUN_80182078(0,uVar5);
LAB_80181708:
  if (cVar7 != '\0') {
    return 0;
  }
  if (DAT_801847e9 < 2) {
    if ((DAT_8009c72a & 0xa000) != 0) {
      FUN_80048ae8(6,0xff,0);
      DAT_801847e9 = (DAT_8009c72a & 0x8000) == 0;
      if (1 < DAT_801847e8) {
        DAT_801847ea = DAT_801847e9;
        return 0;
      }
      DAT_801847e8 = DAT_801847e9;
      DAT_801847ea = DAT_801847e9;
      return 0;
    }
    if ((DAT_8009c72a & 0x4000) == 0) {
      return 0;
    }
    uVar5 = 2;
  }
  else {
    if ((DAT_8009c72a & 0xa000) != 0) {
      uVar2 = (uint)DAT_801847f8;
      FUN_80048ae8(6,0xff,0);
      if ((DAT_8009c72a & 0x8000) == 0) {
        uVar4 = 500;
        if ((1 < uVar2) && (uVar4 = uVar2 + 500, 8000 < uVar4)) {
          uVar4 = 8000;
        }
      }
      else {
        uVar4 = uVar2 - 500;
        if ((int)uVar4 < 1) {
          uVar4 = 1;
        }
      }
      DAT_801847f8 = (short)uVar4;
      return 0;
    }
    uVar5 = DAT_801847ea;
    if ((DAT_8009c72a & 0x1000) == 0) {
      return 0;
    }
  }
  FUN_80182078(1,uVar5);
  return 0;
}

