/* Analysis pseudo-C, not buildable source. */

void FUN_80070d64(undefined4 param_1,undefined4 *param_2,int *param_3)

{
  int iVar1;
  
  switch(param_1) {
  case 0:
  case 1:
    *param_2 = 1;
    iVar1 = 5;
    break;
  case 2:
    *param_2 = 0xb;
    iVar1 = FUN_80070d3c();
    iVar1 = iVar1 + 10;
    break;
  case 3:
  case 4:
  case 5:
    *param_2 = 0x38;
    iVar1 = 0x3c;
    break;
  case 6:
    *param_2 = 0x42;
    iVar1 = 0x46;
    break;
  default:
    goto switchD_80070d94_default;
  }
  *param_3 = iVar1;
switchD_80070d94_default:
  return;
}

