// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);
    // UE_LOG(LogTemp, Warning, TEXT("A pawn was killed"));

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());

    if (PlayerController != nullptr)
    {
        EndGame(false);
    }

    for(AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!Controller->IsDead())   return;

        
    }
    EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        Controller->GameHasEnded(Controller->GetPawn(), bIsPlayerWinner == Controller->IsPlayerController());     // 플레이어가 우승자인 경우(bIsPlayerWinner, Controller->IsPlayerController()가 모두 true)
    }                                                                                                             // ai가 우승자인 경우(bIsPlayerWinner, Controller->IsPlayerController()가 모두 false)
}
