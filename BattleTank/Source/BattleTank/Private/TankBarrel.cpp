// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "BattleTank.h"

void UTankBarrel::Elevate(float degreesPerSecond)
{
	// move barrel the correct amount this frame given a max elevation speed and the frame time
	UE_LOG(LogTemp, Warning, TEXT("Barrel Elevate Called at Speed: %f"), degreesPerSecond);
}


