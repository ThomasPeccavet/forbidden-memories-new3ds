/* Analysis pseudo-C, not buildable source. */

undefined1 FUN_8007bdd4(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  
  if (param_1 == 0) {
    iVar3 = (DAT_800f72f8 + -1) * 0x10;
    if (DAT_800f72f8 + -1 < 0) {
      iVar3 = 0x70;
    }
    iVar4 = *(int *)((int)&DAT_800f7278 + iVar3);
  }
  else {
    FUN_8007e888(0);
    iVar4 = 0;
    iVar3 = DAT_800f72f8;
    do {
      iVar5 = iVar3 * 4;
      iVar3 = iVar3 + 1;
      if ((&DAT_800f7278)[iVar5] == param_1) goto LAB_8007be6c;
      if (7 < iVar3) {
        iVar3 = 0;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 8);
    iVar3 = 0;
    if (param_1 < (int)(&DAT_800f7278)[DAT_800f72f8 * 4]) {
LAB_8007be6c:
      iVar3 = 7;
    }
    if (iVar3 != 7) {
      return 0;
    }
    iVar4 = DAT_800f72f8 + -1;
    if (iVar4 < 0) {
      iVar4 = 7;
    }
    iVar5 = 0;
    if (param_1 != 0) {
      do {
        iVar3 = iVar4 * 0x10;
        iVar1 = iVar4 * 4;
        iVar4 = iVar4 + -1;
        if ((&DAT_800f7278)[iVar1] == param_1) goto LAB_8007bf3c;
        if (iVar4 < 0) {
          iVar4 = 7;
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < 8);
      puVar6 = (undefined4 *)0x0;
      goto LAB_8007bf90;
    }
    iVar3 = iVar4 * 0x10;
    iVar4 = (&DAT_800f7278)[iVar4 * 4];
  }
  puVar6 = (undefined4 *)0x0;
  if (iVar4 != 0) {
LAB_8007bf3c:
    DAT_800f7168 = *(undefined4 *)((int)&DAT_800f7278 + iVar3);
    DAT_800f716c = *(undefined4 *)(&DAT_800f727c + iVar3);
    DAT_800f7170 = *(undefined4 *)(&DAT_800f7280 + iVar3);
    DAT_800f7174 = *(undefined4 *)(iVar3 + -0x7ff08d7c);
    puVar6 = &DAT_800f7168;
  }
LAB_8007bf90:
  if (puVar6 == (undefined4 *)0x0) {
    uVar2 = 6;
  }
  else {
    FUN_8007d304(param_2,(int)puVar6 + 5);
    uVar2 = *(undefined1 *)(puVar6 + 1);
  }
  return uVar2;
}

