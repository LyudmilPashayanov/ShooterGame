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
	UE_LOG(LogTemp, Log, TEXT("SPAWNEDE SPAWNEDE SPAWNEDESPAWNEDESPAWNEDESPAWNEDESPAWNEDESPAWNEDESPAWNEDESPAWNEDESPAWNEDE"));
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* owner = Cast<APawn>(GetOwner());
	FVector PlayerViewPointLoc;
	FRotator PlayerViewPointRot;
	if (owner != nullptr)
	{
		AController* controller = owner->GetController();
		if(controller!=nullptr)
		{

			controller->GetPlayerViewPoint(PlayerViewPointLoc, PlayerViewPointRot);
		}
	}

	DrawDebugCamera(GetWorld(), PlayerViewPointLoc, PlayerViewPointRot, 90, 1, FColor::Red, true);

}

