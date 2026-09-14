/* Analysis pseudo-C, not buildable source. */

undefined8 FUN_8008ec6c(int param_1)

{
  byte *pbVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  byte *pbVar4;
  
  pbVar1 = DAT_8009b218;
  pbVar1[10] = 0;
  pbVar1[0xb] = 0;
  FUN_8008ed40(0x91);
  pbVar1 = DAT_8009b218;
  uVar2 = 0x1003;
  if (param_1 != 0) {
    uVar2 = 0x3003;
  }
  *(undefined2 *)(DAT_8009b218 + 10) = uVar2;
  uVar3 = 1;
  pbVar4 = pbVar1;
  if ((*(ushort *)(pbVar1 + 4) & 0x200) != 0) {
    *(ushort *)(pbVar1 + 10) = *(ushort *)(pbVar1 + 10) | 0x10;
    pbVar4 = DAT_8009b21c;
    if ((*(ushort *)(pbVar1 + 4) & 0x200) == 0) {
      pbVar1 = DAT_8009b21c;
      pbVar1[0] = 0x7f;
      pbVar1[1] = 0xff;
      pbVar1[2] = 0xff;
      pbVar1[3] = 0xff;
      uVar3 = 1;
    }
    else {
      *pbVar1 = 1;
      do {
        uVar3 = 0;
      } while ((*(ushort *)(DAT_8009b218 + 4) & 2) == 0);
      pbVar4 = (byte *)(uint)*DAT_8009b218;
    }
  }
  return CONCAT44(pbVar4,uVar3);
}

