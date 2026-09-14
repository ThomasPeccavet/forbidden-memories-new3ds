/* Analysis pseudo-C, not buildable source. */

void FUN_8008a9b8(int *param_1,int *param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  
  iVar7 = 0;
  iVar3 = 100;
  do {
    (&DAT_800ff600)[iVar7] = (int)param_1;
    iVar2 = DAT_800ff600;
    if ((int *)param_1[0x13] == (int *)0x0) {
      if ((*param_1 == DAT_800ff450) || (*param_1 == 0)) {
        param_1[9] = param_1[1];
        param_1[10] = param_1[2];
        param_1[0xb] = param_1[3];
        param_1[0xc] = param_1[4];
        param_1[0xd] = param_1[5];
        param_1[0xe] = param_1[6];
        param_1[0xf] = param_1[7];
        param_1[0x10] = param_1[8];
        iVar3 = DAT_800ff450;
        iVar2 = param_1[10];
        iVar4 = param_1[0xb];
        iVar5 = param_1[0xc];
        *param_2 = param_1[9];
        param_2[1] = iVar2;
        param_2[2] = iVar4;
        param_2[3] = iVar5;
        iVar2 = param_1[0xe];
        iVar4 = param_1[0xf];
        iVar5 = param_1[0x10];
        param_2[4] = param_1[0xd];
        param_2[5] = iVar2;
        param_2[6] = iVar4;
        param_2[7] = iVar5;
        *param_1 = iVar3;
      }
      else {
        iVar7 = iVar3 + 1;
        if (iVar3 == 100) {
          iVar3 = *(int *)(DAT_800ff600 + 0x28);
          iVar7 = *(int *)(DAT_800ff600 + 0x2c);
          iVar4 = *(int *)(DAT_800ff600 + 0x30);
          *param_2 = *(int *)(DAT_800ff600 + 0x24);
          param_2[1] = iVar3;
          param_2[2] = iVar7;
          param_2[3] = iVar4;
          iVar3 = *(int *)(iVar2 + 0x38);
          iVar7 = *(int *)(iVar2 + 0x3c);
          iVar4 = *(int *)(iVar2 + 0x40);
          param_2[4] = *(int *)(iVar2 + 0x34);
          param_2[5] = iVar3;
          param_2[6] = iVar7;
          param_2[7] = iVar4;
          iVar7 = 0;
        }
        else {
          iVar3 = (&DAT_800ff600)[iVar7];
          iVar2 = *(int *)(iVar3 + 0x28);
          iVar4 = *(int *)(iVar3 + 0x2c);
          iVar5 = *(int *)(iVar3 + 0x30);
          *param_2 = *(int *)(iVar3 + 0x24);
          param_2[1] = iVar2;
          param_2[2] = iVar4;
          param_2[3] = iVar5;
          iVar2 = *(int *)(iVar3 + 0x38);
          iVar4 = *(int *)(iVar3 + 0x3c);
          iVar5 = *(int *)(iVar3 + 0x40);
          param_2[4] = *(int *)(iVar3 + 0x34);
          param_2[5] = iVar2;
          param_2[6] = iVar4;
          param_2[7] = iVar5;
        }
      }
LAB_8008abdc:
      if (0 < iVar7) {
        piVar6 = &DAT_800ff5fc + iVar7;
        do {
          FUN_800865a8(param_2,*piVar6 + 4);
          iVar3 = *piVar6;
          iVar7 = iVar7 + -1;
          iVar2 = param_2[1];
          iVar4 = param_2[2];
          iVar5 = param_2[3];
          *(int *)(iVar3 + 0x24) = *param_2;
          *(int *)(iVar3 + 0x28) = iVar2;
          *(int *)(iVar3 + 0x2c) = iVar4;
          *(int *)(iVar3 + 0x30) = iVar5;
          iVar2 = param_2[5];
          iVar4 = param_2[6];
          iVar5 = param_2[7];
          *(int *)(iVar3 + 0x34) = param_2[4];
          *(int *)(iVar3 + 0x38) = iVar2;
          *(int *)(iVar3 + 0x3c) = iVar4;
          *(int *)(iVar3 + 0x40) = iVar5;
          piVar1 = (int *)*piVar6;
          piVar6 = piVar6 + -1;
          *piVar1 = DAT_800ff450;
        } while (0 < iVar7);
      }
      iVar3 = param_2[1];
      iVar7 = param_2[2];
      iVar2 = param_2[3];
      *param_3 = *param_2;
      param_3[1] = iVar3;
      param_3[2] = iVar7;
      param_3[3] = iVar2;
      iVar3 = param_2[5];
      iVar7 = param_2[6];
      iVar2 = param_2[7];
      param_3[4] = param_2[4];
      param_3[5] = iVar3;
      param_3[6] = iVar7;
      param_3[7] = iVar2;
      FUN_80086528(&DAT_800ff4d0,param_3);
      return;
    }
    if (*param_1 == DAT_800ff450) {
      iVar3 = param_1[10];
      iVar2 = param_1[0xb];
      iVar4 = param_1[0xc];
      *param_2 = param_1[9];
      param_2[1] = iVar3;
      param_2[2] = iVar2;
      param_2[3] = iVar4;
      iVar3 = param_1[0xe];
      iVar2 = param_1[0xf];
      iVar4 = param_1[0x10];
      param_2[4] = param_1[0xd];
      param_2[5] = iVar3;
      param_2[6] = iVar2;
      param_2[7] = iVar4;
      goto LAB_8008abdc;
    }
    if (*param_1 == 0) {
      iVar3 = iVar7;
    }
    iVar7 = iVar7 + 1;
    param_1 = (int *)param_1[0x13];
  } while( true );
}

