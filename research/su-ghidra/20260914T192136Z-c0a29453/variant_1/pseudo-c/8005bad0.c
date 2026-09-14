/* Analysis pseudo-C, not buildable source. */

void FUN_8005bad0(uint param_1,ushort param_2,undefined4 param_3,undefined4 param_4,short param_5,
                 int param_6)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  ushort uVar5;
  int iVar6;
  ushort *puVar7;
  
  uVar5 = (param_2 & 1) << 2;
  iVar6 = 0;
  puVar7 = &DAT_800f4088;
  do {
    if ((*puVar7 & 1) == 0) {
      uVar1 = *puVar7;
      uVar2 = (ushort)((param_1 & 1) << 1);
      iVar4 = 0;
      *puVar7 = uVar1 & 0xfff9 | 1 | uVar2 | uVar5;
      *puVar7 = uVar1 & 0xff01 | 1 | uVar2 | uVar5 |
                ((byte)(&DAT_800f4d6d)[param_1 * 0xe20] & 0x1f) << 3;
      uVar5 = (&DAT_800f4f7e)[param_1 * 0x710];
      puVar7[6] = 0;
      puVar7[7] = param_5 << 1;
      puVar7[5] = uVar5;
      *(undefined4 *)(puVar7 + 8) = param_3;
      *(undefined4 *)(puVar7 + 10) = param_4;
      iVar3 = iVar6;
      do {
        if (param_6 == 0) {
          *(undefined1 *)((int)&DAT_800f4088 + iVar3 + 1) = 0xff;
        }
        else {
          *(undefined1 *)((int)&DAT_800f4088 + iVar3 + 1) = *(undefined1 *)(param_6 + iVar4);
        }
        iVar4 = iVar4 + 1;
        iVar3 = iVar4 + iVar6;
      } while (iVar4 < 8);
      return;
    }
    puVar7 = puVar7 + 0xc;
    iVar6 = iVar6 + 0x18;
  } while ((int)puVar7 < -0x7ff0be88);
  return;
}

