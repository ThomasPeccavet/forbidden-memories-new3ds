/* Analysis pseudo-C, not buildable source. */

void FUN_80038b4c(int param_1)

{
  byte bVar1;
  byte *pbVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)(param_1 + *(char *)(param_1 + 0x58) * 4);
  pbVar2 = (byte *)*puVar3;
  bVar1 = *pbVar2;
  *puVar3 = pbVar2 + 1;
  (*(code *)(&PTR_FUN_800922b8)[bVar1])();
  return;
}

