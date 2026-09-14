/* Analysis pseudo-C, not buildable source. */

void FUN_800828ec(uint *param_1,uint *param_2)

{
  uint *puVar1;
  uint *puVar2;
  uint uVar3;
  uint *puVar4;
  
  FUN_80082798();
  if (param_1 == (uint *)0x0) {
    param_1 = param_2;
    if (param_2 == (uint *)0x0) {
      return;
    }
  }
  else if (param_2 != (uint *)0x0) {
    uVar3 = *(uint *)(*param_1 & 0xffffff | 0x80000000);
    puVar4 = param_1;
    puVar2 = param_1;
    while (puVar1 = puVar4, (uVar3 & 0xffffff) != 0xffffff) {
      puVar4 = (uint *)(*puVar1 & 0xffffff | 0x80000000);
      uVar3 = *(uint *)(*puVar4 & 0xffffff | 0x80000000);
      puVar2 = puVar1;
    }
    *puVar2 = *puVar2 & 0xff000000 | (uint)param_2 & 0xffffff;
  }
  *DAT_80095bf8 = 0x4000002;
  *DAT_80095be8 = param_1;
  *DAT_80095bec = 0;
  *DAT_80095bf0 = 0x1000401;
  return;
}

