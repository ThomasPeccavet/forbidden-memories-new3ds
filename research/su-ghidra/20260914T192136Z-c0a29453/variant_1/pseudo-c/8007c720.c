/* Analysis pseudo-C, not buildable source. */

void FUN_8007c720(void)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_10 [8];
  
  iVar2 = DAT_80094cf4 + -1;
  if ((0 < DAT_80094cf4) && (DAT_80094cf4 = iVar2, iVar2 == 0)) {
    FUN_8007c9f0();
    return;
  }
  if (0 < DAT_80094cf0) {
    DAT_80094cf0 = DAT_80094cf0 + -1;
  }
  if (0 < DAT_80094cfc) {
    DAT_80094cfc = DAT_80094cfc + -1;
  }
  if (((DAT_80094cd0 == 1) || (DAT_80094cd0 != 2)) || (DAT_80094cd4 == 0xb)) goto LAB_8007c94c;
  if (DAT_80094cd4 == 0xc) {
    if (DAT_80094e04 == 0) {
      if (DAT_80094cf4 < 1) {
        DAT_80094ccc = 0x20;
        FUN_8007c548(1,0);
      }
      DAT_80094e04 = 1;
    }
    else {
      local_10[0] = 0;
      if (DAT_80094cf4 < 1) {
        DAT_80094ccc = 0x20;
        FUN_8007c548(0xe,local_10);
      }
      DAT_80094e04 = 0;
    }
    goto LAB_8007c94c;
  }
  if (DAT_80094cd4 == 0xd) {
    DAT_80094e04 = 0;
    goto joined_r0x8007c87c;
  }
  if (DAT_80094cd4 != 0xe) {
    if (DAT_80094cd4 == 0xf) {
      if (DAT_80094cf0 != 0) goto LAB_8007c94c;
    }
    else {
      cVar1 = DAT_80094ce4;
      if ((DAT_80094cd4 != 0x10) && (cVar1 = DAT_80094ce6, DAT_80094cd4 != 0x11)) goto LAB_8007c94c;
      if (cVar1 == '\0') goto joined_r0x8007c87c;
    }
    DAT_80094cd0 = 1;
    DAT_80094cd4 = 0xb;
    goto LAB_8007c94c;
  }
  if (DAT_80094cd8 == 0x15) {
joined_r0x8007c87c:
    if (0 < DAT_80094cf4) goto LAB_8007c94c;
    uVar3 = 1;
  }
  else {
    if (DAT_80094cd8 == 0x16) {
      DAT_80094ce8 = DAT_80094ce8 + 1;
      goto joined_r0x8007c87c;
    }
    if (DAT_80094cd8 != 0x17) {
      if (DAT_80094cd8 != 0x18) goto LAB_8007c94c;
      goto joined_r0x8007c87c;
    }
    if (0 < DAT_80094cf4) goto LAB_8007c94c;
    uVar3 = 0x13;
  }
  DAT_80094ccc = 0x20;
  FUN_8007c548(uVar3,0);
LAB_8007c94c:
  if ((DAT_800f7308 != (code *)0x0) && (DAT_80094cb0 != 0)) {
    (*DAT_800f7308)();
  }
  if ((((DAT_80094cd0 == 1) && (DAT_80094ce7 == '\0')) || (DAT_80094cd0 == 3)) && (DAT_80094cf4 < 1)
     ) {
    DAT_80094ccc = 0x21;
    FUN_8007c548(1,0);
  }
  return;
}

