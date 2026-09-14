/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_800424b8(uint *param_1,int param_2,int param_3,uint param_4,short *param_5)

{
  undefined1 uVar1;
  ushort uVar2;
  char cVar3;
  int iVar4;
  
  switch(param_4 >> 0x10) {
  case 0:
    break;
  case 1:
    FUN_80084978(param_1,param_3,param_4 & 0xffff);
    break;
  case 2:
    FUN_80084af8(param_1,param_3,param_4 & 0xffff);
    break;
  case 3:
    FUN_80084478(param_1,param_3,param_4 & 0xffff);
    break;
  case 4:
    if (((uint)param_1 & 0x4000000) != 0) {
      _DAT_1f800300 = *(short *)(param_2 + 8) - *param_5;
      _DAT_1f800302 = *(short *)(param_2 + 10) - param_5[1];
      _DAT_1f800308 = *(short *)(param_2 + 0x10) - *param_5;
      _DAT_1f80030a = *(short *)(param_2 + 0x12) - param_5[1];
      _DAT_1f800310 = *(short *)(param_2 + 0x18) - *param_5;
      _DAT_1f800312 = *(short *)(param_2 + 0x1a) - param_5[1];
      _DAT_1f800318 = *(short *)(param_2 + 0x20) - *param_5;
      _DAT_1f80031a = *(short *)(param_2 + 0x22) - param_5[1];
      _DAT_1f80031c = 0;
      _DAT_1f800314 = 0;
      _DAT_1f80030c = 0;
      _DAT_1f800304 = 0;
      iVar4 = FUN_80087b48(&DAT_1f800300,&DAT_1f800308,&DAT_1f800310,&DAT_1f800318,param_2 + 8,
                           param_2 + 0x10,param_2 + 0x18,param_2 + 0x20,&DAT_1f8002e0,&DAT_1f8002e4,
                           &DAT_1f8002e8);
joined_r0x800427c0:
      if (iVar4 < 1) {
        return;
      }
    }
    goto joined_r0x800427d0;
  case 5:
    if (((uint)param_1 & 0x4000000) != 0) {
      _DAT_1f800300 = *(short *)(param_2 + 8) - *param_5;
      _DAT_1f800302 = *(short *)(param_2 + 10) - param_5[1];
      _DAT_1f800308 = *(short *)(param_2 + 0x14) - *param_5;
      _DAT_1f80030a = *(short *)(param_2 + 0x16) - param_5[1];
      _DAT_1f800310 = *(short *)(param_2 + 0x20) - *param_5;
      _DAT_1f800312 = *(short *)(param_2 + 0x22) - param_5[1];
      _DAT_1f800318 = *(short *)(param_2 + 0x2c) - *param_5;
      _DAT_1f80031a = *(short *)(param_2 + 0x2e) - param_5[1];
      _DAT_1f80031c = 0;
      _DAT_1f800314 = 0;
      _DAT_1f80030c = 0;
      _DAT_1f800304 = 0;
      iVar4 = FUN_80087b48(&DAT_1f800300,&DAT_1f800308,&DAT_1f800310,&DAT_1f800318,param_2 + 8,
                           param_2 + 0x14,param_2 + 0x20,param_2 + 0x2c,&DAT_1f8002e0,&DAT_1f8002e4,
                           &DAT_1f8002e8);
      goto joined_r0x800427c0;
    }
joined_r0x800427d0:
    if (((uint)param_1 & 0x40000000) == 0) {
LAB_80042a10:
      FUN_800842a8(param_2,param_3,param_4 & 0xffff);
    }
    else {
      FUN_8004d5b8(param_2,param_3,param_4 & 0xffff,(uint)param_1 >> 0x1c & 3);
    }
    break;
  default:
    uVar2 = (ushort)(*param_1 >> 0x10);
    *(ushort *)(param_2 + 0x16) = (ushort)param_1[3] | uVar2 >> 1 & 0x180 | uVar2 >> 7 & 0x60;
    if ((*param_1 & 0x40000000) != 0) {
      FUN_80082da8(param_2,1);
    }
    *(ushort *)(param_2 + 0xe) =
         *(short *)((int)param_1 + 0x12) << 6 | (ushort)param_1[4] >> 4 & 0x3f;
    if ((*param_1 & 0x800000) == 0) {
      uVar1 = *(undefined1 *)((int)param_1 + 0xe);
      *(undefined1 *)(param_2 + 0x1c) = uVar1;
      *(undefined1 *)(param_2 + 0xc) = uVar1;
      uVar1 = *(undefined1 *)((int)param_1 + 0xf);
      *(undefined1 *)(param_2 + 0x15) = uVar1;
      *(undefined1 *)(param_2 + 0xd) = uVar1;
      if ((*param_1 & 0x80) == 0) {
        cVar3 = *(char *)((int)param_1 + 0xe) + (char)param_1[2] + -1;
        *(char *)(param_2 + 0x24) = cVar3;
        *(char *)(param_2 + 0x14) = cVar3;
        goto LAB_8004292c;
      }
      cVar3 = *(char *)((int)param_1 + 0xe) + (char)param_1[2];
      *(char *)(param_2 + 0x24) = cVar3;
      *(char *)(param_2 + 0x14) = cVar3;
      cVar3 = *(char *)((int)param_1 + 0xf) + *(char *)((int)param_1 + 10);
    }
    else {
      uVar1 = *(undefined1 *)((int)param_1 + 0xe);
      *(undefined1 *)(param_2 + 0x24) = uVar1;
      *(undefined1 *)(param_2 + 0x14) = uVar1;
      cVar3 = *(char *)((int)param_1 + 0xe) + (char)param_1[2] + -1;
      *(char *)(param_2 + 0x1c) = cVar3;
      *(char *)(param_2 + 0xc) = cVar3;
      uVar1 = *(undefined1 *)((int)param_1 + 0xf);
      *(undefined1 *)(param_2 + 0x15) = uVar1;
      *(undefined1 *)(param_2 + 0xd) = uVar1;
LAB_8004292c:
      cVar3 = *(char *)((int)param_1 + 0xf) + *(char *)((int)param_1 + 10) + -1;
    }
    *(char *)(param_2 + 0x25) = cVar3;
    *(char *)(param_2 + 0x1d) = cVar3;
    _DAT_1f800300 = (short)param_1[1] - *param_5;
    _DAT_1f800308 = _DAT_1f800300 + (short)param_1[2];
    _DAT_1f800302 = *(short *)((int)param_1 + 6) - param_5[1];
    _DAT_1f800312 = _DAT_1f800302 + *(short *)((int)param_1 + 10);
    _DAT_1f80031c = 0;
    _DAT_1f800314 = 0;
    _DAT_1f80030c = 0;
    _DAT_1f800304 = 0;
    _DAT_1f80030a = _DAT_1f800302;
    _DAT_1f800310 = _DAT_1f800300;
    _DAT_1f800318 = _DAT_1f800308;
    _DAT_1f80031a = _DAT_1f800312;
    iVar4 = FUN_80087b48(&DAT_1f800300,&DAT_1f800308,&DAT_1f800310,&DAT_1f800318,param_2 + 8,
                         param_2 + 0x10,param_2 + 0x18,param_2 + 0x20,&DAT_1f8002e0,&DAT_1f8002e4,
                         &DAT_1f8002e8);
    if (iVar4 < 1) {
      return;
    }
    if (*(int *)(param_5 + 2) != 0) {
      _DAT_1f800004 = 0x140;
      _DAT_1f800008 = 0x120;
      _DAT_1f800280 = *(undefined4 *)(param_2 + 4);
      _DAT_1f800290 = *(undefined4 *)(param_2 + 0xc);
      _DAT_1f800294 = *(undefined4 *)(param_2 + 0x14);
      _DAT_1f800298 = *(undefined4 *)(param_2 + 0x1c);
      _DAT_1f80029c = *(undefined4 *)(param_2 + 0x24);
      _DAT_1f800000 = *(int *)(param_5 + 2);
      DAT_800ff5c4 = FUN_800891e8(&DAT_1f800300,&DAT_1f800308,&DAT_1f800310,&DAT_1f800318,
                                  &DAT_1f800290,&DAT_1f800294,&DAT_1f800298,&DAT_1f80029c,
                                  &DAT_1f800280,DAT_800ff5c4,
                                  *(int *)(param_3 + 4) + (short)param_4 * 4,0x1f800000);
      return;
    }
    goto LAB_80042a10;
  }
  return;
}

