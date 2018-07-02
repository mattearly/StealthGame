// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,
	Suspicious,
	Alerted
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPawnSensingComponent * PawnSensingComp;

	UFUNCTION()
		void OnPawnSeen(APawn *SeenPawn);


	UFUNCTION()
		void OnNoiseHeard(APawn* HeardPawn, const FVector& Location, float Volume);

	FRotator OriginalRotation;

	UFUNCTION()
		void ResetOrientation();

	FTimerHandle TimerHandle_ResetOrientation;

	EAIState GuardState;

	UFUNCTION()
		void SetGuardState(EAIState NewState);


	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
		void OnStateChanged(EAIState NewState);


	/* Patrolling Guards System */

	UPROPERTY(EditInstanceOnly, Category = "AI")
		bool bPatrol;

	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
		AActor *FirstPatrolPoint;	
	
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
		AActor *SecondPatrolPoint;

	AActor* CurrentPatrolPoint;

	void MoveToNextPatrolPoint();

	/* End Patrolling Guards System */


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
