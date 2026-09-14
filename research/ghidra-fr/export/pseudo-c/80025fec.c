/* Analysis pseudo-C, not buildable source. */

void FUN_80025fec(void)

{
  byte bVar1;
  int iVar2;
  undefined2 *puVar3;
  int iVar4;
  
  iVar2 = FUN_80024ee0();
  if (iVar2 == 0) {
    puVar3 = (undefined2 *)FUN_8002c7d8(0x15);
    DAT_8009c598 = puVar3;
    *(undefined2 **)(&DAT_8009c4d0 + (DAT_8009c504 ^ 1) * 4) = puVar3;
    *puVar3 = 0xa0;
    *(byte *)(puVar3 + 0xe) = *(byte *)(puVar3 + 0xe) | 0x20;
    bVar1 = DAT_8009c504;
    puVar3[1] = 0x78;
    puVar3[0xd] = bVar1 ^ 1;
    FUN_80040204(0x23);
  }
  else if ((DAT_8009c550 & 0x40) == 0) {
    if (*(char *)((int)DAT_8009c598 + 0x1d) != '\0') {
      iVar2 = 5;
      DAT_8009c550 = DAT_8009c550 | 0x40;
      do {
        if ((*(uint *)(&DAT_801a7aec +
                      (uint)(byte)(&DAT_800919e0)[iVar2 + (uint)DAT_8009c504 * 0x14] * 0xe) &
            0x90000000) == 0x90000000) {
          iVar4 = (&DAT_801a7ad8)
                  [(uint)(byte)(&DAT_800919e0)[iVar2 + (uint)DAT_8009c504 * 0x14] * 7];
          *(code **)(iVar4 + 0x24) = FUN_80025bd8;
          *(undefined1 *)(iVar4 + 0x6c) = 1;
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 < 10);
    }
  }
  else {
    iVar2 = FUN_80042e70(1);
    if ((iVar2 == 0) && (1 < *(byte *)((int)DAT_8009c598 + 0x1d))) {
      (&DAT_800eb291)[(DAT_8009c504 ^ 1) * 0x20] = 4;
      DAT_8009c550 = 0;
    }
  }
  return;
}

