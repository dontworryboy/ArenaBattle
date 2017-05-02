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

	FString PackageName = TEXT("/Temp/SavedWebConnection");
	UPackage* NewPackage = CreatePackage(nullptr, *PackageName);
	WebConnectionNew = NewObject<UWebConnect>(NewPackage);
	FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());

	WebConnectionNew->Host = TEXT("127.0.0.7");
	WebConnectionNew->URI = TEXT("/");
	if (UPackage::SavePackage(NewPackage, WebConnectionNew, RF_Standalone, *PackageFileName))
	{
		UPackage* SavedPackage = ::LoadPackage(NULL, *PackageFileName, LOAD_None);
		TArray<UObject *> ObjectsInPackage;
		GetObjectsWithOuter(SavedPackage, ObjectsInPackage, false);
		for (const auto& EachObject : ObjectsInPackage)
		{
			UWebConnect* WebConnectionFromFile = Cast<UWebConnect>(EachObject);
			if (WebConnectionFromFile)
			{
				AB_LOG(Warning, TEXT("WebConnection From File : Host %s , URI %s"), *WebConnectionFromFile->Host, *WebConnectionFromFile->URI);
			}
		}
	}
	//WebConnectionNew = NewObject<UWebConnect>(this);
	//WebConnectionNew->Host = TEXT("127.0.0.7");
	//WebConnectionNew->URI = TEXT("/");

	//AB_LOG(Warning, TEXT("Outer Class Name : %s"), WebConnect->GetOuter()->GetClass()->GetName());

	//AB_LOG(Warning, TEXT("Outermost Class Name : %s"), WebConnect->GetOutermost()->GetClass()->GetName());

	//FString FullPath = FString::Printf(TEXT("%s%s"), *FPaths::GameSavedDir(), TEXT("WebConnection.txt"));
	//FArchive* ArWriter = IFileManager::Get().CreateFileWriter(*FullPath);
	//if (ArWriter)
	//{
	//	*ArWriter << *WebConnectionNew;
	//	ArWriter->Close();
	//	delete ArWriter;
	//	ArWriter = NULL;
	//}

	//TSharedPtr<FArchive> FileReader = MakeShareable(IFileManager::Get().CreateFileReader(*FullPath));
	//if (FileReader.IsValid())
	//{
	//	UWebConnect* WebConnectionFromFile = NewObject<UWebConnect>(this);
	//	*FileReader.Get() << *WebConnectionFromFile;
	//	FileReader->Close();
	//	AB_LOG(Warning, TEXT("WebConnection From File : Host %s , URI %s"), *WebConnectionFromFile->Host, *WebConnectionFromFile->URI);
	//}

	////WebConnect->TokenCompleteDelegate.AddUObject(this, &UABGameInstance::RequestTokenComplete);
	////WebConnect->TokenCompleteDelegate.AddUObject(this, &UABGameInstance::RequestTokenComplete2);
	//WebConnect->TokenCompleteDelegate.AddDynamic(this, &UABGameInstance::RequestTokenComplete);
	//WebConnect->TokenCompleteDelegate.AddDynamic(this, &UABGameInstance::RequestTokenComplete2);
	//WebConnect->RequestToken(TEXT("destiny"));
	//
	////FHouse* HouseNew = new FHouse();

	////WebConnect->TokenCompleteDelegate.AddUObject(this, &UABGameInstance::RequestTokenComplete);
	////WebConnect->TokenCompleteDelegate.AddUObject(this, &UABGameInstance::RequestTokenComplete2);
	////WebConnect->TokenCompleteDelegate.AddRaw(HouseNew, &FHouse::RequestTokenComplete);
	////WebConnect->RequestToken(TEXT("Destiny"));
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