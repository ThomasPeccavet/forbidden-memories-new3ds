/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80036298(int param_1,undefined4 param_2)

{
  byte bVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  ushort uVar4;
  longlong lVar5;
  ushort uVar6;
  ushort uVar7;
  int iVar8;
  uint uVar9;
  uint *puVar10;
  undefined1 *puVar11;
  uint *local_58;
  short local_48;
  int local_44;
  
  FUN_80087858(300);
  local_48 = *(short *)(param_1 + 0x30);
  local_44 = (int)*(short *)(param_1 + 0x32);
  uVar3 = *(undefined2 *)(param_1 + 0x14);
  if ((*(ushort *)(param_1 + 8) & 8) == 0) {
    local_48 = local_48 - DAT_8009c4c0;
    local_44 = local_44 - DAT_8009c4c2;
  }
  local_58 = (uint *)&DAT_1f8000c0;
  FUN_80082ee8(0x1f800000);
  FUN_80082da8(0x1f800000,1);
  DAT_1f80003b = 9;
  _DAT_1f80003c = 0x2c808080;
  _DAT_1f800046 = *(short *)(param_1 + 0x42) << 6 | *(ushort *)(param_1 + 0x40) >> 4 & 0x3f;
  _DAT_1f80004e = (ushort)*(byte *)(param_1 + 0x66);
  if ((*(uint *)(param_1 + 4) & 0x1000000) != 0) {
    _DAT_1f80004e = *(byte *)(param_1 + 0x66) | 0x80;
  }
  _DAT_1f80004e = (ushort)(*(uint *)(param_1 + 4) >> 0x17) & 0x60 | _DAT_1f80004e;
  _DAT_1f8000c0 = *(uint *)(param_1 + 4) | 0x8000000;
  _DAT_1f8000d4 = *(undefined4 *)(param_1 + 0xc);
  _DAT_1f800114 = *(undefined4 *)(param_1 + 0xc);
  _DAT_1f800154 = *(undefined4 *)(param_1 + 0xc);
  _DAT_1f8000c8 = 0x100008;
  _DAT_1f8000d0 = *(undefined4 *)(param_1 + 0x40);
  _DAT_1f80014c = 10;
  _DAT_1f8000cc = 10;
  puVar11 = (undefined1 *)(*(int *)(&DAT_800f0874 + (uint)*(byte *)(param_1 + 0x67) * 100) + 0x15);
  _DAT_1f800100 = _DAT_1f8000c0;
  _DAT_1f800140 = _DAT_1f8000c0;
LAB_800364d8:
  do {
    bVar1 = puVar11[-6];
    if ((bVar1 & 0x80) == 0) {
      return;
    }
    if ((bVar1 & 0x43) == 0) {
      _DAT_1f8000d0 = CONCAT22((byte)puVar11[-1] + 0xc0,0x280);
      DAT_1f8000ce = puVar11[-7] << 3;
      DAT_1f8000cf = (undefined1)(((byte)puVar11[-7] & 0xe0) >> 1);
      puVar10 = local_58;
    }
    else if ((bVar1 & 0x40) == 0) {
      if ((bVar1 & 2) == 0) {
        puVar10 = (uint *)&DAT_1f800140;
        _DAT_1f800148 = 0x80008;
        _DAT_1f800150 = 0x280;
        _DAT_1f800152 = (byte)puVar11[-1] + 0xc0;
        bVar1 = puVar11[-7];
        if (bVar1 < 0xe0) {
          _DAT_1f80014e = CONCAT11((char)(((byte)puVar11[-7] & 0xe0) >> 1) + '@',bVar1 << 3);
        }
        else {
          _DAT_1f800152 = 199;
          _DAT_1f80014e = 0x40f8;
          if (bVar1 == 0xe1) {
            _DAT_1f80014e = 0x48f8;
          }
        }
      }
      else {
        puVar10 = (uint *)&DAT_1f800140;
        _DAT_1f800148 = 0x10000c;
        lVar5 = (ulonglong)(uint)(byte)puVar11[-7] * 0x86186187;
        _DAT_1f800150 = 0x280;
        _DAT_1f80014e =
             CONCAT11(((char)((ulonglong)lVar5 >> 0x20) +
                       (char)((uint)(byte)puVar11[-7] - (int)((ulonglong)lVar5 >> 0x20) >> 1) &
                      0xf0U) + 0x50,((byte)puVar11[-7] % 0x15) * '\f');
        _DAT_1f800152 = (byte)puVar11[-1] + 0xc0;
      }
    }
    else {
      puVar10 = (uint *)&DAT_1f800100;
      _DAT_1f800108 = 0x100010;
      _DAT_1f80010c = 0xb;
      _DAT_1f8000a0 = (byte)puVar11[-7] & 0x7f;
      if (_DAT_1f8000a0 < 0x22) {
        DAT_1f80010e = (DAT_1f8000a0 & 7) * '\x10' + -0x80;
        DAT_1f80010f = (DAT_1f8000a0 & 0x38) << 1;
        if (0x18 < _DAT_1f8000a0) {
          _DAT_1f8000a0 = 0x18;
        }
        uVar4 = _DAT_1f8000a0;
        _DAT_1f800110 = (uVar4 & 0xf) * 0x10 + 0x280;
        _DAT_1f800112 = (DAT_1f8000a0 >> 4) + 0xf9;
        _DAT_1f800100 = *(uint *)(param_1 + 4) | 0x8000000;
        if ((puVar11[-7] & 0x80) != 0) {
          _DAT_1f80010c = 0x1e;
          if (_DAT_1f8000a0 == 0x15) {
            DAT_1f80010e = '@';
            _DAT_1f800112 = 0xe3;
          }
          else if (_DAT_1f8000a0 < 0x16) {
            _DAT_1f800112 = 0xe1;
            if (_DAT_1f8000a0 == 0x14) {
              _DAT_1f800112 = 0xe2;
LAB_800366c0:
              DAT_1f80010e = '\0';
            }
            else {
              DAT_1f80010e = '\0';
            }
          }
          else if (_DAT_1f8000a0 == 0x16) {
            DAT_1f80010e = '`';
            _DAT_1f800112 = 0xe4;
          }
          else {
            if (_DAT_1f8000a0 != 0x17) {
              _DAT_1f800112 = 0xe1;
              goto LAB_800366c0;
            }
            DAT_1f80010e = ' ';
            _DAT_1f800112 = 0xe1;
          }
          DAT_1f80010f = '`';
          _DAT_1f800108 = 0x100020;
          _DAT_1f800110 = 0x280;
          _DAT_1f800100 = *(uint *)(param_1 + 4) | 0x9000000;
        }
      }
      else {
        DAT_1f80010f = -0x80;
        _DAT_1f800112 = 0xfc;
        _DAT_1f800110 = 0x280;
        DAT_1f80010e = DAT_1f8000a0 * '\x10' + -0x10;
        if (DAT_1f80010e == 'P') {
          _DAT_1f800110 = 0x290;
        }
      }
    }
    *(short *)(puVar10 + 1) = *(short *)(puVar11 + -0x13) + local_48;
    uVar4 = *(ushort *)(puVar11 + -0x11);
    *(short *)((int)puVar10 + 6) = (short)((uint)uVar4 + local_44);
    bVar1 = puVar11[-2];
    if (bVar1 == 1) {
      if (puVar11[-9] == '\0' && (puVar11[-0xb] == '\0' && puVar11[-10] == '\0')) goto LAB_80036c24;
      uVar6 = (ushort)puVar10[2] >> 1;
      uVar7 = *(ushort *)((int)puVar10 + 10) >> 1;
      FUN_80087838((int)(short)puVar10[1] + (uint)uVar6,
                   ((int)(((uint)uVar4 + local_44) * 0x10000) >> 0x10) + (uint)uVar7);
      DAT_1f800044 = *(undefined1 *)((int)puVar10 + 0xe);
      DAT_1f80004c = *(char *)((int)puVar10 + 0xe) + (char)puVar10[2] + -1;
      DAT_1f800045 = *(undefined1 *)((int)puVar10 + 0xf);
      _DAT_1f80008c = 0;
      _DAT_1f800090 = 0;
      _DAT_1f800094 = 300;
      DAT_1f800055 = *(char *)((int)puVar10 + 0xf) + *(char *)((int)puVar10 + 10) + -1;
      _DAT_1f800060 = (ushort)(byte)puVar11[-0xb] << 4;
      _DAT_1f800062 = (ushort)(byte)puVar11[-10] << 4;
      _DAT_1f800064 = (ushort)(byte)puVar11[-9] << 4;
      DAT_1f80004d = DAT_1f800045;
      DAT_1f800054 = DAT_1f800044;
      DAT_1f80005c = DAT_1f80004c;
      DAT_1f80005d = DAT_1f800055;
      FUN_80088bd8(&DAT_1f800060,&DAT_1f800078);
      FUN_80085558(&DAT_1f800078);
      _DAT_1f800068 = -uVar6;
      _DAT_1f80006a = -uVar7;
      _DAT_1f800084 = 0;
      _DAT_1f80007c = 0;
      _DAT_1f800074 = 0;
      _DAT_1f80006c = 0;
      _DAT_1f800070 = uVar6;
      _DAT_1f800078 = _DAT_1f800068;
      _DAT_1f80007a = uVar7;
      _DAT_1f800080 = uVar6;
      _DAT_1f800072 = _DAT_1f80006a;
      _DAT_1f800082 = uVar7;
      iVar8 = FUN_80087b48(&DAT_1f800068,&DAT_1f800070,&DAT_1f800078,&DAT_1f800080,&DAT_1f800040,
                           &DAT_1f800048,&DAT_1f800050,&DAT_1f800058,&DAT_1f8000a0,&DAT_1f8000a4,
                           0x1f8000a8);
      if (iVar8 < 1) {
LAB_80036c2c:
        puVar11 = puVar11 + 0x16;
      }
      else {
        FUN_800842a8(&DAT_1f800038,param_2,uVar3);
        puVar11 = puVar11 + 0x16;
      }
      goto LAB_800364d8;
    }
    if (bVar1 < 2) {
      if (bVar1 == 0) {
LAB_80036c24:
        FUN_80084978(puVar10,param_2,uVar3);
        goto LAB_80036c2c;
      }
      puVar11 = puVar11 + 0x16;
    }
    else if (bVar1 == 2) {
      DAT_1f800004 = puVar11[-0xf];
      DAT_1f800010 = puVar11[-0xe];
      DAT_1f80001c = puVar11[-0xd];
      DAT_1f800028 = puVar11[-0xc];
      _DAT_1f800008 = (undefined2)puVar10[1];
      _DAT_1f800014 = (ushort)(byte)puVar11[-3] + (short)puVar10[1] + (short)puVar10[2];
      _DAT_1f80000a = *(short *)((int)puVar10 + 6) + (ushort)((byte)puVar11[-3] >> 2);
      _DAT_1f800016 = *(undefined2 *)((int)puVar10 + 6);
      _DAT_1f800022 = *(short *)((int)puVar10 + 6) + *(short *)((int)puVar10 + 10);
      DAT_1f80000c = *(undefined1 *)((int)puVar10 + 0xe);
      DAT_1f800030 = *(char *)((int)puVar10 + 0xe) + (char)puVar10[2];
      if (DAT_1f800030 == '\0') {
        DAT_1f800030 = -1;
      }
      DAT_1f80000d = *(undefined1 *)((int)puVar10 + 0xf);
      DAT_1f800031 = *(char *)((int)puVar10 + 0xf) + *(char *)((int)puVar10 + 10);
      if (DAT_1f800031 == '\0') {
        DAT_1f800031 = -1;
      }
      _DAT_1f80001a = (ushort)puVar10[3] | 0x20;
      _DAT_1f80000e = *(short *)((int)puVar10 + 0x12) << 6 | (ushort)puVar10[4] >> 4 & 0x3f;
      DAT_1f800005 = DAT_1f800004;
      DAT_1f800006 = DAT_1f800004;
      DAT_1f800011 = DAT_1f800010;
      DAT_1f800012 = DAT_1f800010;
      DAT_1f800018 = DAT_1f800030;
      DAT_1f800019 = DAT_1f80000d;
      DAT_1f80001d = DAT_1f80001c;
      DAT_1f80001e = DAT_1f80001c;
      _DAT_1f800020 = _DAT_1f800008;
      DAT_1f800024 = DAT_1f80000c;
      DAT_1f800025 = DAT_1f800031;
      DAT_1f800029 = DAT_1f800028;
      DAT_1f80002a = DAT_1f800028;
      _DAT_1f80002c = _DAT_1f800014;
      _DAT_1f80002e = _DAT_1f800022;
      FUN_800842a8(0x1f800000,param_2,uVar3);
      _DAT_1f80000e = 0x3fea;
      _DAT_1f80001a = (ushort)puVar10[3] | 0x40;
      FUN_800842a8(0x1f800000,param_2,uVar3);
      puVar11 = puVar11 + 0x16;
    }
    else {
      if (bVar1 == 3) {
        uVar9 = *puVar10;
        uVar2 = *puVar11;
        *(undefined1 *)((int)puVar10 + 0x16) = uVar2;
        *(undefined1 *)((int)puVar10 + 0x15) = uVar2;
        *(undefined1 *)(puVar10 + 5) = uVar2;
        *puVar10 = uVar9 & 0x8fffffff | 0x50000000;
        FUN_80084978(puVar10,param_2,uVar3);
        *(undefined2 *)(puVar10 + 4) = 0x2a0;
        *puVar10 = uVar9 & 0x8fffffff | 0x60000000;
        *(undefined2 *)((int)puVar10 + 0x12) = 0xff;
        goto LAB_80036c24;
      }
      puVar11 = puVar11 + 0x16;
    }
  } while( true );
}

