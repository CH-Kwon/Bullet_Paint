#include "Actions.h"

#include "WEStateManager.h"
#include "DemoStates.h"

void NULLAction(void)
{
  //Do Nothing
}
void QuitAction(void)
{
  WEStateManager::Quit();
}
void ChangeToRainAction(void)
{
  WEStateManager::SetNextState(DS_RAIN);
}