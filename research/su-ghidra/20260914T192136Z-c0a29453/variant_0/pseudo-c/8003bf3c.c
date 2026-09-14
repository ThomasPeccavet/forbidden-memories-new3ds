/* Analysis pseudo-C, not buildable source. */

void FUN_8003bf3c(byte *param_1,short *param_2,int param_3)

{
  int iVar1;
  short *psVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  
  iVar5 = param_3 + -1;
  if (-1 < iVar5) {
    psVar2 = param_2 + iVar5;
    do {
      if (*psVar2 != 0) {
        param_3 = iVar5 + 1;
        break;
      }
      iVar5 = iVar5 + -1;
      psVar2 = psVar2 + -1;
    } while (-1 < iVar5);
  }
  iVar5 = 0;
  if (0 < param_3) {
    do {
      uVar4 = (uint)(*param_2 != 0);
      piVar3 = (int *)(&DAT_801d9000 + uVar4 * 4);
      iVar1 = *piVar3;
      while (iVar1 != 0) {
        if ((short)*piVar3 == *param_2) {
          if (0xef < (int)uVar4) {
            *param_1 = (byte)(uVar4 >> 8) | 0xf0;
            param_1[1] = (byte)uVar4;
            param_1 = param_1 + 2;
            goto LAB_8003bff4;
          }
          *param_1 = (byte)uVar4;
          goto LAB_8003bff0;
        }
        piVar3 = piVar3 + 1;
        uVar4 = uVar4 + 1;
        iVar1 = *piVar3;
      }
      *param_1 = 0;
LAB_8003bff0:
      param_1 = param_1 + 1;
LAB_8003bff4:
      iVar5 = iVar5 + 1;
      param_2 = param_2 + 1;
    } while (iVar5 < param_3);
  }
  *param_1 = 0xff;
  return;
}

