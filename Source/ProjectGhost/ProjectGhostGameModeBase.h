// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "ProjectGhostGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGHOST_API AProjectGhostGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Project Ghost")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Project Ghost")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
		UUserWidget* CurrentWidget;
};
