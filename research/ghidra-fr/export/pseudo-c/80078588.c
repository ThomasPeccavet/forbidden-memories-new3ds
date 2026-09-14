/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80078588(uint param_1)

{
  bool bVar1;
  undefined1 uVar2;
  ushort uVar3;
  int iVar4;
  undefined *puVar5;
  undefined4 *puVar6;
  undefined4 local_58 [18];
  
  bVar1 = (param_1 & 0x100) != 0;
  if (bVar1) {
    param_1 = param_1 & 0xfffffeff;
  }
  if (param_1 < 10) {
    iVar4 = FUN_800762c8((&DAT_80094548)[param_1]);
    puVar6 = local_58;
    if (iVar4 == 0) {
      puVar5 = &DAT_80094578 + param_1 * 0x44;
      iVar4 = 0x43;
      DAT_80093f54 = (&DAT_80094548)[param_1];
      do {
        uVar2 = *puVar5;
        puVar5 = puVar5 + 1;
        iVar4 = iVar4 + -1;
        *(undefined1 *)puVar6 = uVar2;
        puVar6 = (undefined4 *)((int)puVar6 + 1);
      } while (iVar4 != -1);
      local_58[0] = 0;
      if (param_1 == 7) {
        DAT_80093f68 = 0x7f;
        DAT_80093f64 = 0x7f;
      }
      else if (param_1 == 8) {
        DAT_80093f68 = 0;
        DAT_80093f64 = 0x7f;
      }
      else {
        DAT_80093f68 = 0;
        DAT_80093f64 = 0;
      }
      uVar3 = *(ushort *)(DAT_80093fb8 + 0x1aa) >> 7;
      DAT_80093f5c = param_1;
      if ((uVar3 & 1) != 0) {
        *(ushort *)(DAT_80093fb8 + 0x1aa) = *(ushort *)(DAT_80093fb8 + 0x1aa) & 0xff7f;
      }
      iVar4 = DAT_80093fb8;
      *(undefined2 *)(DAT_80093fb8 + 0x184) = 0;
      *(undefined2 *)(iVar4 + 0x186) = 0;
      DAT_80093f60 = 0;
      DAT_80093f62 = 0;
      FUN_80076858(local_58);
      if (bVar1) {
        FUN_80077108(param_1);
      }
      FUN_80075e64(0xd1,DAT_80093f54,0);
      if ((uVar3 & 1) == 0) {
        return 0;
      }
      *(ushort *)(DAT_80093fb8 + 0x1aa) = *(ushort *)(DAT_80093fb8 + 0x1aa) | 0x80;
      return 0;
    }
  }
  return 0xffffffff;
}

