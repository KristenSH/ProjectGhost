// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameLiftServerSDK.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "ProjectGhostGameModeBase.generated.h"

USTRUCT()
struct FStartGameSessionState
{
	GENERATED_BODY()

		UPROPERTY()
		bool Status;

	FStartGameSessionState()
	{
		Status = false;
	}
};

USTRUCT()
struct FUpdateGameSessionState
{
	GENERATED_BODY()

	FUpdateGameSessionState()
	{
		
	}
};

USTRUCT()
struct FTerminateProcessState
{
	GENERATED_BODY()

	UPROPERTY()
		bool Status;

	long TerminationTime;

	FTerminateProcessState()
	{
		Status = false;
	}
};

USTRUCT()
struct FHealthCheckState
{
	GENERATED_BODY()

		UPROPERTY()
		bool Status;

	FHealthCheckState()
	{
		Status = false;
	}
};

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

private:

	UPROPERTY()
		FStartGameSessionState StartGameSessionState;

	UPROPERTY()
		FUpdateGameSessionState UpdateGameSessionState;

	UPROPERTY()
		FTerminateProcessState TerminateProcessState;

	UPROPERTY()
		FHealthCheckState HealthCheckState;
};
