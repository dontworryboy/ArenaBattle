// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "ABGameInstance.generated.h"

class FHouse
{
public:
	TSharedPtr<FHouse> OthersDeed;
	TWeakPtr<FHouse> AccessHouse;
	int32 Size = 10;
};

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UABGameInstance();

	virtual void Init() override;
	
	UPROPERTY()
		class UWebConnect* WebConnect;
	UPROPERTY()
		class UWebConnect* WebConnect2;
	//UPROPERTY()
		class UWebConnect* WebConnectionNew;
	//��Ʈ���� �Ǵ� �ּ��� ������ ������Ʈ
	UPROPERTY()
		FStreamableManager AssetLoader;

	FTimerHandle ObjectCheckTimer;

	UFUNCTION()
		void CheckUObjectAlive();
};
