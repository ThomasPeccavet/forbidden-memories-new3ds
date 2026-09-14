/* Analysis pseudo-C, not buildable source. */

void FUN_8004c5a4(undefined4 *param_1,uint param_2,char param_3,char param_4)

{
  byte bVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  uVar6 = param_2 & 0xf;
  param_2 = param_2 & 0xf0;
  if (param_2 == 0xb0) {
    if (param_3 == 'c') {
      if (param_4 == '\x14') {
        if (*(short *)(DAT_8009c7d8 + 0x7f8) == 0) {
          *(undefined1 *)((int)param_1 + 0x26) = 0x7f;
          param_1[1] = *param_1;
        }
        else {
          iVar4 = 0;
          if (*(short *)(DAT_8009c7d8 + 0x7fa) != 0) {
            iVar5 = 0x518;
            iVar2 = DAT_8009c7d8;
            do {
              puVar3 = (undefined4 *)(iVar2 + iVar5);
              *(undefined1 *)((int)puVar3 + 0x26) = 0x14;
              *(undefined1 *)((int)puVar3 + 0x25) = *(undefined1 *)(puVar3 + 9);
              *(undefined1 *)((int)puVar3 + 0x2a) = *(undefined1 *)((int)puVar3 + 0x29);
              iVar2 = DAT_8009c7d8;
              *(undefined2 *)((int)puVar3 + 0x1a) = *(undefined2 *)(puVar3 + 6);
              puVar3[1] = *puVar3;
              puVar3[8] = puVar3[7];
              iVar4 = iVar4 + 1;
              iVar5 = iVar5 + 0x2c;
            } while (iVar4 < (int)(uint)*(ushort *)(iVar2 + 0x7fa));
          }
          *(undefined4 *)(DAT_8009c7d8 + 0x7f4) = *(undefined4 *)(DAT_8009c7d8 + 0x7f0);
        }
      }
      else if (param_4 == '\x1e') {
        bVar1 = *(byte *)((int)param_1 + 0x26);
        if (bVar1 != 0) {
          if (bVar1 < 0x7f) {
            *(byte *)((int)param_1 + 0x26) = bVar1 - 1;
          }
          if (*(short *)(DAT_8009c7d8 + 0x7f8) == 0) {
            *param_1 = param_1[1];
          }
          else {
            iVar4 = 0;
            if (*(short *)(DAT_8009c7d8 + 0x7fa) != 0) {
              iVar5 = 0x518;
              iVar2 = DAT_8009c7d8;
              do {
                puVar3 = (undefined4 *)(iVar2 + iVar5);
                *(undefined1 *)(puVar3 + 9) = *(undefined1 *)((int)puVar3 + 0x25);
                *(undefined1 *)((int)puVar3 + 0x29) = *(undefined1 *)((int)puVar3 + 0x2a);
                iVar2 = DAT_8009c7d8;
                *(undefined2 *)(puVar3 + 6) = *(undefined2 *)((int)puVar3 + 0x1a);
                *puVar3 = puVar3[1];
                puVar3[7] = puVar3[8];
                iVar4 = iVar4 + 1;
                iVar5 = iVar5 + 0x2c;
              } while (iVar4 < (int)(uint)*(ushort *)(iVar2 + 0x7fa));
            }
            *(undefined4 *)(DAT_8009c7d8 + 0x7f0) = *(undefined4 *)(DAT_8009c7d8 + 0x7f4);
          }
        }
      }
    }
    if ((param_3 == '\x06') && (*(char *)(DAT_8009c7d8 + uVar6 * 0x18 + 0x12) == '\x14')) {
      if (*(short *)(DAT_8009c7d8 + 0x7f8) == 0) {
        *(char *)((int)param_1 + 0x26) = param_4;
        return;
      }
      iVar4 = 0;
      if (*(short *)(DAT_8009c7d8 + 0x7fa) != 0) {
        iVar2 = 0;
        do {
          *(char *)(DAT_8009c7d8 + iVar2 + 0x53e) = param_4;
          iVar4 = iVar4 + 1;
          iVar2 = iVar2 + 0x2c;
        } while (iVar4 < (int)(uint)*(ushort *)(DAT_8009c7d8 + 0x7fa));
      }
    }
    FUN_8004b92c(uVar6,param_3,param_4);
  }
  else if (param_2 < 0xb1) {
    if (param_2 == 0x80) {
      FUN_8004b804(uVar6,param_3,param_4);
    }
    else if (param_2 == 0x90) {
      if (param_4 == '\0') {
        FUN_8004b804(uVar6,param_3,0);
      }
      else {
        FUN_8004b278(uVar6,param_3);
      }
    }
  }
  else if (param_2 == 0xc0) {
    FUN_8004bb78(uVar6,param_3);
  }
  else if (param_2 == 0xe0) {
    FUN_8004bb9c(uVar6,param_3,param_4);
  }
  return;
}

