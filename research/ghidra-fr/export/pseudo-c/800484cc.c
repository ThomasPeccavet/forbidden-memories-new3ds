/* Analysis pseudo-C, not buildable source. */

void FUN_800484cc(ushort param_1,uint param_2,short param_3,uint param_4,short param_5,
                 undefined1 param_6,undefined1 param_7)

{
  int *piVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  iVar4 = DAT_8009c7e0;
  uVar5 = (uint)*(ushort *)((uint)param_1 * 2 + *(int *)(DAT_8009c7e0 + 0x43c));
  if (uVar5 != 0xffff) {
    piVar1 = (int *)(DAT_8009c7e0 + 0x444);
    *(ushort *)(DAT_8009c7e0 + 0x38c) =
         (ushort)((int)((uint)*(byte *)(uVar5 * 8 + *(int *)(DAT_8009c7e0 + 0x444)) *
                       (param_4 & 0xff)) >> 1) | 0xff;
    *(ushort *)(iVar4 + 0x38e) =
         (ushort)((int)((uint)*(byte *)(uVar5 * 8 + *piVar1) * (param_4 & 0xff)) >> 1) | 0xff;
    if (param_5 != 0) {
      if ((ushort)(param_5 - 1U) < 0x80) {
        iVar3 = (int)*(short *)(iVar4 + 0x38c) * (0x80 - param_5);
        if (iVar3 < 0) {
          iVar3 = iVar3 + 0x7f;
        }
        *(short *)(iVar4 + 0x38c) = (short)(iVar3 >> 7);
      }
      if ((ushort)(param_5 + 0x80U) < 0x80) {
        iVar4 = (int)*(short *)(DAT_8009c7e0 + 0x38e) * (param_5 + 0x80);
        if (iVar4 < 0) {
          iVar4 = iVar4 + 0x7f;
        }
        *(short *)(DAT_8009c7e0 + 0x38e) = (short)(iVar4 >> 7);
      }
    }
    iVar4 = DAT_8009c7e0;
    iVar6 = uVar5 * 8;
    uVar5 = param_2 & 0xff;
    sVar2 = *(short *)(iVar6 + *(int *)(DAT_8009c7e0 + 0x444) + 4);
    *(int *)(DAT_8009c7e0 + 900) = 1 << (uVar5 + 0x14 & 0x1f);
    *(short *)(iVar4 + 0x39a) = sVar2 + param_3;
    *(uint *)(iVar4 + 0x3a0) = (uint)*(ushort *)(iVar6 + *(int *)(iVar4 + 0x444) + 6) << 4;
    FUN_80077468(0,*(undefined4 *)(iVar4 + 900));
    *(byte *)(DAT_8009c7e0 + 0x434) =
         *(byte *)(DAT_8009c7e0 + 0x434) | (byte)(1 << (param_2 & 0x1f));
    *(undefined1 *)(DAT_8009c7e0 + uVar5 + 0x40c) = param_7;
    *(undefined1 *)(DAT_8009c7e0 + uVar5 + 0x410) = param_6;
    iVar4 = DAT_8009c7e0;
    iVar3 = DAT_8009c7e0 + uVar5 * 2;
    *(ushort *)(iVar3 + 0x404) = param_1;
    *(undefined2 *)(iVar3 + 0x414) = *(undefined2 *)(iVar4 + 0x38c);
    *(undefined2 *)(iVar3 + 0x41c) = *(undefined2 *)(iVar4 + 0x38e);
    *(undefined1 *)(iVar4 + uVar5 + 0x424) = 0xff;
    *(undefined1 *)(DAT_8009c7e0 + uVar5 + 0x428) = 0;
    iVar4 = DAT_8009c7e0 + 900;
    *(ushort *)(DAT_8009c7e0 + uVar5 * 2 + 0x42c) =
         (ushort)*(byte *)(iVar6 + *(int *)(DAT_8009c7e0 + 0x444) + 1) << 2;
    FUN_800776b8(iVar4);
  }
  return;
}

