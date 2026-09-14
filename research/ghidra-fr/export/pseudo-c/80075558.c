/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80075558(int param_1)

{
  uint uVar1;
  undefined2 *puVar2;
  int iVar3;
  undefined2 *puVar4;
  
  *DAT_80093fc8 = *DAT_80093fc8 | 0xb0000;
  puVar2 = DAT_80093fb8;
  DAT_80093fd4 = 0;
  DAT_80093fd8 = 0;
  DAT_80093fd0 = 0;
  DAT_80093fb8[0xc0] = 0;
  puVar2[0xc1] = 0;
  puVar2[0xd5] = 0;
  FUN_80076030();
  puVar2 = DAT_80093fb8;
  DAT_80093fb8[0xc0] = 0;
  puVar2[0xc1] = 0;
  if ((puVar2[0xd7] & 0x7ff) != 0) {
    uVar1 = 1;
    do {
      if (0xf00 < uVar1) {
        FUN_8008fa78(s_SPU_T_O___s__8001196c,s_wait__reset__8001197c);
        break;
      }
      uVar1 = uVar1 + 1;
    } while ((DAT_80093fb8[0xd7] & 0x7ff) != 0);
  }
  puVar2 = DAT_80093fb8;
  iVar3 = 0;
  puVar4 = &DAT_800f70a8;
  DAT_80093fdc = 2;
  DAT_80093fe0 = 3;
  DAT_80093fe4 = 8;
  DAT_80093fe8 = 7;
  DAT_80093fb8[0xd6] = 4;
  puVar2[0xc2] = 0;
  puVar2[0xc3] = 0;
  puVar2[0xc6] = 0xffff;
  puVar2[199] = 0xffff;
  puVar2[0xcc] = 0;
  puVar2[0xcd] = 0;
  do {
    *puVar4 = 0;
    puVar2 = DAT_80093fb8;
    iVar3 = iVar3 + 1;
    puVar4 = puVar4 + 1;
  } while (iVar3 < 10);
  if (param_1 == 0) {
    DAT_80093fd0 = 0x200;
    DAT_80093fb8[200] = 0;
    puVar2[0xc9] = 0;
    puVar2[0xca] = 0;
    puVar2[0xcb] = 0;
    puVar2[0xd8] = 0;
    puVar2[0xd9] = 0;
    puVar2[0xda] = 0;
    puVar2[0xdb] = 0;
    FUN_800757d8(&DAT_80093ff8,0x10);
    iVar3 = 0;
    puVar2 = DAT_80093fb8;
    do {
      *puVar2 = 0;
      puVar2[1] = 0;
      puVar2[2] = 0x3fff;
      puVar2[3] = 0x200;
      puVar2[4] = 0;
      puVar2[5] = 0;
      puVar4 = DAT_80093fb8;
      iVar3 = iVar3 + 1;
      puVar2 = puVar2 + 8;
    } while (iVar3 < 0x18);
    DAT_80093fb8[0xc4] = 0xffff;
    puVar4[0xc5] = 0xff;
    FUN_80076030();
    FUN_80076030();
    FUN_80076030();
    FUN_80076030();
    puVar2 = DAT_80093fb8;
    DAT_80093fb8[0xc6] = 0xffff;
    puVar2[199] = 0xff;
    FUN_80076030();
    FUN_80076030();
    FUN_80076030();
    FUN_80076030();
  }
  DAT_80093fec = 1;
  DAT_80093fb8[0xd5] = 0xc000;
  DAT_80093ff0 = 0;
  DAT_80093ff4 = 0;
  return 0;
}

