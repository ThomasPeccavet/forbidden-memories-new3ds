/* Analysis pseudo-C, not buildable source. */

void FUN_80047b44(int *param_1,uint param_2)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  iVar4 = 0;
  if (0 < *param_1) {
    piVar3 = param_1;
    piVar5 = param_1;
    do {
      iVar1 = DAT_8009c7e0;
      if (*(ushort *)(piVar3 + 2) != 0xffff) {
        *(undefined2 *)((uint)*(ushort *)(piVar3 + 2) * 2 + *(int *)(DAT_8009c7e0 + 0x43c)) =
             *(undefined2 *)(DAT_8009c7e0 + 0x440);
        piVar2 = (int *)((uint)*(ushort *)(iVar1 + 0x440) * 8 + *(int *)(iVar1 + 0x444));
        iVar6 = piVar5[0x69];
        *piVar2 = piVar5[0x68];
        piVar2[1] = iVar6;
        iVar6 = (uint)*(ushort *)(iVar1 + 0x440) * 8 + *(int *)(iVar1 + 0x444);
        *(short *)(iVar6 + 6) = *(short *)(iVar6 + 6) + (short)(param_2 >> 4);
        *(short *)(iVar1 + 0x440) = *(short *)(iVar1 + 0x440) + 1;
      }
      piVar5 = piVar5 + 2;
      iVar4 = iVar4 + 1;
      piVar3 = (int *)((int)piVar3 + 2);
    } while (iVar4 < *param_1);
  }
  return;
}

