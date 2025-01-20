#include "MyTest.h"

#include "MyObject.h"

#include "UObject/Object.h"
#include "UObject/Package.h"

int32 UMyObject::FreeCount = 0;
int32 UMyObject::NewCount = 0;

UMyObject::UMyObject(): PlayerLocation(), PlayerHealth(0)
{
	NewCount++;
	SetFlags(RF_Transactional);
}

void UMyObject::Serialize(FArchive& Ar)
{
	UObject::Serialize(Ar);

	if (Ar.IsLoading() || Ar.IsSaving())
	{
		Ar << SelfSerialNumber;
	}
}

UOiObject1::UOiObject1(const FObjectInitializer& ObjectInitializer)
{
	check(ObjectInitializer.GetClass() == UOiObject1::StaticClass());

	if (const UObject* Archetype = ObjectInitializer.GetArchetype())
	{
		check(Archetype == UObject::StaticClass()->GetDefaultObject())
	}

	if (const UObject* Obj = ObjectInitializer.GetObj())
	{
		check(Obj == this);
	}

	if (const UClass* Class = ObjectInitializer.GetClass())
	{
		check(Class == UOiObject1::StaticClass());
	}

	const UObject* Outer = GetOuter();
	
	// 下面检查会失败，猜测是由于在构造函数中调用GetOuter()导致的
	// check(Outer->IsA(UOiObject2::StaticClass()))
	
	const UClass* OuterClass = Outer->GetClass();
	check(OuterClass != nullptr);	
}

UOiObject2::UOiObject2(const FObjectInitializer& ObjectInitializer)
{
	Object1 = ObjectInitializer.CreateDefaultSubobject<UOiObject1>(this, TEXT("Object1"));
	check(ObjectInitializer.GetClass() == UOiObject2::StaticClass());

	const UObject* Outer = GetOuter();
	check(Outer != nullptr);
	check(Outer->IsA(UPackage::StaticClass()));
}
