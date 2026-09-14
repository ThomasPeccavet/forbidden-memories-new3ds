/* Analysis pseudo-C, not buildable source. */

void FUN_80039770(void)

{
  ushort uVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined *puVar6;
  int iVar7;
  
  puVar6 = &DAT_800f0850;
  iVar7 = 4;
  puVar5 = &DAT_800f0880;
  do {
    if ((*(ushort *)(puVar5 + 1) & 0x8000) != 0) {
      DAT_8009c6d6 = 0;
      iVar4 = -1;
      if ((*(ushort *)(puVar5 + 1) & 0x2000) == 0) {
        DAT_8009c6d6 = -1;
        do {
          while( true ) {
            FUN_800393b8(puVar6);
            uVar1 = *(ushort *)(puVar5 + 1);
            iVar4 = iVar4 + 1;
            if ((uVar1 & 0x2000) != 0) {
              if ((uVar1 & 0x10) != 0) {
                uVar2 = FUN_8003748c(puVar6);
                *puVar5 = uVar2;
              }
              goto LAB_8003988c;
            }
            if ((uVar1 & 0x1c00) == 0) break;
            DAT_8009c6d6 = -1;
          }
        } while (iVar4 < (int)(uint)DAT_8009c454);
      }
      else if (((*(ushort *)(puVar5 + 1) & 0x10) != 0) && ((DAT_8009c72c & 0xc0) != 0)) {
        *(ushort *)(puVar5 + 1) = *(ushort *)(puVar5 + 1) & 0xffef;
        FUN_80040690(*puVar5);
        *puVar5 = 0;
        FUN_80040204(0xb);
      }
LAB_8003988c:
      uVar3 = 0xffffffff;
      if (-1 < DAT_8009c6d6) {
        uVar3 = (ushort)(&DAT_801d9002)[DAT_8009c6d6 * 2] & 7;
        if (uVar3 == 4) {
          uVar3 = (uint)DAT_8009c6d9;
        }
        else {
          DAT_8009c6d9 = (byte)uVar3;
        }
      }
      FUN_8003b89c(uVar3);
      FUN_8003a0cc(puVar6);
    }
    puVar5 = puVar5 + 0x19;
    iVar7 = iVar7 + -1;
    puVar6 = puVar6 + 100;
    if (iVar7 == 0) {
      return;
    }
  } while( true );
}

