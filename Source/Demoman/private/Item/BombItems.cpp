// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/BombItems.h"

#include "ItemsFactory.h"
#include "UObject/ConstructorHelpers.h"
#include "Character/BaseCharacter.h"

ABombItems::ABombItems()
{
	ConstructorHelpers::FObjectFinder<UMaterialInterface> MeshAsset(TEXT("/Game/Material/Item/MI_BonusBomb.MI_BonusBomb"));
	if (MeshAsset.Succeeded())
	{
		ItemMesh->SetMaterial(0, MeshAsset.Object);
	}
	FItemsFactory::GetFactory()->RegisterNewItem(ABombItems::StaticClass());
}

void ABombItems::Consume(ABaseCharacter* InstigatorChar)
{
	InstigatorChar->AddBombsCount(1);
	Destroy();
}
