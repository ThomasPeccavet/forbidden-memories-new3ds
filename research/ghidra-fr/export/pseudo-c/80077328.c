/* Analysis pseudo-C, not buildable source. */

int FUN_80077328(int param_1)

{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  
  iVar1 = DAT_80093fb8;
  if (((param_1 == 0) || (param_1 == 3)) &&
     (*(ushort *)(DAT_80093fb8 + 0x1aa) = *(ushort *)(DAT_80093fb8 + 0x1aa) & 0xffbf,
     (*(ushort *)(iVar1 + 0x1aa) & 0x40) != 0)) {
    uVar2 = 1;
    do {
      if (0xf00 < uVar2) {
        pcVar3 = s_wait__IRQ_ON__800119cc;
        goto LAB_8007741c;
      }
      uVar2 = uVar2 + 1;
    } while ((*(ushort *)(DAT_80093fb8 + 0x1aa) & 0x40) != 0);
  }
  iVar1 = DAT_80093fb8;
  if (((param_1 == 1) || (param_1 == 3)) &&
     (*(ushort *)(DAT_80093fb8 + 0x1aa) = *(ushort *)(DAT_80093fb8 + 0x1aa) | 0x40,
     (*(ushort *)(iVar1 + 0x1aa) & 0x40) == 0)) {
    uVar2 = 1;
    do {
      if (0xf00 < uVar2) {
        pcVar3 = s_wait__IRQ_OFF__800119dc;
LAB_8007741c:
        FUN_8008fa78(s_SPU_T_O___s__800119bc,pcVar3);
        return -1;
      }
      uVar2 = uVar2 + 1;
    } while ((*(ushort *)(DAT_80093fb8 + 0x1aa) & 0x40) == 0);
  }
  return param_1;
}

