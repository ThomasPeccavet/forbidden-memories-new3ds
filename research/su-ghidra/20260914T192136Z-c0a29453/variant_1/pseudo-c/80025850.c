/* Analysis pseudo-C, not buildable source. */

void FUN_80025850(void)

{
  ushort uVar1;
  int iVar2;
  undefined2 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int unaff_gp;
  
  iVar2 = FUN_80024ee0();
  if (iVar2 == 0) {
    FUN_800402ac(0x8020);
  }
  else {
    uVar1 = *(ushort *)(unaff_gp + 0x2b8);
    if ((uVar1 & 0x20) == 0) {
      if ((DAT_8009c47c & 0x4000) != 0) {
        *(ushort *)(unaff_gp + 0x2b8) = uVar1 | 0x20;
        puVar3 = (undefined2 *)FUN_8002c860(0x11);
        if (*(short *)(unaff_gp + 0x32c) == 0x149) {
          uVar1 = *(ushort *)(unaff_gp + 0x2b8);
          puVar3[0xd] = 1;
          *(ushort *)(unaff_gp + 0x2b8) = uVar1 | 0x40;
        }
        *puVar3 = 0;
        puVar3[1] = 0;
        puVar3[2] = 0;
      }
    }
    else if ((DAT_8009c47c & 0x4000) == 0) {
      iVar2 = 5;
      if ((uVar1 & 0x40) == 0) {
        puVar4 = &DAT_801a7b64;
        puVar5 = &DAT_801a7d08;
        iVar2 = 0;
        do {
          if ((*(ushort *)((int)puVar4 + 0x16) & 0x8000) != 0) {
            FUN_80024a10(puVar4);
          }
          if ((*(ushort *)((int)puVar5 + 0x16) & 0x8000) != 0) {
            FUN_80024a10(puVar5);
          }
          iVar2 = iVar2 + 1;
          puVar4 = puVar4 + 7;
          puVar5 = puVar5 + 7;
        } while (iVar2 < 10);
      }
      else {
        do {
          if ((((&DAT_801a7aee)
                [(uint)(byte)(&DAT_800919e0)[iVar2 + (uint)*(byte *)(unaff_gp + 0x26c) * 0x14] * 0xe
                ] & 0x8000) != 0) &&
             (*(char *)((&DAT_801a7ad8)
                        [(uint)(byte)(&DAT_800919e0)
                                     [iVar2 + (uint)*(byte *)(unaff_gp + 0x26c) * 0x14] * 7] + 0x68)
              == '\0')) {
            FUN_80024a10(&DAT_801a7ad8 +
                         (uint)(byte)(&DAT_800919e0)
                                     [iVar2 + (uint)*(byte *)(unaff_gp + 0x26c) * 0x14] * 7);
          }
          iVar2 = iVar2 + 1;
        } while (iVar2 < 10);
      }
      *(undefined2 *)(unaff_gp + 0x2b8) = 0;
    }
  }
  return;
}

