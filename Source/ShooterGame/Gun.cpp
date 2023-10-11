// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h" 


// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	// Spawning particles when firing
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	// getting the position for the ray trace.
	APawn* owner = Cast<APawn>(GetOwner());
	FVector PlayerViewPointLoc;
	FRotator PlayerViewPointRot;
	if (owner == nullptr) return;
	AController* controller = owner->GetController();
	if (controller == nullptr) return;
	controller->GetPlayerViewPoint(PlayerViewPointLoc, PlayerViewPointRot);

	FVector End = PlayerViewPointLoc + PlayerViewPointRot.Vector() * MaxRange;
	FHitResult hitResult;
	bool succesfulHit = GetWorld()->LineTraceSingleByChannel(hitResult, PlayerViewPointLoc, End, ECollisionChannel::ECC_GameTraceChannel1);
	if (succesfulHit) 
	{
		FString nameOfHit = hitResult.GetActor()->GetName();
		UE_LOG(LogTemp, Log, TEXT("hit result: %s"), *nameOfHit);
	}

	//DrawDebugPoint(GetWorld(), PlayerViewPointLoc, 20, FColor::Red, true);
	//DrawDebugCamera(GetWorld(), PlayerViewPointLoc, PlayerViewPointRot, 90, 1, FColor::Red, true);
}

