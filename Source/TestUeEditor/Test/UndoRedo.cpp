#include "CQTest.h"
#include "TestUe/Test/MyObject.h"
#include "Misc/TransactionObjectEvent.h"

#define LOCTEXT_NAMESPACE "UndoRedo"

class FMyEditorUndoClient : public FEditorUndoClient
{
public:
    explicit FMyEditorUndoClient(UMyObject* InObject) : Object(InObject)
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

    virtual void PostRedo(bool bSuccess) override { RedoCount++; }
    virtual void PostUndo(bool bSuccess) override { UndoCount++; }

    UMyObject* Object;
    int32 RedoCount = 0;
    int32 UndoCount = 0;
};

TEST_CLASS(UndoRedo, "TestUe")
{
    TEST_METHOD(BaseTest)
    {
        UMyObject* MyObject = NewObject<UMyObject>();
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

        ASSERT_THAT(AreEqual(MyObject->PlayerHealth, 20));
        ASSERT_THAT(AreEqual(MyObject->SelfSerialNumber, 200));
        ASSERT_THAT(AreEqual(MyObject->NormalNumber, 200));
        ASSERT_THAT(AreEqual(MyObject->NumbersProperty.Num(), 2));
        ASSERT_THAT(AreEqual(MyObject->Numbers.Num(), 2));

        GEditor->UndoTransaction();

        ASSERT_THAT(AreEqual(MyObject->PlayerHealth, 10));
        ASSERT_THAT(AreEqual(MyObject->SelfSerialNumber, 100));
        
        // NormalNumber没有被序列化，所以撤销后值不变
        ASSERT_THAT(AreEqual(MyObject->NormalNumber, 200));
        
        ASSERT_THAT(AreEqual(MyObject->NumbersProperty.Num(), 1));
        ASSERT_THAT(AreEqual(MyObject->Numbers.Num(), 2));
    }

    TEST_METHOD(EditorUndoClientTest)
    {
        UMyObject* MyObject1 = NewObject<UMyObject>();
        UMyObject* MyObject2 = NewObject<UMyObject>();

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

        ASSERT_THAT(AreEqual(UndoClient1->UndoCount, 1));
        ASSERT_THAT(AreEqual(UndoClient1->RedoCount, 1));
    }
};

#undef LOCTEXT_NAMESPACE
