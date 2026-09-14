/* Analysis pseudo-C, not buildable source. */

void FUN_8002f898(void)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined2 *puVar4;
  int unaff_gp;
  
  iVar1 = FUN_8002e650();
  if (iVar1 == 0) {
    uVar2 = (uint)DAT_8009c44b;
    puVar4 = *(undefined2 **)(unaff_gp + 0x38c);
    *(undefined2 **)(unaff_gp + 0x38c) = puVar4 + 1;
    *(undefined2 *)(unaff_gp + 0x37a) = *puVar4;
    FUN_80014d38(0,0,uVar2 * 0x32 + 0x2528,0x32,FUN_8002f724,0,0);
    FUN_80013700();
  }
  if ((*(ushort *)(unaff_gp + 0x378) & 0x4000) == 0) {
    if ((DAT_8009c460 & 0x2000030) == 0 && DAT_8009c484 == 0) {
      iVar1 = *(int *)(unaff_gp + 0x37c);
      *(ushort *)(unaff_gp + 0x378) = *(ushort *)(unaff_gp + 0x378) | 0x4000;
      if (iVar1 != 0) {
        *(ushort *)(iVar1 + 8) = *(ushort *)(iVar1 + 8) & 0xffbf;
      }
      FUN_8002e2a4(&DAT_800ec220);
      uVar3 = FUN_80040350();
      iVar1 = FUN_800403d0(uVar3,2);
      FUN_80042bd8(iVar1,0,0,0,0,DAT_8009c44b,0x17,4,&DAT_801af000);
      FUN_80042c1c(iVar1,1);
      *(ushort *)(iVar1 + 8) = *(ushort *)(iVar1 + 8) | 0x28;
      *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0x1000000;
      DAT_800ec220 = iVar1;
      uVar3 = FUN_80040350();
      uVar3 = FUN_800403d0(uVar3,1);
      FUN_80040844(uVar3,0,0,0x140,0x100,0,0,0x19,0x280,0xd5);
      FUN_80042c1c(uVar3,0xffffffff);
      DAT_800ec248 = 0;
      DAT_800ec234 = uVar3;
      uVar3 = FUN_80040350();
      iVar1 = FUN_800403d0(uVar3,4);
      FUN_80042b0c(iVar1,1);
      *(undefined4 *)(iVar1 + 0x30) = 0x140;
      *(undefined4 *)(iVar1 + 0x38) = 0x400000;
      uVar2 = *(uint *)(iVar1 + 4);
      *(undefined4 *)(iVar1 + 0x2c) = 0xffffff;
      *(undefined4 *)(iVar1 + 0x34) = 0xffffff;
      *(undefined4 *)(iVar1 + 0x4c) = 0xffffff;
      *(undefined4 *)(iVar1 + 0x54) = 0xffffff;
      *(undefined4 *)(iVar1 + 0x28) = 0;
      *(undefined4 *)(iVar1 + 0x40) = 0x400140;
      *(undefined4 *)(iVar1 + 0x48) = 0x1000000;
      *(undefined4 *)(iVar1 + 0x50) = 0x1000140;
      *(int *)(unaff_gp + 0x3a4) = iVar1;
      *(uint *)(iVar1 + 4) = uVar2 | 0x60000000;
      FUN_800156f8();
      DAT_800eb24f = 4;
      FUN_800158b4();
    }
  }
  else {
    uVar2 = FUN_800474cc();
    if ((uVar2 & 0x80) == 0) {
      FUN_80015a1c();
      iVar1 = *(int *)(unaff_gp + 0x37c);
      if (iVar1 != 0) {
        *(ushort *)(iVar1 + 8) = *(ushort *)(iVar1 + 8) | 0x40;
      }
      FUN_80040690(*(undefined4 *)(unaff_gp + 0x3a4));
      FUN_8002e2a4(&DAT_800ec220);
      *(undefined2 *)(unaff_gp + 0x378) = 0;
    }
  }
  return;
}

