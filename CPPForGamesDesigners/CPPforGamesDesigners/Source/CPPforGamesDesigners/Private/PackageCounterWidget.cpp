#include "PackageCounterWidget.h"
#include "Components/TextBlock.h"

void UPackageCounterWidget::UpdatePackageCount(int32 Count)
{
if(PackageText)
{
PackageText->SetText(FText::FromString(FString::Printf(TEXT("Packages: %d"), Count)));
}
}