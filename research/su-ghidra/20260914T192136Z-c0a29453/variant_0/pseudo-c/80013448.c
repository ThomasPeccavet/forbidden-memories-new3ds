/* Analysis pseudo-C, not buildable source. */

void FUN_80013448(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = (int)DAT_800f11e0;
  iVar2 = FUN_800866f8((int)DAT_800f11e4);
  iVar2 = -iVar1 * iVar2;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0xfff;
  }
  iVar3 = FUN_80086628((int)DAT_800f11e4);
  iVar3 = -iVar1 * iVar3;
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0xfff;
  }
  iVar1 = FUN_80086628((int)DAT_800f11e2);
  iVar1 = (iVar2 >> 0xc) * iVar1;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0xfff;
  }
  iVar4 = FUN_800866f8((int)DAT_800f11e2);
  iVar4 = (iVar2 >> 0xc) * iVar4;
  if (iVar4 < 0) {
    iVar4 = iVar4 + 0xfff;
  }
  FUN_800133fc(&DAT_800f11e0,iVar4 >> 0xc,iVar3 >> 0xc,iVar1 >> 0xc);
  return;
}

