// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyActor.h"

AKeyActor::AKeyActor()
{
	ItemNum = 1;
	IsInteract = false;
}


void AKeyActor::Interact()
{
	// IsInteract에서 True가 되면 바로 Door에서 Key를 삭제하고 문을 여는 코드를 실행 하므로 False로 변경하지 않음.
	IsInteract = true;
}

void AKeyActor::DestroyKey()
{
	PlayerDoll->HasKey = false;
	PlayerDollController->PlayerInventory->RemoveItem(this);
	this->Destroy();
}


void AKeyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Key 획득 시 HasKey 변수를 True로 변경
	if(!PlayerDoll->HasKey && this->IsPlayerOwned)
	{
		PlayerDoll->HasKey = true;
	}
	
}



