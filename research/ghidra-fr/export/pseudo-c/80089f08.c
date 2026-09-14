/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80089f08(int *param_1,int *param_2,int *param_3,undefined4 *param_4)

{
  uint *puVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  
  if (param_1 == (int *)0x0) {
    DAT_8009b154 = DAT_8009b154 - 1;
    if ((int)((uint)DAT_8009b154 << 0x10) < 0) {
      piVar3 = DAT_8009b148 + 3;
      if (DAT_8009b148 == (int *)0xffffffff) {
        return 0;
      }
      DAT_8009b150 = (uint *)DAT_8009b148[1];
      DAT_8009b154 = (short)DAT_8009b148[2] - 1;
      DAT_8009b148 = (int *)*DAT_8009b148;
      DAT_8009b14c = piVar3;
    }
    piVar3 = DAT_8009b14c;
    if (DAT_8009b14c[1] < 0) {
      iVar4 = *DAT_8009b14c;
      param_2[1] = (int)DAT_8009b14c;
      *param_2 = iVar4;
      piVar3[1] = piVar3[1] & 0x7fffffff;
    }
    else {
      *param_2 = 0;
      param_2[1] = 0;
    }
    piVar3 = DAT_8009b14c;
    param_4[1] = param_3;
    *param_4 = piVar3 + 1;
    puVar1 = DAT_8009b150;
    param_4[2] = 0xe - *param_3;
    iVar4 = param_3[2];
    param_4[4] = DAT_800ff5c4;
    param_4[3] = iVar4;
    uVar5 = 0;
    if (*puVar1 != 0) {
      do {
        iVar4 = uVar5 + 1;
        uVar5 = uVar5 + 1;
        param_4[5] = puVar1[iVar4];
        param_4 = param_4 + 1;
      } while (uVar5 < *puVar1);
    }
    uVar2 = 1;
    DAT_8009b14c = DAT_8009b14c + *(ushort *)(DAT_8009b14c + 1) + 1;
  }
  else {
    DAT_8009b148 = (int *)*param_1;
    DAT_8009b150 = (uint *)param_1[1];
    DAT_8009b154 = *(ushort *)(param_1 + 2);
    DAT_8009b14c = param_1 + 3;
    uVar2 = 0;
  }
  return uVar2;
}

