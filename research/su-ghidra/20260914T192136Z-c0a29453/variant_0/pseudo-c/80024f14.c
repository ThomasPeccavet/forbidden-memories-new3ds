/* Analysis pseudo-C, not buildable source. */

void FUN_80024f14(void)

{
  ushort uVar1;
  undefined4 uVar2;
  byte bVar3;
  undefined2 uVar4;
  int iVar5;
  undefined2 *puVar6;
  int *piVar7;
  
  iVar5 = FUN_80024ee0();
  bVar3 = DAT_8009c6f9;
  uVar2 = DAT_8009c4e8;
  if (iVar5 == 0) {
    *(char *)(DAT_8009c500 + 10) = *(char *)(DAT_8009c500 + 10) + '\x01';
    DAT_8009c6f9 = (char)DAT_8009c5c4 + 0xb7;
    uVar1 = (ushort)DAT_8009c6f9;
    DAT_8009c598 = FUN_8002c7d8(10);
    *(ushort *)(DAT_8009c598 + 0x1a) = uVar1 - 1;
    FUN_80040204(0x13);
  }
  else if ((DAT_8009c550 & 0x40) == 0) {
    if (*(char *)(DAT_8009c598 + 0x1d) != '\0') {
      DAT_8009c550 = DAT_8009c550 | 0x40;
      FUN_80014d38(0,0,(uint)DAT_8009c6f9 * 0xf0 + 0x1c58,0x10,0,0,0x1000280);
    }
  }
  else if ((DAT_8009c550 & 0x20) == 0) {
    if ((DAT_8009c460 & 0x2000030) == 0 && DAT_8009c484 == 0) {
      *(undefined2 *)(DAT_8009c598 + 0x1a) = 0xfffe;
      FUN_80040734(uVar2,bVar3);
      DAT_8009c550 = DAT_8009c550 | 0x20;
    }
  }
  else if ((*(byte *)(DAT_8009c598 + 0x1c) & 0x80) == 0) {
    piVar7 = &DAT_801a7ad8;
    iVar5 = 0;
    puVar6 = &DAT_801a7aec;
    do {
      if ((puVar6[1] & 0x8000) != 0) {
        uVar4 = FUN_80024a38(*(undefined1 *)(*piVar7 + 0x68));
        *puVar6 = uVar4;
      }
      iVar5 = iVar5 + 1;
      puVar6 = puVar6 + 0xe;
      piVar7 = piVar7 + 7;
    } while (iVar5 < 0x1e);
    DAT_8009c550 = 0;
  }
  return;
}

