// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GamePlayerController.h"

#include "UObject/ConstructorHelpers.h"
#include "UserWidget/GameUserWidget.h"
#include "UserWidget/SessionUserWidget.h"
#include "GameFramework/HUD.h"

AGamePlayerController::AGamePlayerController()
{
	ConstructorHelpers::FClassFinder<UGameUserWidget> WidgetClass(TEXT("/Game/Widgets/WD_Game"));
	if (WidgetClass.Succeeded())
	{
		GameWidgetClass = WidgetClass.Class;
	}
	ConstructorHelpers::FClassFinder<USessionUserWidget> gameLobbyWidgetClass(TEXT("/Game/Widgets/WD_GameLobby"));
	if (gameLobbyWidgetClass.Succeeded())
	{
		GameLobbyWidgetClass = gameLobbyWidgetClass.Class;
	}
}

void AGamePlayerController::UpdateGameWidget(int8 bombs, int8 power, float speed)
{
	if (!GameWidget)
	{
		GameWidget = CreateWidget<UGameUserWidget>(this, GameWidgetClass);
		GameWidget->AddToPlayerScreen(-1);
	}
	if (GameWidget) GameWidget->UpdateWidget(bombs, power, speed);
}

void AGamePlayerController::BeginPlay()
{
	if (IsLocalController())
	{
		SessionWidget = CreateWidget<USessionUserWidget>(this, GameLobbyWidgetClass);
		checkf(SessionWidget, TEXT("GameController cant create session widget!"));

		SessionWidget->AddToViewport(-1);

		SetInputMode(FInputModeUIOnly());
		SetShowMouseCursor(true);
	}
}

void AGamePlayerController::OnPrepareGame_Implementation()
{
	SessionWidget->RemoveFromViewport();
	
	APawn* tempPawn = GetPawn();
	checkf(tempPawn, TEXT("PlayerController missed pawn"));

	tempPawn->DisableInput(this);
	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red, TEXT("ClearedViewport"));
}

void AGamePlayerController::OnStartGame_Implementation()
{
	SetInputMode(FInputModeGameOnly());

	APawn* tempPawn = GetPawn();
	checkf(tempPawn, TEXT("PlayerController missed pawn"));

	tempPawn->EnableInput(this);
	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red, TEXT("Game Started!"));
}
