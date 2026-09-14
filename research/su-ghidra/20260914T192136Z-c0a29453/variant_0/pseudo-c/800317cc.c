/* Analysis pseudo-C, not buildable source. */

void FUN_800317cc(int param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4,
                 undefined2 param_5)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  
  uVar2 = FUN_80040350();
  iVar3 = FUN_800403d0(uVar2,1);
  FUN_80040844(iVar3,param_2,param_3,0x10,0x10,0,0xc0,0xb,0x2e0,0xfc);
  uVar4 = (int)(&DAT_801d4244)[param_1 + -1] >> 0x1a & 0x1f;
  if (uVar4 == 0x15) {
    sVar1 = *(short *)(iVar3 + 0x40) + 0x20;
  }
  else {
    if (uVar4 < 0x16) {
      if (uVar4 != 0x14) goto LAB_800318d4;
    }
    else {
      if (uVar4 == 0x16) {
        sVar1 = *(short *)(iVar3 + 0x40) + 0x30;
        goto LAB_800318d0;
      }
      if (uVar4 != 0x17) goto LAB_800318d4;
    }
    sVar1 = *(short *)(iVar3 + 0x40) + 0x10;
  }
LAB_800318d0:
  *(short *)(iVar3 + 0x40) = sVar1;
LAB_800318d4:
  FUN_80042c48(iVar3);
  FUN_80042c1c(iVar3,10);
  *(undefined4 *)(iVar3 + 0x44) = 0;
  *(undefined2 *)(iVar3 + 0x18) = param_4;
  *(undefined2 *)(iVar3 + 0x1a) = param_5;
  *(code **)(iVar3 + 0x24) = FUN_80031640;
  *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) & 0xf7ffffff;
  *(ushort *)(iVar3 + 8) = *(ushort *)(iVar3 + 8) & 0xfff7;
  return;
}

