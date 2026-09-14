/* Analysis pseudo-C, not buildable source. */

void FUN_8002c1ac(void)

{
  undefined1 *puVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  uint uVar4;
  short *psVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  DAT_8009c4c2 = 0;
  DAT_8009c4c0 = 0;
  FUN_80035b68(0);
  FUN_8002970c(0);
  iVar7 = 0x2d1;
  psVar5 = (short *)&LAB_801805a0_2;
  DAT_800eb498 = 0x100;
  DAT_800eb49a = 0x100;
  DAT_800eb49c = 0x280;
  DAT_800eb49e = 0xf0;
  do {
    *psVar5 = (short)iVar7 + 1;
    iVar7 = iVar7 + -1;
    psVar5 = psVar5 + -1;
  } while (-1 < iVar7);
  FUN_80014d38(0,0,0x233a,0x8f,FUN_8002be90,0,0);
  FUN_80013700();
  FUN_8002c11c();
  DAT_8009c8a4 = &LAB_8002a05c;
  FUN_80029728();
  DAT_800eb570 = 0;
  if (DAT_8009c5f0 < '\n') {
    DAT_800eb578 = ((short)DAT_8009c5f0 + ((short)DAT_8009c5f0 / 10) * -10) * 0xe + 0xe;
  }
  else {
    DAT_800eb578 = ((short)DAT_8009c5f0 + ((short)DAT_8009c5f0 / 10) * -10) * 0xe + 0xae;
  }
  DAT_800eb57a = DAT_8009c5f1 * 0x10 + ((short)DAT_8009c5f1 / 10) * 0x12 + 0xe;
  DAT_800eb582 = DAT_800eb578;
  DAT_800eb584 = DAT_800eb57a;
  FUN_8002a7f0(&DAT_800eb570);
  uVar3 = FUN_80040350();
  iVar7 = FUN_800403d0(uVar3,2);
  FUN_80040800(iVar7,0x10,0xe8,0,2,1,0x1b,0x127);
  *(undefined1 *)(iVar7 + 0x5f) = 0x80;
  FUN_80042c48(iVar7);
  iVar8 = 1;
  *(ushort *)(iVar7 + 8) = *(ushort *)(iVar7 + 8) | 8;
  DAT_800eb5b8 = iVar7;
  uVar3 = FUN_80040350();
  iVar7 = FUN_800403d0(uVar3,2);
  FUN_80040800(iVar7,(int)DAT_800eb578,(int)DAT_800eb57a,0,2,2,0x1b,0x147);
  iVar6 = 0;
  *(undefined1 *)(iVar7 + 0x5f) = 0x80;
  DAT_800eb5c6 = 0;
  puVar1 = &DAT_800eb570;
  DAT_800eb5b4 = iVar7;
  do {
    puVar1[0x5a] = 0;
    DAT_800eb5c4 = 0;
    uVar4 = *(int *)((int)&DAT_801d4244 + iVar6) >> 0x1a & 0x1f;
    if (uVar4 == 0x15) {
      uVar2 = 0x300;
LAB_8002c4c8:
      *(undefined2 *)(puVar1 + 0x58) = uVar2;
    }
    else {
      if (uVar4 < 0x16) {
        if (uVar4 != 0x14) {
          *(undefined2 *)(puVar1 + 0x58) = 0x2e0;
          goto LAB_8002c4cc;
        }
      }
      else {
        uVar2 = 0x310;
        if ((uVar4 == 0x16) || (uVar2 = 0x2e0, uVar4 != 0x17)) goto LAB_8002c4c8;
      }
      *(undefined2 *)(puVar1 + 0x58) = 0x2f0;
    }
LAB_8002c4cc:
    iVar8 = iVar8 + 1;
    iVar6 = iVar6 + 4;
    puVar1 = puVar1 + 4;
    if (0x2d2 < iVar8) {
      DAT_801bf88c = 0;
      iVar7 = 1;
      puVar1 = &DAT_800eb570;
      do {
        iVar6 = FUN_8002ce7c(iVar7 + 0x120);
        if (iVar6 != 0) {
          DAT_801bf88c = DAT_801bf88c + 1;
          puVar1[0x5a] = 0x80;
          iVar6 = FUN_8002c6ec(iVar7);
          if (iVar6 < 0) {
            puVar1[0x5a] = puVar1[0x5a] | 1;
          }
        }
        iVar7 = iVar7 + 1;
        puVar1 = puVar1 + 4;
      } while (iVar7 < 0x2d3);
      iVar7 = FUN_800361d8(3,0xf8,0x58,0xffffffe8,0x90,0x10,3);
      FUN_800399f0(iVar7);
      FUN_80042c6c(*(undefined4 *)(iVar7 + 0x28));
      *(ushort *)(*(int *)(iVar7 + 0x28) + 8) = *(ushort *)(*(int *)(iVar7 + 0x28) + 8) & 0xfff7;
      FUN_8002a484(&DAT_800eb570);
      FUN_8004022c(0x72d0);
      return;
    }
  } while( true );
}

