// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "WebConnect.h"
#include "ABGameInstance.h"

UABGameInstance::UABGameInstance()
{
	AB_LOG(Warning, TEXT("ABGameInstance Constructor!"));

	WebConnect = CreateDefaultSubobject<UWebConnect>(TEXT("WebConnect"));
}

void UABGameInstance::Init() //어플리케이션(런타임)에서 가장 먼저 호출되는 함수
{
	AB_LOG_CALLONLY(Warning);
	Super::Init();

	WebConnect->TokenCompleteDelegate.AddUObject(this, &UABGameInstance::RequestTokenComplete);
	WebConnect->TokenCompleteDelegate.AddUObject(this, &UABGameInstance::RequestTokenComplete2);
	WebConnect->RequestToken(TEXT("destiny"));
	
	//FHouse* HouseNew = new FHouse();

	//WebConnect->TokenCompleteDelegate.AddUObject(this, &UABGameInstance::RequestTokenComplete);
	//WebConnect->TokenCompleteDelegate.AddUObject(this, &UABGameInstance::RequestTokenComplete2);
	//WebConnect->TokenCompleteDelegate.AddRaw(HouseNew, &FHouse::RequestTokenComplete);
	//WebConnect->RequestToken(TEXT("Destiny"));
}

void UABGameInstance::CheckUObjectAlive()
{
	if (!WebConnectionNew)
	{
		AB_LOG(Warning, TEXT("언리얼오브젝트가 널입니다."));
		return;
	}

	if (!WebConnectionNew->IsValidLowLevel())
	{
		AB_LOG(Warning, TEXT("언리얼오브젝트가 유효하지 않습니다."));
		return;
	}

	AB_LOG(Warning, TEXT("언리얼오브젝트가 아직 살아있습니다. : %s"), *WebConnectionNew->Host); //신발에?
}

void UABGameInstance::RequestTokenComplete(const FString& Token)
{
	AB_LOG(Warning, TEXT("Token : %s"), *Token);
}
void UABGameInstance::RequestTokenComplete2(const FString& Token)
{
	AB_LOG(Warning, TEXT("Token2 : %s"), *Token);
}