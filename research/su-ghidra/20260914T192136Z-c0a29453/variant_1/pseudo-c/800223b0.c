/* Analysis pseudo-C, not buildable source. */

void FUN_800223b0(void)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 *puVar3;
  ushort uVar4;
  
  if ((DAT_8009c710 & 0x800) != 0) {
    FUN_80022174();
  }
  if ((DAT_8009c564 & 0x8000) == 0) {
    DAT_8009c564 = DAT_8009c564 | 0xc000;
    DAT_8009c538 = 0;
    DAT_8009c2c6 = 0;
    DAT_8009c2c0 = 0;
    DAT_8009c2c5 = 0;
    DAT_8009c58c = 0;
    DAT_8009c588 = 0;
  }
  if ((DAT_8009c564 & 0x4000) == 0) {
    uVar4 = DAT_8009c564 | 0x4000;
    if ((DAT_8009c72c & 0x100) == 0) {
      if ((DAT_8009c72c & 0xa000) == 0) {
        if ((DAT_8009c728 & 0x5000) == 0) {
          if ((DAT_8009c72c & 0x40) != 0) {
            puVar3 = (undefined2 *)FUN_8002c7d8(DAT_8009c2c4);
            DAT_8009c538 = DAT_8009c538 + 1 & 7;
            puVar3[0xd] = (ushort)DAT_8009c2c5;
            uVar1 = DAT_80091ac0;
            if (DAT_8009c2c6 == 1) {
              *puVar3 = 0xa0;
              uVar1 = 0x78;
            }
            else {
              if (DAT_8009c2c6 < 2) {
                if (DAT_8009c2c6 != 0) {
                  return;
                }
                puVar3[1] = 0xffe8;
                *puVar3 = uVar1;
                puVar3[2] = DAT_80091ac2;
                return;
              }
              if ((DAT_8009c2c6 != 2) && (DAT_8009c2c6 != 3)) {
                return;
              }
              *puVar3 = 0xa0;
              uVar1 = 0x70;
            }
            puVar3[1] = uVar1;
          }
        }
        else {
          (&DAT_8009c2c4)[DAT_8009c2c0] = (&DAT_8009c2c4)[DAT_8009c2c0] + '\x01';
          if ((DAT_8009c728 & 0x4000) != 0) {
            (&DAT_8009c2c4)[DAT_8009c2c0] = (&DAT_8009c2c4)[DAT_8009c2c0] + -2;
          }
        }
      }
      else {
        DAT_8009c2c0 = DAT_8009c2c0 ^ 1;
      }
    }
    else {
      DAT_8009c2c6 = DAT_8009c2c6 + 1;
      DAT_8009c564 = uVar4;
      if (3 < DAT_8009c2c6) {
        DAT_8009c2c6 = 0;
      }
    }
  }
  else {
    DAT_8009c564 = DAT_8009c564 & 0xbfff;
    FUN_800296c0(0);
    FUN_80040690(DAT_8009c588);
    FUN_80040690(DAT_8009c58c);
    DAT_8009c58c = 0;
    DAT_8009c588 = 0;
    if (DAT_8009c2c6 == 1) {
      FUN_800292dc(0,1);
      FUN_80013700();
      iVar2 = FUN_80029354(0,0xffffffff,0xffffffff);
      *(undefined2 *)(iVar2 + 0x30) = 0x5a;
      *(undefined2 *)(iVar2 + 0x32) = 0xe;
      FUN_80012c88(4);
      FUN_800193dc(iVar2);
    }
    else if (1 < DAT_8009c2c6) {
      if (DAT_8009c2c6 == 2) {
        DAT_8009c588 = FUN_80017e94(&DAT_801a7b80,0x86,0x52);
      }
      else if (DAT_8009c2c6 == 3) {
        DAT_8009c588 = FUN_80017e94(&DAT_801a7b80,0x5c,0x52);
        DAT_8009c58c = FUN_80017e94(&DAT_801a7b9c,0xb0,0x52);
      }
    }
  }
  return;
}

