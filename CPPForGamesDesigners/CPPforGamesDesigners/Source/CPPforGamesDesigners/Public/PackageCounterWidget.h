// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PackageCounterWidget.generated.h"

class UTextBlock;

UCLASS()
class CPPFORGAMESDESIGNERS_API UPackageCounterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdatePackageCount(int32 Count);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PackageText;
};