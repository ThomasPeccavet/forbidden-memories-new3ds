/* Analysis pseudo-C, not buildable source. */

void FUN_80040fe0(void)

{
  short sVar1;
  int iVar2;
  
  sVar1 = DAT_800f11c0;
  while (-1 < sVar1) {
    iVar2 = sVar1 * 0x70;
    sVar1 = *(short *)(&DAT_800f1212 + iVar2);
    if (*(code **)(&DAT_800f1234 + iVar2) != (code *)0x0) {
      (**(code **)(&DAT_800f1234 + iVar2))();
    }
  }
  return;
}

