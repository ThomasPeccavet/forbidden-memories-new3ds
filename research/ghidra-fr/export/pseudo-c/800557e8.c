/* Analysis pseudo-C, not buildable source. */

void FUN_800557e8(int param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = (int)DAT_800f4082;
  iVar4 = 700;
  iVar5 = 1000;
  if ((-1 < iVar3) && (iVar4 = FUN_8004f1c8(iVar3,700), 999 < iVar4)) {
    iVar5 = FUN_8004f1c8(iVar3,1000);
  }
  iVar3 = FUN_800544a4(1,0x96,0);
  if (iVar3 == 0) {
    if ((DAT_800f405e < DAT_800f405c) &&
       (uVar1 = DAT_800f405c - 2, DAT_800f405c = DAT_800f405c - 2, uVar1 < DAT_800f405e)) {
      DAT_800f405c = DAT_800f405e;
    }
  }
  else {
    if (DAT_800f405c < 0x200) {
      DAT_800f405c = DAT_800f405c + 2;
    }
    DAT_800f4059 = DAT_800f4059 & 0xfe;
  }
  FUN_8005567c();
  iVar3 = (int)DAT_8009c7f8;
  if (iVar3 < 300) {
    if (iVar3 < 0x96) {
      iVar2 = 0x96 - iVar3;
    }
    else {
      iVar2 = 300 - iVar3;
      if (10 < iVar2) {
        iVar2 = 10;
      }
    }
LAB_80055958:
    FUN_8005b5cc(1,0,0,iVar2,0);
  }
  else {
    iVar2 = iVar4 - iVar3;
    if (iVar3 < iVar4) {
      if (5 < iVar2) {
        iVar2 = 5;
      }
      goto LAB_80055958;
    }
  }
  if (param_1 == 0) {
LAB_800559a8:
    if (DAT_8009c7f8 <= iVar5) goto LAB_800559ec;
  }
  else {
    iVar3 = (int)DAT_8009c7f8;
    if (iVar3 <= iVar5) {
      iVar2 = iVar4 - iVar3;
      if (iVar4 < iVar3) {
        if (iVar2 < -10) {
          iVar2 = -10;
        }
        FUN_8005b5cc(1,0,0,iVar2,0);
      }
      goto LAB_800559a8;
    }
  }
  iVar5 = iVar5 - DAT_8009c7f8;
  if (iVar5 < -0x14) {
    iVar5 = -0x14;
  }
  FUN_8005b5cc(1,0,0,iVar5,0);
LAB_800559ec:
  FUN_8005567c();
  return;
}

