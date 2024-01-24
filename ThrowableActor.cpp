// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowableActor.h"

AThrowableActor::AThrowableActor() : AInteractableActor()
{
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->InitialSpeed = 0.0f; // Set an initial speed
	ProjectileMovement->MaxSpeed = 4000.0f; // Set max speed
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 1.0f;
	
}

// Interact
void AThrowableActor::Interact()
{
	this->IsPlayerOwned = false;
	this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	//CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//CapsuleComponent->SetSimulatePhysics(true);
	//CapsuleComponent->AddImpulse(FVector::ForwardVector *  1000.0f);
	
	
	ProjectileMovement->Velocity = PlayerDoll->GetActorRotation().Vector();
	
	
}

// 매 Tick마다 Interact를 실시
void AThrowableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

