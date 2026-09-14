/* Analysis pseudo-C, not buildable source. */

void FUN_80050d8c(int param_1,int param_2,int param_3,uint param_4)

{
  short sVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  ushort *puVar8;
  uint uVar9;
  
  uVar6 = (uint)*(ushort *)(param_1 + param_2 * 2 + param_3 * 0x74 + 0x2c8);
  iVar7 = *(int *)(param_1 + param_2 * 4 + 0x1e0);
  piVar5 = (int *)(*(int *)(param_1 + 0xdd8) + uVar6 * 4);
  if ((iVar7 != 0) && (uVar6 != 0xffff)) {
    uVar6 = (uint)*(ushort *)(param_1 + param_2 * 2 + param_3 * 0x76 + 0x750);
    if (uVar6 != 0) {
      uVar9 = param_4 % (uVar6 << 4);
      if (uVar6 == 0) {
        trap(0x1c00);
      }
      puVar8 = (ushort *)(piVar5 + -1);
      if (((uVar9 == 0) && (param_4 != 0)) && (*(char *)(param_1 + 0xe16) != '<')) {
        uVar9 = uVar6 << 4;
      }
      uVar6 = (uint)*puVar8;
      iVar4 = 0;
      if (uVar6 != 0) {
        piVar2 = piVar5;
        do {
          if (*(char *)(param_1 + 0xe16) == '<') {
            if ((int)(uVar9 + (uint)*(byte *)((int)piVar2 + 2) * -0x10) < 0) break;
          }
          else if ((int)(uVar9 + (uint)*(byte *)((int)piVar2 + 2) * -0x10) < 1) break;
          uVar9 = uVar9 + (uint)*(byte *)((int)piVar2 + 2) * -0x10;
          if (piVar2[1] < 0) break;
          iVar4 = iVar4 + 1;
          piVar5 = piVar5 + 1;
          piVar2 = piVar2 + 1;
        } while (iVar4 < (int)uVar6);
        uVar6 = (uint)*puVar8;
        piVar2 = piVar5;
        if (iVar4 < (int)uVar6) {
          do {
            if (piVar2[1] < 0) break;
            iVar4 = iVar4 + 1;
            piVar2 = piVar2 + 1;
          } while (iVar4 < (int)uVar6);
          iVar4 = (int)piVar5 - *(int *)(param_1 + 0xdd8) >> 2;
          sVar1 = (short)iVar4;
          *(short *)(iVar7 + 0x16) = sVar1;
          if (iVar4 == 0) {
            sVar1 = (short)((int)piVar2 - *(int *)(param_1 + 0xdd8) >> 2);
          }
          else {
            sVar1 = sVar1 + -1;
          }
          *(short *)(iVar7 + 0x14) = sVar1;
          iVar4 = (uint)*(byte *)((int)piVar5 + 2) * 0x10;
          iVar3 = iVar4 - uVar9;
          *(short *)(iVar7 + 0x12) = (short)iVar4;
          *(short *)(iVar7 + 0x10) = (short)iVar3;
          if ((*(char *)(param_1 + 0xe16) == '<') &&
             ((int)(uint)*(ushort *)(iVar7 + 0x12) <= iVar3 * 0x10000 >> 0x10)) {
            *(undefined2 *)(iVar7 + 0x10) = 0x6000;
          }
        }
      }
    }
  }
  return;
}

