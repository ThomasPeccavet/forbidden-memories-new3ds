/* Analysis pseudo-C, not buildable source. */

byte FUN_8002c89c(void)

{
  short sVar1;
  short sVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  byte *pbVar5;
  undefined *puVar6;
  int iVar7;
  int unaff_gp;
  
  puVar6 = &DAT_800ec110;
  iVar7 = 8;
  pbVar5 = &DAT_800ec12c;
  *(byte *)(unaff_gp + 0x360) = *(byte *)(unaff_gp + 0x360) & 0xfe;
  do {
    if ((*pbVar5 & 0x80) != 0) {
      if ((*pbVar5 & 0x20) == 0) {
        *(byte *)(unaff_gp + 0x360) = *(byte *)(unaff_gp + 0x360) | 1;
      }
      *(undefined1 *)(unaff_gp + 0x368) = 0;
      sVar1 = *(short *)(pbVar5 + -2);
      if ((*pbVar5 & 0x40) == 0) {
        *pbVar5 = *pbVar5 | 0x40;
        pbVar5[-0xffffffff00000002] = 0xff;
        pbVar5[-0xffffffff00000001] = 0xff;
      }
      sVar2 = *(short *)(pbVar5 + -4);
      uVar4 = *(undefined4 *)(pbVar5 + -8);
      *(undefined4 *)(pbVar5 + -0x10) = DAT_8009c85c;
      uVar3 = DAT_8009c860;
      *(undefined **)(unaff_gp + 0x364) = puVar6;
      *(undefined4 *)(pbVar5 + -0x14) = uVar3;
      FUN_80146258((int)sVar2,(int)sVar1,uVar4,puVar6);
      FUN_80087838(0,0);
      FUN_80087858((int)DAT_800f11ee);
      if (*(char *)(unaff_gp + 0x368) == '\x01') {
        *pbVar5 = 0;
      }
    }
    pbVar5 = pbVar5 + 0x20;
    iVar7 = iVar7 + -1;
    puVar6 = puVar6 + 0x20;
  } while (iVar7 != 0);
  return *(byte *)(unaff_gp + 0x360) & 1;
}

