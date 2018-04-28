// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (PlayerTank) {
		MoveToActor(PlayerTank, AcceptanceRadius);
		
		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		if (!AimingComponent) { return; }
		// Aim towards the player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		AimingComponent->Fire();
	}
}
