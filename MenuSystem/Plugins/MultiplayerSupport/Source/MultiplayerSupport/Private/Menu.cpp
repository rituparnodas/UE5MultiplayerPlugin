// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu.h"
#include "MultiplayerSupportSubsystem.h"
#include "Components/Button.h"

void UMenu::MenuSetup()
{
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
}

bool UMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (HostButton)
		HostButton->OnClicked.AddDynamic(this, &ThisClass::OnClickHostButton);

	if (JoinButton)
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::OnClickJoinButton);

	return true;
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