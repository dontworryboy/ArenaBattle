// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ABWeapon.generated.h"

UCLASS()
class ARENABATTLE_API AABWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABWeapon();      

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	// ����
	//��ü Ÿ���� visible, ��� Ÿ���� edit
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "weapon")
	class USkeletalMeshComponent* weapon;

	UFUNCTION(BlueprintCallable, Category = "weapon|Stat")
	float getDamage(){ return BaseDamage; }

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	float BaseDamage;

};
