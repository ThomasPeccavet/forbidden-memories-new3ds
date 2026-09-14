/* Analysis pseudo-C, not buildable source. */

void FUN_8003b3e4(int *param_1)

{
  undefined2 uVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  short sVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  iVar3 = FUN_8003a2ac();
  if (iVar3 == 0) {
    if ((short)param_1[0x10] == 0) {
      iVar3 = param_1[0xc];
      iVar6 = (char)iVar3 + -0x41;
      uVar4 = FUN_80040350();
      iVar7 = FUN_800403d0(uVar4,1);
      FUN_80040844(iVar7,(int)(short)param_1[0xd],(int)*(short *)((int)param_1 + 0x36),0x30,0x30,0,0
                   ,0xe,0x380,0xf0);
      *(short *)(iVar7 + 0x40) = *(short *)(iVar7 + 0x40) + (short)(iVar6 >> 4) * 0x40;
      cVar2 = (char)(iVar6 / 5);
      *(char *)(iVar7 + 0x5c) = ((char)iVar6 + cVar2 * -5) * '0';
      *(char *)(iVar7 + 0x5d) = cVar2 * '0';
      iVar8 = iVar6;
      if (iVar6 < 0) {
        iVar8 = (char)iVar3 + -0x32;
      }
      *(undefined2 *)(iVar7 + 0x46) = 0;
      *(undefined4 *)(iVar7 + 0xc) = 0;
      *(short *)(iVar7 + 0x42) =
           *(short *)(iVar7 + 0x42) + (short)iVar6 + (short)(iVar8 >> 4) * -0x10;
      *(uint *)(iVar7 + 4) = *(uint *)(iVar7 + 4) | 0x51000000;
      FUN_80042c48(iVar7);
      FUN_80042c1c(iVar7,0xfffffff8);
      *param_1 = iVar7;
      *(undefined2 *)(iVar7 + 0x60) = 0x14;
    }
    else {
      iVar7 = *param_1;
      *(undefined2 *)(iVar7 + 0x60) = 0;
    }
    *(undefined2 *)(iVar7 + 0x4a) = 0;
    *(uint *)(iVar7 + 4) = *(uint *)(iVar7 + 4) & 0xf7ffffff | 0x50000000;
    uVar4 = FUN_80040350();
    iVar3 = FUN_800403d0(uVar4,1);
    FUN_80040844(iVar3,(int)*(short *)(iVar7 + 0x30),(int)*(short *)(iVar7 + 0x32),0x30,0x30,
                 *(undefined1 *)(iVar7 + 0x5c),*(undefined1 *)(iVar7 + 0x5d),0xe,0x280,0xfd);
    *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) & 0xf7ffffff | 0x61000000;
    uVar1 = *(undefined2 *)(iVar7 + 0x46);
    *(undefined2 *)(iVar3 + 0x4a) = 0;
    *(undefined2 *)(iVar3 + 0x46) = uVar1;
    FUN_80042c48(iVar3);
    FUN_80042c1c(iVar3,0xfffffff7);
    param_1[1] = iVar3;
  }
  iVar3 = *param_1;
  iVar8 = param_1[1];
  if ((short)param_1[0x10] == 0) {
    sVar5 = *(short *)(iVar3 + 0x60) - DAT_8009c43c;
  }
  else {
    sVar5 = *(short *)(iVar3 + 0x60) + DAT_8009c43c;
  }
  *(short *)(iVar3 + 0x60) = sVar5;
  sVar5 = *(short *)(iVar3 + 0x60);
  if (sVar5 < 1) {
    *(undefined4 *)(iVar3 + 0xc) = 0x808080;
    *(undefined2 *)(iVar3 + 0x46) = 0x1000;
    *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) & 0x8fffffff | 0x8000000;
    FUN_80040690(iVar8);
    param_1[1] = 0;
  }
  else {
    if (sVar5 < 0x14) {
      cVar2 = (char)sVar5 * -6 + -0x80;
      *(char *)(iVar8 + 0xe) = cVar2;
      *(char *)(iVar8 + 0xd) = cVar2;
      *(char *)(iVar8 + 0xc) = cVar2;
      *(char *)(iVar3 + 0xe) = cVar2;
      *(char *)(iVar3 + 0xd) = cVar2;
      *(char *)(iVar3 + 0xc) = cVar2;
      sVar5 = *(short *)(iVar3 + 0x60) * 0xcc + 0x1000;
      *(short *)(iVar8 + 0x46) = sVar5;
      *(short *)(iVar3 + 0x46) = sVar5;
      sVar5 = (ushort)*(byte *)(iVar3 + 0xc) << 5;
      *(short *)(iVar8 + 0x44) = sVar5;
      *(short *)(iVar3 + 0x44) = sVar5;
      return;
    }
    FUN_8003a364(param_1);
  }
  *(undefined1 *)((int)param_1 + 0x33) = 0;
  return;
}

