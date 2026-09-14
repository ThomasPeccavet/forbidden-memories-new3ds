/* Analysis pseudo-C, not buildable source. */

void FUN_800741a4(int *param_1,undefined4 param_2,undefined4 param_3)

{
  code *pcVar1;
  int in_zero;
  int iVar2;
  int *piVar3;
  int *piVar4;
  
  if (*param_1 == 0) {
    *param_1 = 1;
  }
  pcVar1 = DAT_800f7048;
  piVar4 = *(int **)(in_zero + 0x150);
  piVar3 = piVar4 + (*(uint *)(in_zero + 0x154) / 0x50) * 0x14;
  do {
    if (piVar3 <= piVar4) {
LAB_80074268:
      (*DAT_800f7048)(param_1,param_2,param_3);
      return;
    }
    if ((*piVar4 != 0) && (iVar2 = FUN_8008f7f8(*piVar4,&DAT_800f7050), iVar2 == 0)) {
      piVar4[0xd] = (int)pcVar1;
      goto LAB_80074268;
    }
    piVar4 = piVar4 + 0x14;
  } while( true );
}

