/* Analysis pseudo-C, not buildable source. */

void FUN_8002e848(void)

{
  ushort uVar1;
  int iVar2;
  ushort *puVar3;
  int unaff_gp;
  
  iVar2 = FUN_8002e650();
  if (iVar2 == 0) {
    puVar3 = *(ushort **)(unaff_gp + 0x38c);
    *(ushort **)(unaff_gp + 0x38c) = puVar3 + 1;
    uVar1 = *puVar3;
    *(ushort *)(unaff_gp + 0x390) = *(ushort *)(unaff_gp + 0x390) | 0x4000;
    iVar2 = FUN_80036184(0,uVar1 & 0xfff,0x10,0xb0,0x120,0x40);
    FUN_8002e60c(iVar2);
    *(ushort *)(iVar2 + 0x34) = *(ushort *)(iVar2 + 0x34) | 0x10;
    if ((uVar1 & 0x8000) != 0) {
      uVar1 = *(ushort *)(iVar2 + 0x34);
      *(ushort *)(unaff_gp + 0x378) = *(ushort *)(unaff_gp + 0x378) | 0x4000;
      *(ushort *)(iVar2 + 0x34) = uVar1 & 0xffef;
    }
    *(undefined2 *)(unaff_gp + 0x38a) = *(undefined2 *)(unaff_gp + 0x378);
  }
  else if ((*(ushort *)(unaff_gp + 0x390) & 0x4000) == 0) {
    if ((*(ushort *)(unaff_gp + 0x378) & 0x4000) == 0) {
      FUN_800360d8(&DAT_800f0850);
    }
    *(undefined2 *)(unaff_gp + 0x38a) = 0;
    *(undefined2 *)(unaff_gp + 0x378) = 0;
  }
  return;
}

