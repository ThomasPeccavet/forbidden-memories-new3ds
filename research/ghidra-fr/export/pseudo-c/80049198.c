/* Analysis pseudo-C, not buildable source. */

void FUN_80049198(uint param_1,undefined4 param_2)

{
  ushort uVar1;
  ushort uVar2;
  short sVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int *piVar9;
  int *piVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  int iVar14;
  
  if (param_1 < 2) {
    piVar13 = (int *)(param_1 * 0x800 + -0x7fe18800);
    FUN_80049100(piVar13,param_2);
    FUN_80047acc();
    iVar11 = 0;
    do {
      piVar10 = (int *)((1 - param_1) * 0x800 + -0x7fe18800);
      if (iVar11 != 0) {
        piVar10 = piVar13;
      }
      iVar7 = 0;
      piVar8 = piVar10;
      piVar9 = piVar10;
      iVar12 = param_1 << 6;
      if (0 < *piVar10) {
        do {
          iVar4 = DAT_8009c7e0;
          uVar1 = *(ushort *)(piVar8 + 2);
          if (uVar1 != 0xffff) {
            uVar2 = *(ushort *)(DAT_8009c7e0 + 0x440);
            *(ushort *)((uint)uVar1 * 2 + *(int *)(DAT_8009c7e0 + 0x43c)) = uVar2;
            iVar6 = (uint)uVar2 * 8;
            piVar5 = (int *)(iVar6 + *(int *)(iVar4 + 0x444));
            iVar14 = piVar9[0x69];
            *piVar5 = piVar9[0x68];
            piVar5[1] = iVar14;
            iVar6 = iVar6 + *(int *)(iVar4 + 0x444);
            if (iVar11 == 0) {
              sVar3 = (short)(((int)(1 - param_1) % 2) * 0x19000 + 0xd810U >> 4);
            }
            else {
              sVar3 = (short)(((int)param_1 % 2) * 0x19000 + 0xd810U >> 4);
            }
            *(short *)(iVar6 + 6) = *(short *)(iVar6 + 6) + sVar3;
            *(short *)(DAT_8009c7e0 + 0x440) = *(short *)(DAT_8009c7e0 + 0x440) + 1;
          }
          if (iVar11 != 0) {
            *(ushort *)(DAT_8009c7e0 + iVar12 + 0x44c) = uVar1;
          }
          iVar7 = iVar7 + 1;
          piVar8 = (int *)((int)piVar8 + 2);
          piVar9 = piVar9 + 2;
          iVar12 = iVar12 + 2;
        } while (iVar7 < *piVar10);
      }
      iVar11 = iVar11 + 1;
    } while (iVar11 < 2);
  }
  return;
}

