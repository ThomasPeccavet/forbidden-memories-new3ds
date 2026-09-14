/* Analysis pseudo-C, not buildable source. */

void FUN_80035ba0(int param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  iVar2 = (param_3 >> 2) - 1;
  if (-1 < iVar2) {
    puVar5 = (undefined4 *)(iVar2 * 4 + param_1);
    puVar4 = (undefined4 *)(iVar2 * 4 + param_2);
    do {
      uVar1 = *puVar4;
      puVar4 = puVar4 + -1;
      iVar2 = iVar2 + -1;
      *puVar5 = uVar1;
      puVar5 = puVar5 + -1;
    } while (-1 < iVar2);
  }
  uVar3 = param_3 & 3;
  if (uVar3 == 1) {
LAB_80035c04:
    *(undefined4 *)((param_3 & 0xfffffffc) + param_1) =
         *(undefined4 *)((param_3 & 0xfffffffc) + param_2);
    return;
  }
  if (uVar3 != 0) {
    if (uVar3 == 2) goto LAB_80035c04;
    if (uVar3 == 3) {
      *(undefined4 *)((param_3 & 0xfffffffc) + param_1) =
           *(undefined4 *)((param_3 & 0xfffffffc) + param_2);
      *(undefined1 *)(param_3 + param_1 + -1) = *(undefined1 *)(param_3 + param_2 + -1);
      return;
    }
  }
  return;
}

