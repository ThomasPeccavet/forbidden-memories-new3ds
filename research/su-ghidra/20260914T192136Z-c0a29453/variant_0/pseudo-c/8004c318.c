/* Analysis pseudo-C, not buildable source. */

void FUN_8004c318(int param_1,byte param_2)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  
  if (param_2 != 0x51) {
    if (param_2 < 0x52) {
      if ((param_2 < 0x10) || (param_2 != 0x2f)) goto LAB_8004c514;
      *(undefined1 *)(param_1 + 0x24) = 1;
    }
    else {
      if (param_2 == 0x58) {
        FUN_8004bf74(param_1);
        FUN_8004c0bc(param_1);
        return;
      }
      if (param_2 < 0x59) {
        if (param_2 != 0x54) {
LAB_8004c514:
          uVar5 = FUN_8004bfc4(param_1);
          FUN_8004c2fc(param_1,uVar5);
          return;
        }
        FUN_8004bf74(param_1);
        FUN_8004bf74(param_1);
        FUN_8004bf74(param_1);
      }
      else if (param_2 != 0x59) goto LAB_8004c514;
      FUN_8004bf74(param_1);
      FUN_8004bf74(param_1);
    }
    FUN_8004bf74(param_1);
    return;
  }
  iVar2 = FUN_8004bf74(param_1);
  iVar3 = FUN_8004bf74(param_1);
  uVar4 = FUN_8004bf74(param_1);
  iVar7 = DAT_8009c7d8;
  uVar4 = iVar2 << 0x10 | iVar3 << 8 | uVar4;
  *(uint *)(DAT_8009c7d8 + 0x808) = uVar4;
  iVar2 = DAT_8009c7d8;
  if (uVar4 == 0) {
    trap(0x1c00);
  }
  uVar4 = ((60000000 / uVar4) * 100) / 0x73;
  if (0xff < uVar4) {
    uVar4 = 0xff;
  }
  uVar1 = *(ushort *)(iVar7 + 0x7fc);
  if (uVar1 == 0x1e) {
    uVar4 = uVar4 >> 2;
  }
  else {
    if (uVar1 < 0x1f) {
      if (uVar1 != 0x18) goto LAB_8004c474;
    }
    else if (uVar1 != 0x3c) goto LAB_8004c474;
    uVar4 = uVar4 >> 1;
  }
LAB_8004c474:
  uVar6 = 0;
  if (*(short *)(DAT_8009c7d8 + 0x7fa) != 0) {
    iVar7 = 0;
    do {
      iVar3 = iVar2 + iVar7;
      *(short *)(iVar3 + 0x52e) = (short)uVar4;
      *(short *)(iVar3 + 0x52c) = (short)uVar4;
      uVar6 = uVar6 + 1;
      iVar7 = iVar7 + 0x2c;
    } while (uVar6 < *(ushort *)(iVar2 + 0x7fa));
  }
  return;
}

