#include "MyTest.h"

#include "Serialization/MemoryReader.h"
#include "Serialization/MemoryWriter.h"
#include "Misc/AutomationTest.h"

#include "MyObject.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(Serializer_Base, "MyTest.Serializer.Base", TEST_FILTER)

bool Serializer_Base::RunTest(const FString& Parameters)
{
	// 保存 & 加载
	{
		// 序列化到内存
		TArray<uint8> BinaryData;
		{
			FMemoryWriter MemoryWriter(BinaryData, true);
			UMyObject* MyObject = NewObject<UMyObject>();
			MyObject->PlayerLocation = FVector3f(1.0f, 2.0f, 3.0f);
			MyObject->PlayerHealth = 100;
			MyObject->Serialize(MemoryWriter);
			MemoryWriter.Close();
		}

		// 反序列化从内存
		{
			FMemoryReader MemoryReader(BinaryData, true);
			UMyObject* MyObject = NewObject<UMyObject>();
			MyObject->Serialize(MemoryReader);
			MemoryReader.Close();

			TestNearlyEqual(TEXT("MyObject.PlayerLocation.X should be 1.0f"), MyObject->PlayerLocation.X, 1.0f);
			TestEqual(TEXT("MyObject.PlayerHealth should be 100"), MyObject->PlayerHealth, 100);
		}		
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(Serializer_Custom, "MyTest.Serializer.Custom", TEST_FILTER)

bool Serializer_Custom::RunTest(const FString& Parameters)
{		
	TArray<uint8> BinaryData;	
	FMemoryWriter MemoryWriter(BinaryData, true);
	UMyObject* MyObjectForWrite = NewObject<UMyObject>();
	MyObjectForWrite->SelfSerialNumber = 123;
	MyObjectForWrite->Serialize(MemoryWriter);
	MemoryWriter.Close();
	
	FMemoryReader MemoryReader(BinaryData, true);
	UMyObject* MyObjectForRead = NewObject<UMyObject>();
	MyObjectForRead->Serialize(MemoryReader);
	MemoryReader.Close();

	TestEqual(TEXT("MyObject.SelfSerialNumber should be 123"), MyObjectForRead->SelfSerialNumber, 123);
	
	return true;
}
