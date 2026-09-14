/* Analysis pseudo-C, not buildable source. */

void FUN_8003a8f0(int param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  undefined *puVar5;
  
  iVar2 = FUN_8003a2ac();
  if (iVar2 == 0) {
    iVar2 = 4;
    DAT_8009c6df = '\0';
    puVar5 = PTR_FUN_80010000 + 0x63040;
    do {
      iVar3 = (int)(char)(&DAT_8015c410)[iVar2];
      if (iVar3 < 0) {
        DAT_8009c6df = (char)iVar2;
        iVar3 = (int)(char)(&DAT_8015c410)[iVar2];
      }
      if (iVar3 == *(char *)(param_1 + 0x30)) {
        do {
          iVar2 = FUN_8008288c(10);
        } while (iVar2 != 0);
        bVar1 = *(byte *)(param_1 + 0x3c);
        *(undefined2 *)(puVar5 + 0x18c04) = 0xc0;
        *(undefined2 *)(puVar5 + 0x18c02) = 0x100;
        *(undefined2 *)(puVar5 + 0x18c06) = 0x100;
        *(ushort *)(puVar5 + 0x18c00) = (ushort)bVar1 * -0xc0 + 0x340;
        FUN_8007ff10(puVar5 + 0x18c00,puVar5);
        *(undefined2 *)(puVar5 + 0x18c08) = 0x280;
        bVar1 = *(byte *)(param_1 + 0x3c);
        *(undefined2 *)(puVar5 + 0x18c0c) = 0x100;
        *(undefined2 *)(puVar5 + 0x18c0e) = 2;
        *(ushort *)(puVar5 + 0x18c0a) = (ushort)bVar1 * 2 + 0xf0;
        FUN_8007ff10(puVar5 + 0x18c08);
        if (*(char *)(param_1 + 0x3c) == '\0') {
          puVar4 = &DAT_801af000;
        }
        else {
          puVar4 = &DAT_801af800;
        }
        FUN_80035ba0(puVar4,puVar5 + 0x18400,0x800);
        *(byte *)(param_1 + 0x33) = *(byte *)(param_1 + 0x33) | 0x40;
        return;
      }
      iVar2 = iVar2 + -1;
      puVar5 = puVar5 + -0x18c10;
    } while (-1 < iVar2);
    if ((DAT_8009c460 & 0x2000030) == 0 && DAT_8009c484 == 0) {
      iVar2 = FUN_80014e08(0,0,*(char *)(param_1 + 0x30) * 0x32 + 0x4361,0x32,FUN_8003a3ac,0,0);
      *(undefined **)(iVar2 + 0x38) = &DAT_801af000;
      *(uint *)(iVar2 + 0x3c) = (uint)*(byte *)(param_1 + 0x3c);
      if (*(char *)(param_1 + 0x3c) != '\0') {
        *(undefined **)(iVar2 + 0x38) = &DAT_801af800;
      }
      DAT_8009c460 = *(uint *)(iVar2 + 0x2c) | 0x10;
    }
    else {
      *(byte *)(param_1 + 0x33) = *(byte *)(param_1 + 0x33) & 0x7f;
    }
  }
  else if ((*(byte *)(param_1 + 0x33) & 0x40) == 0) {
    if ((DAT_8009c460 & 0x2000030) == 0 && DAT_8009c484 == 0) {
      *(byte *)(param_1 + 0x33) = *(byte *)(param_1 + 0x33) | 0x40;
      (&DAT_8015c410)[DAT_8009c6df] = *(undefined1 *)(param_1 + 0x30);
      do {
        iVar2 = FUN_8008288c(10);
      } while (iVar2 != 0);
      puVar5 = PTR_FUN_80010000 + DAT_8009c6df * 0x18c10;
      bVar1 = *(byte *)(param_1 + 0x3c);
      *(undefined2 *)(puVar5 + 0x18c02) = 0x100;
      *(undefined2 *)(puVar5 + 0x18c06) = 0x100;
      *(ushort *)(puVar5 + 0x18c00) = (ushort)bVar1 * -0xc0 + 0x340;
      *(undefined2 *)(puVar5 + 0x18c04) = 0xc0;
      FUN_8007ff70(puVar5 + 0x18c00,puVar5);
      *(undefined2 *)(puVar5 + 0x18c08) = 0x280;
      bVar1 = *(byte *)(param_1 + 0x3c);
      *(undefined2 *)(puVar5 + 0x18c0c) = 0x100;
      *(undefined2 *)(puVar5 + 0x18c0e) = 2;
      *(ushort *)(puVar5 + 0x18c0a) = (ushort)bVar1 * 2 + 0xf0;
      FUN_8007ff70(puVar5 + 0x18c08);
      if (*(char *)(param_1 + 0x3c) == '\0') {
        puVar4 = &DAT_801af000;
      }
      else {
        puVar4 = &DAT_801af800;
      }
      FUN_80035ba0(puVar5 + 0x18400,puVar4,0x800);
    }
  }
  else {
    FUN_8003a57c(param_1,param_1,*(undefined1 *)(param_1 + 0x31));
    *(undefined1 *)(param_1 + 0x33) = 0;
    *(byte *)(param_1 + 0x32) = *(byte *)(param_1 + 0x32) | 0x40;
  }
  return;
}

