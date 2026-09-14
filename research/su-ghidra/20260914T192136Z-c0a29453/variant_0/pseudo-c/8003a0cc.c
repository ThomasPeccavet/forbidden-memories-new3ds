/* Analysis pseudo-C, not buildable source. */

void FUN_8003a0cc(int param_1)

{
  undefined2 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  byte *pbVar8;
  int iVar9;
  
  iVar9 = *(int *)(param_1 + 0x24);
  DAT_8009c6e4 = 0;
  if ((*(byte *)(iVar9 + 0xf) & 0x80) != 0) {
    pbVar8 = (byte *)(iVar9 + 0xf);
    do {
      if (pbVar8[2] != 0) {
        (*(code *)(&PTR_FUN_8009236c)[pbVar8[2] & 0x1f])(iVar9,param_1);
      }
      pbVar8 = pbVar8 + 0x16;
      iVar9 = iVar9 + 0x16;
    } while ((*pbVar8 & 0x80) != 0);
  }
  if (DAT_8009c6e4 != 0) {
    puVar4 = *(undefined4 **)(param_1 + 0x20);
    puVar2 = (undefined4 *)(&DAT_800ec390 + (uint)*(ushort *)(param_1 + 0x5c) * 0x16);
    puVar3 = puVar2;
    for (; puVar2 != puVar4; puVar2 = (undefined4 *)((int)puVar2 + 0x16)) {
      if ((*(byte *)((int)puVar2 + 0xf) & 0x80) != 0) {
        uVar5 = puVar2[1];
        uVar6 = puVar2[2];
        uVar7 = puVar2[3];
        *puVar3 = *puVar2;
        puVar3[1] = uVar5;
        puVar3[2] = uVar6;
        puVar3[3] = uVar7;
        uVar1 = *(undefined2 *)(puVar2 + 5);
        puVar3[4] = puVar2[4];
        *(undefined2 *)(puVar3 + 5) = uVar1;
        puVar3 = (undefined4 *)((int)puVar3 + 0x16);
      }
    }
    *(undefined4 **)(param_1 + 0x20) = puVar3;
    *(undefined1 *)((int)puVar3 + 0xf) = 0;
  }
  return;
}

