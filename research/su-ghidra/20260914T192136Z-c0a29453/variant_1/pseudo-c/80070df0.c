/* Analysis pseudo-C, not buildable source. */

void FUN_80070df0(undefined4 param_1,undefined4 *param_2,int *param_3)

{
  int iVar1;
  
  switch(param_1) {
  case 0:
  case 1:
    *param_2 = 1;
    iVar1 = 5;
    break;
  case 2:
  case 3:
    *param_2 = 6;
    iVar1 = 10;
    break;
  case 4:
    *param_2 = 0xb;
    iVar1 = FUN_80070d3c();
    iVar1 = iVar1 + 10;
    break;
  case 5:
  case 6:
    *param_2 = 0x38;
    iVar1 = 0x3c;
    break;
  case 7:
  case 8:
    *param_2 = 0x3d;
    iVar1 = 0x41;
    break;
  case 9:
    *param_2 = 0x42;
    iVar1 = 0x46;
    break;
  default:
    goto switchD_80070e20_default;
  }
  *param_3 = iVar1;
switchD_80070e20_default:
  return;
}

