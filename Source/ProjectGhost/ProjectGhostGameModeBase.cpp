// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectGhostGameModeBase.h"

void AProjectGhostGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ChangeMenuWidget(StartingWidgetClass);

#if WITH_GAMELIFT
    auto InitSDKOutcome = Aws::GameLift::Server::InitSDK();

    if (InitSDKOutcome.IsSuccess())
    {
        auto OnStartGameSession = [](Aws::GameLift::Server::Model::GameSession GameSession GameSessionObj, void* params)
        {
            FStartGameSessionState* State = (FStartGameSessionState*)Params;

            State->Status = Aws::GameLift::Server::ActivateGameSession().IsSuccess();
        };
    }

    auto onUpdateGameSession = [](AWs::GameLift::Server::Model::UpdateGameSession UpdateGameSessionObj, void* Params)
    {
        FStartGameSessionState* State = (FUpdateGameSessionState*)Params;
    };

    auto OnProcessTerminate = [](void* Params)
    {
        FProcessTerminateState* State = (FProcessTerminateState*)Params;
        auto GetTerminationTimeOutcome = Aws::GameLift::Server::GetTerminationTime();
        if (GetTerminationTimeOutcome.IsSuccess())
        {
            State->TerminationTime = GetTerminationTimeOutcome.GetResult();
        }

        auto ProcessEndingOutcome = Aws::GameLift::Server::ProcessEnding();

        if (ProcessEndingOutcome.IsSuccess())
        {
            State->Status = true;
            FGenericPlatformMisc::RequestExit(false);
        }
    };

    auto OnHealthCheck = [](void* Params)
    {
        FHealthCheckState* State = (FHealthCheckState*)Params;
        State->Status = true;

        return State->Status;
    };


    TArray<FString> CommandLineTokens;
    TArray<FString> CommandLineSwitches;
    int Port = FURL::UrlConfig.Default;

    FCommandLine::Parse(FCommandLine::Get, CommandLineTokens, CommandLineSwitches);

    for (FString str : CommandLineSwitches)
    {
        FString Key;
        FString Value;

        if (str.Split("=", &Key, &Value))
        {
            if (Key.Equals("port"))
                Port = FCString::Atoi(*Value);
        }
    }

    const char* LogFile = "aLogFile.txt";
    const char** LogFiles = &LogFile;
    auto LogParams = new Aws::GameLift::Server::LogParameters(LogFiles, 1);

    auto Params = new Aws::GameLift::Server::ProcessParameters(
        OnStartGameSession,
        &StartGameSessionState,
        OnUpdateGameSession,
        &UpdateGameSessionState,
        OnProcessTerminate,
        &ProcessTerminateState,
        OnHealthCheck,
        &HealthCheckState,
        Port,
        *LogParams
    );

    auto ProcessReadyOutcome = Aws::GameLift::Server::ProcessReady(*Params);


#endif
}

void AProjectGhostGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
    if (CurrentWidget != nullptr)
    {
        CurrentWidget->RemoveFromViewport();
        CurrentWidget = nullptr;
    }
    if (NewWidgetClass != nullptr)
    {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
        if (CurrentWidget != nullptr)
        {
            CurrentWidget->AddToViewport();
        }
    }
}