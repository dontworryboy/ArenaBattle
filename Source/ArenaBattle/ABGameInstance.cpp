// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "WebConnect.h"
#include "ABGameInstance.h"

UABGameInstance::UABGameInstance()
{
	AB_LOG(Warning, TEXT("ABGameInstance Constructor!"));

	WebConnect = CreateDefaultSubobject<UWebConnect>(TEXT("WebConnect"));
}

void UABGameInstance::Init() //���ø����̼�(��Ÿ��)���� ���� ���� ȣ��Ǵ� �Լ�
{
	AB_LOG_CALLONLY(Warning);
	Super::Init();
	//UE_LOG(LogClass, Warning, TEXT("GameInstance Init!"));
	WebConnect2 = NewObject<UWebConnect>(this);//GameInstance�� �ڽ����� ����
	
	UClass * ClassInfo1 = WebConnect->GetClass();
	UClass * ClassInfo2 = UWebConnect::StaticClass();
	if (ClassInfo1 == ClassInfo2)
	{
		AB_LOG(Warning, TEXT("ClassInfo1 is same with ClassInfo2"));
	}

	for (TFieldIterator<UProperty> It(ClassInfo1); It; ++It)
	{
		AB_LOG(Warning, TEXT("Field : %s, Type : %s"),
			*It->GetName(), *It->GetClass()->GetName());
		UStrProperty* StrProp = FindField<UStrProperty>(ClassInfo1, *It->GetName());
		if (StrProp)
		{
			AB_LOG(Warning, TEXT("Value = %s"), *StrProp->GetPropertyValue_InContainer(WebConnect));
		}
	}

	for (const auto& Entry : ClassInfo1->NativeFunctionLookupTable)
	{
		AB_LOG(Warning, TEXT("Function = %s"), *Entry.Name.ToString());
		UFunction* Func1 = ClassInfo1->FindFunctionByName(Entry.Name);
		if (Func1->ParmsSize == 0)
		{
			WebConnect->ProcessEvent(Func1, NULL);
		}
	}

	TArray<UObject*> DefaultSubobjects;
	GetDefaultSubobjects(DefaultSubobjects);
	for (const auto& Entry : DefaultSubobjects)
	{
		AB_LOG(Warning, TEXT("DefaultSubobject : %s"), *Entry->GetClass()->GetName());
		AB_LOG(Warning, TEXT("Outer of DefaultSubobject : %s"), *Entry->GetOuter()->GetClass()->GetName());
		AB_LOG(Warning, TEXT("DefaultSubobject : %s"), *Entry->GetClass()->GetFullName());
		AB_LOG(Warning, TEXT("Outer of DefaultSubobject : %s"), *Entry->GetOuter()->GetClass()->GetFullName());
	}
	//���� -> ������ 3���� ����(ȯ��)
	//���� -> ���忡 �����ϴ� ��ü���� ����(��ü�� ����Ʈ)

	WebConnectionNew = NewObject<UWebConnect>(this);
	AB_LOG(Warning, TEXT("Outer of NewObject : %s"), *WebConnectionNew->GetOuter()->GetClass()->GetName());
	AB_LOG(Warning, TEXT("Outer of NewObject : %s"), *WebConnectionNew->GetOuter()->GetClass()->GetFullName());

	UWorld* CurrentWorld = GetWorld();
	for (const auto& Entry : FActorRange(CurrentWorld))
	{
		AB_LOG(Warning, TEXT("Actor : %s"), *Entry->GetName());
		TArray<UObject*> Components;
		Entry->GetDefaultSubobjects(Components);
		for (const auto& CEntry : Components)
		{
			AB_LOG(Warning, TEXT(" -- Component : %s"), *CEntry->GetName());
		}
	}
}