// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS(Blueprintable)
class NEONEKON_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	float speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	int durationBeats;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	bool friendly;

	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
