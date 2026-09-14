/* Analysis pseudo-C, not buildable source. */

void FUN_80043e3c(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  DAT_8009c7a8 = 0;
  DAT_8009c440 = 0;
  if (param_1 == 0) {
    FUN_80014d38(0,0,0x2503,0x25,FUN_800438d4,0,0);
    FUN_80013700();
    FUN_8001569c();
    uVar1 = FUN_80040350();
    iVar2 = FUN_800403d0(uVar1,2);
    FUN_80042bd8(iVar2,0,0,0,0,0,0x13,0x100,&DAT_801af000);
    *(ushort *)(iVar2 + 8) = *(ushort *)(iVar2 + 8) | 0x28;
    FUN_80043a78(0,iVar2);
    FUN_80043cd4(0xb4);
    FUN_8007e8e8();
    FUN_801680f4();
    do {
      iVar3 = FUN_80168160(1);
    } while (iVar3 != 0);
    FUN_8007b53c();
    uVar1 = FUN_80040350();
    iVar3 = FUN_800403d0(uVar1,2);
    FUN_80042bd8(iVar3,0,0,0,0,1,0x13,0x100,&DAT_801af000);
    *(ushort *)(iVar3 + 8) = *(ushort *)(iVar3 + 8) | 0x28;
    FUN_80043a78(iVar2);
    FUN_80047f60(2);
    FUN_80012c88(4);
    FUN_80043cd4(0xb4);
    DAT_8009c44b = 1;
    FUN_80043dc8(1,0);
    FUN_800159f4();
    FUN_8002cf60();
    if ((DAT_8009c460 & 0x2000030) != 0 || DAT_8009c484 != 0) {
      do {
        FUN_80012c50();
      } while ((DAT_8009c460 & 0x2000030) != 0 || DAT_8009c484 != 0);
    }
    FUN_80043d7c();
    FUN_8006b560();
  }
  else {
    FUN_80043dc8(DAT_8009c44b,1);
    FUN_80047f60(2);
    FUN_80012c88(4);
  }
  FUN_80013700();
  return;
}

