/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_8004fc2c(int param_1,int param_2,int param_3,uint param_4)

{
  byte bVar1;
  undefined2 uVar2;
  short sVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  uint uVar9;
  int *piVar10;
  int iVar11;
  int *piVar12;
  undefined4 uVar13;
  uint local_38;
  undefined4 *local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  iVar4 = param_1 * 0xe20;
  piVar10 = (int *)(&DAT_800f4178 + iVar4);
  uVar13 = DAT_8009c864;
  if (param_1 < 2) {
    uVar13 = DAT_8009c860;
  }
  local_2c = 0;
  local_30 = 0;
  (&DAT_800f4f8b)[iVar4] = 0;
  (&DAT_800f4f8a)[iVar4] = 0;
  if (-1 < (int)param_4) {
    (&DAT_800f4f89)[iVar4] = (byte)param_4 & 0x7f;
    if ((param_4 & 0x80) == 0) {
      (&DAT_800f4f3f)[iVar4] = 0;
    }
    else {
      (&DAT_800f4f3f)[iVar4] = 5;
    }
  }
  (&DAT_800f4f3e)[iVar4] = 0;
  (&DAT_800f4f3d)[iVar4] = 0;
  (&DAT_800f4f3c)[iVar4] = 0;
  (&DAT_800f4f40)[param_1 * 0x710] = 0;
  (&DAT_800f4f42)[param_1 * 0x710] = 0;
  (&DAT_800f4f44)[param_1 * 0x710] = 0;
  (&DAT_800f4f46)[param_1 * 0x710] = 0;
  (&DAT_800f4f48)[param_1 * 0x710] = 0;
  *(undefined2 *)(&DAT_800f4f4e + iVar4) = 0xfea2;
  (&DAT_800f4f4a)[param_1 * 0x710] = 0xfea2;
  if (param_1 == 0) {
    uVar2 = 0x1c2;
LAB_8004fd28:
    (&DAT_800f4f4c)[param_1 * 0x710] = uVar2;
  }
  else {
    uVar2 = 0xfe3e;
    if (param_1 == 1) goto LAB_8004fd28;
    (&DAT_800f4f4c)[param_1 * 0x710] = 0;
  }
  *(undefined1 *)((int)&DAT_800f4f84 + iVar4 + 2) = 6;
  *(undefined1 *)((int)&DAT_800f4f84 + iVar4 + 3) = 0;
  (&DAT_800f4f88)[iVar4] = 0;
  (&DAT_800f4f8f)[iVar4] = 0;
  (&DAT_800f4f90)[iVar4] = 0;
  (&DAT_800f4e90)[param_1 * 0x388] = 0;
  *(undefined4 *)(&DAT_800f4e8c + iVar4) = 0;
  *(undefined4 *)(&DAT_800f4e94 + iVar4) = 0;
  (&DAT_800f4f91)[iVar4] = 0;
  (&DAT_800f4f93)[iVar4] = 0;
  (&DAT_800f4f94)[iVar4] = 0;
  *(undefined4 *)(&DAT_800f4f60 + iVar4) = 0;
  (&DAT_800f4f64)[param_1 * 0x388] = (undefined *)0x0;
  if (param_1 < 2) {
    if (param_1 == 0) {
      _DAT_800f4f60 = PTR_DAT_8001001c;
      DAT_800f4f64 = PTR_DAT_80010024;
    }
    else {
      *(undefined **)(&DAT_800f4f60 + iVar4) = PTR_DAT_80010020;
      (&DAT_800f4f64)[param_1 * 0x388] = PTR_DAT_80010028;
    }
  }
  *(undefined4 *)(&DAT_800f4f68 + iVar4) = 0;
  *(undefined2 *)(&DAT_800f4f78 + iVar4) = 0;
  *(undefined2 *)(&DAT_800f4f7a + iVar4) = 0;
  *(undefined2 *)(&DAT_800f4f7c + iVar4) = 0;
  *(undefined4 *)(&DAT_800f4f6c + iVar4) = 0;
  (&DAT_800f4f8d)[iVar4] = 0;
  (&DAT_800f4f96)[iVar4] = 0;
  (&DAT_800f4f97)[iVar4] = 0;
  if (param_2 == 0) {
    (&DAT_800f4f95)[iVar4] = 0;
    (&DAT_800f4f8c)[iVar4] = 0xff;
    return;
  }
  FUN_8008a208(param_2);
  FUN_800506e0(param_1,param_2);
  bVar1 = *(byte *)(param_2 + 0xc);
  (&DAT_800f4f92)[iVar4] = bVar1;
  piVar12 = (int *)(param_2 + 0x10);
  if (0x3c < bVar1) {
    (&DAT_800f4f92)[iVar4] = 0x3c;
  }
  iVar11 = 0;
  if ((&DAT_800f4f92)[iVar4] != '\0') {
    piVar7 = piVar10;
    do {
      *piVar7 = 0;
      iVar8 = *piVar12;
      piVar12 = piVar12 + 1;
      piVar7[1] = iVar8;
      if (iVar8 != 0) {
        FUN_80089f08(iVar8,0,0,0);
        while (iVar8 = FUN_80089f08(0,&local_38,uVar13,0x1f800000), iVar8 != 0) {
          uVar9 = local_38 >> 0x18;
          if (local_38 != 0) {
            if (((uVar9 < 2) || ((uVar9 < 7 && (4 < uVar9)))) && ((local_38 & 0x800000) != 0)) {
              uVar5 = FUN_8008a3a8(param_2,local_34);
              *(undefined4 *)(&DAT_800f4e8c + iVar4) = uVar5;
              local_38 = local_38 & 0xff7fffff;
            }
            if (uVar9 == 1) {
              sVar3 = FUN_80050254(param_1,&local_38,0x1f800000,0,&local_2c);
              *(short *)(&DAT_800f4f7c + iVar4) = *(short *)(&DAT_800f4f7c + iVar4) + sVar3;
              FUN_8005f7d4(&local_38);
            }
            else if (uVar9 == 0) {
              sVar3 = FUN_80050254(param_1,&local_38,0x1f800000,&local_30,&local_2c);
              *(short *)(&DAT_800f4f7c + iVar4) = *(short *)(&DAT_800f4f7c + iVar4) + sVar3;
              FUN_8005f530(&local_38);
            }
            else if (uVar9 == 2) {
              FUN_8005ee7c(param_1,&local_38,0x1f800000);
            }
            else if (uVar9 == 3) {
              FUN_8005db58(&local_38,piVar10);
            }
            else {
              *local_34 = &LAB_80089da8;
            }
          }
        }
      }
      iVar11 = iVar11 + 1;
      piVar7 = piVar7 + 2;
    } while (iVar11 < (int)(uint)(byte)(&DAT_800f4f92)[iVar4]);
  }
  iVar11 = 1;
  *(undefined2 *)(&DAT_800f4f78 + iVar4) = (undefined2)local_2c;
  *(short *)(&DAT_800f4f7a + iVar4) = (short)local_30 + 1;
  if (1 < (int)((byte)(&DAT_800f4f92)[iVar4] - 1)) {
    iVar8 = 0;
    piVar12 = piVar10;
    do {
      (&DAT_800f4f8f)[iVar4] = (&DAT_800f4f8f)[iVar4] + '\x01';
      if (piVar12[3] != 0) {
        piVar12[2] = *(int *)(&DAT_800f4e8c + iVar4) + iVar8;
      }
      iVar8 = iVar8 + 0x50;
      iVar11 = iVar11 + 1;
      piVar12 = piVar12 + 2;
    } while (iVar11 < (int)((byte)(&DAT_800f4f92)[iVar4] - 1));
  }
  iVar11 = *(int *)(&DAT_800f4e8c + iVar4);
  if (iVar11 != 0) {
    iVar8 = 0;
    iVar6 = *(int *)(iVar11 + 0x4c);
    while (iVar6 != 0) {
      iVar8 = iVar8 + 1;
      iVar6 = *(int *)(iVar11 + 0x9c);
      iVar11 = iVar11 + 0x50;
    }
    (&DAT_800f4f90)[iVar4] = (char)iVar8;
    (&DAT_800f4e90)[param_1 * 0x388] = *(int *)(&DAT_800f4e8c + iVar4) + iVar8 * 0x50;
    bVar1 = FUN_8005d4d8(piVar10);
    (&DAT_800f4f91)[iVar4] = bVar1;
    if ((byte)(&DAT_800f4f8f)[iVar4] <= bVar1) {
      (&DAT_800f4f91)[iVar4] = (&DAT_800f4f90)[iVar4];
    }
    iVar11 = *(int *)(&DAT_800f4e8c + iVar4) + (uint)(byte)(&DAT_800f4f91)[iVar4] * 0x50;
    *(int *)(&DAT_800f4e94 + iVar4) = iVar11;
    do {
      iVar8 = 0;
      piVar12 = piVar10;
      if ((byte)(&DAT_800f4f92)[iVar4] != 0) {
        do {
          if ((((*piVar12 != 0) && (piVar7 = (int *)piVar12[1], piVar7 != (int *)0x0)) &&
              ((*piVar7 != -1 || (piVar7[2] != 0)))) && (*(int *)(*piVar12 + 0x4c) == iVar11))
          break;
          iVar8 = iVar8 + 1;
          piVar12 = piVar12 + 2;
        } while (iVar8 < (int)(uint)(byte)(&DAT_800f4f92)[iVar4]);
        if (iVar8 < (int)(uint)(byte)(&DAT_800f4f92)[iVar4]) goto LAB_800501ac;
      }
      iVar8 = FUN_8005d4d8(piVar10,iVar11);
      if ((int)(uint)(byte)(&DAT_800f4f8f)[iVar4] <= iVar8) goto LAB_800501ac;
      iVar11 = *(int *)(&DAT_800f4e8c + iVar4) + iVar8 * 0x50;
    } while( true );
  }
LAB_80050200:
  if (*(int *)(&DAT_800f4f58 + iVar4) == 0) {
    *(int *)(&DAT_800f4f58 + iVar4) = param_2 + param_3;
  }
  return;
LAB_800501ac:
  iVar11 = *(int *)(iVar11 + 0x4c);
  if ((iVar11 != (&DAT_800f4e90)[param_1 * 0x388]) &&
     (*(int *)(&DAT_800f4e94 + iVar4) = iVar11, iVar11 != 0)) {
    (&DAT_800f4f91)[iVar4] = (char)((iVar11 - *(int *)(&DAT_800f4e8c + iVar4)) * -0x33333333 >> 4);
  }
  goto LAB_80050200;
}

