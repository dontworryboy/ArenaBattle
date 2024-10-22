// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "WebConnect.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTokenCompleteSignature, const FString&, Token);

/**
 * 
 */
UCLASS()
class WEBSERVICE_API UWebConnect : public UObject
{
	GENERATED_BODY()
	
public:
	UWebConnect();
	
	UPROPERTY()
		FString Host;

	UPROPERTY()
		FString URI;

	UFUNCTION()
		void RequestToken(const FString& UserID); //const 이유 -> 받은놈은 유저ID를 변경할 수 없다.

	UPROPERTY(BlueprintAssignable, Category = "WebService")
		FTokenCompleteSignature TokenCompleteDelegate;

	friend FArchive& operator<<(FArchive& Ar, UWebConnect& WC)
	{
		if (Ar.IsLoading())
		{
			UE_LOG(LogTemp, Warning, TEXT("Archive is Loading State"));
		}
		else if (Ar.IsSaving())
		{
			UE_LOG(LogTemp, Warning, TEXT("Archive is Saving State"));
		}
		else
		{
			return Ar;
		}

		return Ar << WC.Host << WC.URI;
	}
};
