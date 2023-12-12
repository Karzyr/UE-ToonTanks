// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	TrailParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Component"));
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = 4000.f;
	ProjectileMovementComponent->MaxSpeed = 4000.f;
	
	RootComponent = ProjectileMesh;
	TrailParticleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	if (LaunchSound)
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("HitComponent: %s || OtherActor: %s || OtherComponent: %s"), *Hit.GetActor()->GetName(), *OtherActor->GetName(), *OtherComp->GetName());

	auto MyOwner = GetOwner();

	if (!MyOwner)
	{
		Destroy();
		return;
	}

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, UDamageType::StaticClass());

		if (HitParticles)
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, HitComp->GetComponentLocation());

		if (HitSound)
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, HitComp->GetComponentLocation());
	}
	
	if (HitCameraShakeClass)
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
	
	Destroy();
}

