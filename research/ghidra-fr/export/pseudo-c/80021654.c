/* Analysis pseudo-C, not buildable source. */

void FUN_80021654(void)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  uint *puVar5;
  char *pcVar6;
  int *piVar7;
  int iVar8;
  
  iVar3 = DAT_8009c508;
  pcVar6 = &DAT_800eb278;
  *(undefined1 *)(DAT_8009c508 + 0x34) = 0x40;
  *(undefined1 *)(iVar3 + 0x35) = 0x44;
  *(undefined1 *)(iVar3 + 0x36) = 0x45;
  piVar7 = &DAT_801bf88c;
  if ((&DAT_800eb278)[(uint)DAT_8009c584 * 0x20] == '(') {
    *(undefined1 *)(iVar3 + 0x34) = 0x42;
  }
  iVar8 = 0;
  if ((&DAT_800eb278)[(uint)DAT_8009c584 * 0x20] == -0x28) {
    *(undefined1 *)(iVar3 + 0x34) = 0x41;
  }
  puVar5 = &DAT_801bf904;
  pbVar4 = &DAT_800eb279;
  *(undefined4 *)(iVar3 + 0x30) = 0x32;
  *(undefined4 *)(iVar3 + 0x2c) = 0x32;
  do {
    *(int *)(iVar3 + 0x2c) = *(int *)(iVar3 + 0x2c) + (int)*pcVar6;
    *piVar7 = (int)(char)pbVar4[0x17];
    iVar2 = FUN_80021614(6);
    *(int *)(iVar3 + 0x2c) = *(int *)(iVar3 + 0x2c) + iVar2;
    puVar5[-0x1c] = (int)*(short *)(pbVar4 + 0x13);
    iVar2 = FUN_80021614(7);
    *(int *)(iVar3 + 0x2c) = *(int *)(iVar3 + 0x2c) + iVar2;
    puVar5[-0x1a] = (int)*(short *)(pbVar4 + 0xd);
    puVar5[-0x18] = (uint)pbVar4[10];
    puVar5[-0x16] = (uint)pbVar4[1];
    iVar2 = FUN_80021614(1);
    *(int *)(iVar3 + 0x2c) = *(int *)(iVar3 + 0x2c) + iVar2;
    puVar5[-0x14] = (int)*(short *)(pbVar4 + 0xf);
    puVar5[-0x12] = (uint)pbVar4[0xb];
    puVar5[-0x10] = (uint)pbVar4[2];
    iVar2 = FUN_80021614(2);
    *(int *)(iVar3 + 0x2c) = *(int *)(iVar3 + 0x2c) + iVar2;
    puVar5[-0xe] = (uint)pbVar4[6];
    puVar5[-0xc] = (uint)pbVar4[3];
    iVar2 = FUN_80021614(3);
    *(int *)(iVar3 + 0x2c) = *(int *)(iVar3 + 0x2c) + iVar2;
    puVar5[-10] = (uint)pbVar4[7];
    iVar2 = FUN_80021614(8);
    *(int *)(iVar3 + 0x2c) = *(int *)(iVar3 + 0x2c) + iVar2;
    puVar5[-8] = (uint)pbVar4[8];
    iVar2 = FUN_80021614(9);
    iVar8 = iVar8 + 1;
    *(int *)(iVar3 + 0x2c) = *(int *)(iVar3 + 0x2c) + iVar2;
    pcVar6 = pcVar6 + 0x20;
    puVar5[-6] = (uint)pbVar4[9];
    puVar5[-4] = (uint)pbVar4[4];
    iVar2 = FUN_80021614(4);
    piVar7 = piVar7 + 1;
    *(int *)(iVar3 + 0x2c) = *(int *)(iVar3 + 0x2c) + iVar2;
    puVar5[-2] = (uint)pbVar4[5];
    iVar2 = FUN_80021614(5);
    *(int *)(iVar3 + 0x2c) = *(int *)(iVar3 + 0x2c) + iVar2;
    bVar1 = *pbVar4;
    pbVar4 = pbVar4 + 0x20;
    *puVar5 = (uint)bVar1;
    iVar2 = FUN_80021614(0);
    puVar5 = puVar5 + 1;
    *(int *)(iVar3 + 0x2c) = *(int *)(iVar3 + 0x2c) + iVar2;
    iVar3 = iVar3 + 4;
  } while (iVar8 < 2);
  return;
}

