// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("No tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Tank being controlled: %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // OUT Parameter
	if (GetSightRayHitLocation(HitLocation)) {
		// UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
	
	// find crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(CrossHairXLocation * ViewportSizeX, CrossHairYLocation * ViewportSizeY);

	// de-project the screen position of the crosshair to a world direction
	FVector CameraWorldLocation;
	FVector WorldDirection;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, WorldDirection)) {
		UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *WorldDirection.ToString());
		return true;
	}

	// line-trace along that direction, and see what we hit
	return false;
}


