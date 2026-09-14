/* Analysis pseudo-C, not buildable source. */

void FUN_8005d644(code *param_1,int *param_2,undefined4 param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = param_4 + -1;
  if (param_4 != 0) {
    do {
      uVar1 = FUN_80068c10(*param_2);
      uVar3 = param_2[1];
      if ((((((uint)((int)uVar1 >> 0x18) < 2) && ((uVar1 & 0xffff) != 0)) &&
           ((uVar3 & 0xffff0000) != 0)) || (((int)uVar1 >> 0x18 == 1 && ((uVar1 & 0xffff) == 0))))
         && (iVar2 = (*param_1)(*param_2), iVar2 != -1)) {
        *param_2 = iVar2;
      }
      iVar4 = iVar4 + -1;
      param_2 = param_2 + (uVar3 & 0xffff) + 1;
    } while (iVar4 != -1);
  }
  return;
}

