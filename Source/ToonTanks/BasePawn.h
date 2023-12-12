// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	void Fire();
	void RotateTurret(FVector LookAtTarget);

	void HandleDestruction();

private:
	UPROPERTY(VisibleAnywhere, Category = "Pawn Components", BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;
	
	UPROPERTY(VisibleAnywhere, Category = "Pawn Components", BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleAnywhere, Category = "Pawn Components", BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, Category = "Pawn Components", BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category="Combat")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category="Combat")
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

};
