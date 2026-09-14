/* Analysis pseudo-C, not buildable source. */

int FUN_8003d638(uint param_1,int param_2)

{
  int iVar1;
  
  DAT_8009c6d0 = 0xff;
  iVar1 = FUN_80036184(DAT_800f0cea,param_1 & 0x7fff,8,0x50,0x130,0x30);
  *(char *)(iVar1 + 0x59) = DAT_8009c2fa + -1;
  if (param_2 == 0) {
    if ((param_1 & 0x8000) != 0) {
      FUN_800399f0(iVar1);
    }
  }
  else {
    *(ushort *)(iVar1 + 0x34) = *(ushort *)(iVar1 + 0x34) | 0x1010;
  }
  return iVar1;
}

