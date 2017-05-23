// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABAnimInstance.h"

UABAnimInstance::UABAnimInstance()
{
	VelocityAnim = 0.0f;
	CurrentStateAnim = EPlayerState::PEACE;
}

void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	APawn* OwnerPawn = TryGetPawnOwner();

	if (OwnerPawn != nullptr)
	{
		if (OwnerPawn->IsValidLowLevel())
		{
			VelocityAnim = OwnerPawn->GetVelocity().Size();
			AABPawn* ABPawn = Cast<AABPawn>(OwnerPawn);
			if (ABPawn)
			{
				CurrentStateAnim = ABPawn->CurrentState;
			}
		}
	}
}

void UABAnimInstance::AnimNotify_AttackEnd(UAnimNotify* Notify)
{
	AB_LOG_CALLONLY(Warning);

	APawn* OwnerPawn = TryGetPawnOwner();

	AABPawn* ABPawn = Cast<AABPawn>(OwnerPawn);

	ABPawn->CurrentState = EPlayerState::PEACE;
}