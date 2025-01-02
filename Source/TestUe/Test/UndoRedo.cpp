#include "MyObject.h"
#include "Misc/AutomationTest.h"
#include "Misc/TransactionObjectEvent.h"

#define LOCTEXT_NAMESPACE "UndoRedo"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UndoRedo_Base, "TestUe.UndoRedo.Base", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool UndoRedo_Base::RunTest(const FString& Parameters)
{
	UMyObject *MyObject = NewObject<UMyObject>();
	MyObject->PlayerHealth = 10;
	MyObject->SelfSerialNumber = 100;
	MyObject->NormalNumber = 100;
	MyObject->NumbersProperty.Add(1);
	MyObject->Numbers.Add(1);

	{
		FScopedTransaction Transaction(LOCTEXT("ChangePlayerHealth", "Change Player Health"));

		// 注意： UMyObject中必须设定RF_Transactional标志，参考其构造函数
		MyObject->Modify();
		MyObject->PlayerHealth = 20;

		// SelfSerialNumber没有添加UPROPERTY标签，但是序列化函数中有处理
		MyObject->SelfSerialNumber = 200;

		MyObject->NormalNumber = 200;

		MyObject->NumbersProperty.Add(2);
		MyObject->Numbers.Add(2);
	}

	TestEqual("PlayerHealth must be 20", MyObject->PlayerHealth, 20);
	TestEqual("SelfSerialNumber must be 200", MyObject->SelfSerialNumber, 200);
	TestEqual("NormalNumber must be 200", MyObject->NormalNumber, 200);
	TestEqual("NumbersProperty.Num() must be 2", MyObject->NumbersProperty.Num(), 2);
	TestEqual("Numbers.Num() must be 2", MyObject->Numbers.Num(), 2);
		
	GEditor->UndoTransaction();	

	TestEqual("PlayerHealth must be 10", MyObject->PlayerHealth, 10);
	TestEqual("SelfSerialNumber must be 100", MyObject->SelfSerialNumber, 100);

	// NormalNumber没有被序列化，所以撤销后值不变
	TestEqual("NormalNumber must be 100", MyObject->NormalNumber, 200);

	TestEqual("NumbersProperty.Num() must be 1", MyObject->NumbersProperty.Num(), 1);
	TestEqual("Numbers.Num() must be 1", MyObject->Numbers.Num(), 2);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UndoRedo_EditorUndoClient, "TestUe.UndoRedo.EditorUndoClient", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

class FMyEditorUndoClient : public FEditorUndoClient
{
public:
	explicit FMyEditorUndoClient(UMyObject* InObject)
		: Object(InObject)
	{
		GEditor->RegisterForUndo(this);
	}

	virtual ~FMyEditorUndoClient() override
	{
		GEditor->UnregisterForUndo(this);
	}
	
	virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts) const override
	{
		for (const TPair<UObject*, FTransactionObjectEvent>& TransactionObjectContext : TransactionObjectContexts)
		{
			if (TransactionObjectContext.Key == Object)
			{
				return true;
			}
		}

		return false;		
	}
	
	virtual void PostRedo(bool bSuccess) override
	{
		RedoCount++;
	}
	
	virtual void PostUndo(bool bSuccess) override
	{
		UndoCount++;
	}

	UMyObject* Object;
	int32 RedoCount = 0;
	int32 UndoCount = 0;
};

bool UndoRedo_EditorUndoClient::RunTest(const FString& Parameters)
{
	UMyObject *MyObject1 = NewObject<UMyObject>();
	UMyObject *MyObject2 = NewObject<UMyObject>();

	auto ModifyObject = [](UMyObject* Object, const int32 Health)
	{
		FScopedTransaction Transaction(LOCTEXT("ChangePlayerHealth", "Change Player Health"));

		Object->Modify();
		Object->PlayerHealth = Health;
	};

	const TSharedPtr<FMyEditorUndoClient> UndoClient1 = MakeShared<FMyEditorUndoClient>(MyObject1);

	ModifyObject(MyObject1, 10);
	ModifyObject(MyObject2, 20);

	GEditor->UndoTransaction();
	GEditor->UndoTransaction();
	GEditor->RedoTransaction();
	GEditor->RedoTransaction();

	TestEqual("Undo count must be 1", UndoClient1->UndoCount, 1);
	TestEqual("Redo count must be 1", UndoClient1->RedoCount, 1);
	
	return true;
}

#undef LOCTEXT_NAMESPACE