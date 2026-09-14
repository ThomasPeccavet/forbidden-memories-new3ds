/* Analysis pseudo-C, not buildable source. */

void FUN_800393b8(undefined4 *param_1)

{
  bool bVar1;
  char cVar2;
  ushort uVar3;
  int iVar4;
  undefined *puVar5;
  byte *pbVar6;
  uint uVar7;
  
  uVar3 = *(ushort *)(param_1 + 0xd);
  if ((uVar3 & 0x4000) != 0) {
    if (DAT_8009c6d2 != '\0') {
      (*(code *)(&PTR_FUN_80092068)[(byte)DAT_8009c610])();
      if (DAT_8009c610 == 0) {
        DAT_8009c6d2 = '\0';
      }
    }
    if (*(byte *)((int)param_1 + 0x51) == 0) {
      if ((*(ushort *)(param_1 + 0xd) & 0x1c00) == 0) {
        if (((DAT_8009c710 & 0x80) != 0) || ((DAT_8009c72c & 0xc0) != 0)) {
          FUN_80037354(param_1,0,0);
          *(undefined1 *)((int)param_1 + 0x52) = 1;
          *(ushort *)(param_1 + 0xd) = *(ushort *)(param_1 + 0xd) | 0x400;
        }
        cVar2 = *(char *)((int)param_1 + 0x52) + -1;
        *(char *)((int)param_1 + 0x52) = cVar2;
        if (cVar2 != '\0') {
          return;
        }
      }
      *(undefined1 *)((int)param_1 + 0x52) = *(undefined1 *)((int)param_1 + 0x53);
      while( true ) {
        pbVar6 = (byte *)param_1[*(char *)(param_1 + 0x16)];
        DAT_8009c6da = (ushort)*pbVar6;
        bVar1 = DAT_8009c6da < 0xf0;
        param_1[*(char *)(param_1 + 0x16)] = pbVar6 + 1;
        if (bVar1) break;
        DAT_8009c6cc = 0;
        (**(code **)(&DAT_80091f6c + ((int)((uint)DAT_8009c6da << 0x10) >> 0xe)))(param_1);
        if (DAT_8009c6cc < 0) break;
        if (DAT_8009c6cc == 1) {
          return;
        }
      }
      iVar4 = FUN_80037c0c(param_1);
      if (iVar4 != 0) {
        *(undefined1 *)((int)param_1 + 0x51) = 4;
        return;
      }
      DAT_8009c6d6 = DAT_8009c6da;
      iVar4 = FUN_80036c64(param_1,*(uint *)(&DAT_801d9000 +
                                            ((int)((uint)DAT_8009c6da << 0x10) >> 0xe)) & 0x8ff0ffff
                          );
      iVar4 = (uint)*(byte *)((int)param_1 + 0x5a) + iVar4;
      *(short *)(param_1 + 0xe) = *(short *)(param_1 + 0xe) + (short)iVar4;
      iVar4 = (uint)*(ushort *)(param_1 + 0x18) + iVar4;
      *(short *)(param_1 + 0x18) = (short)iVar4;
      if (*(short *)((int)param_1 + 0x62) == 0) {
        return;
      }
      if ((int)((iVar4 * 0x10000 >> 0x10) + (uint)*(byte *)((int)param_1 + 0x5a)) <=
          (int)*(short *)((int)param_1 + 0x62)) {
        return;
      }
      uVar3 = *(ushort *)(param_1 + 0xd) | 0x2000;
    }
    else {
      (*(code *)(&PTR_FUN_80092270)[*(byte *)((int)param_1 + 0x51) & 0x1f])(param_1);
      uVar3 = *(ushort *)(param_1 + 0xd) & 0xfbff;
    }
    *(ushort *)(param_1 + 0xd) = uVar3;
    return;
  }
  *(ushort *)(param_1 + 0xd) = uVar3 | 0x4000;
  if ((uVar3 & 4) == 0) {
    FUN_8003a22c();
  }
  uVar7 = (uint)*(ushort *)((int)param_1 + 0x36);
  DAT_8009c6d2 = 0;
  DAT_8009c6bc = 0;
  *(undefined1 *)((int)param_1 + 0x52) = 1;
  *(undefined2 *)(param_1 + 0x18) = 0;
  *(undefined1 *)(param_1 + 0x16) = 0;
  if (uVar7 < 0x8000) {
    if (0x4ff < uVar7) {
      puVar5 = &DAT_801c0000 + *(ushort *)(&DAT_801b0004 + (uVar7 - 0x100) * 2);
      goto LAB_80039494;
    }
    puVar5 = &DAT_801b0004;
    iVar4 = uVar7 << 1;
  }
  else {
    puVar5 = &DAT_801d5804;
    iVar4 = (uVar7 - 0x8000) * 2;
  }
  puVar5 = (undefined *)(((uint)puVar5 & 0xffff0000) + (uint)*(ushort *)(puVar5 + iVar4));
LAB_80039494:
  *param_1 = puVar5;
  *(undefined1 *)((int)param_1 + 0x56) = 0;
  *(undefined1 *)((int)param_1 + 0x51) = 0;
  FUN_80040690(param_1[0xc]);
  FUN_80040690(param_1[0xb]);
  param_1[0xc] = 0;
  param_1[0xb] = 0;
  FUN_800391ec(param_1);
  if ((*(ushort *)(param_1 + 0xd) & 0x80) == 0) {
    param_1[9] = &DAT_800ec390 + (uint)*(ushort *)(param_1 + 0x17) * 0x16;
    param_1[8] = &DAT_800ec390 + (uint)*(ushort *)(param_1 + 0x17) * 0x16;
    FUN_80036238(*(undefined1 *)((int)param_1 + 0x57));
  }
  return;
}

