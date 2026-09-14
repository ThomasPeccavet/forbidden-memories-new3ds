/* Analysis pseudo-C, not buildable source. */

void FUN_80048740(ushort param_1,short param_2,undefined1 param_3,short param_4,uint param_5,
                 byte param_6)

{
  ushort uVar1;
  bool bVar2;
  uint uVar3;
  byte bVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  short local_38;
  undefined1 local_36;
  short local_30;
  
  if (*(short *)((uint)param_1 * 2 + *(int *)(DAT_8009c7e0 + 0x43c)) != -1) {
    local_36 = param_3;
    local_30 = param_4;
    if ((param_1 & 0x8000) == 0) {
      bVar2 = false;
      if (((param_5 & 0xf) != 0) && (uVar3 = FUN_800483c8(), uVar3 != 0)) {
        bVar4 = 0;
        do {
          if ((uVar3 & 1) != 0) {
            *(byte *)(DAT_8009c7e0 + 0x435) = bVar4;
            goto LAB_800487f4;
          }
          bVar4 = bVar4 + 1;
          uVar3 = (int)uVar3 >> 1;
        } while (bVar4 < 4);
      }
      bVar4 = 0;
      if ((param_5 & 0xf0) != 0) {
        bVar5 = 0;
        iVar6 = 0;
        do {
          FUN_800781e8(iVar6 + 0x14,&local_38);
          if (((local_38 != 0) &&
              (uVar1 = *(ushort *)(DAT_8009c7e0 + (uint)bVar4 * 2 + 0x404), uVar1 == param_1)) &&
             (bVar5 = bVar5 + 1, (uint)bVar5 == (param_5 & 0xf0) >> 4)) {
            *(byte *)(DAT_8009c7e0 + 0x435) = bVar4;
            param_1 = uVar1;
LAB_800487f4:
            FUN_800484cc(param_1,*(undefined1 *)(DAT_8009c7e0 + 0x435),(int)param_2,local_36,
                         (int)local_30,param_5 & 0xff,param_6);
            return;
          }
          iVar6 = iVar6 + 1;
          bVar4 = bVar4 + 1;
        } while (iVar6 < 4);
      }
      uVar3 = 1 << (*(byte *)(DAT_8009c7e0 + 0x435) & 0x1f);
      iVar7 = 0;
      iVar6 = (int)local_30;
      do {
        FUN_800781e8(*(byte *)(DAT_8009c7e0 + 0x435) + 0x14,&local_38);
        if (local_38 == 0) {
          bVar2 = true;
          FUN_800484cc(param_1,*(undefined1 *)(DAT_8009c7e0 + 0x435),(int)param_2,local_36,iVar6,
                       param_5 & 0xff,param_6);
        }
        uVar3 = uVar3 << 1;
        if ((uVar3 & 0x10) != 0) {
          uVar3 = 1;
        }
        *(char *)(DAT_8009c7e0 + 0x435) = *(char *)(DAT_8009c7e0 + 0x435) + '\x01';
        iVar7 = iVar7 + 1;
        *(byte *)(DAT_8009c7e0 + 0x435) = *(byte *)(DAT_8009c7e0 + 0x435) & 3;
      } while ((iVar7 < 4) && (!bVar2));
      iVar6 = 0;
      if (!bVar2) {
        iVar7 = (int)local_30;
        uVar3 = 1 << (*(byte *)(DAT_8009c7e0 + 0x435) & 0x1f);
        do {
          if (*(byte *)(DAT_8009c7e0 + (uint)*(byte *)(DAT_8009c7e0 + 0x435) + 0x40c) <= param_6) {
            bVar2 = true;
            FUN_800484cc(param_1,(uint)*(byte *)(DAT_8009c7e0 + 0x435),(int)param_2,local_36,iVar7,
                         param_5 & 0xff,param_6);
          }
          uVar3 = uVar3 << 1;
          if ((uVar3 & 0x10) != 0) {
            uVar3 = 1;
          }
          *(char *)(DAT_8009c7e0 + 0x435) = *(char *)(DAT_8009c7e0 + 0x435) + '\x01';
          iVar6 = iVar6 + 1;
          *(byte *)(DAT_8009c7e0 + 0x435) = *(byte *)(DAT_8009c7e0 + 0x435) & 3;
        } while ((iVar6 < 4) && (!bVar2));
      }
    }
    else {
      FUN_8004569c((uint)param_1,0);
    }
  }
  return;
}

