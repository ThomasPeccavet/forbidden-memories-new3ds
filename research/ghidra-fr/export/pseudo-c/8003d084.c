/* Analysis pseudo-C, not buildable source. */

uint FUN_8003d084(byte *param_1,int param_2)

{
  byte *pbVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  uVar2 = 0;
  iVar4 = 0;
  pbVar1 = param_1;
  if (0 < param_2) {
    do {
      iVar3 = 7;
      uVar2 = uVar2 ^ (uint)*pbVar1 << 8;
      do {
        if ((uVar2 & 0x8000) == 0) {
          uVar2 = uVar2 << 1;
        }
        else {
          uVar2 = uVar2 << 1 ^ 0x1021;
        }
        iVar3 = iVar3 + -1;
      } while (-1 < iVar3);
      iVar4 = iVar4 + 1;
      pbVar1 = param_1 + iVar4;
    } while (iVar4 < param_2);
  }
  return uVar2 & 0xffff;
}

