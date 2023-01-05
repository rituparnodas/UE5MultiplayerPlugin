// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GameState)
	{
		int32 NumOfPlayers = GameState.Get()->PlayerArray.Num();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				1,
				60.f,
				FColor::Yellow,
				FString::Printf(TEXT("Current Player in The Session: %d"), NumOfPlayers)
				);

			APlayerState* PS = NewPlayer->GetPlayerState<APlayerState>();
			if (PS)
			{
				FString PlayerName = PS->GetPlayerName();

				GEngine->AddOnScreenDebugMessage(
					1,
					60.f,
					FColor::Cyan,
					FString::Printf(TEXT("%s Joined"), *PlayerName)
				);
			}
		}
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	if (GEngine)
	{
		int32 NumOfPlayers = GameState.Get()->PlayerArray.Num();
		GEngine->AddOnScreenDebugMessage(
			1,
			60.f,
			FColor::Yellow,
			FString::Printf(TEXT("Current Player in The Session: %d"), NumOfPlayers - 1)
		);

		APlayerState* PS = Exiting->GetPlayerState<APlayerState>();
		if (PS)
		{
			FString PlayerName = PS->GetPlayerName();

			GEngine->AddOnScreenDebugMessage(
				1,
				60.f,
				FColor::Cyan,
				FString::Printf(TEXT("%s Left The Game"), *PlayerName)
			);
		}
	}
}