/* Analysis pseudo-C, not buildable source. */

void FUN_80059294(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  
  iVar1 = param_1 * 0xe20;
  puVar4 = &DAT_800f4178 + iVar1;
  FUN_8004d954(puVar4,0,0x388);
  iVar2 = 3;
  iVar3 = iVar1 + -0x7ff0be85;
  *(undefined4 *)(&DAT_800f4f20 + iVar1) = 0x800;
  *(undefined4 *)(&DAT_800f4f1c + iVar1) = 0x800;
  *(undefined4 *)(&DAT_800f4f18 + iVar1) = 0x800;
  *(undefined1 *)((int)&DAT_800f4f38 + iVar1 + 2) = 0x80;
  *(undefined1 *)((int)&DAT_800f4f38 + iVar1 + 1) = 0x80;
  *(undefined1 *)(&DAT_800f4f38 + param_1 * 0x388) = 0x80;
  *(undefined1 *)(&DAT_800f4f84 + param_1 * 0x388) = 7;
  *(undefined1 *)((int)&DAT_800f4f84 + iVar1 + 1) = 8;
  (&DAT_800f4f8c)[iVar1] = 0xff;
  *(undefined4 *)(&DAT_800f4f30 + iVar1) = 0x1000;
  *(undefined4 *)(&DAT_800f4f2c + iVar1) = 0x1000;
  *(undefined4 *)(&DAT_800f4f28 + iVar1) = 0x1000;
  *(undefined1 *)((int)&DAT_800f4f38 + iVar1 + 3) = 0;
  *(undefined2 *)(&DAT_800f4f82 + iVar1) = 0x1000;
  (&DAT_800f4f95)[iVar1] = 0;
  (&DAT_800f4f76)[iVar1] = (char)param_1;
  (&DAT_800f4f77)[iVar1] = 0;
  *(undefined2 *)(&DAT_800f4f74 + iVar1) = 0xffff;
  *(undefined2 *)(&DAT_800f4f72 + iVar1) = 0xffff;
  do {
    *(undefined1 *)(iVar3 + 0xbf4) = 1;
    iVar2 = iVar2 + -1;
    iVar3 = iVar3 + -1;
  } while (-1 < iVar2);
  iVar2 = 0;
  do {
    iVar2 = iVar2 + 1;
    *(uint *)(puVar4 + 0xbf8) = *(uint *)(puVar4 + 0xbf8) & 0x8000ffff;
    puVar4[0xbf9] = 0;
    puVar4[0xbf8] = 0;
    puVar4 = puVar4 + 4;
  } while (iVar2 < 0x40);
  (&DAT_800f4e80)[param_1 * 0x388] = 0xffffffff;
  (&DAT_800f4e84)[param_1 * 0x388] = 0xffffffff;
  (&DAT_800f4e88)[param_1 * 0x388] = 0xffffffff;
  (&DAT_800f4f8e)[iVar1] = 0x3e;
  (&DAT_800f4f97)[iVar1] = 0;
  FUN_8005c23c(param_1);
  return;
}

