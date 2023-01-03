// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu.h"
#include "MultiplayerSupportSubsystem.h"
#include "Components/Button.h"
#include "OnlineSessionSettings.h"

void UMenu::MenuSetup(int32 PublicConnections, FString TypeOfMatch)
{
	NumOfpublicConnection = PublicConnections;
	MatchType = TypeOfMatch;

	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;
	UWorld* WorldPtr = GetWorld();
	if (WorldPtr)
	{
		APlayerController* PC = WorldPtr->GetFirstPlayerController();
		if (PC)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PC->SetInputMode(InputModeData);
			PC->SetShowMouseCursor(true);
		}
	}

	UGameInstance* GI = GetGameInstance();
	if (GI) MultiplayerSupportSubsystem = GI->GetSubsystem<UMultiplayerSupportSubsystem>();
	if (MultiplayerSupportSubsystem) MultiplayerSupportSubsystem->MultiplayerOnSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
}

void UMenu::MenuTearDown()
{
	RemoveFromParent();

	UWorld* WorldPtr = GetWorld();
	if (WorldPtr)
	{
		APlayerController* PC = WorldPtr->GetFirstPlayerController();
		if (PC)
		{
			FInputModeGameOnly InputModeData;
			PC->SetInputMode(InputModeData);
			PC->SetShowMouseCursor(false);
		}
	}
}

bool UMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (HostButton) HostButton->OnClicked.AddDynamic(this, &ThisClass::OnClickHostButton);
	if (JoinButton) JoinButton->OnClicked.AddDynamic(this, &ThisClass::OnClickJoinButton);

	return true;
}

void UMenu::NativeDestruct()
{
	MenuTearDown();

	Super::NativeDestruct();
}

void UMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Yellow,
				FString::Printf(TEXT("Session Created Successfully"))
			);

			UWorld* WorldPtr = GetWorld();
			if (WorldPtr) WorldPtr->ServerTravel(FString("/Game/ThirdPerson/Maps/Lobby?listen"));
		}
	}
}

void UMenu::OnClickHostButton()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Blue,
			FString::Printf(TEXT("Host Button Clicked"))
		);
	}

	if (MultiplayerSupportSubsystem) MultiplayerSupportSubsystem->CreateSession(NumOfpublicConnection, MatchType);
}

void UMenu::OnClickJoinButton()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Green,
			FString::Printf(TEXT("join Button Clicked"))
		);
	}
}