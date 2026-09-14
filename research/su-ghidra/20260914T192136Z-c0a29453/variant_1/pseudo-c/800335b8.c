/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_800335b8(int param_1)

{
  char cVar1;
  byte bVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  sVar3 = 0;
  if (*(short *)(param_1 + 0x2d3c) != 0 || *(char *)(param_1 + 0x2d48) != 0) {
    iVar5 = (int)*(short *)(param_1 + 0x2d42);
    iVar6 = ((int)*(short *)(param_1 + 0x2d3c) + (int)*(char *)(param_1 + 0x2d48) + 1) * 0xaf;
    sVar3 = (short)(iVar6 / iVar5);
    if (iVar5 == 0) {
      trap(0x1c00);
    }
    if ((iVar5 == -1) && (iVar6 == -0x80000000)) {
      trap(0x1800);
    }
  }
  *(short *)(*(int *)(param_1 + 0x2d38) + 0x32) = sVar3 + 0x2a;
LAB_8003363c:
  do {
    iVar6 = (int)*(short *)(param_1 + 0x2d3c);
    if (iVar6 != *(short *)(param_1 + 0x2d3e)) {
      sVar3 = *(short *)(param_1 + 0x2d3c) + -1;
      if (iVar6 <= *(short *)(param_1 + 0x2d3e)) {
        sVar3 = *(short *)(param_1 + 0x2d3c) + 1;
      }
      *(short *)(param_1 + 0x2d3c) = sVar3;
LAB_80033834:
      FUN_800321d8(param_1,9);
      return 1;
    }
    iVar5 = -1;
    if ((DAT_8009c710 & 0xc) != 0) {
      if ((DAT_8009c710 & 8) == 0) {
        if ((iVar6 == 0) && (*(char *)(param_1 + 0x2d48) != '\0')) {
          iVar5 = 0;
        }
        iVar7 = iVar6 + -9;
      }
      else {
        if ((iVar6 == *(short *)(param_1 + 0x2d40) + -9) && (*(char *)(param_1 + 0x2d48) != '\b')) {
          iVar5 = 8;
        }
        iVar4 = *(short *)(param_1 + 0x2d40) + -9;
        iVar7 = iVar6 + 9;
        if (iVar4 < iVar6 + 9) {
          iVar7 = iVar4;
        }
      }
      if (iVar7 < 0) {
        iVar7 = 0;
      }
      *(short *)(param_1 + 0x2d3e) = (short)iVar7;
      if (*(short *)(param_1 + 0x2d3c) == iVar7) {
LAB_80033730:
        if (iVar5 < 0) {
          return 1;
        }
        *(char *)(param_1 + 0x2d48) = (char)iVar5;
        *(short *)(*(int *)(param_1 + 0x2d34) + 0x32) = (short)iVar5 * 0x16 + 0x2b;
        FUN_80040204(6);
        return 1;
      }
      FUN_80040204(6);
      goto LAB_8003363c;
    }
    iVar5 = -1;
    if ((DAT_8009c728 & 3) != 0) {
      if ((DAT_8009c728 & 2) == 0) {
        if ((iVar6 == 0) && (*(char *)(param_1 + 0x2d48) != '\0')) {
          iVar5 = 0;
        }
        iVar7 = iVar6 + -0x32;
        if (iVar7 < 0) {
          iVar7 = 0;
        }
      }
      else {
        if ((iVar6 == *(short *)(param_1 + 0x2d40) + -9) && (*(char *)(param_1 + 0x2d48) != '\b')) {
          iVar5 = 8;
        }
        iVar4 = *(short *)(param_1 + 0x2d40) + -9;
        iVar7 = iVar6 + 0x32;
        if (iVar4 < iVar6 + 0x32) {
          iVar7 = iVar4;
        }
      }
      if (*(short *)(param_1 + 0x2d3c) != iVar7) {
        FUN_80040204(6);
        *(short *)(param_1 + 0x2d3e) = (short)iVar7;
        *(short *)(param_1 + 0x2d3c) = (short)iVar7;
        goto LAB_80033834;
      }
      goto LAB_80033730;
    }
    if ((DAT_8009c728 & 0x5000) == 0) {
      if ((DAT_8009c728 & 0x900) != 0) {
        if ((DAT_8009c728 & 0x800) == 0) {
          bVar2 = *(char *)(param_1 + 0x2d46) - 1;
          *(byte *)(param_1 + 0x2d46) = bVar2;
          if ((int)((uint)bVar2 << 0x18) < 0) {
            *(undefined1 *)(param_1 + 0x2d46) = 6;
          }
        }
        else {
          cVar1 = *(char *)(param_1 + 0x2d46) + '\x01';
          *(char *)(param_1 + 0x2d46) = cVar1;
          if ('\x06' < cVar1) {
            *(undefined1 *)(param_1 + 0x2d46) = 0;
          }
        }
        FUN_80040204(0x2f);
        *(byte *)(param_1 + 0x2d45) =
             (&DAT_80092215)
             [(uint)*(byte *)(param_1 + 0x2d47) * 0x10 + *(char *)(param_1 + 0x2d46) * 2] & 0xf;
        FUN_80033144();
        return 1;
      }
      return 0;
    }
    if ((DAT_8009c728 & 0x4000) == 0) {
      bVar2 = *(char *)(param_1 + 0x2d48) - 1;
      *(byte *)(param_1 + 0x2d48) = bVar2;
      if ((int)((uint)bVar2 << 0x18) < 0) {
        iVar6 = iVar6 + -1;
        *(undefined1 *)(param_1 + 0x2d48) = 0;
      }
    }
    else {
      cVar1 = *(char *)(param_1 + 0x2d48) + '\x01';
      *(char *)(param_1 + 0x2d48) = cVar1;
      if ('\b' < cVar1) {
        iVar6 = iVar6 + 1;
        *(undefined1 *)(param_1 + 0x2d48) = 8;
      }
    }
    *(short *)(*(int *)(param_1 + 0x2d34) + 0x32) = *(char *)(param_1 + 0x2d48) * 0x16 + 0x2b;
    if (*(short *)(param_1 + 0x2d40) + -9 < iVar6) {
      return 1;
    }
    if (iVar6 < 0) {
      return 1;
    }
    FUN_80040204(6);
    *(short *)(param_1 + 0x2d3e) = (short)iVar6;
    if (*(short *)(param_1 + 0x2d3c) == iVar6) {
      return 1;
    }
  } while( true );
}

