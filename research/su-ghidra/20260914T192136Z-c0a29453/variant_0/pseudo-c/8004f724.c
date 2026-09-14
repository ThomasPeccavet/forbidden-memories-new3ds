/* Analysis pseudo-C, not buildable source. */

void FUN_8004f724(int param_1,int param_2,undefined4 param_3)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  
  cVar1 = DAT_8009c312;
  if (param_1 < 0) {
    iVar4 = 0;
  }
  else {
    iVar4 = param_1 * 8 + -0x7ff6dbcc;
  }
  if (param_2 < 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = param_2 * 8 + -0x7ff6dbcc;
  }
  if ((DAT_8009c313 != '\x01') || (DAT_8009c314 != '\x01')) {
    cVar2 = DAT_8009c312 + '\x01';
    if (DAT_8009c312 < '\0') {
      cVar2 = DAT_8009c312;
    }
    DAT_8009c312 = cVar2;
    FUN_8004f92c('\0' < cVar1,iVar4,iVar3,param_3);
  }
  return;
}

