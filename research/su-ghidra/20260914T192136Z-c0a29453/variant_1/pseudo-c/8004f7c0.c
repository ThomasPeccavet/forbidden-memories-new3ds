/* Analysis pseudo-C, not buildable source. */

void FUN_8004f7c0(undefined2 param_1,undefined4 param_2)

{
  char cVar1;
  char cVar2;
  undefined2 local_10;
  undefined2 local_e;
  undefined2 local_c;
  undefined2 local_a;
  
  cVar1 = DAT_8009c312;
  local_a = 5;
  local_e = 0;
  local_c = 0;
  if ((DAT_8009c313 != '\x01') || (DAT_8009c314 != '\x01')) {
    cVar2 = DAT_8009c312 + '\x01';
    if (DAT_8009c312 < '\0') {
      cVar2 = DAT_8009c312;
    }
    DAT_8009c312 = cVar2;
    local_10 = param_1;
    FUN_8004f92c('\0' < cVar1,&local_10,&local_10,param_2);
  }
  return;
}

