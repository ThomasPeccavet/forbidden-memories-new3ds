/* Analysis pseudo-C, not buildable source. */

void FUN_8005b444(uint param_1,uint param_2,uint param_3)

{
  short sVar1;
  undefined2 uVar2;
  int iVar3;
  undefined2 *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined2 local_820 [1024];
  
  if (param_1 < 2) {
    iVar7 = param_1 * 0x10 + 0xd0;
    if ((((int)param_2 < 7) || ((param_2 & 8) != 0)) || ((int)param_3 < 0x1000)) {
      DAT_8009c7f0 = 0x280;
      DAT_8009c7f4 = 0x100;
      DAT_8009c7f6 = 4;
      iVar3 = 8;
      iVar5 = 0;
      do {
        sVar1 = (short)iVar7;
        DAT_8009c7f2 = sVar1 + (short)iVar3;
        do {
          iVar3 = FUN_8008288c(3);
        } while (iVar3 != 0);
        do {
          iVar3 = FUN_8008246c(&DAT_8009c7f0,local_820);
        } while (iVar3 != 0);
        do {
          iVar3 = FUN_8008288c(3);
          puVar4 = local_820;
        } while (iVar3 != 0);
        iVar3 = 0;
        do {
          iVar3 = iVar3 + 1;
          uVar2 = FUN_80068264(*puVar4,param_2 & 0xff,param_3 & 0xffff);
          *puVar4 = uVar2;
          puVar4 = puVar4 + 1;
        } while (iVar3 < 0x400);
        DAT_8009c7f2 = sVar1 + (short)iVar5;
        do {
          iVar3 = FUN_8008288c(3);
        } while (iVar3 != 0);
        do {
          iVar3 = FUN_80082380(&DAT_8009c7f0,local_820);
        } while (iVar3 != 0);
        do {
          iVar3 = FUN_8008288c(3);
        } while (iVar3 != 0);
        iVar6 = iVar5 + 4;
        iVar3 = iVar5 + 0xc;
        iVar5 = iVar6;
      } while (iVar6 < 8);
    }
    else {
      DAT_8009c7f0 = 0x280;
      DAT_8009c7f2 = (short)(param_1 * 0x10) + 0xd8;
      DAT_8009c7f4 = 0x100;
      DAT_8009c7f6 = 8;
      FUN_8007ffd0(&DAT_8009c7f0,0x280,iVar7);
    }
  }
  return;
}

