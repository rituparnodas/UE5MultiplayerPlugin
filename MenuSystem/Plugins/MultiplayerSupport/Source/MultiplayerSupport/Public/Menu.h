// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class MULTIPLAYERSUPPORT_API UMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		void MenuSetup();

protected:

	virtual bool Initialize() override;

	
private:

	UPROPERTY(meta = (BindWidget))
		UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
		UButton* JoinButton;

	UFUNCTION()
		void OnClickHostButton();

	UFUNCTION()
		void OnClickJoinButton();

	class UMultiplayerSupportSubsystem* MultiplayerSupportSubsystem;
};