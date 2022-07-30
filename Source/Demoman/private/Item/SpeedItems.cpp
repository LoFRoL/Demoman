// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/SpeedItems.h"

#include "ItemsFactory.h"
#include "UObject/ConstructorHelpers.h"
#include "Character/BaseCharacter.h"

ASpeedItems::ASpeedItems()
{
	ConstructorHelpers::FObjectFinder<UMaterialInterface> MeshAsset(TEXT("/Game/Material/Item/MI_BonusSpeed.MI_BonusSpeed"));
	if (MeshAsset.Succeeded())
	{
		ItemMesh->SetMaterial(0, MeshAsset.Object);
	}
	FItemsFactory::GetFactory()->RegisterNewItem(ASpeedItems::StaticClass());
}

void ASpeedItems::Consume(ABaseCharacter* InstigatorChar)
{
	InstigatorChar->AddMovementSpeed(100.f);
	Destroy();
}