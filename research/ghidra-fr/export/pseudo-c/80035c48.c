/* Analysis pseudo-C, not buildable source. */

void FUN_80035c48(int param_1,byte param_2,uint param_3)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = (param_3 >> 2) - 1;
  uVar3 = (uint)param_2;
  uVar3 = (uint)param_2 << 0x18 | uVar3 << 0x10 | uVar3 << 8 | uVar3;
  if (-1 < iVar4) {
    puVar1 = (uint *)(iVar4 * 4 + param_1);
    do {
      *puVar1 = uVar3;
      iVar4 = iVar4 + -1;
      puVar1 = puVar1 + -1;
    } while (-1 < iVar4);
  }
  uVar2 = param_3 & 3;
  if (uVar2 == 1) {
LAB_80035cbc:
    *(uint *)((param_3 & 0xfffffffc) + param_1) = uVar3;
    return;
  }
  if (uVar2 != 0) {
    if (uVar2 == 2) goto LAB_80035cbc;
    if (uVar2 == 3) {
      *(uint *)((param_3 & 0xfffffffc) + param_1) = uVar3;
      *(byte *)(param_3 + param_1 + -1) = param_2;
      return;
    }
  }
  return;
}

