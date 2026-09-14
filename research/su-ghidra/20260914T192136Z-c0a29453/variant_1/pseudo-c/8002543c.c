/* Analysis pseudo-C, not buildable source. */

void FUN_8002543c(void)

{
  byte bVar1;
  undefined2 uVar2;
  int iVar3;
  undefined2 *puVar4;
  uint uVar5;
  int *piVar6;
  
  iVar3 = FUN_80024ee0();
  if (iVar3 == 0) {
    puVar4 = (undefined2 *)FUN_8002c860(0xf);
    *puVar4 = 0;
    puVar4[1] = 0;
    puVar4[2] = 0;
    FUN_80040204(0x22);
    iVar3 = 0;
    while ((byte)(&DAT_80091e64)[iVar3] + 600 != (int)DAT_8009c5c4) {
      iVar3 = iVar3 + 2;
    }
    puVar4[0xd] = (short)(iVar3 / 2);
    bVar1 = *(byte *)(iVar3 + -0x7ff6e19b);
    DAT_8009c5a8 = (ushort)bVar1;
    if (0x14 < bVar1) {
      DAT_8009c5a8 = ((ushort)bVar1 * 4 + (ushort)bVar1) * 2;
      DAT_8009c550 = DAT_8009c550 | 1;
    }
    DAT_8009c5aa = 5;
  }
  else {
    do {
      if (((&DAT_801a7aee)
           [(uint)(byte)(&DAT_800919e0)[(int)DAT_8009c5aa + (uint)DAT_8009c504 * 0x14] * 0xe] &
          0x8000) != 0) {
        if ((DAT_8009c550 & 1) == 0) {
          if (*(byte *)((&DAT_801a7ad8)
                        [(uint)(byte)(&DAT_800919e0)[(int)DAT_8009c5aa + (uint)DAT_8009c504 * 0x14]
                         * 7] + 0x68) == DAT_8009c5a8) {
LAB_800255ec:
            piVar6 = &DAT_801a7ad8 +
                     (uint)(byte)(&DAT_800919e0)[(int)DAT_8009c5aa + (uint)DAT_8009c504 * 0x14] * 7;
            puVar4 = (undefined2 *)FUN_8002c860(0xb);
            *puVar4 = *(undefined2 *)(*piVar6 + 0x30);
            puVar4[1] = *(undefined2 *)(*piVar6 + 0x32);
            puVar4[2] = *(undefined2 *)(*piVar6 + 0x34);
            uVar2 = FUN_8001817c(*piVar6);
            puVar4[0xd] = uVar2;
            FUN_80024a10(piVar6);
            FUN_80040204(0x1f);
            return;
          }
        }
        else {
          uVar5 = FUN_80016fe4(&DAT_801a7ad8 +
                               (uint)(byte)(&DAT_800919e0)
                                           [(int)DAT_8009c5aa + (uint)DAT_8009c504 * 0x14] * 7);
          if ((int)(short)DAT_8009c5a8 <= (int)(uVar5 & 0xffff)) goto LAB_800255ec;
        }
      }
      DAT_8009c5aa = DAT_8009c5aa + 1;
    } while (DAT_8009c5aa < 10);
    DAT_8009c550 = 0;
  }
  return;
}

